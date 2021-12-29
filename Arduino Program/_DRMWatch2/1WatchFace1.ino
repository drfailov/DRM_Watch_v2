void drawWatchFace1(byte hour, byte minute, byte second, byte day, byte month, int year){
    displayClear();
  
  { //time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    byte second1 = second / 10;
    byte second2 = second - (second1 * 10);
    
    displayDrawNumber(hour1   ,  5, 20, 3, 4);
    displayDrawNumber(hour2   , 19, 20, 3, 4);
    displayDrawNumber(10      , 34, 20, 3, 4); // :
    displayDrawNumber(minute1 , 40, 20, 3, 4);
    displayDrawNumber(minute2 , 54, 20, 3, 4);
    displayDrawNumber(10      , 70, 25, 2, 3); // :
    displayDrawNumber(second1 , 75, 25, 2, 3);
    displayDrawNumber(second2 , 85, 25, 2, 3);
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
  
  {//battery
    float voltage = batteryVoltage();
    bool isCharging = batteryIsCharging();
    bool isLowPower = batteryIsLowPower();
    byte level = 0;
    if(voltage > 3.40) level = 1;
    if(voltage > 3.65) level = 2;
    if(voltage > 3.85) level = 3;
    if(voltage > 4.00) level = 4;
  
    displayDrawBattery(78, 0, level, isCharging, isLowPower);
  }

  //Silent mode sign
  if(eepromReadSilentMode()){ 
    displayDrawSilentModeIcon(85, 60, 1);
  }
  
  //Alert sign
  if(eepromReadAlertEnabled()){ 
    displayDrawAlertSign(72, 60, 1);
  }

  displayUpdate();
  
}
