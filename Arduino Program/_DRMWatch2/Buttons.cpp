/*Global functions related to control buttons.
*/
#ifndef BUTTONCPP
#define BUTTONCPP

#include <Arduino.h>
#include "Generic.cpp"
#include "MyEEPROM.cpp"

class Button_{
  private:
  byte pin;
  bool buttonLastValue = false;
  long lastTimePushDownTimeForButton = 0;

  public:
  Button_(byte pin_){
    pin = pin_;
  }
  
  bool isButtonPressed(){
    pinMode(pin, INPUT);
    delay(1);
    int sum = 0;
    for(int i=0; i<10; i++)
      if(digitalRead(pin) == HIGH)
        sum += 1;
    bool value = sum > 5;
    bool lastValue = buttonLastValue;
    buttonLastValue = value;
    bool isButtonPressDown = value && !lastValue;
  
    if(isButtonPressDown)
      lastTimePushDownTimeForButton = millis();
    if(isButtonPressDown)
      return true;
    if(value && lastValue && millis()-lastTimePushDownTimeForButton > 500)
      return true;
    return false;
  }
};

static Button_ ButtonUp(pinButtonUp);
static Button_ ButtonDown(pinButtonDown);

#endif
