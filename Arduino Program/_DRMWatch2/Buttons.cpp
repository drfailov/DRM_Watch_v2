/*Global functions related to control buttons.
*/
#ifndef BUTTONCPP
#define BUTTONCPP

#include <Arduino.h>
#include "Generic.cpp"

class Button_{
  private:
  byte pin;
  bool buttonLastValue = false;
  long lastTimePushDownTimeForButton = 0;

  public:
  Button_(byte pin_){
    pin = pin_;
  }

  //Ткнуть мордой в тот факт что кнопка нажата или отпущена
  void refresh(){
    buttonLastValue = readDebounce();
  }

  //Выдаёт true если кнопка сейчас нажата, а во время прошлого вызова не была.
  //Если вызывать снова, начнёт выдавать true если держать кнопку полсекунды не отпуская
  bool isButtonPressed(){
    bool value = readDebounce();
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
    if(!readDebounce()) 
      return false;
    long started = millis();
    while(readDebounce() && millis() - started < 3000);
    return readDebounce();
  }

  
  
  bool readDebounce(){
    pinMode(pin, INPUT);
    delay(1);
    byte sum = 0;
    for(int i=0; i<10; i++)
      if(digitalRead(pin) == HIGH)
        sum += 1;
    return sum > 5;
  }
};

static Button_ ButtonUp(pinButtonUp);
static Button_ ButtonDown(pinButtonDown);

#endif
