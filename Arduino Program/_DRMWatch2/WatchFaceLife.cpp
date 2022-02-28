#include <Arduino.h>
#include "GenericWatchface.cpp"
#include "Display.cpp"
#include "RTC.cpp"
#include "Battery.cpp"
#include "MyEEPROM.cpp"


#ifndef WATCHFACELIFECPP
#define WATCHFACELIFECPP
class WatchfaceLife : public GenericWatchface  { //
  int steps = 0;
  
  public :
    virtual const char* name() {
      return (const char*)F("Life");
    }
    
    virtual const byte updateMode() {  
      return WATCHFACE_UPDATE_MODE_8S_10FRAMES;
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
      //loop every 200 steps
      if(animate) steps = 0;
      if(steps > 200) steps = 0;
      
      //if first step, fill screen with random pattern
      if(steps == 0){
        Display.displayClear();
        for(byte x = 0; x < LCD_X; x++){
          for(byte y = 0; y < LCD_Y; y++){
            bool c = micros()%3 == 0;
            Display.displaySetPixel(x,y, c);
          }
        }
      }

      //draw
      lifeStep();
      drawTime (hour, minute);
      Display.displayUpdate();
    }

    void drawTime(byte hour, byte minute){
      Display.displayFillRect(/*x*/ 29, /*y*/ 20, /*w*/ 42, /*h*/ 29, /*color*/ 0);
      Display.displayDrawRect(/*x*/ 30, /*y*/ 21, /*w*/ 40, /*h*/ 27, /*color*/ 1);
      sprintf(Generic.buffer, "%02d:%02d", hour, minute);
      Display.displayDrawText(35, 25, 1, Generic.buffer);
      Display.displayDrawBattery(39, 38);
    }

    void lifeStep(){
      steps++;
      bool lastCol [LCD_Y];
      bool currCol [LCD_Y];
      
      for(byte x = 0; x < LCD_X; x++){
        for(byte y = 0; y < LCD_Y; y++)
          lastCol[y] = currCol[y];
        for(byte y = 0; y < LCD_Y; y++)
          currCol[y] = Display.displayGetPixel(x,y);
          
        for(byte y = 0; y < LCD_Y; y++){
          bool topleft = lastCol[y-1];
          bool top = currCol[y-1];
          bool topright = Display.displayGetPixel(x + 1, y-1);
          
          bool left = lastCol[y];
          bool current = currCol[y];
          bool right = Display.displayGetPixel(x + 1, y);
          
          bool bottomleft = lastCol[y+1];
          bool bottom = currCol[y+1];
          bool bottomright = Display.displayGetPixel(x + 1, y+1);

          byte neighbours = topleft+top+topright+left+right+bottomleft+bottom+bottomright;
          
          bool c;
          if(current)
            c = (neighbours == 2 || neighbours == 3);
          else
            c = neighbours == 3;
          Display.displaySetPixel(x, y, c);
        }
      }
    }

};

#endif
