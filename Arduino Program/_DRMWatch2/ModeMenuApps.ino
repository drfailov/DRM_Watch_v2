/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuAppsItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:              |          |
#ifdef LANG_EN
const char modeMenuAppsItem1[] PROGMEM = "Status";
const char modeMenuAppsItem2[] PROGMEM = "Melodies";
const char modeMenuAppsItem3[] PROGMEM = "Stopwatch";
const char modeMenuAppsItem4[] PROGMEM = "Alarm";
const char modeMenuAppsItem5[] PROGMEM = "Zrada";
#endif
#ifdef LANG_RU
const char modeMenuAppsItem1[] PROGMEM = "Cтaтyc";
const char modeMenuAppsItem2[] PROGMEM = "Meлoдии";
const char modeMenuAppsItem3[] PROGMEM = "Ceкyндoмep";
const char modeMenuAppsItem4[] PROGMEM = "Бyдильник";
const char modeMenuAppsItem5[] PROGMEM = "Зpaдa";
#endif

const char* modeMenuAppsItems[] = {
  Generic.getMenuItemBack(),
  modeMenuAppsItem1,
  modeMenuAppsItem2,
  modeMenuAppsItem3,
  modeMenuAppsItem4,
  modeMenuAppsItem5
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
  else if (index == 1) { //Status screen
    setMode(MODE_STATUS);
  }
  else if (index == 2) { //Melodies
    setMode(MODE_MENU_MELODIES);
  }
  else if (index == 3) { //Stopwatch
    setMode(MODE_STOPWATCH);
  }
  else if (index == 4) { //alarm
    setMode(MODE_SET_ALARM);
  }
  else if (index == 5) { //Zrada
    if(millis()%2==0){
      Display.displayMessage(F("3paдa"));
    }
    else{
      Display.displayMessage(F("Пepeмoгa"));
    }
  }
}
