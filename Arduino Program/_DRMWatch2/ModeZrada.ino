/*Used to test new functionality*/
#include "Display.cpp"
#include "Buttons.cpp"

#define MODE_ZRADA_STATE_NONE  0
#define MODE_ZRADA_STATE_PEREMOGA  1
#define MODE_ZRADA_STATE_ZRADA  2
byte modeZradaState = MODE_ZRADA_STATE_NONE;


void modeZradaSetup() {
  modeZradaState = MODE_ZRADA_STATE_NONE;
  randomSeed(analogRead(0));
}

void modeZradaLoop() {
  if (ButtonDown.isButtonPressed()) {
    beep();
    goToWatchface();
    return;
  }
  if (ButtonUp.isButtonPressed()) {
    beep();
    for(byte i=0; i<20; i++){
      modeZradaState = 1+ (i%2);
      modeZradaDraw(false);
    }
    modeZradaState = 1+ (rand()%2);
    return;
  }


  modeZradaDraw(true);
}


void modeZradaDraw(bool drawZubat) {
  Display.displayClear();
  if (modeZradaState == MODE_ZRADA_STATE_NONE) {
    Display.displayDrawText(60, 20, 1, F("---"));
  }
  else if (modeZradaState == MODE_ZRADA_STATE_ZRADA) {
#ifdef LANG_EN
    Display.displayDrawText(55, 20, 1, F("Zrada"));
#endif
#ifdef LANG_RU
    Display.displayDrawText(55, 20, 1, F("Зрада"));
#endif
  }
  else if (modeZradaState == MODE_ZRADA_STATE_PEREMOGA) {
#ifdef LANG_EN
    Display.displayDrawText(45, 20, 1, F("Peremoga"));
#endif
#ifdef LANG_RU
    Display.displayDrawText(45, 20, 1, F("Перемога"));
#endif
  }
  if(drawZubat){
    Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/5, /*y*/10, /*animate*/false, /*color*/1);
    Display.displayDrawPlaySign(/*X*/2, /*Y*/2, 1);
    Display.displayDrawCheck(/*X*/1, /*Y*/59, 1);
  }
  Display.displayUpdate();
}

void modeZradaFinish() {

}
