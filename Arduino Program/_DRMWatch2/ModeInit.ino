/*Mode is initial. Needed to init modules and welcome message.*/

void modeInitSetup(){
  displayInit();
  displayBacklightOn();
  displaySimpleMessage("RTC Init");
  rtcInit();
  displayClear();
  displayDrawText(66, 61, 1, version);
  displayDrawVector(/*path*/pathZubat, /*x*/24, /*y*/10, /*animate*/false, /*color*/1);
  displayUpdate();
  beepConfirm();
  for(byte x=24; x > 0; x -= 4){
    displayClear();
  displayDrawText(66, 61, 1, version);
    displayDrawVector(/*path*/pathZubat, /*x*/x, /*y*/10, /*animate*/false, /*color*/1);
    displayUpdate();
  }
  displayClear();
  displayDrawText(66, 61, 1, version);
  displayDrawVector(/*path*/pathZubat, /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
  displayDrawVector(/*path*/pathDrmWatch, /*x*/48, /*y*/15, /*animate*/true, /*color*/1);
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
