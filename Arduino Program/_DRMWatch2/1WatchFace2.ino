void drawWatchFace2(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek){
    displayClear();
  
  { //time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    
    displayDrawNumber(hour1   ,  6, 18, 4, 5);
    displayDrawNumber(hour2   , 25, 18, 4, 5);
    displayDrawNumber(10      , 46, 18, 4, 5); // :
    displayDrawNumber(minute1 , 55, 18, 4, 5);
    displayDrawNumber(minute2 , 74, 18, 4, 5);
  }

  {//date
    sprintf(buffer, "%02d.%02d.%04d", day, month, year);
    displayDrawText(0, 0, 1, buffer);
  }
  
  {//Temperature
    float temp = rtcGetTemp();
    /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
    dtostrf(temp, 4, 1, buffer);
    sprintf(buffer, "%sC", buffer);
    displayDrawText(0, 61, 1, buffer);
  }
  
  {//DayOfWeek
    modeWatchFaceDrawDayOfWeek(55, 61, dayOfWeek);
  }
  
  {//battery
    modeWatchFaceDrawBattery(78, 0);
  }

  //Silent mode sign
  if(eepromReadSilentMode()){ 
    displayDrawSilentModeIcon(85, 60, 1);
  }
  
  //Alert sign
  if(eepromReadAlertEnabled()){ 
    displayDrawAlertSign(75, 60, 1);
  }

  displayUpdate();
  
}
