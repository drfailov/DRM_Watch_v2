void drawWatchFace4(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek){
  displayClear();
  
  {//time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    
    displayDrawNumber(hour1   , 38, 19, 3, 4);
    displayDrawNumber(hour2   , 52, 19, 3, 4);
    displayDrawNumber(10      , 66, 19, 3, 4); // :
    displayDrawNumber(minute1 , 71, 19, 3, 4);
    displayDrawNumber(minute2 , 85, 19, 3, 4);
  }
  
  {//date
    sprintf(buffer, "%02d.%02d.%04d", day, month, year);
    displayDrawText(36, 61, 1, buffer);
  }
  
  if(eepromReadAlertEnabled()){   //Alert sign
    displayDrawAlertSign(0, 0, 1);
  }
  
  if(eepromReadSilentMode()){  //Silent mode sign
    displayDrawSilentModeIcon(12, 0, 1);
  }
  
  {//DayOfWeek
    modeWatchFaceDrawDayOfWeek(0, 61, dayOfWeek);
  }  
  
  {//battery
    modeWatchFaceDrawBattery(78, 0);
  }

  displayDrawVector(/*path*/getPathZubat(), /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
  displayUpdate();
}
