void WatchfaceDrmWatch(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate)
{
  displayClear();

  { //date
    sprintf(buffer, dateFormat, day, month, year);
    displayDrawText(0, 0, 1, buffer);
  }

  { //DayOfWeek
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

  { //Temperature
    float temp = rtcGetTemp();
    /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
    dtostrf(temp, 4, 1, buffer);
    sprintf(buffer, "%sC", buffer);
    displayDrawText(0, 61, 1, buffer);
  }


  byte X = 96;

  { //battery
    X -= 17;
    displayDrawBattery(X, 61);
    if (!batteryIsCharging() && !batteryIsLowPower()) X += 5;
  }

  //Silent mode sign
  if (eepromReadSilentMode()) {
    X -= 10;
    displayDrawSilentModeIcon(X, 61, 1);
  }

  //Alert sign
  if (eepromReadAlertEnabled()) {
    X -= 11;
    displayDrawAlertSign(X, 61, 1);
  }


  { //time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    byte second1 = second / 10;
    byte second2 = second - (second1 * 10);

    displayDrawNumber(hour1   ,  5, 20, 3, 4, animate);
    displayDrawNumber(hour2   , 19, 20, 3, 4, animate);
    displayDrawNumber(10      , 34, 20, 3, 4, animate); // :
    displayDrawNumber(minute1 , 40, 20, 3, 4, animate);
    displayDrawNumber(minute2 , 54, 20, 3, 4, animate);
    displayDrawNumber(10      , 70, 25, 2, 3, animate); // :
    displayDrawNumber(second1 , 75, 25, 2, 3, animate);
    displayDrawNumber(second2 , 85, 25, 2, 3, animate);
  }

  displayUpdate();
}
