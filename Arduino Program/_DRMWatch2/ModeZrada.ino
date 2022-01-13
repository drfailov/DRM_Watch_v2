/*Used to test new functionality*/
#define MODE_ZRADA_STATE_NONE  0
#define MODE_ZRADA_STATE_PEREMOGA  1
#define MODE_ZRADA_STATE_ZRADA  2
byte modeZradaState = MODE_ZRADA_STATE_NONE;


void modeZradaSetup() {
}

void modeZradaLoop() {
  if (isButtonDownPressed()) {
    beep();
    goToWatchface();
    return;
  }
  if (isButtonUpPressed()) {
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
//  displayClear();
//  if (modeZradaState == MODE_ZRADA_STATE_NONE) {
//    displayDrawText(60, 20, 1, F("---"));
//  }
//  else if (modeZradaState == MODE_ZRADA_STATE_ZRADA) {
//#ifdef LANG_EN
//    displayDrawText(55, 20, 1, F("Zrada"));
//#endif
//#ifdef LANG_RU
//    displayDrawText(55, 20, 1, F("Зрада"));
//#endif
//  }
//  else if (modeZradaState == MODE_ZRADA_STATE_PEREMOGA) {
//#ifdef LANG_EN
//    displayDrawText(45, 20, 1, F("Peremoga"));
//#endif
//#ifdef LANG_RU
//    displayDrawText(45, 20, 1, F("Перемога"));
//#endif
//  }
//  if(drawZubat){
//    displayDrawVector(/*path*/getPathZubat(), /*x*/5, /*y*/10, /*animate*/false, /*color*/1);
//    displayDrawPlaySign(/*X*/2, /*Y*/2, 1);
//    displayDrawCheck(/*X*/1, /*Y*/59, 1);
//  }
//  displayUpdate();
}

void modeZradaFinish() {

}
