/*Global functions related to buzzer.
*/

void beepConfirm() {
  Serial.print(F("Beep confirm..."));
  pinMode(pinBuzzer, OUTPUT);

  tone(pinBuzzer, 2000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 3000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 4000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  Serial.println(F("OK"));
}



void beepAlert() {
  Serial.print(F("Beep alert..."));
  pinMode(pinBuzzer, OUTPUT);

  tone(pinBuzzer, 1000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 2000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 3000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 4000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 3000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 2000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 1000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать

  Serial.println(F("OK"));
}

void beep() {
  pinMode(pinBuzzer, OUTPUT);
  if(eepromReadBeepSound() == eepromBeepSoundNone){
    //play nothing
  }
  else if(eepromReadBeepSound() == eepromBeepSoundClick){
    tone(pinBuzzer, 1500);  
    delay(1);
  }
  else if(eepromReadBeepSound() == eepromBeepSoundTone){
    tone(pinBuzzer, 1000);  
    delay(150);
  }
  else if(eepromReadBeepSound() == eepromBeepSoundWhistle){
    tone(pinBuzzer, 2000);  
    delay(40);
    tone(pinBuzzer, 3000);  
    delay(40);
  }
  else{//standartBeep
    tone(pinBuzzer, 1500);  
    delay(80);
  }
  noTone(pinBuzzer);
}
