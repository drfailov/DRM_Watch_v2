#include <Arduino.h>

#ifndef GENERICWATCHFACECPP
#define GENERICWATCHFACECPP
class GenericWatchface{ 
private: 
  //byte watchFaceCode;
  
public :
  GenericWatchface(){
    //constructor
  }
  
  byte code(){ 
    return 0;
  }
  
  const char* name(){ 
    return 0;
  }
  
  
  void drawWatchface(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate)
  {
    //draw here
  }
  
};

#endif
