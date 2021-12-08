void modeInitSetup(){
  displayInit();
  displayBacklightOn();
  displayMessage("RTC Init...");
  rtcInit();
  displayMessage("RTC OK");
  beepConfirm();
  //displayBacklightOff();
}

void modeInitLoop(){
  delay(100);
  goToWatchface();
  return;
}

void modeInitFinish(){
  
}
