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

  //Выдаёт true если кнопка сейчас нажата, а во время прошлого вызова не была.
  //Если вызывать снова, начнёт выдавать true если держать кнопку полсекунды не отпуская
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

  //Вызывать после того как получен true на pressed. Выдает true после нажатия кнопку не отпускать в течении 5 секунды
  bool isButtonHold(){
    long started = millis();
    while(digitalRead(pin) == HIGH && millis() - started < 5000);
    return digitalRead(pin) == HIGH;
  }
};

static Button_ ButtonUp(pinButtonUp);
static Button_ ButtonDown(pinButtonDown);

#endif
