#include <Arduino.h>
#include "GenericWatchface.cpp"
#include "Display.cpp"
#include "RTC.cpp"
#include "Battery.cpp"
#include "MyEEPROM.cpp"


#ifndef WATCHFACEDRMWATCHCPP
#define WATCHFACEDRMWATCHCPP
class WatchfaceDrmWatch : public GenericWatchface  { //
  public :
    virtual const char* name() {
      return (const char*)F("DRM Wat");
    }
    
    virtual const byte updateMode() {  
      return WATCHFACE_UPDATE_MODE_1S_1FRAME;
    }

    /*
       EN:
       Drawing watchfacw 1 (DRM Watch). Arguments:
       hour, minute, second, day, month, year, dayOfWeek - current values to draw
       animate - 0=draw without animation, 1 - animate slowly, 2 - animate more quickly, ...
       RU:
       Рисование циферблата 1 (DRM Watch). Принимает аргументы:
       hour, minute, second, day, month, year, dayOfWeek - текущие значения которые нужно вывести на циферблат
       animate - Анимировать ли вывод. 0 = не анимировать. 1 = анимировать медленно, 2 = анимировать быстрее ...
    */
    virtual void drawWatchface(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate)
    {
      Display.displayClear();

      { //date
        sprintf(Generic.buffer, Generic.getDateFormat(), day, month, year);
        Display.displayDrawText(0, 0, 1, Generic.buffer);
      }

      { //DayOfWeek
#ifdef LANG_EN
        Display.drawDayOfWeek(79, 0, dayOfWeek, /*color*/1);
#endif
#ifdef LANG_RU
        Display.drawDayOfWeek(85, 0, dayOfWeek, /*color*/1);
#endif
      }

      { //Temperature
        float temp = RTC.rtcGetTemp();
        /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
        dtostrf(temp, 4, 1, Generic.buffer);
        sprintf(Generic.buffer, "%sC", Generic.buffer);
        Display.displayDrawText(0, 61, 1, Generic.buffer);
      }


      byte X = 96;

      { //battery
        X -= 17;
        Display.displayDrawBattery(X, 61);
        if (!Battery.batteryIsCharging() && !Battery.batteryIsLowPower()) X += 5;
      }

      //Silent mode sign
      if (MyEEPROM.eepromReadSilentMode()) {
        X -= 10;
        Display.displayDrawSilentModeIcon(X, 61, 1);
      }

      //Alert sign
      if (MyEEPROM.eepromReadAlertEnabled()) {
        X -= 11;
        Display.displayDrawAlertSign(X, 61, 1);
      }


      { //time
        byte hour1 = hour / 10;
        byte hour2 = hour - (hour1 * 10);
        byte minute1 = minute / 10;
        byte minute2 = minute - (minute1 * 10);
        byte second1 = second / 10;
        byte second2 = second - (second1 * 10);

        Display.displayDrawNumber(hour1   ,  5, 20, 3, 4, animate);
        Display.displayDrawNumber(hour2   , 19, 20, 3, 4, animate);
        Display.displayDrawNumber(10      , 34, 20, 3, 4, animate); // :
        Display.displayDrawNumber(minute1 , 40, 20, 3, 4, animate);
        Display.displayDrawNumber(minute2 , 54, 20, 3, 4, animate);
        Display.displayDrawNumber(10      , 70, 25, 2, 3, animate); // :
        Display.displayDrawNumber(second1 , 75, 25, 2, 3, animate);
        Display.displayDrawNumber(second2 , 85, 25, 2, 3, animate);
      }

      Display.displayUpdate();
    }

};

#endif
