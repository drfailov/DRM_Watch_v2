#include <Arduino.h>
#include "GenericWatchface.cpp"
#include "Display.cpp"
#include "RTC.cpp"
#include "Battery.cpp"
#include "MyEEPROM.cpp"


#ifndef WATCHFACEMATRIXCPP
#define WATCHFACEMATRIXCPP

//0 OK
static const PROGMEM byte pathMatrix0[] = { 17,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   3,0,   12,0,  15,3,  15,30, 12,33,
   3,33,  0,30,  0,3,   2,2,   13,2,
   13,31, 2,31,  2,1,   14,1,  14,32,
   1,32,  1,1
};
//1 OK
static const PROGMEM byte pathMatrix1[] = { 19,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   1,0,   8,0,   8,30,  7,1,   0,1,
   1,2,   6,2,   6,30,  7,4,   7,31,
   1,31,  13,31, 13,29, 14,28, 14,32,
   0,32,  1,33,  15,33, 15,29
};
//2 OK
static const PROGMEM byte pathMatrix2[] = { 21,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   1,0,   13,0,  15,2,  15,14, 13,16,
   2,16,  2,31,  14,31, 15,32, 1,32,
   1,15,  14,15, 14,1,  0,1,   1,2,
   13,2,  13,14, 2,14,  0,16,  0,33,
   14,33
};
//3 OK
static const PROGMEM byte pathMatrix3[] = { 31,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   3,0,   12,0,  15,3,  15,12, 13,15,
   15,18, 15,30, 12,33, 1,33,  1,31,
   13,31, 13,18, 11,16, 6,16,  6,14,
   11,14, 13,12, 13,2,  3,2,   2,1,
   14,1,  14,12, 11,15, 5,15,  11,15,
   14,18, 14,32, 0,32,  13,32, 13,14,
   12,15
};
//4 OK
static const PROGMEM byte pathMatrix4[] = { 16,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   0,1,   0,20,  14,20, 15,19, 1,19,
   1,0,   2,1,   2,18,  14,18, 255,255,
   11,4,  11,32, 12,33, 12,3,  13,4,
   13,32
};
//5 OK
static const PROGMEM byte pathMatrix5[] = { 21,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   14,0,  0,0,   0,14,  2,16,  13,16,
   13,31, 1,31,  0,32,  14,32, 14,15,
   1,15,  1,1,   15,1,  14,2,  2,2,
   2,14,  13,14, 15,16, 15,31, 13,33,
   1,33
};
//6 OK
static const PROGMEM byte pathMatrix6[] = { 22,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   3,22,  14,22, 15,23, 15,32, 14,33,
   1,33,  0,32,  0,1,   1,0,   3,0,
   3,2,   2,2,   2,31,  13,31, 13,24,
   3,24,  3,23,  14,23, 14,32, 1,32,
   1,1,   4,1
};
//7 OK
static const PROGMEM byte pathMatrix7[] = { 20,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   2,3,   0,3,   0,1,   1,0,   13,0,
   14,1,  14,11, 8,17,  8,32,  6,32,
   6,17,  12,11, 12,2,  1,2,   1,4,
   1,1,   13,1,  13,11, 7,17,  7,33
};
//8 OK
static const PROGMEM byte pathMatrix8[] = { 30,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   4,0,   10,0,  11,1,  11,15, 3,15,
   3,1,   10,1,  10,14, 4,14,  4,2,
   9,2,   9,14,  5,14,  5,3,   5,15,
   1,15,  13,15, 13,32, 1,32,  1,16,
   12,16, 12,31, 2,31,  2,16,  0,17,
   0,30,  3,33,  11,33, 14,30, 14,17
};
//9 OK
static const PROGMEM byte pathMatrix9[] = { 23,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   12,11, 1,11,  0,10,  0,1,   1,0,
   14,0,  15,1,  15,32, 14,33, 12,33,
   11,32, 14,32, 12,31, 13,31, 13,2,
   2,2,   2,9,   12,9,  12,10, 1,10,
   1,1,   14,1,  14,31
};


class WatchfaceMatrix : public GenericWatchface  { //
  public :
    virtual const char* name() {
      return (const char*)F("Matrix");
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
        Display.displayDrawText(28, 60, 1, Generic.buffer);
      }
      
      {//DayOfWeek
    #ifdef LANG_EN
        Display.drawDayOfWeek(6, 60, dayOfWeek, 1);
    #endif
    #ifdef LANG_RU
        Display.drawDayOfWeek(10, 60, dayOfWeek, 1);
    #endif
      }
    
    
    
      {//time
        byte hour1 = hour / 10;
        byte hour2 = hour - (hour1 * 10);
        byte minute1 = minute / 10;
        byte minute2 = minute - (minute1 * 10);
        Display.displayDrawNumber(10, 47, 18, 4, 5, animate); // :
        drawNumber(/*x*/8, /*y*/12, /*num*/hour1, /*animate*/ animate);
        drawNumber(/*x*/26, /*y*/12, /*num*/hour2, /*animate*/ animate);
        drawNumber(/*x*/54, /*y*/12, /*num*/minute1, /*animate*/ animate);
        drawNumber(/*x*/72, /*y*/12, /*num*/minute2, /*animate*/ animate);
      }
      
      Display.displayUpdate();
    }

    void drawNumber(byte x, byte y, byte num, byte animate){
      if(num == 0)
        Display.displayDrawVector(/*path*/pathMatrix0, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 1)
        Display.displayDrawVector(/*path*/pathMatrix1, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 2)
        Display.displayDrawVector(/*path*/pathMatrix2, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 3)
        Display.displayDrawVector(/*path*/pathMatrix3, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 4)
        Display.displayDrawVector(/*path*/pathMatrix4, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 5)
        Display.displayDrawVector(/*path*/pathMatrix5, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 6)
        Display.displayDrawVector(/*path*/pathMatrix6, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 7)
        Display.displayDrawVector(/*path*/pathMatrix7, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 8)
        Display.displayDrawVector(/*path*/pathMatrix8, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      if(num == 9)
        Display.displayDrawVector(/*path*/pathMatrix9, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);        
    }
    

};
#endif
