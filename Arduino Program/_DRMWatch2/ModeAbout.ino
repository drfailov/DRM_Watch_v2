#include "Display.cpp"
#include "Buttons.cpp"
#include "Buzzer.cpp"

/*Used to test new functionality*/

void modeAboutSetup() {
  genericMenuSetup();
}

void modeAboutLoop() {
  if(ButtonUp.isButtonPressed()){
    Buzzer.beep();
    goToWatchface();
    return;
  } 
  if(ButtonDown.isButtonPressed()){
    Buzzer.beep();
    goToWatchface();
    return;
  } 
  
  //auto exit
  if (millis() - Generic.genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
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
  Display.displayDrawText(73, 61, 1, F("2022"));
  Display.displayDrawText(00, 61, 1, version);

  
  Display.displayDrawVector(/*path*/Display.getPathDrmWatch(), /*x*/26, /*y*/22, /*animate*/3, /*color*/1);
  Display.displayUpdate();
  for(long st = millis(); millis() - st < 900; ){
    if(ButtonUp.isButtonPressed()){
      Buzzer.beep();
      goToWatchface();
      return;
    } 
    if(ButtonDown.isButtonPressed()){
      Buzzer.beep();
      goToWatchface();
      return;
    } 
  }
  Display.displayDrawVector(/*path*/Display.getPathDrmWatch(), /*x*/26, /*y*/22, /*animate*/5, /*color*/0);
  Display.displayUpdate();
  
}

void modeAboutFinish() {

}
