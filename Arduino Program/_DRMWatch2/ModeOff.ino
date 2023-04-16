void(* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0


void modeOffInit(){
  displayPowerOff();
  displayBacklightOff();
  delay(500);
  attachInterrupt(1, wakeToCheckButton, RISING); //down
  attachInterrupt(0, wakeToCheckButton, RISING);  //up
  
}

void modeOffLoop(){
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  if (isButtonUpHold()) {
    resetFunc();
  }
}


void wakeToCheckButton(){
}
