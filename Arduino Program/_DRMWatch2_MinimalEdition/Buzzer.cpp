/*Global functions related to buzzer.
*/
#ifndef BUZZERCPP
#define BUZZERCPP

#include <Arduino.h>
#include "Generic.cpp"
#include "Display.cpp"
#include "myEEPROM.cpp"

class Buzzer_{
  public:
  void beepConfirm() {
    if(MyEEPROM.eepromReadSilentMode())
      return;
    pinMode(pinBuzzer, OUTPUT);
    for(byte i=2; i<5; i++){
      tone(pinBuzzer, i*1000); 
      delay(100);
      noTone(pinBuzzer);      // не пищать
      delay(100);
    }
    for(byte i=0; i<6; i++){
      Display.displayBacklightOff();
      tone(pinBuzzer, 5000);  
      delay(30);
      Display.displayBacklightOn();
      noTone(pinBuzzer);      // не пищать
      delay(30);
    }
    pinMode(pinBuzzer, INPUT);
  }
  
  void beep() {
    if(MyEEPROM.eepromReadSilentMode())
      return;
    pinMode(pinBuzzer, OUTPUT);
    tone(pinBuzzer, 2000);  
    delay(15);
    tone(pinBuzzer, 3000);  
    delay(50);
    
    noTone(pinBuzzer);
    pinMode(pinBuzzer, INPUT);
  }
};

static Buzzer_ Buzzer;
#endif
