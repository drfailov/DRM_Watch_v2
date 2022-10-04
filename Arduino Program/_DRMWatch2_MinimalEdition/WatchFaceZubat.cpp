#include <Arduino.h>
#include "GenericWatchface.cpp"
#include "Display.cpp"
#include "RTC.cpp"
#include "Battery.cpp"
#include "MyEEPROM.cpp"


#ifndef WATCHFAZUBATCPP
#define WATCHFAZUBATCPP
class WatchfaceZubat : public GenericWatchface  { //
  public :
    virtual const char* name() {
      return (const char*)F("Zubat");
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
  
      {//date
        sprintf(Generic.buffer, Generic.getDateFormat(), day, month, year);
        Display.displayDrawText(37, 61, 1, Generic.buffer);
      }
      
      if(MyEEPROM.eepromReadAlertEnabled()){   //Alert sign
        Display.displayDrawAlertSign(0, 0, 1);
      }
      
      if(MyEEPROM.eepromReadSilentMode()){  //Silent mode sign
        Display.displayDrawSilentModeIcon(10, 0, 1);
      }
      
      {//DayOfWeek
        Display.drawDayOfWeek(0, 61, dayOfWeek, /*color*/1);
      }  
      
      {//battery
        Display.displayDrawBattery(79, 0);
      }
    
      {//zubat
        Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
      }
      
      {//time
        sprintf(Generic.buffer, Generic.getTimeFormat(), hour, minute);
        Display.displayDrawText(47, 26, 1, Generic.buffer);
      }
    
      Display.displayUpdate();
    }

};

#endif
