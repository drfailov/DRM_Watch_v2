#include <Arduino.h>

#ifndef GENERICWATCHFACECPP
#define GENERICWATCHFACECPP

//Define behavior of system. Power-saving modes for watchfaces.
#define WATCHFACE_UPDATE_MODE_8S_1FRAME   (byte)0   //8S 1FRAME: draw 1 frame, then sleep for 8 seconds, then draw 1 frame, then sleep, ... The most power-efficient mode.
#define WATCHFACE_UPDATE_MODE_1S_1FRAME   (byte)1   //1S 1FRAME: draw 1 frame, then sleep for 1 second, then draw 1 frame, then sleep, ...  Not very power-efficient mode.
#define WATCHFACE_UPDATE_MODE_8S_10FRAMES (byte)2   //8S 10FRAMES: draw 10 frames (animation), then sleep for 8 seconds, then draw 10 frames, then sleep, ... Not very power-efficient mode.
#define WATCHFACE_UPDATE_MODE_1S_10FRAMES (byte)3   //1S 10FRAMES: draw 10 frames (animation), then sleep for 1 second, then draw 10 frames, then sleep, ... Not power-efficient mode.
#define WATCHFACE_UPDATE_MODE_NO_SLEEP    (byte)4   //NO SLEEP: draw frames without sleep. No any power-saving. True wasting of power.

class GenericWatchface{   
public :
  //returns visible name of watchface which will be shown at settings screen.
  //Name should not be too long, othervise it will not fit on screen.
  //Max length is 8 char
  //Example of usage:    return (const char*)F("Matrix");
  virtual const char* name() = 0;

  //Returns update mode of this watchface.
  //Update mode can be one of listed above.
  //Update mode defines how frequently drawWatchface will be called.
  //For regular watchfaces i suggest to use WATCHFACE_UPDATE_MODE_8S_1FRAME, because it the most power saving mode.
  //Example of usage:       return WATCHFACE_UPDATE_MODE_8S_1FRAME;
  virtual const byte updateMode() = 0;

  //Called every time when system needs to redraw screen.
  //Draws one frame of watchface.
  //Argument "animate" is not 0 when watchface drawn first time (after reboot or exiting menu).
  // hour, minute, second, day, month, year, dayOfWeek - current values to draw
  // animate - 0=draw without animation, 1 - animate slowly, 2 - animate more quickly, ...
  //Non-blocking function. Allowed only drawing one frame of watchface.
  //Frequency of calling this is defined by updateMode function.
  virtual void drawWatchface(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate) = 0;
};

#endif
