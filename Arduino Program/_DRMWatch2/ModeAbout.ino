#include "Display.cpp"
#include "Buttons.cpp"
#include "Buzzer.cpp"

/*Used to test new functionality*/

bool color = 1;

void modeAboutSetup() {
  genericMenuSetup();
  Display.displayClear();
  color = 1;
}

void modeAboutLoop() {  
  //auto exit
  if (millis() - Generic.genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }
  
#ifdef LANG_EN
  Display.displayDrawText(0, 0, 1, F("Softw: Dr.Failov"));
#endif
#ifdef LANG_RU
  Display.displayDrawText(0, 0, 1, F("Coфт:  Dr.Failov"));
#endif
  Display.displayDrawText(73, 61, 1, F("2022"));
  Display.displayDrawText(00, 61, 1, version);

  
  Display.displayDrawVector(/*path*/Display.getPathDrmWatch(), /*x*/26, /*y*/17, /*animate*/4, /*color*/color);
  Display.displayUpdate();
  color = !color;
  for(long st = millis(); millis() - st < 900 && !color; ){
    if(ButtonUp.isButtonPressed() || ButtonDown.isButtonPressed()){
      if(ButtonUp.waitHold() || ButtonDown.waitHold()){
        setMode(MODE_STATUS);
        return;
      }
      Buzzer.beep();
      goToWatchface();
      return;
    } 
  }
  
}

void modeAboutFinish() {

}
