void drawWatchFace3(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate){
  displayClear();
  
  {//date
    sprintf(buffer, "%02d.%02d.%04d", day, month, year);
    displayDrawText(16, 61, 1, buffer);
  }
  
  if(eepromReadAlertEnabled()){   //Alert sign
    displayDrawAlertSign(0, 0, 1);
  }
  
  if(eepromReadSilentMode()){  //Silent mode sign
    displayDrawSilentModeIcon(88, 0, 1);
  }
  
  {//DayOfWeek
    modeWatchFaceDrawDayOfWeek(0, 61, dayOfWeek);
  }
  
  {//battery
    modeWatchFaceDrawBattery(79, 61);
  }

  {//time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    displayFillRect(/*x*/46, /*y*/24, /*w*/3, /*h*/3, /*c*/1);
    displayFillRect(/*x*/46, /*y*/35, /*w*/3, /*h*/3, /*c*/1);
    drawNumber(/*x*/8, /*y*/16, /*num*/hour1, /*animate*/ animate);
    drawNumber(/*x*/25, /*y*/16, /*num*/hour2, /*animate*/ animate);
    drawNumber(/*x*/55, /*y*/16, /*num*/minute1, /*animate*/ animate);
    drawNumber(/*x*/72, /*y*/16, /*num*/minute2, /*animate*/ animate);
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
static const PROGMEM byte pathUp[] = { 6,
   2,0,    12,0,   11,1,   3,1,   4,2,
   10,2
};
static const PROGMEM byte pathUpLeft[] = { 6,
   0,1,    0,12,   1,11,   1,2,   2,3,
   2,10
};
static const PROGMEM byte pathUpRight[] = { 6,
   14,1,   14,12,  13,11,  13,2,  12,3,
   12,10
};
static const PROGMEM byte pathCenter[] = { 6,
   3,12,   11,12,  12,13,  2,13,  3,14,
   11,14
};
static const PROGMEM byte pathBottomLeft[] = { 6,
   0,14,   0,27,   1,26,   1,15,  2,16,
   2,25
};
static const PROGMEM byte pathBottomRight[] = { 6,
   14,14,  14,27,  13,26,  13,15, 12,16,
   12,25
};
static const PROGMEM byte pathBottom[] = { 6,
   2,28,   12,28,  11,27,  3,27,  4,26,
   10,26
};
void drawNumber(byte x, byte y, byte num, byte animate){
  byte b = pgm_read_byte(&fontWtf3[num]);
  if(bitRead(b, 7)){ 
    displayDrawVector(/*path*/pathUp, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
  }
  if(bitRead(b, 6)){ 
    displayDrawVector(/*path*/pathUpLeft, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
  }
  if(bitRead(b, 5)){ 
    displayDrawVector(/*path*/pathUpRight, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
  }
  if(bitRead(b, 4)){ 
    displayDrawVector(/*path*/pathCenter, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
  }
  if(bitRead(b, 3)){ 
    displayDrawVector(/*path*/pathBottomLeft, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
  }
  if(bitRead(b, 2)){ 
    displayDrawVector(/*path*/pathBottomRight, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
  }
  if(bitRead(b, 1)){ 
    displayDrawVector(/*path*/pathBottom, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
  }
}
