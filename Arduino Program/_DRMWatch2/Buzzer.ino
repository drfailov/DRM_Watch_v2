/*Global functions related to buzzer.
*/

void beepConfirm() {
  if(eepromReadSilentMode())
    return;
#ifdef LOG
  Serial.print(F("Beep init..."));
#endif
  pinMode(pinBuzzer, OUTPUT);
  for(byte i=2; i<5; i++){
    tone(pinBuzzer, i*1000);  // пищать на пине 12, 1 кГц
    delay(100);
    noTone(pinBuzzer);      // не пищать
    delay(100);
  }
  for(byte i=0; i<6; i++){
    tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
    delay(30);
    noTone(pinBuzzer);      // не пищать
    delay(30);
  }
  pinMode(pinBuzzer, INPUT);
#ifdef LOG
  Serial.println(F("OK"));
#endif
}

void beep() {
  if(eepromReadSilentMode())
    return;
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
  pinMode(pinBuzzer, INPUT);
}
