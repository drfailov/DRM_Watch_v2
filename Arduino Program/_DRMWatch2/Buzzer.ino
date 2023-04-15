/*Global functions related to buzzer.
*/
void buzzerInit(){
  pinMode(pinBuzzer, OUTPUT);
}

void beepConfirm() {
  if(eepromReadSilentMode())
    return;
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
  //pinMode(pinBuzzer, INPUT);
}

void beep() {
  if(eepromReadSilentMode())
    return;
    
  //click (1)
//  tone(pinBuzzer, 3000);  
//  delay(5);
    
  //tone (2)
//  tone(pinBuzzer, 2000);  
//  delay(40);
  
  // whistle (3)
  tone(pinBuzzer, 2000);  
  delay(15);
  tone(pinBuzzer, 3000);  
  delay(50);
  
  //  standartBeep  
//  tone(pinBuzzer, 5000);  
//  delay(15);
//  tone(pinBuzzer, 3000);  
//  delay(50); 
  noTone(pinBuzzer);
}
