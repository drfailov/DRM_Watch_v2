#include <Arduino.h>
#include "GenericWatchface.cpp"
#include "Display.cpp"
#include "RTC.cpp"
#include "Battery.cpp"
#include "MyEEPROM.cpp"


#ifndef WATCHFACENOMENSCPP
#define WATCHFACENOMENSCPP

const byte fontWtf3[] PROGMEM = {
  0b11101110, //0 
  0b00100100, //1
  0b10111010, //2
  0b10110110, //3
  0b01110100, //4 
  0b11010110, //5
  0b11011110, //6
  0b10100100, //7
  0b11111110, //8
  0b11110110 //9
};
static const PROGMEM byte pathUp[] = { 6,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   2,0,   12,0,  11,1,  3,1,   4,2,
   10,2
};
static const PROGMEM byte pathUpLeft[] = { 6,
// 00,00, 00,00, 00,00, 00,00, 00,00,
   0,1,   0,12,  1,11,  1,2,   2,3,
   2,10
};
static const PROGMEM byte pathUpRight[] = { 6,
   14,1,   14,12,  13,11,  13,2,  12,3,
   12,10
};
static const PROGMEM byte pathCenter[] = { 6,
   3,12,   11,12,  12,13,  2,13,  3,14,
   11,14
};
static const PROGMEM byte pathBottomLeft[] = { 6,
   0,14,   0,27,   1,26,   1,15,  2,16,
   2,25
};
static const PROGMEM byte pathBottomRight[] = { 6,
   14,14,  14,27,  13,26,  13,15, 12,16,
   12,25
};
static const PROGMEM byte pathBottom[] = { 6,
   2,28,   12,28,  11,27,  3,27,  4,26,
   10,26
};

class WatchfaceNomens : public GenericWatchface  { //
  public :
    virtual const char* name() {
      return (const char*)F("Nomens");
    }
    
    virtual const byte updateMode() {  
      return WATCHFACE_UPDATE_MODE_8S_1FRAME;
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


      {//треугольничек с полосочкой рисуем
        byte X = 63;
        byte Y = 54;
        for(byte i=1; i<14; i++){
           Display.displayDrawLine(/*X1*/X+i, /*Y1*/Y+i, /*X2*/96, /*Y2*/Y+i, /*C*/1);
        }
        Display.displayDrawLine(/*X1*/0, /*Y1*/Y, /*X2*/96, /*Y2*/Y, /*C*/1);
      }
       
      {//date
        sprintf(Generic.buffer, Generic.getDateFormat(), day, month, year);
        Display.displayDrawText(3, 58, 1, Generic.buffer);
      }
      
      {//DayOfWeek
    #ifdef LANG_EN
        Display.drawDayOfWeek(76, 58, dayOfWeek, 0);
    #endif
    #ifdef LANG_RU
        Display.drawDayOfWeek(80, 58, dayOfWeek, 0);
    #endif
      }
    
      byte X = 96;
      
      {//battery
        X -= 17;
        Display.displayDrawBattery(X, 0);
        if(!Battery.batteryIsCharging() && !Battery.batteryIsLowPower()) X += 5;
      }
    
      
      //Alert sign
      if(MyEEPROM.eepromReadAlertEnabled()){ 
        X-= 13;
        Display.displayDrawAlertSign(X, 0, 1);
      }
    
      
      //Silent mode sign
      if(MyEEPROM.eepromReadSilentMode()){ 
        X -= 12;
        Display.displayDrawSilentModeIcon(X, 0, 1);
      }
      
    
    
      {//time
        byte hour1 = hour / 10;
        byte hour2 = hour - (hour1 * 10);
        byte minute1 = minute / 10;
        byte minute2 = minute - (minute1 * 10);
        Display.displayDrawNumber(10, 46, 18, 4, 5, animate); // :
//        Display.displayFillRect(/*x*/46, /*y*/24, /*w*/3, /*h*/3, /*c*/1);
//        Display.displayFillRect(/*x*/46, /*y*/35, /*w*/3, /*h*/3, /*c*/1);
        drawNumber(/*x*/8, /*y*/14, /*num*/hour1, /*animate*/ animate);
        drawNumber(/*x*/26, /*y*/14, /*num*/hour2, /*animate*/ animate);
        drawNumber(/*x*/54, /*y*/14, /*num*/minute1, /*animate*/ animate);
        drawNumber(/*x*/72, /*y*/14, /*num*/minute2, /*animate*/ animate);
      }
      
      Display.displayUpdate();
    }

    void drawNumber(byte x, byte y, byte num, byte animate){
      byte b = pgm_read_byte(&fontWtf3[num]);
      if(bitRead(b, 7)){ 
        Display.displayDrawVector(/*path*/pathUp, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      }
      if(bitRead(b, 6)){ 
        Display.displayDrawVector(/*path*/pathUpLeft, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      }
      if(bitRead(b, 5)){ 
        Display.displayDrawVector(/*path*/pathUpRight, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      }
      if(bitRead(b, 4)){ 
        Display.displayDrawVector(/*path*/pathCenter, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      }
      if(bitRead(b, 3)){ 
        Display.displayDrawVector(/*path*/pathBottomLeft, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      }
      if(bitRead(b, 2)){ 
        Display.displayDrawVector(/*path*/pathBottomRight, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      }
      if(bitRead(b, 1)){ 
        Display.displayDrawVector(/*path*/pathBottom, /*x*/x, /*y*/y, /*animate*/animate, /*color*/1);
      }
    }
    

};

#endif