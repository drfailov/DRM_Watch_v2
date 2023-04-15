  /*Global functions related to display. 
   * Init, draw primitives, draw text...
   * Every call to display has to be done by some call from this file.
   * It needed to make migration to other display easier.
  */
#include "lcd1202.h"

#define LCD_X        96
#define LCD_Y        68


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

  //LCD1202 lcd;
  LCD1202 lcd(pinLcdRst, pinLcdCs, pinLcdMosi, pinLcdSck);
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
    if(batteryIsLowPower()) return; //если батарея разряжена, подсветку не включать
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
    Serial.println(F("LCD PWR OFF"));
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
  //Если в параметрах указано перевернктый дисплей, эта функция сама это сделает. Она обращается к MyEEPROM
  static void displayUpdate(){
    //true is flip 180, false is no flip
    lcd.Update(/*flip*/eepromReadFlipScreen()); 
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
  
  //Функция рисования залитого круга. Она здесь указана для простоты перехода на другой дисплей - всё взаимодействие с дисплее происходит через эти "обёртки".
  static void displayFillCircle(byte x, byte y, byte r, boolean color){
    lcd.fillCircle(x, y, r, color);
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
  
  static void displaySetPixel(byte x, byte y, bool color){
    lcd.drawPixel(x, y, color);
  }
  
  static bool displayGetPixel(byte x, byte y){
    return lcd.getPixel(x, y);
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
        if (isButtonUpPressed()) 
          animate = false;
      }
      currentIndex += 2;
      lx = x;
      ly = y;
    }
  }
  
  //Рисование на экране текста из макроса F().
  static void displayDrawText(int X, int Y, int color, const __FlashStringHelper* str){
    strcpy_P(buffer, (PGM_P)str);
    byte pos = 0;
    for(int i=0; i<BUFFER_SIZE; i++){
      if(buffer[i] == '\0') 
        break;
      if((byte)buffer[i] != 208 && (byte)buffer[i] != 209){
        displayDrawText(X + pos*6, Y, color, buffer[i]);
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
    strcpy_P(buffer, (PGM_P)str);
    byte pos = 0;
    bool animate = true;
    for(byte i=0; i<BUFFER_SIZE; i++){
      if(buffer[i] == '\0') 
        break;
      if((byte)buffer[i] != 208 && (byte)buffer[i] != 209){
        displayDrawText(10 + pos*6, 6, 1, buffer[i]);
        pos ++;
        if(animate){
          displayUpdate();
          delay(6);
        }
      }
      if (isButtonUpPressed()) 
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
    static const unsigned char img[6] PROGMEM = { 
        0b00011000,
        0b01110000,
        0b01110000,
        0b00111000,
        0b00001110,
        0b00000011,
      };
    displayDrawBitmap(x, y, img, 6, 8, color);
  }
  
  //Рисование иконки сброса. Используется сейчас нигде
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawResetIcon(byte x, byte y, bool color){
    static const unsigned char img[6] PROGMEM = { 
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
    static const unsigned char img[7] PROGMEM = { 
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
    static const unsigned char img[7] PROGMEM = { 
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
    static const unsigned char img[7] PROGMEM = { 
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
    static const unsigned char img[7] PROGMEM = { 
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
    static const unsigned char img[7] PROGMEM = { 
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
    static const unsigned char img[9] PROGMEM = { 
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

  
  

  //Рисование иконки приложений. Используется в главном меню.
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawAppsIcon(byte x, byte y, bool color){
        static const unsigned char img[7] PROGMEM = { 
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
  

  
  //Рисование иконки настроек. Используется в главном меню
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconSettings(byte x, byte y, bool color){
    static const unsigned char img[7] PROGMEM = { 
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
    static const unsigned char img[7] PROGMEM = { 
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
  
  
  //Рисование иконки перезагрузки. Используется в меню настроек и в секундомере
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconReboot(byte x, byte y, bool color){
    static const unsigned char img[7] PROGMEM = { 
        0b01110110,
        0b00110001,
        0b01010001,
        0b01000001,
        0b01000101,
        0b01000110,
        0b00110111
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  

  
  
  //Рисование иконки сна. Используется в меню настроек
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconSleep(byte x, byte y, bool color){
    static const unsigned char img[7] PROGMEM = { 
        0b00011100,
        0b00111110,
        0b01111111,
        0b01111000,
        0b01110000,
        0b00110000,
        0b00010000
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  
  //Рисование иконки звука. Используется в меню настроек
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconBeep(byte x, byte y, bool color){
    static const unsigned char img[7] PROGMEM = { 
        0b00011100,
        0b00000000,
        0b00111110,
        0b00000000,
        0b00111110,
        0b00000000,
        0b00011100
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  
  //Рисование иконки времени. Используется в меню настроек
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconTime(byte x, byte y, bool color){
    static const unsigned char img[7] PROGMEM = { 
        0b00011100,
        0b00100010,
        0b01001001,
        0b01001101,
        0b01000001,
        0b00100010,
        0b00011100
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }
  
  
  //Рисование иконки сброса. Используется в меню настроек
  //Рисунок находится в битовом массиве.
  //Начало массива - левая часть рисунка. Один бит - один пиксель.
  //Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.
  static void displayDrawIconReset(byte x, byte y, bool color){
    static const unsigned char img[7] PROGMEM = { 
        0b01011110,
        0b01100001,
        0b00000000,
        0b00101110,
        0b00000000,
        0b01000011,
        0b00111101
      };
    displayDrawBitmap(x, y, img, 7, 8, color);
  }

  
  //Рисование прямоугольника с цифрами. Используется на экранах настройки будильника и времени
  static void displayDraw2DigitNumberWithFrame(byte x, byte y, byte number, bool selected){
    sprintf(buffer, "%02d", number);
    if(selected){
      displayFillRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, buffer);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, buffer);
    }
  }
  //Рисование рамки с картинкой
  
  //Рисование прямоугольника с иконкой 7x7. Используется на экранах главного меню, секундомера
  static void displayDrawIconWithFrame(byte x, byte y, byte additionalWidth, void (*drawIcon)(byte x,byte y,bool color), bool selected){
    if(selected){
      displayFillRect(/*x*/x, /*y*/y, /*w*/20 + additionalWidth, /*h*/15, /*c*/1);
      drawIcon(x + 6, y+4, 0);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/20 + additionalWidth, /*h*/15, /*c*/1);
      drawIcon(x + 6, y+4, 1);
    }
  }
  
  /*draws battery
  Эта функция предполагается быть приватной*/
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
  
  
    
    if(isCharging){ //draw charging symbol
      static const unsigned char img[6] PROGMEM = { 
        0b00000000,
        0b01001100,
        0b00111110,
        0b00011001,
        0b00000000,
        0b00000000
      };
      displayDrawBitmap(x, y, img, 6, 8, 1);
    }
    else if(isLowPower) //draw low power symbol
    {
      static const unsigned char img[4] PROGMEM = { 
        0b00000000,
        0b00000000,
        0b01101111,
        0b01101111
      };
      displayDrawBitmap(x, y, img, 4, 8, 1);
    }
  }

  //Это основная функция которая вызывается с циферлатов
  void displayDrawBattery(byte x, byte y) {
    bool isCharging = batteryIsCharging();
    bool isLowPower = batteryIsLowPower();
    byte level = batteryBars();  
    //isLowPower = true; //for test
    //isCharging = false; //for test
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
    const __FlashStringHelper* txt;
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
