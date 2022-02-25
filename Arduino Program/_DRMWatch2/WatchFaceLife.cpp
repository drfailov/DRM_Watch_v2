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
    virtual const bool secondsUpdate() {
      /* true - циферблат рисует секунды, требуется обновление экрана раз в секунду
       * false - циферблат не рисует секунды, можно обновлять экран реже
      */
      return false;
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
      if(animate) steps = 0;
      if(steps > 300) steps = 0;

      //fill screen with random pattern
      if(steps == 0){
        Display.displayClear();
        for(byte x = 0; x < LCD_X; x++){
          for(byte y = 0; y < LCD_Y; y++){
            bool c = micros()%3 == 0;
            Display.displaySetPixel(x,y, c);
          }
        }
      }
      
      for(byte i=0; i<10 ; i++){
        lifeStep();
        drawTime (hour, minute);
        Display.displayUpdate();
        if(ButtonUp.readDebounce() || ButtonDown.readDebounce())
          break;
      }
    }

    void drawTime(byte hour, byte minute){
      Display.displayFillRect(/*x*/ 30, /*y*/ 25, /*w*/ 39, /*h*/ 17, /*color*/ 0);
      sprintf(Generic.buffer, "%02d:%02d", hour, minute);
      Display.displayDrawText(35, 30, 1, Generic.buffer);
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
