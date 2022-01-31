  /*Global functions related to display. 
   * Init, draw primitives, draw text...
   * Every call to display has to be done by some call from this file.
   * It needed to make migration to other display easier.
  */

#ifndef DISPLAYCPP
#define DISPLAYCPP

#include "lcd1202.h"
#include "Generic.cpp"
#include "Buttons.cpp"
#include "Battery.cpp"

const int32_t  PROGMEM watchFaceFont [] { 
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111001100110011111, //0
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011100100010001000110, //1
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011110001111110001111, //2
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111000111110001111, //3
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000010001000111110011001, //4
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111000111100011111, //5
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111001111100011111, //6
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000001000100010010001111, //7
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111001111110011111, //8
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111000111110011111, //9
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000000000001000000010000 // [10] = :
};
const PROGMEM byte pathDrmWatch[] = { 57,
   0,  0,     7,  0,    10,  3,    10, 13,     7, 16,  //D
   0, 16,     0,  0,   255,255,    13, 16,    13,  0,  //R
  20,  0,    22,  2,    22,  6,    20,  8,    14,  8,
  22, 16,   255,255,    25, 16,    25,  0,    33,  8,  //M
  41,  0,    41, 16,   255,255,     1, 23,     4, 34,  //W
   6, 28,     8, 34,    11, 22,   255,255,    11, 34,  //A
  15, 22,    17, 29,    14, 29,    17, 29,    19, 34,
 255,255,    20, 22,    26, 22,    23, 22,    23, 34,  //T
 255,255,    36, 24,    34, 22,    31, 22,    29, 24,  //C
  29, 32,    31, 34,    34, 34,    36, 32,   255,255,
  39, 22,    39, 34,    39, 30,    41, 28,    43, 28,  //H
  45, 30,    45, 34
}; 

const PROGMEM byte pathBubble[] = { 12,
  39, 28,    53, 18,    89, 18,    95, 15,    95,  3,  
  89,  0,    5,   0,     0,  3,     0, 15,     5, 18,
  40, 18,   37,  29
}; 

const PROGMEM byte pathZubat[] = { 42,
   0, 36,     4, 35,    20,  3,    23,  0,    36,  0, //контур
  34,  3,    34,  8,    23,  8,    16, 24,    35, 24,
  35, 35,    33, 37,     0, 37,   255,255,    16, 43,//лапы
  18, 41,    20, 43,    18, 41,    18, 37,    26, 37,
  26, 41,    24, 43,    26, 41,    28, 43,   255,255,
  33,  9,    29, 17,    28,  9,    23, 17,    23,  8, //зубы
  20, 16,    23, 23,    27, 15,    29, 23,    33, 15,
  34, 23,   255,255,    31,  2,    31,  4,    31,  3, //глаз
  32,  3,    30,  3
};

class Display_{
  private:
  static LCD1202 lcd;
  /*
   * Display workflow:
   * 
   * > displayInit();
   *       V
   * > displayClear();
   *       V
   * > displayDrawLine(...)
   * > displayFillRect(...)
   * > displayDrawText(...)
   *   ...
   *       V
   * > displayUpdate() 
   *       V
   * > displayClear();
   *   ...
   *
  */
  
  public:
  

  static const byte* const getPathZubat(){
    return pathZubat;
  }

   
  static const byte* const getPathDrmWatch(){ 
    return pathDrmWatch;
  }

  static const byte* const getPathBubble(){
    return pathBubble;
  } 
  
  
  //Инициализация дисплея. Подаём питание, ждём немного и инициализируем программно
  static void displayInit(){
    #ifdef LOG
      Serial.print(F("LCD Init..."));
    #endif
    //lcd = LCD1202(0,0,0,0);  // RST, CS, MOSI, SCK
    lcd = LCD1202(pinLcdRst, pinLcdCs, pinLcdMosi, pinLcdSck);  // RST, CS, MOSI, SCK
    pinMode(pinLcdPower, OUTPUT);
    digitalWrite(pinLcdPower, HIGH);
    delay(100);
    lcd.Inicialize();  //Инициализация дисплея
    delay(10);
    #ifdef LOG
      Serial.println("OK");
    #endif
  }
  
