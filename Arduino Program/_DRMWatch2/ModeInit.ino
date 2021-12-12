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
  displayClear();
  displayDrawVector(pathZubat, 0, 10, false);
  displayDrawVector(pathDrmWatch, 48, 15, true);
}

void modeInitLoop(){
  delay(100);
  goToWatchface();
  //setMode(MODE_DEBUG_SCREEN1);
  return;
}

void modeInitFinish(){
  
}
