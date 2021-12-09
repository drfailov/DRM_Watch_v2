#define BLOCK_WIDTH  4  // how many blocks contains one symbol
#define BLOCK_HEIGHT 5  // how many blocks contains one symbol

PROGMEM const int32_t font [] {
  
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
  0b00000000000010001000100010001111, //7
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111001111110011111, //8
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000011111000111110011111, //9
  //  Lines:    |5 ||4 ||3 ||2 ||1 |  <<<<
  0b00000000000000000001000000010000, // [10] = :
};


int modeWatchFace1BacklightCounter = 10; //сколько секунд осталось подсветке светить. 0 = выключена

void modeWatchFace1Setup() {
  modeWatchFace1BacklightCounter = 10;
}

void modeWatchFace1Loop() {
  if (isButtonUpPressed()) {
    beep();
    modeWatchFace1BacklightCounter = 10;
  }

  if (isButtonDownPressed()) {
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  }
  displayClear();
  float voltage = batteryVoltage();
  bool isCharging = batteryIsCharging();
  bool isChargeComplete = batteryIsChargeComplete();

  { //time
    int hour = rtcGetHours();
    int minute = rtcGetMinutes();
    int second = rtcGetSeconds();
    int hour1 = hour / 10;
    int hour2 = hour - (hour1 * 10);
    int minute1 = minute / 10;
    int minute2 = minute - (minute1 * 10);
    int second1 = second / 10;
    int second2 = second - (second1 * 10);
    
    drawSymbol(hour1   ,  5, 20, 3, 4);
    drawSymbol(hour2   , 19, 20, 3, 4);
    drawSymbol(10      , 34, 20, 3, 4); // :
    drawSymbol(minute1 , 40, 20, 3, 4);
    drawSymbol(minute2 , 54, 20, 3, 4);
    drawSymbol(10      , 69, 20, 3, 4); // :
    drawSymbol(second1 , 75, 25, 2, 3);
    drawSymbol(second2 , 85, 25, 2, 3);
  }
  
  {//date
    int day = rtcGetDay();
    int month = rtcGetMonth();
    int year = rtcGetYear();

    char chars[11];
    sprintf(chars, "%02d.%02d.%04d", day, month, year);
    displayDrawText(2, 2, 1, chars);
  }
  
  {//Temperature
    float temp = rtcGetTemp();
    char chars[8];
    /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
    dtostrf(temp, 4, 1, chars);
    sprintf(chars, "%s C", chars);
    displayDrawText(2, 59, 1, chars);
  }

  displayUpdate();
  { //Baclight
    modeWatchFace1BacklightCounter --;
    if (modeWatchFace1BacklightCounter < 0) modeWatchFace1BacklightCounter = 0;
    if (modeWatchFace1BacklightCounter > 0)
      digitalWrite(pinLcdBacklight, HIGH);
    else
      digitalWrite(pinLcdBacklight, LOW);
  }

  Serial.flush();
  delay(50);
  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
}

void modeWatchFace1Finish() {

}


void drawSymbol(int symbol, int offsetX, int offsetY, int blockSizeX, int blockSizeY){
  for(int bx=0;bx<BLOCK_WIDTH; bx++){
    for(int by=0;by<BLOCK_HEIGHT;by++){
      int bitIndex = bx + by * BLOCK_WIDTH;
      int32_t data = pgm_read_dword(&font[symbol]);
      bool fill = bitRead(data, bitIndex);
      if(fill){
        int x = blockSizeX*bx + offsetX;
        int y = blockSizeY*by + offsetY;
        displayFillRect(/*x*/x, /*y*/y, /*w*/blockSizeX-1, /*h*/blockSizeY-1, /*c*/1);    
      }
    }
  }
}
