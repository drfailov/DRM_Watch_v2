#include "Display.cpp"
#include "Battery.cpp"

/* 
 * EN: 
 * Drawing watchfacw 2 (DRM Lite). Arguments:
 * hour, minute, second, day, month, year, dayOfWeek - current values to draw
 * animate - 0=draw without animation, 1 - animate slowly, 2 - animate more quickly, ...
 * RU: 
 * Рисование циферблата 2 (DRM Lite). Принимает аргументы:
 * hour, minute, second, day, month, year, dayOfWeek - текущие значения которые нужно вывести на циферблат
 * animate - Анимировать ли вывод. 0 = не анимировать. 1 = анимировать медленно, 2 = анимировать быстрее ...
*/
void drawWatchFaceDrmLite(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate){
    Display.displayClear();
  
  {//date
    sprintf(Generic.buffer, "%02d.%02d.%04d", day, month, year);
    Display.displayDrawText(0, 0, 1, Generic.buffer);
  }
  
  {//DayOfWeek
#ifdef LANG_EN
    modeWatchFaceDrawDayOfWeek(79, 0, dayOfWeek, /*color*/1);
#endif
#ifdef LANG_RU
    modeWatchFaceDrawDayOfWeek(85, 0, dayOfWeek, /*color*/1);
#endif
  }
  
  {//Temperature
    float temp = rtcGetTemp();
    /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
    dtostrf(temp, 4, 1, Generic.buffer);
    sprintf(Generic.buffer, "%sC", Generic.buffer);
    Display.displayDrawText(0, 61, 1, Generic.buffer);
  }

  byte X = 96;
  
  {//battery
    X -= 17;
    modeWatchFaceDrawBattery(X, 61);
    if(!Battery.batteryIsCharging() && !Battery.batteryIsLowPower()) X += 5;
  }
  
  //Silent mode sign
  if(eepromReadSilentMode()){ 
    X -= 10;
    Display.displayDrawSilentModeIcon(X, 61, 1);
  }
  
  //Alert sign
  if(eepromReadAlertEnabled()){ 
    X-= 11;
    Display.displayDrawAlertSign(X, 61, 1);
  }
  
  
  { //time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    
    Display.displayDrawNumber(hour1   ,  6, 18, 4, 5, animate);
    Display.displayDrawNumber(hour2   , 25, 18, 4, 5, animate);
    Display.displayDrawNumber(10      , 46, 18, 4, 5, animate); // :
    Display.displayDrawNumber(minute1 , 55, 18, 4, 5, animate);
    Display.displayDrawNumber(minute2 , 74, 18, 4, 5, animate);
  }

  Display.displayUpdate();
  
}
