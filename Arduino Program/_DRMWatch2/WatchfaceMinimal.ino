void WatchfaceMinimal(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate)
{
    displayClear();

    if(isButtonDownNowPressed()){//date
      sprintf(buffer, dateFormat, day, month, year);
      displayDrawText(0, 0, 1, buffer);
    }
    
    if(isButtonDownNowPressed()){//DayOfWeek
  #ifdef LANG_EN
      drawDayOfWeek(79, 0, dayOfWeek, /*color*/1);
  #endif
  #ifdef LANG_RU
      drawDayOfWeek(85, 0, dayOfWeek, /*color*/1);
  #endif
  #ifdef LANG_UA
      drawDayOfWeek(85, 0, dayOfWeek, /*color*/1);
  #endif
    }
    
    if(isButtonDownNowPressed()){//Temperature
      float temp = rtcGetTemp();
      /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
      dtostrf(temp, 4, 1, buffer);
      sprintf(buffer, "%sC", buffer);
      displayDrawText(0, 61, 1, buffer);
    }
  
    byte X = 96;
    if(isButtonDownNowPressed()){
      {//battery
        X -= 17;
        displayDrawBattery(X, 61);
        if(!batteryIsCharging() && !batteryIsLowPower()) X += 5;
      }
      
      //Silent mode sign
      if(eepromReadSilentMode()){ 
        X -= 11;
        displayDrawSilentModeIcon(X, 61, 1);
      }
      
      //Alert sign
      if(eepromReadAlertEnabled()){ 
        X-= 11;
        displayDrawAlertSign(X, 61, 1);
      }
    }
    
    
    { //time
      sprintf(buffer, timeFormat, hour, minute);
      displayDrawText(33, 28, 1, buffer);
    }
    
    displayUpdate();
}
