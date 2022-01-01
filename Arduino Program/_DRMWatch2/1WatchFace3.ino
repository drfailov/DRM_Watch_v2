void drawWatchFace3(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek){
  displayClear();

  {//time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    displayFillRect(/*x*/46, /*y*/26, /*w*/4, /*h*/5, /*c*/1);
    displayFillRect(/*x*/46, /*y*/38, /*w*/4, /*h*/5, /*c*/1);
    drawNumber(/*x*/05, /*y*/16, /*num*/hour1);
    drawNumber(/*x*/25, /*y*/16, /*num*/hour2);
    drawNumber(/*x*/54, /*y*/16, /*num*/minute1);
    drawNumber(/*x*/74, /*y*/16, /*num*/minute2);
  }

  
  {//date
    sprintf(buffer, "%02d.%02d.%04d", day, month, year);
    displayDrawText(20, 61, 1, buffer);
  }
  

  if(eepromReadAlertEnabled()){   //Alert sign
    displayDrawAlertSign(0, 0, 1);
  }
  
  if(eepromReadSilentMode()){  //Silent mode sign
    displayDrawSilentModeIcon(12, 0, 1);
  }
  
  {//DayOfWeek
    modeWatchFaceDrawDayOfWeek(30, 0, dayOfWeek);
  }
  
  {//battery
    modeWatchFaceDrawBattery(78, 0);
  }
  displayUpdate();
}

const byte fontWtf3[] PROGMEM = {
  0b11101110, //0 
  0b00100100, //1
  0b10111010, //2
  0b10110110, //3
  0b01110100, //4 
  0b11010110, //5
  0b11011110, //6
  0b10100100, //7
  0b11111110, //8
  0b11110110 //9
};
static const PROGMEM byte pathUp[] = { 8,
   2,0,    14,0,   13,1,   3,1,    4,2,
   12,2,   11,3,   5,3
};
static const PROGMEM byte pathUpLeft[] = { 8,
   0,1,    0,14,   1,2,    1,13,   2,3,
   2,12,   3,4,    3,11
};
static const PROGMEM byte pathUpRight[] = { 8,
   13,4,   13,11,  14,12,  14,3,   15,2,
   15,13,  16,14,  16,1
};
static const PROGMEM byte pathCenter[] = { 10,
   4,13,   12,13,  13,14,  3,14,   2,15,
   14,15,  13,16,  3,16,   4,17,   12,17
};
static const PROGMEM byte pathBottomLeft[] = { 8,
   0,16,   0,32,   1,31,   1,17,   2,18,
   2,30,   3,29,   3,19
};
static const PROGMEM byte pathBottomRight[] = { 8,
   13,19,  13,29,  14,30,  14,18,  15,17,
   15,31,  16,32,  16,16
};
static const PROGMEM byte pathBottom[] = { 8,
   5,30,   11,30,  12,31,  4,31,   3,32,
   13,32,  14,33,  2,33
};
void drawNumber(byte x, byte y, byte num){
  byte b = pgm_read_byte(&fontWtf3[num]);
  if(bitRead(b, 7)){ 
    displayDrawVector(/*path*/pathUp, /*x*/x, /*y*/y, /*animate*/false, /*color*/1);
  }
  if(bitRead(b, 6)){ 
    displayDrawVector(/*path*/pathUpLeft, /*x*/x, /*y*/y, /*animate*/false, /*color*/1);
  }
  if(bitRead(b, 5)){ 
    displayDrawVector(/*path*/pathUpRight, /*x*/x, /*y*/y, /*animate*/false, /*color*/1);
  }
  if(bitRead(b, 4)){ 
    displayDrawVector(/*path*/pathCenter, /*x*/x, /*y*/y, /*animate*/false, /*color*/1);
  }
  if(bitRead(b, 3)){ 
    displayDrawVector(/*path*/pathBottomLeft, /*x*/x, /*y*/y, /*animate*/false, /*color*/1);
  }
  if(bitRead(b, 2)){ 
    displayDrawVector(/*path*/pathBottomRight, /*x*/x, /*y*/y, /*animate*/false, /*color*/1);
  }
  if(bitRead(b, 1)){ 
    displayDrawVector(/*path*/pathBottom, /*x*/x, /*y*/y, /*animate*/false, /*color*/1);
  }
}
