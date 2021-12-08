#include <Arduino.h>
#include <avr/pgmspace.h>
#include "lcd1202.h"
#include "font.h"


#define LCD_X        96
#define LCD_Y        68
#define LCD_String    9

#define W   94
#define H   66

#define SetYAddr   0xB0
#define SetXAddr4  0x00
#define SetXAddr3  0x10

#define pgm     pgm_read_byte
#define swap(a, b) { int t = a; a = b; b = t; }

#define LCD_D         1
#define LCD_C         0

byte LCD_RAM[LCD_X*LCD_String];

volatile uint8_t RES, CS, Data, Clock;

//======================================================Определение пинов подключения дисплея
  LCD1202::LCD1202(uint8_t _RES, uint8_t _CS, uint8_t _Data, uint8_t _Clock)

{
RES = _RES;
CS = _CS;
Data = _Data;
Clock = _Clock;
}
 
//======================================================Очистка дисплея
void LCD1202::Clear_LCD() {
  for (int index = 0; index < 864 ; index++){
     LCD_RAM[index] = (0x00);
  }
}
//=======================================================Управление пинами  
void LCD1202::dWrite(byte pin, byte val){
  byte bit = digitalPinToBitMask(pin);
  volatile byte *out;
  out = portOutputRegister(digitalPinToPort(pin));
  (val)? *out |= bit : *out &=~bit;
}

//=========================================================Отправка 9 байт    
void LCD1202::SendByte(byte mode, byte c){
  dWrite(CS, 0);
  (mode)? dWrite(Data,1) : dWrite(Data,0);
  dWrite(Clock, 1);
  
  for(byte i=0;i<8;i++){
    dWrite(Clock,0);
    (c & 0x80)? dWrite(Data,1) : dWrite(Data,0);
    dWrite(Clock,1);
    c <<= 1;
  }

  dWrite(Clock, 0);
}
//=====================================================Обновить дисплей
void LCD1202::Update(){
  for(byte p = 0; p < 9; p++){
    SendByte(LCD_C, SetYAddr| p); 
    SendByte(LCD_C, SetXAddr4);
    SendByte(LCD_C, SetXAddr3);

    for(byte col=0; col < LCD_X; col++){
      SendByte(LCD_D, LCD_RAM[(LCD_X * p) + col]);
    }
  }
}

//===================================================Инициализация дисплея
void LCD1202::Inicialize(){
  pinMode(RES,   OUTPUT);
  pinMode(CS,    OUTPUT);
  pinMode(Data,  OUTPUT);
  pinMode(Clock, OUTPUT);

  // Инициализация дисплея
  dWrite(RES, 1);
  dWrite(Clock, 0);
  dWrite(Data, 0);
  dWrite(CS, 0);
  delay(20);
  dWrite(CS, 1);

  SendByte(LCD_C,0x2F);            // Power control set(charge pump on/off)
  SendByte(LCD_C,0xA4);   
  SendByte(LCD_C,0xAF);            // экран вкл/выкл
  Clear_LCD();
  Update();
}

//===================================================Нарисовать пиксель
void LCD1202::drawPixel (byte x, byte y, boolean color) {
  if ((x < 0) || (x >= LCD_X) || (y < 0) || (y >= LCD_Y)) return;

  if (color) LCD_RAM[x+ (y/8)*LCD_X] |= _BV(y%8);
  else       LCD_RAM[x+ (y/8)*LCD_X] &= ~_BV(y%8); 
}

//**********************************************************************************************************//
//======================================================Заливка экрана
void LCD1202::fillScreen(boolean color) {
  fillRect(0, 0, LCD_X, LCD_Y, color);
}
//=====================================================Нарисовать букву
void LCD1202::drawChar(byte x, byte y, boolean color, unsigned char c) {

  if((x >= LCD_X) ||(y >= LCD_Y) || ((x + 4) < 0) || ((y + 7) < 0))
    return;

  if(c<128)            c = c-32;
  if(c>=144 && c<=175) c = c-48;
  if(c>=128 && c<=143) c = c+16;
  if(c>=176 && c<=191) c = c-48;
  if(c>191)  return;

  for (byte i=0; i<6; i++ ) {
    byte line;
    (i == 5)? line = 0x0 : line = pgm(font+(c*5)+i);
    for (byte j = 0; j<8; j++) {
      (line & 0x1)? drawPixel(x+i, y+j, color) : drawPixel(x+i, y+j, !color);
      line >>= 1;
    }
  }
}

//========================================================Вывод строки
void LCD1202::print(byte x, byte y, boolean color, const char *str){
  unsigned char type = *str;
  if(type>=128) x=x-3;
  while(*str){ 
    drawChar(x, y, color, *str++);
    unsigned char type = *str;
    (type>=128)? x=x+3 : x=x+6;
  }
}
//========================================================Вывод числовых значений
void LCD1202::print(byte x, byte y, boolean color, long num){
  char c[20];
  print(x, y, color, ltoa(num,c,10));
}
//========================================================Вывод строки в заданное знакоместо и строку
void LCD1202::print_1607(byte x, byte y, boolean color, char *str)
{
byte nPos[16]={0,6,12,18,24,30,36,42,48,54,60,66,72,78,84,90};
byte nStr[7]={1,10,20,30,40,50,60};
print(nPos[x], nStr[y], color, str);
}

