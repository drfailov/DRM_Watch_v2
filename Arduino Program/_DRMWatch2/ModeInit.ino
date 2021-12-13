/*Mode is initial. Needed to init modules and welcome message.*/

void modeInitSetup(){
  displayInit();
  displayBacklightOn();
  displayMessage("RTC Init...");
  rtcInit();
  displayClear();
  displayDrawVector(pathZubat, 20, 10, false);
  displayUpdate();
  beepConfirm();
  for(byte x=20; x > 0; x -= 5){
    displayClear();
    displayDrawVector(pathZubat, x, 10, false);
    displayUpdate();
  }
  displayClear();
  displayDrawVector(pathZubat, 0, 10, false);
  displayDrawVector(pathDrmWatch, 48, 15, true);
  delay(200);
}

void modeInitLoop(){
  delay(100);
  goToWatchface();
  //setMode(MODE_DEBUG_SCREEN1);
  return;
}

void modeInitFinish(){
  
}
