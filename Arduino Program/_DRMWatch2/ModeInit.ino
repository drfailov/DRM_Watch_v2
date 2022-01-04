/*Mode is initial. Needed to init modules and welcome message.*/

void modeInitSetup(){
  displayInit();
  displayBacklightOn();
  displaySimpleMessage("RTC Init");
  rtcInit();
  displayClear();
  displayDrawText(66, 61, 1, version);
  displayDrawVector(/*path*/getPathZubat(), /*x*/25, /*y*/10, /*animate*/6, /*color*/1);
  displayUpdate();
  beepConfirm();
  for(byte x=25; x > 0; x -= 5){
    displayClear();
    displayDrawText(66, 61, 1, version);
    displayDrawVector(/*path*/getPathZubat(), /*x*/x, /*y*/10, /*animate*/false, /*color*/1);
    displayUpdate();
  }
  displayClear();
  displayDrawText(66, 61, 1, version);
  displayDrawVector(/*path*/pathZubat, /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
  displayDrawVector(/*path*/pathDrmWatch, /*x*/48, /*y*/15, /*animate*/4, /*color*/1);
  displayUpdate();
}

void modeInitLoop(){
  delay(300);
  goToWatchface();
}

void modeInitFinish(){
  
}
