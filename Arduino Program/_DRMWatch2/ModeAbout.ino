bool color = 1;

void modeAboutSetup() {
  genericMenuSetup();
  color = 1;
}

void modeAboutLoop() {  
  doAutoExit();
  
  displayDrawText(0, 0, 1, F("Made by DrFailov"));
  displayDrawText(0, 8, 1, F("Made in Ukraine"));
  displayDrawText(73, 61, 1, F("2023"));
  displayDrawText(00, 61, 1, version);
  displayDrawVector(/*path*/getPathDrmWatch(), /*x*/26, /*y*/21, /*animate*/4, /*color*/color);
  displayUpdate();
  color = !color;
  for(long st = millis(); millis() - st < 900 && !color; ){
    if(isButtonUpPressed()){
      if(isButtonUpHold()){
        setMode(MODE_STATUS);
        return;
      }
      beep();
      goToWatchface();
      return;
    } 
  }
  
}

void modeAboutFinish() {

}
