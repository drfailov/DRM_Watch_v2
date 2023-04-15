

/*Mode is initial. Needed to init modules and welcome message.*/

void modeInitSetup(){
  displayInit();
  displayBacklightOn();

  //------------------ DRM WATCH PLAYGROUND


  //------------------ END DRM WATCH PLAYGROUND
  
  displayClear();
  displayDrawText(67, 61, 1, version);
  displayDrawVector(/*path*/getPathZubat(), /*x*/25, /*y*/10, /*animate*/false, /*color*/1);
  displayUpdate();
  
  beepConfirm();
  for(byte x=25; x > 0; x -= 5){
    displayClear();
    displayDrawText(67, 61, 1, version);
    displayDrawVector(/*path*/getPathZubat(), /*x*/x, /*y*/10, /*animate*/false, /*color*/1);
    displayUpdate();
  }
  displayClear();
  displayDrawText(67, 61, 1, version);
  displayDrawVector(/*path*/getPathZubat(), /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
  displayDrawVector(/*path*/getPathDrmWatch(), /*x*/48, /*y*/15, /*animate*/4, /*color*/1);
  displayUpdate();
  
  displaySimpleMessage("RTC Init");
  rtcInit();

//  for(int i=0; i< 5; i++){
//    displayMessage (F("Срочно"));
//    displayMessage (F("Иди нахуй"));
//  }

    //eepromFIllByOnes();
}

void modeInitLoop(){
  delay(200);
  goToWatchface();
}

void modeInitFinish(){
  
}
