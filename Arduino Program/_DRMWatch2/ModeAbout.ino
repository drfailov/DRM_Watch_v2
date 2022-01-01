/*Used to test new functionality*/

void modeAboutSetup() {
}

void modeAboutLoop() {
  if(isButtonUpPressed()){
    beep();
    goToWatchface();
    return;
  } 
  if(isButtonDownPressed()){
    beep();
    goToWatchface();
    return;
  } 
  
  displayClear();
#ifdef LANG_EN
  displayDrawText(0, 0, 1, F("Softw: Dr.Failov"));
  displayDrawText(0, 9, 1, F("Hardw: MeltemiOS"));
#endif
#ifdef LANG_RU
  displayDrawText(0, 0, 1, F("Coфт:  Dr.Failov"));
  displayDrawText(0, 9, 1, F("Xapд:  MeltemiOS"));
#endif
  displayDrawText(74, 61, 1, F("2021"));
  displayDrawText(00, 61, 1, version);

  
  displayDrawVector(/*path*/pathDrmWatch, /*x*/26, /*y*/22, /*animate*/true, /*color*/1);
  displayUpdate();
  for(long st = millis(); millis() - st < 900; ){
    if(isButtonUpPressed()){
      beep();
      goToWatchface();
      return;
    } 
    if(isButtonDownPressed()){
      beep();
      goToWatchface();
      return;
    } 
  }
  displayDrawVector(/*path*/pathDrmWatch, /*x*/26, /*y*/22, /*animate*/true, /*color*/0);
  displayUpdate();
  
}

void modeAboutFinish() {

}
