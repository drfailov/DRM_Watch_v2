#include <Arduino.h>

#ifndef GENERICWATCHFACECPP
#define GENERICWATCHFACECPP
class GenericWatchface{   
public :
  virtual const char* name() = 0;
  virtual void drawWatchface(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate) = 0;
};

#endif
