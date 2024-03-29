#include <Arduino.h>
#include "GenericWatchface.cpp"
#include "Display.cpp"
#include "RTC.cpp"
#include "Battery.cpp"
#include "MyEEPROM.cpp"


#ifndef WATCHFACECALIBRICPP
#define WATCHFACECALIBRICPP

// 'calibri0', 17x23px
const unsigned char  calibri0 [] PROGMEM = {
  0x80, 0xf0, 0xfc, 0xfe, 0xfe, 0x3f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0xff, 0xfe, 0xfc, 0xf8, 
  0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x01, 0x0f, 0x1f, 0x3f, 0x7f, 0x7e, 0x78, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x7f, 0x3f, 
  0x1f, 0x0f, 0x01
};
// 'calibri1', 17x23px
const unsigned char  calibri1 [] PROGMEM = {
  0x00, 0x00, 0x78, 0x38, 0x3c, 0x1c, 0x1e, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78, 0x78, 0x78, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x78, 0x78, 
  0x78, 0x78, 0x20
};
// 'calibri2', 17x23px
const unsigned char  calibri2 [] PROGMEM = {
  0x00, 0x3c, 0x1e, 0x1e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfe, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 
  0x00, 0x00, 0x00, 0x7c, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7b, 0x79, 0x78, 0x78, 0x78, 0x78, 0x78, 
  0x78, 0x78, 0x70
};
// 'calibri3', 17x23px
const unsigned char  calibri3 [] PROGMEM = {
  0x00, 0x1c, 0x1e, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0x20, 
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c, 0x1c, 0x1e, 0x1e, 0x3f, 0x7f, 0xff, 0xff, 0xf3, 0xf1, 
  0xe0, 0x80, 0x00, 0x3c, 0x78, 0x78, 0x78, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x7f, 0x3f, 0x3f, 
  0x1f, 0x0f, 0x03
};
// 'calibri4', 17x23px
const unsigned char  calibri4 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfe, 0x3f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 
  0x00, 0xe0, 0xf8, 0xfc, 0xff, 0x9f, 0x87, 0x83, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x80, 0x80, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x03, 0x03
};
// 'calibri5', 17x23px
const unsigned char  calibri5 [] PROGMEM = {
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 
  0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x0f, 0x0e, 0x0e, 0x1e, 0x1e, 0x3e, 0xfe, 0xfc, 0xfc, 0xf8, 
  0xf0, 0x80, 0x00, 0x3c, 0x78, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x7f, 0x3f, 0x3f, 
  0x1f, 0x0f, 0x00
};
// 'calibri6', 17x23px
const unsigned char  calibri6 [] PROGMEM = {
  0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfe, 0x1e, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0e, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x1c, 0x1e, 0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0xfe, 0xfe, 0xfc, 
  0xfc, 0xf0, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 0x7f, 0x78, 0x70, 0x70, 0x70, 0x78, 0x78, 0x7f, 0x3f, 
  0x3f, 0x0f, 0x07
};
// 'calibri7', 17x23px
const unsigned char  calibri7 [] PROGMEM = {
  0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xcf, 0xff, 0xff, 0xff, 0xff, 0x3f, 
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x01, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x78, 0x7e, 0x7f, 0x7f, 0x3f, 0x0f, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00
};
// 'calibri8', 17x23px
const unsigned char  calibri8 [] PROGMEM = {
  0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x9f, 0xff, 0xfe, 0xfe, 0xfc, 
  0x00, 0x00, 0xc1, 0xe3, 0xf7, 0xf7, 0x7f, 0x3f, 0x3e, 0x1e, 0x3e, 0x3f, 0x7f, 0xff, 0xf3, 0xf1, 
  0xe0, 0x80, 0x0f, 0x1f, 0x3f, 0x7f, 0x7f, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7f, 0x7f, 
  0x3f, 0x1f, 0x0f
};
// 'calibri9', 17x23px
const unsigned char  calibri9 [] PROGMEM = {
  0xe0, 0xf8, 0xfc, 0xfe, 0xfe, 0x1f, 0x0f, 0x07, 0x07, 0x0f, 0x0f, 0x3f, 0xfe, 0xfe, 0xfc, 0xf8, 
  0x80, 0x03, 0x0f, 0x1f, 0x3f, 0x3f, 0x3c, 0x78, 0x78, 0x78, 0x38, 0x38, 0x3c, 0xff, 0xff, 0xff, 
  0xff, 0x7f, 0x00, 0x38, 0x78, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x3f, 0x3f, 0x1f, 
  0x0f, 0x03, 0x00
};



class WatchfaceCalibri : public GenericWatchface  { //
  public :
    virtual const char* name() {
      return (const char*)F("Calibri");
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
          Display.displayDrawText(0, 0, 1, Generic.buffer);
        }
        
        {//DayOfWeek
          Display.drawDayOfWeek(79, 0, dayOfWeek, /*color*/1);
        }
        
        {//Temperature
          float temp = RTC.rtcGetTemp();
          /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
          dtostrf(temp, 4, 1, Generic.buffer);
          sprintf(Generic.buffer, "%sC", Generic.buffer);
          Display.displayDrawText(0, 61, 1, Generic.buffer);
        }
      
        byte X = 96;
        
        {//battery
          X -= 17;
          Display.displayDrawBattery(X, 61);
          if(!Battery.batteryIsCharging() && !Battery.batteryIsLowPower()) X += 5;
        }
        
        //Silent mode sign
        if(MyEEPROM.eepromReadSilentMode()){ 
          X -= 10;
          Display.displayDrawSilentModeIcon(X, 61, 1);
        }
        
        //Alert sign
        if(MyEEPROM.eepromReadAlertEnabled()){ 
          X-= 11;
          Display.displayDrawAlertSign(X, 61, 1);
        }
        
        
        { //time
          byte hour1 = hour / 10;
          byte hour2 = hour - (hour1 * 10);
          byte minute1 = minute / 10;
          byte minute2 = minute - (minute1 * 10);

          drawNumber(/*x*/8, /*y*/20, /*num*/hour1, /*animate*/ animate);
          drawNumber(/*x*/27, /*y*/20, /*num*/hour2, /*animate*/ animate);
          //Display.displayDrawNumber(/*num*/10, /*x*/46, /*y*/20, /*w*/5, /*h*/5, animate); // :
          drawNumber(/*x*/53, /*y*/20, /*num*/minute1, /*animate*/ animate);
          drawNumber(/*x*/72, /*y*/20, /*num*/minute2, /*animate*/ animate);
        }
        
        Display.displayUpdate();
    }

    

    void drawNumber(byte x, byte y, byte num, byte animate){
      if(num == 0)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri0, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 1)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri1, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 2)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri2, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 3)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri3, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 4)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri4, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 5)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri5, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 6)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri6, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 7)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri7, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 8)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri8, /*w*/17, /*h*/23, /*COLOR*/1);
      if(num == 9)
        Display.displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri9, /*w*/17, /*h*/23, /*COLOR*/1);
      if(animate)
        Display.displayUpdate();
    }

};

#endif
