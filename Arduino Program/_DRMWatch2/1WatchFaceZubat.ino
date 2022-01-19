#include "Display.cpp"
#include "MyEEPROM.cpp"


/* 
 * EN: 
 * Drawing watchface 4 (Zubat). Arguments:
 * hour, minute, second, day, month, year, dayOfWeek - current values to draw
 * animate - 0=draw without animation, 1 - animate slowly, 2 - animate more quickly, ...
 * RU: 
 * Рисование циферблата 4 (Zubat). Принимает аргументы:
 * hour, minute, second, day, month, year, dayOfWeek - текущие значения которые нужно вывести на циферблат
 * animate - Анимировать ли вывод. 0 = не анимировать. 1 = анимировать медленно, 2 = анимировать быстрее ...
*/
void drawWatchFaceZubat(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate){
  Display.displayClear();
  
  {//date
    sprintf(Generic.buffer, "%02d.%02d.%04d", day, month, year);
    Display.displayDrawText(37, 61, 1, Generic.buffer);
  }
  
  if(MyEEPROM.eepromReadAlertEnabled()){   //Alert sign
    Display.displayDrawAlertSign(0, 0, 1);
  }
  
  if(MyEEPROM.eepromReadSilentMode()){  //Silent mode sign
    Display.displayDrawSilentModeIcon(10, 0, 1);
  }
  
  {//DayOfWeek
    modeWatchFaceDrawDayOfWeek(0, 61, dayOfWeek, /*color*/1);
  }  
  
  {//battery
    modeWatchFaceDrawBattery(79, 0);
  }

  {//zubat
    Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
  }
  
  {//time
    byte hour1 = hour / 10;
    byte hour2 = hour - (hour1 * 10);
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    
    Display.displayDrawNumber(hour1   , 38, 19, 3, 4, animate);
    Display.displayDrawNumber(hour2   , 52, 19, 3, 4, animate);
    Display.displayDrawNumber(10      , 66, 19, 3, 4, animate); // :
    Display.displayDrawNumber(minute1 , 71, 19, 3, 4, animate);
    Display.displayDrawNumber(minute2 , 85, 19, 3, 4, animate);
  }

  Display.displayUpdate();
}
