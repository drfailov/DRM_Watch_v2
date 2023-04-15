void watchfaceZubat(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate)
{
  displayClear();

  {//date
    sprintf(buffer, getDateFormat(), day, month, year);
    displayDrawText(37, 61, 1, buffer);
  }
  
  if(eepromReadAlertEnabled()){   //Alert sign
    displayDrawAlertSign(0, 0, 1);
  }
  
  if(eepromReadSilentMode()){  //Silent mode sign
    displayDrawSilentModeIcon(10, 0, 1);
  }
  
  {//DayOfWeek
    drawDayOfWeek(0, 61, dayOfWeek, /*color*/1);
  }  
  
  {//battery
    displayDrawBattery(79, 0);
  }

  {//zubat
    displayDrawVector(/*path*/getPathZubat(), /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
  }
  
  {//time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    
    displayDrawNumber(hour1   , 38, 19, 3, 4, animate);
    displayDrawNumber(hour2   , 52, 19, 3, 4, animate);
    displayDrawNumber(10      , 66, 19, 3, 4, animate); // :
    displayDrawNumber(minute1 , 71, 19, 3, 4, animate);
    displayDrawNumber(minute2 , 85, 19, 3, 4, animate);
  }

  displayUpdate();
}
