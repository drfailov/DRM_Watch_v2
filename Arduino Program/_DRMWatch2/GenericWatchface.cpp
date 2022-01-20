#include <Arduino.h>

#ifndef GENERICWATCHFACECPP
#define GENERICWATCHFACECPP
class GenericWatchface{ 
private: 
  //byte watchFaceCode;
  
public :
  virtual byte code() = 0;
  virtual const char* name() = 0;
  virtual void drawWatchface(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate) = 0;
};

#endif
