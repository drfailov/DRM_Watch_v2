/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuAppsItemsCount = 7; //сколько пунктов меню в массиве

//Максимальная длина строки:              |          |
#ifdef LANG_EN
const char modeMenuAppsItem1[] PROGMEM = "Status";
const char modeMenuAppsItem2[] PROGMEM = "Melodies";
const char modeMenuAppsItem3[] PROGMEM = "Stopwatch";
const char modeMenuAppsItem4[] PROGMEM = "Alarm";
const char modeMenuAppsItem5[] PROGMEM = "Zrada";
const char modeMenuAppsItem6[] PROGMEM = "Svaston";
#endif
#ifdef LANG_RU
const char modeMenuAppsItem1[] PROGMEM = "Cтaтyc";
const char modeMenuAppsItem2[] PROGMEM = "Meлoдии";
const char modeMenuAppsItem3[] PROGMEM = "Ceкyндoмep";
const char modeMenuAppsItem4[] PROGMEM = "Бyдильник";
const char modeMenuAppsItem5[] PROGMEM = "Зpaдa";
const char modeMenuAppsItem6[] PROGMEM = "Cвacтoн";
#endif

const char* const modeMenuAppsItems[] PROGMEM = {
  modeMenuAppsItem1,
  modeMenuAppsItem2,
  modeMenuAppsItem3,
  modeMenuAppsItem4,
  modeMenuAppsItem5,
  modeMenuAppsItem6,
  menuItemBack
};


void modeMenuAppsSetup() {
  genericMenuSetup();
}

void modeMenuAppsLoop() {
  genericMenuLoop(modeMenuAppsItemsCount, modeMenuAppsItems, modeMenuAppsSelected);
}

void modeMenuAppsFinish() {
  genericMenuFinish();
}

void modeMenuAppsSelected(byte index) {
  
  if (index == 0) { //Debug screen
    setMode(MODE_STATUS);
  }
  else if (index == 1) { //Melodies
    setMode(MODE_MENU_MELODIES);
  }
  else if (index == 2) { //Stopwatch
    setMode(MODE_STOPWATCH);
  }
  else if (index == 3) { //alarm
    setMode(MODE_SET_ALARM);
  }
  else if (index == 4) { //Zrada
    displayMessage(F("B paзpaбoткe!"));
  }
  else if (index == 5) { //Svaston
    displayMessage(F("B paзpaбoткe!"));
  } 
  else if (index == 6) { //Back
    setMode(MODE_MENU_MAIN);
  }
}
