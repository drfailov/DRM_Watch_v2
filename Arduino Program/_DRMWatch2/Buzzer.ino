/*Global functions related to buzzer.
*/
void beepConfirm() {
  if(eepromReadSilentMode())
    return;
  pinMode(pinBuzzer, OUTPUT);
  for(byte i=2; i<5; i++){
    tone(pinBuzzer, i*1000); 
    delay(100);
    noTone(pinBuzzer);      // не пищать
    delay(100);
  }
  for(byte i=0; i<6; i++){
    displayBacklightOff();
    tone(pinBuzzer, 5000);  
    delay(30);
    displayBacklightOn();
    noTone(pinBuzzer);      // не пищать
    delay(30);
  }
  pinMode(pinBuzzer, INPUT);
}

void beep() {
  if(eepromReadSilentMode())
    return;
  pinMode(pinBuzzer, OUTPUT);
  if(eepromReadBeepSound() == eepromBeepSoundNone){ // 4
    //play nothing
    delay(20);
  }
  else if(eepromReadBeepSound() == eepromBeepSoundClick){ // 1
    tone(pinBuzzer, 3000);  
    delay(5);
  }
  else if(eepromReadBeepSound() == eepromBeepSoundTone){ // 2
    tone(pinBuzzer, 2000);  
    delay(40);
  }
  else if(eepromReadBeepSound() == eepromBeepSoundWhistle){
    tone(pinBuzzer, 2000);  
    delay(15);
    tone(pinBuzzer, 3000);  
    delay(50);
  }
  else{//standartBeep  //0
    tone(pinBuzzer, 5000);  
    delay(15);
    tone(pinBuzzer, 3000);  
    delay(50); 
  }
  
  noTone(pinBuzzer);
  pinMode(pinBuzzer, INPUT);
}
