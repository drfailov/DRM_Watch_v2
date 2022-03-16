/*Global functions related to control buttons.
*/
#ifndef BUTTONCPP
#define BUTTONCPP

#include <Arduino.h>
#include "Generic.cpp"

#define BUTTON_ACTION_NOTHING 0
#define BUTTON_ACTION_PRESS 1
#define BUTTON_ACTION_LONG 2

class Button_{
  private:
  byte pin;
  bool buttonLastValue = false;
  bool holded = false;
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
  byte isButtonPressed(){
    bool value = readDebounce();
    if(!value) holded = false;
    bool lastValue = buttonLastValue;
    buttonLastValue = value;
    bool isButtonPressDown = value && !lastValue;
    if(isButtonPressDown)
      lastTimePushDownTimeForButton = millis();

  
    if(isButtonPressDown){ //if down
      return BUTTON_ACTION_PRESS;
    }
    
    //multipress
    if(!holded && value && lastValue && millis()-lastTimePushDownTimeForButton > 500)
      return BUTTON_ACTION_PRESS;
    return BUTTON_ACTION_NOTHING;
  }

  //Вызывать после того как получен true на pressed. Выдает true после нажатия кнопку не отпускать в течении 5 секунды
  bool waitHold(){
    if(!readDebounce()) 
      return false;
    long started = millis();
    while(readDebounce() && millis() - started < 1200);
    buttonLastValue = readDebounce();
    if(buttonLastValue)
      holded = true;
    return buttonLastValue;
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
