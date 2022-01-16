#include "Display.cpp"

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
  
  Display.displayClear();
#ifdef LANG_EN
  Display.displayDrawText(0, 0, 1, F("Softw: Dr.Failov"));
  Display.displayDrawText(0, 9, 1, F("Hardw: MeltemiOS"));
#endif
#ifdef LANG_RU
  Display.displayDrawText(0, 0, 1, F("Coфт:  Dr.Failov"));
  Display.displayDrawText(0, 9, 1, F("Xapд:  MeltemiOS"));
#endif
  Display.displayDrawText(74, 61, 1, F("2022"));
  Display.displayDrawText(00, 61, 1, version);

  
  Display.displayDrawVector(/*path*/Display.getPathDrmWatch(), /*x*/26, /*y*/22, /*animate*/3, /*color*/1);
  Display.displayUpdate();
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
  Display.displayDrawVector(/*path*/Display.getPathDrmWatch(), /*x*/26, /*y*/22, /*animate*/5, /*color*/0);
  Display.displayUpdate();
  
}

void modeAboutFinish() {

}
