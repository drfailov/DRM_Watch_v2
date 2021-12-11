void modeInitSetup(){
  displayInit();
  displayBacklightOn();
  delay(500);
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
