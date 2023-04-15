//Рисунок находится в битовом массиве.
//Начало массива - левая часть рисунка. Один бит - один пиксель.
//Т.е. смотреть на массив следует повернув его на 90 градусов против часовой стрелки.

//==========================================================================================---------------------------------------------- frequently used
//BACK
//Рисование иконки стрелки влево. Используется на многи экранах как кнопка НАЗАД.
static void displayDrawArrowLeft(byte x, byte y, bool color){
  static const unsigned char img[7] PROGMEM = { 
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

//CHECK
//Рисование галочки. Используется по всей программе, в частности в менюшках.
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

//Рисование иконки стрелки вниз. Используется менющках.
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



//==========================================================================================---------------------------------------------- settings screen
//SILENT MODE 
//Рисование иконки беззвучного режима. Используется на циферблатах и в настройках.
static void displayDrawSilentModeIcon(byte x, byte y, bool color){
      static const unsigned char img[8] PROGMEM = { 
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

//SILENT MODE OFF
//Рисование иконки небеззвучного режима. Используется на циферблатах и в настройках.
static void displayDrawSilentModeOffIcon(byte x, byte y, bool color){
      static const unsigned char img[8] PROGMEM = { 
      0b00100000,
      0b00111110,
      0b00100001,
      0b01100001,
      0b01100001,
      0b00100001,
      0b00111110,
      0b00100000
    };
    displayDrawBitmap(x, y, img, 8, 8, color);
}

//FLIP
//Рисование иконки переворота диссплей. Используется в меню настроек
static void displayDrawIconFlip(byte x, byte y, bool color){
  static const unsigned char img[7] PROGMEM = { 
      0b00000100,
      0b01110110,
      0b01000100,
      0b01000001,
      0b00010001,
      0b00110111,
      0b00010000
    };
  displayDrawBitmap(x, y, img, 7, 8, color);
}

//TIME
//Рисование иконки времени. Используется в меню настроек
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

//WATCHFACE
//Рисование иконки вочфейс. Используется в меню настроек
static void displayDrawIconWatchface(byte x, byte y, bool color){
  static const unsigned char img[7] PROGMEM = { 
      0b00000000,
      0b01111111,
      0b00111010,
      0b00101110,
      0b00111010,
      0b01111111,
      0b00000000
    };
  displayDrawBitmap(x, y, img, 7, 8, color);
}