  //Врубаем подсветку
  static void displayBacklightOn(){
    pinMode(pinLcdBacklight, OUTPUT);
    digitalWrite(pinLcdBacklight, HIGH);
  }
  
  //Отсоединяем пин подсветки полностью
  static void displayBacklightOff(){
    pinMode(pinLcdBacklight, INPUT);
  }
  
  //Отсоединяем все пины дисплея от ардуины, в том числе и питание
  static void displayPowerOff(){
  #ifdef LOG
    Serial.println(F("LCD POWER OFF"));
  #endif
    pinMode(pinLcdBacklight, INPUT);
    digitalWrite(pinLcdBacklight, LOW);
    
    pinMode(pinLcdRst, INPUT);
    pinMode(pinLcdCs, INPUT);
    pinMode(pinLcdMosi, INPUT);
    pinMode(pinLcdSck, INPUT);
    pinMode(pinLcdPower, INPUT);
    
    delay(50);
  }
  
  //Функция очистки дисплея. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayClear(){
    lcd.Clear_LCD();
  }
  
  //Функция оновления дисплея из буфера. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayUpdate(){
    lcd.Update();
  }
  
  //Функция рисования линии. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayDrawLine(byte x0, byte y0, byte x1, byte y1, boolean color){
    lcd.drawLine(/*X1*/x0, /*Y1*/y0, /*X2*/x1, /*Y2*/y1, /*C*/color);
  }
  
  //Функция рисования периметра прямоугольника. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayDrawRect(byte x, byte y, byte w, byte h, boolean color){
    lcd.drawRect(/*x*/x, /*y*/y, /*w*/w, /*h*/h, /*c*/color);
  }
  
  //Функция рисования залитого прямоугольника. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayFillRect(byte x, byte y, byte w, byte h, boolean color){
    lcd.fillRect(/*x*/x, /*y*/y, /*w*/w, /*h*/h, /*c*/color);
  }
  
  //Функция рисования текста. Эта конкретная функция рисует из оперативки, т.е. из буфера. 
  //Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  //Для рисования PROGMEM строк или строк с макросом F() есть другие функции пониже.
  static void displayDrawText(int X, int Y, int color, const char* text){
    //1 is black, 0 is white
    lcd.print(X, Y, color, text);
  }
  
  //Рисование одного символа из оперативки. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayDrawText(int X, int Y, int color, char c){
    //1 is black, 0 is white
    lcd.drawChar(X, Y, color, c);
  }
  
  //Рисование растровой картинки. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayDrawBitmap(byte x, byte y, const unsigned char *img, byte w, byte h, byte color){
    lcd.drawBitmap(x, y, img, w, h, color);
  }
  
  //-------- Display independent functions
  
  //Реконструкция изначального растра из тестовой программы. Эта функция нигде не вызывается, поэтому памяти не занимает. Пусть валяется.
  static void displayDrawVectorLogo(){
    displayDrawVector(/*path*/getPathZubat(), /*x*/0, /*y*/20, /*animate*/false, /*color*/1);
    displayDrawVector(/*path*/getPathBubble(), /*x*/0, /*y*/0, /*animate*/false, /*color*/1);
    displayDrawVector(/*path*/getPathDrmWatch(), /*x*/48, /*y*/25, /*animate*/true, /*color*/1);
  }
  
  //Рисование векторной картинки. Формат вектора описан в комментарии ниже.
  //max number of points for one path is 255.
  //Array type: const PROGMEM byte path[] = {...);
  //Array format: {numberOfPoints, x0, y0, x1, y1, x2, y2, ...}
  //255,255 coordinates is skipped, so it can be used for separate paths
  //animate: 0-noAnimation, 1...-speed,low is slow.
  static void displayDrawVector(const byte* data_array, byte X, byte Y, byte animate, bool color){
    byte numberOfPoints = pgm_read_byte(&data_array[0]);
    byte lx = pgm_read_byte(&data_array[1]);
    byte ly = pgm_read_byte(&data_array[2]);
    int currentIndex = 3;
    for(byte i=1; i < numberOfPoints; i++){
      byte x = pgm_read_byte(&data_array[currentIndex]);
      byte y = pgm_read_byte(&data_array[currentIndex + 1]);
      if(x != 255 && y != 255 && lx != 255 && ly != 255)
        displayDrawLine(/*X1*/lx + X, /*Y1*/ly + Y, /*X2*/x + X, /*Y2*/y + Y, /*C*/color);
      if(animate!=0 && i%animate==0){
        displayUpdate();
        if (ButtonUp.isButtonPressed()) 
          animate = false;
      }
      currentIndex += 2;
      lx = x;
      ly = y;
    }
  }
  
  //Рисование на экране текста из макроса F().
  static void displayDrawText(int X, int Y, int color, const __FlashStringHelper* str){
    strcpy_P(Generic.buffer, (PGM_P)str);
    byte pos = 0;
    for(int i=0; i<BUFFER_SIZE; i++){
      if(Generic.buffer[i] == '\0') 
        break;
      if((byte)Generic.buffer[i] != 208 && (byte)Generic.buffer[i] != 209){
        displayDrawText(X + pos*6, Y, color, Generic.buffer[i]);
        pos++;
      }
    }
  }
  
  //Отображение красивого уведомления с Зубатом и анимацией.
  //Анимацию можно перемотать кнопкой вверх
  static void displayMessage(const __FlashStringHelper* str){
    displayClear();
    displayDrawVector(/*path*/getPathZubat(), /*x*/0, /*y*/20, /*animate*/false, /*color*/1);
    displayDrawVector(/*path*/getPathBubble(), /*x*/0, /*y*/0, /*animate*/false, /*color*/1);
    strcpy_P(Generic.buffer, (PGM_P)str);
    byte pos = 0;
    bool animate = true;
    for(byte i=0; i<BUFFER_SIZE; i++){
      if(Generic.buffer[i] == '\0') 
        break;
      if((byte)Generic.buffer[i] != 208 && (byte)Generic.buffer[i] != 209){
        displayDrawText(10 + pos*6, 6, 1, Generic.buffer[i]);
        pos ++;
        if(animate){
          displayUpdate();
          delay(6);
        }
      }
      if (ButtonUp.isButtonPressed()) 
        animate = false;
    }
    displayUpdate();
    if(animate)
      delay(500);
    else
      delay(200);
  }
  
  //Вывод простого сообщения из оперативки.
  static void displaySimpleMessage(const char* text){
    displayClear();
    displayDrawText(10, 30, 1, text);
    displayUpdate();
  }
  
  //Рисование галочки. Используется по всей программе, в частности в менюшках.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawCheck(byte x, byte y, bool color){
    static const char img[6] PROGMEM = { 
        0b00011000,
        0b01110000,
        0b01110000,
        0b00111000,
        0b00001110,
        0b00000011,
      };
    displayDrawBitmap(x, y, img, 6, 8, color);
  }
  
  //Рисование иконки сброса. Используется в секундомере
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawResetIcon(byte x, byte y, bool color){
    static const char img[6] PROGMEM = { 
        0b01001111,
        0b10000011,
        0b10000101,
        0b01001001,
        0b00110000,
        0b00000000,
      };
    displayDrawBitmap(x, y, img, 6, 8, color);
  }
  
  //Рисование иконки стрелки вниз. Используется менющках.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawArrowDown(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b00000001,
        0b00000111,
        0b00011110,
        0b01111000,
        0b00011110,
        0b00000111,
        0b00000001,
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование иконки стрелки вправо. Используется на экране установки времени и будильника.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawArrowRight(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b01100011,
        0b00110110,
        0b00110110,
        0b00011100,
        0b00011100,
        0b00001000,
        0b00001000
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование иконки плэй. 7х7. Используется на экране секундомера.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawPlaySign(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b01111111,
        0b00111110,
        0b00111110,
        0b00011100,
        0b00011100,
        0b00001000,
        0b00001000
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование иконки паузы. 7х7. Используется на экране секундомера.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawPauseSign(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b01111111,
        0b01111111,
        0b00000000,
        0b00000000,
        0b00000000,
        0b01111111,
        0b01111111
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование иконки стоп. 7х7. Используется на экране воспроизведения музыки.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawStopSign(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b01111111,
        0b01111111,
        0b01111111,
        0b01111111,
        0b01111111,
        0b01111111,
        0b01111111
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование иконки будильника. Используется на циферблатах.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawAlertSign(byte x, byte y, bool color){
    static const char img[9] PROGMEM = { 
        0b00000010,
        0b00011101,
        0b00100010,
        0b01000001,
        0b01001101,
        0b01001001,
        0b00100010,
        0b00011101,
        0b00000010
      };
    displayDrawBitmap(x, y, img, 9, 8, color);
  }

  
  //Рисование иконки беззвучного режима. Используется на циферблатах.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawSilentModeIcon(byte x, byte y, bool color){
        static const char img[8] PROGMEM = { 
        0b00100000,
        0b01011110,
        0b00100001,
        0b01010001,
        0b01101001,
        0b00100101,
        0b00111010,
        0b00100001
      };
      displayDrawBitmap(x, y, img, 8, 8, color);
  }

  //Рисование иконки приложений. Используется в главном меню.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawAppsIcon(byte x, byte y, bool color){
        static const char img[7] PROGMEM = { 
        0b01110111,
        0b01110111,
        0b01110111,
        0b00000000,
        0b01110111,
        0b01110111,
        0b01110111
      };
      displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование иконки стрелки влево. Используется на многи экранах как кнопка НАЗАД.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawArrowLeft(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b00001000,
        0b00001000,
        0b00011100,
        0b00011100,
        0b00110110,
        0b00110110,
        0b01100011
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование иконки настроек. Используется в главном меню
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconSettings(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b00001100,
        0b00011000,
        0b00011001,
        0b00011111,
        0b00111110,
        0b01110000,
        0b01100000
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  
  //Рисование иконки инфор о программе. Используется в главном меню
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconAbout(byte x, byte y, bool color){
    static const char img[7] PROGMEM = { 
        0b00111110,
        0b01111111,
        0b01111111,
        0b01000101,
        0b01111111,
        0b01111111,
        0b00111110
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  //Рисование прямоугольника с цифрами. Используется на экранах настройки будильника и времени
  static void displayDraw2DigitNumberWithFrame(byte x, byte y, byte number, bool selected){
    sprintf(Generic.buffer, "%02d", number);
    if(selected){
      displayFillRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, Generic.buffer);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, Generic.buffer);
    }
  }
  //Рисование рамки с картинкой
  
  //Рисование прямоугольника с иконкой 7x7. Используется на экранах главного меню, секундомера
  static void displayDrawIconWithFrame(byte x, byte y, void (*drawIcon)(byte x,byte y,bool color), bool selected){
    if(selected){
      displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      drawIcon(x + 6, y+4, 0);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      drawIcon(x + 6, y+4, 1);
    }
  }
  
  /*draws battery*/
  static void displayDrawBattery(byte x, byte y, byte level, bool isCharging, bool isLowPower){
  
    //draw battery
    byte xshift = 5;
    displayDrawRect(/*x*/x+xshift+1, /*y*/y, /*w*/11, /*h*/7, /*color*/1);
    displayDrawLine(/*X1*/x+xshift+0, /*Y1*/y+2, /*X2*/x+xshift+0, /*Y2*/y+4, /*C*/1);
    displayDrawLine(/*X1*/x+xshift+1, /*Y1*/y+2, /*X2*/x+xshift+1, /*Y2*/y+4, /*C*/0);
    if(level >= 1)
      displayDrawLine(/*X1*/x+xshift+9, /*Y1*/y+2, /*X2*/x+xshift+9, /*Y2*/y+4, /*C*/1);
    if(level >= 2)
      displayDrawLine(/*X1*/x+xshift+7, /*Y1*/y+2, /*X2*/x+xshift+7, /*Y2*/y+4, /*C*/1);
    if(level >= 3)
      displayDrawLine(/*X1*/x+xshift+5, /*Y1*/y+2, /*X2*/x+xshift+5, /*Y2*/y+4, /*C*/1);
    if(level >= 4)
      displayDrawLine(/*X1*/x+xshift+3, /*Y1*/y+2, /*X2*/x+xshift+3, /*Y2*/y+4, /*C*/1);
  
  
    //draw charging symbol
    if(isCharging){
      static const char img[6] PROGMEM = { 
        0b00000000,
        0b01001100,
        0b00111110,
        0b00011001,
        0b00000000,
        0b00000000
      };
      displayDrawBitmap(x, y, img, 6, 8, 1);
    }
    
    //draw low power symbol
    if(isLowPower)
    {
      static const char img[6] PROGMEM = { 
        0b00100010,
        0b00010100,
        0b00001000,
        0b00010100,
        0b00100010,
        0b00000000
      };
      displayDrawBitmap(x, y, img, 6, 8, 1);
    }
  }

  
  void displayDrawBattery(byte x, byte y) {
    float voltage = Battery.batteryVoltage();
    bool isCharging = Battery.batteryIsCharging();
    bool isLowPower = Battery.batteryIsLowPower();
    byte level = 0;
    if (voltage > 3.40) level = 1;
    if (voltage > 3.65) level = 2;
    if (voltage > 3.85) level = 3;
    if (voltage > 4.00) level = 4;
  
    displayDrawBattery(x, y, level, isCharging, isLowPower);
  }
  
  #define BLOCK_WIDTH  4  // how many blocks contains one symbol
  #define BLOCK_HEIGHT 5  // how many blocks contains one symbol      
  void displayDrawNumber(byte symbol, byte offsetX, byte offsetY, byte blockSizeX, byte blockSizeY, byte animate){
    for(byte bx=0;bx<BLOCK_WIDTH; bx++){
      for(byte by=0;by<BLOCK_HEIGHT;by++){
        byte bitIndex = bx + by * BLOCK_WIDTH;
        int32_t data = pgm_read_dword(&watchFaceFont[symbol]);
        bool fill = bitRead(data, bitIndex);
        if(fill){
          byte x = blockSizeX*bx + offsetX;
          byte y = blockSizeY*by + offsetY;
          displayFillRect(/*x*/x, /*y*/y, /*w*/blockSizeX-1, /*h*/blockSizeY-1, /*c*/1);
          if(animate && bitIndex%animate == 0){
            displayUpdate();
          }
        }
      }
    }
  }

  void drawDayOfWeek(byte x, byte y, byte dayOfWeek, bool color) { //
    __FlashStringHelper* txt;
  #ifdef LANG_RU
    if (dayOfWeek == 1) txt = F("Пн");
    if (dayOfWeek == 2) txt = F("Вт");
    if (dayOfWeek == 3) txt = F("Ср");
    if (dayOfWeek == 4) txt = F("Чт");
    if (dayOfWeek == 5) txt = F("Пт");
    if (dayOfWeek == 6) txt = F("Сб");
    if (dayOfWeek == 0) txt = F("Вс");
  #endif
  #ifdef LANG_EN
    if (dayOfWeek == 1) txt = F("Mon");
    if (dayOfWeek == 2) txt = F("Tue");
    if (dayOfWeek == 3) txt = F("Wed");
    if (dayOfWeek == 4) txt = F("Thu");
    if (dayOfWeek == 5) txt = F("Fri");
    if (dayOfWeek == 6) txt = F("Sat");
    if (dayOfWeek == 0) txt = F("Sun");
  #endif
    displayDrawText(x, y, color, txt);
  }
};

static Display_ Display;

#endif
