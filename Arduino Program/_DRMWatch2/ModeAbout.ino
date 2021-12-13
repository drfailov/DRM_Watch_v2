/*Used to test new functionality*/

void modeAboutSetup() {
}

void modeAboutLoop() {
  if(isButtonUpPressed()){
    beep();
  }
  if(isButtonDownPressed()){
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  } 
  
  displayClear();
  displayDrawText(0, 0, 1,  F("Softw: Dr.Failov"));
  displayDrawText(0, 9, 1, F("Hardw: MeltemiOS"));
  displayDrawText(74, 61, 1, F("2021"));
  displayDrawCheck(0, 61);


  
  displayDrawVector(/*path*/pathDrmWatch, /*x*/26, /*y*/23, /*animate*/true, /*color*/1);
  if(isButtonDownPressed()){
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  } 
  displayDrawVector(/*path*/pathDrmWatch, /*x*/26, /*y*/23, /*animate*/true, /*color*/0);
  displayUpdate();
  
}

void modeAboutFinish() {

}
