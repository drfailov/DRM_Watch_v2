/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuAppsItemsCount = 5; //сколько пунктов меню в массиве

//Максимальная длина строки:              |          |
#ifdef LANG_EN
const char modeMenuAppsItem1[] PROGMEM = "Stopwatch";
const char modeMenuAppsItem2[] PROGMEM = "Alarm";
const char modeMenuAppsItem3[] PROGMEM = "Zrada";
const char modeMenuAppsItem4[] PROGMEM = "Melodies";
#endif
#ifdef LANG_RU
const char modeMenuAppsItem1[] PROGMEM = "Ceкyндoмep";
const char modeMenuAppsItem2[] PROGMEM = "Бyдильник";
const char modeMenuAppsItem3[] PROGMEM = "Зpaдa";
const char modeMenuAppsItem4[] PROGMEM = "Meлoдии";
#endif

const char* modeMenuAppsItems[] = {
  Generic.getMenuItemBack(),
  modeMenuAppsItem1,
  modeMenuAppsItem2,
  modeMenuAppsItem3,
  modeMenuAppsItem4
};


void modeMenuAppsSetup() {
  genericMenuSetup();
}

void modeMenuAppsLoop() {
  genericMenuLoop(modeMenuAppsItemsCount, modeMenuAppsItems, modeMenuAppsSelected, false);
}

void modeMenuAppsFinish() {
  genericMenuFinish();
}

void modeMenuAppsSelected(byte index) {
  if (index == 0) { //Back
    setMode(MODE_MENU_MAIN);
  }
  else if (index == 1) { //Stopwatch
    setMode(MODE_STOPWATCH);
  }
  else if (index == 2) { //alarm
    setMode(MODE_SET_ALARM);
  }
  else if (index == 3) { //Zrada
    if(millis()%2==0){
      Display.displayMessage(F("3paдa"));
    }
    else{
      Display.displayMessage(F("Пepeмoгa"));
    }
  }
  else if (index == 4) { //Melodies
    setMode(MODE_MENU_MELODIES);
  }
}