//====================================================Рисование линии
void LCD1202::drawLine(byte x0, byte y0, byte x1, byte y1, boolean color) {
  int steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }
  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }
  int dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int err = dx / 2;
  int ystep;

  (y0 < y1)?  ystep = 1 : ystep = -1;

  for (; x0<=x1; x0++) {
    (steep)? drawPixel(y0, x0, color) : drawPixel(x0, y0, color);
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

//========================================Рисование вертикальной линии
void LCD1202::drawFastVLine(byte x, byte y, byte h, boolean color) {
  drawLine(x, y, x, y+h-1, color);
}

//======================================Рисование горизонтальной линии
void LCD1202::drawFastHLine(byte x, byte y, byte w, boolean color) {
  drawLine(x, y, x+w-1, y, color);
}

//============================================Рисование прямоугольника
void LCD1202::drawRect(byte x, byte y, byte w, byte h, boolean color) {
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}

//============================================Рисование окружности
void LCD1202::drawCircle(byte x0, byte y0, int16_t r, boolean color) {
  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

  drawPixel(x0, y0+r, color);
  drawPixel(x0, y0-r, color);
  drawPixel(x0+r, y0, color);
  drawPixel(x0-r, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

//===============================Рисование скругленного прямоугольника
void LCD1202::drawRoundRect(byte x, byte y, byte w, byte h, byte r, boolean color) {
  // smarter version
  drawFastHLine(x+r , y , w-2*r, color); // Top
  drawFastHLine(x+r , y+h-1, w-2*r, color); // Bottom
  drawFastVLine( x , y+r , h-2*r, color); // Left
  drawFastVLine( x+w-1, y+r , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r , y+r , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r , y+h-r-1, r, 8, color);
}

//==============================================Рисование треугольника
void LCD1202::drawTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, boolean color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

//======================================================Рисование дуги
void LCD1202::drawCircleHelper(byte x0, byte y0, byte r, byte cornername, boolean color) {
  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

//========================================Рисование залитой окружности
void LCD1202::fillCircle(byte x0, byte y0, byte r, boolean color) {
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

//======================================================Рисование дуги
void LCD1202::fillCircleHelper(byte x0, byte y0, byte r, byte cornername, byte delta, boolean color) {

  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

//=====================================Рисование залитый прямоугольник
void LCD1202::fillRect(byte x, byte y, byte w, byte h, boolean color) {
  for (int16_t i=x; i<x+w; i++) {
    drawFastVLine(i, y, h, color);
  }
}

//======================Рисование залитого скругленного прямоугольника
void LCD1202::fillRoundRect(byte x, byte y, byte w, byte h, byte r, boolean color) {
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r , y+r, r, 2, h-2*r-1, color);
}

//=====================================Рисование залитого треугольника
void LCD1202::fillTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, boolean color) {

  int a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a) a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a) a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa = 0,
    sb = 0;

  if(y1 == y2) last = y1; // Include y1 scanline
  else last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a = x0 + sa / dy01;
    b = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
*/
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }

  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a = x1 + sa / dy12;
    b = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
*/
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}

//======================================================Вывод картинки
void LCD1202::drawBitmap(byte x, byte y, const unsigned char *bitmap, byte w, byte h, boolean color) {
  for (int16_t j=0; j<h; j++) {
    for (int16_t i=0; i<w; i++ ) {
      if (pgm(bitmap + i + (j/8)*w) & _BV(j%8)) {
        drawPixel(x+i, y+j, color);
      }
    }
  }
}

//=========================Вывод символа 16х32 пикселя в координаты XY
void LCD1202::simb16x32(byte x, byte y, boolean color, byte c){
  for (byte k=0;k<4;k++){
    for (byte i=0;i<16;i++){
      byte line = pgm(&(mass16x32[c][i+k*16]));
      for (byte j = 0; j<8; j++) {
        (line & 0x01)? drawPixel(x+i, y+j+k*8, color) : drawPixel(x+i, y+j+k*8, !color);
        line >>= 1;
      }
    }
  }
}
//=========================Вывод символа 10х16 пикселя в координаты XY
void LCD1202::simb10x16(byte x, byte y, boolean color, byte c){
  for (byte k=0;k<2;k++){
    for (byte i=0;i<10;i++){
      byte line = pgm(&(mass10x16[c][i+k*10]));
      for (byte j = 0; j<8; j++) {
        (line & 0x01)? drawPixel(x+i, y+j+k*8, color) : drawPixel(x+i, y+j+k*8, !color);
        line >>= 1;
      }
    }
  }
}
//**********************************************************************************************************//
