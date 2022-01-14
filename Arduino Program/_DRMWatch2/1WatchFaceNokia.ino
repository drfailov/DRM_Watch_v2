#include "Display.cpp"

/* 
 * EN: 
 * Drawing watchface 5 (DRM Lite). Arguments:
 * hour, minute, second, day, month, year, dayOfWeek - current values to draw
 * animate - 0=draw without animation, 1 - animate slowly, 2 - animate more quickly, ...
 * RU: 
 * Рисование циферблата 2 (DRM Lite). Принимает аргументы:
 * hour, minute, second, day, month, year, dayOfWeek - текущие значения которые нужно вывести на циферблат
 * animate - Анимировать ли вывод. 0 = не анимировать. 1 = анимировать медленно, 2 = анимировать быстрее ...
*/
void drawWatchFaceNokia(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate){
    Display.displayClear();
      
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
