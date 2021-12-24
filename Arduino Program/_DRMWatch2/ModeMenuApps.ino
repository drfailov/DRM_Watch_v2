/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuAppsItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:              |          |
#ifdef LANG_EN
const char modeMenuAppsItem1[] PROGMEM = "Debug view";
const char modeMenuAppsItem2[] PROGMEM = "Melodies";
const char modeMenuAppsItem3[] PROGMEM = "Stopwatch";
const char modeMenuAppsItem4[] PROGMEM = "Alarm";
const char modeMenuAppsItem5[] PROGMEM = "Zrada";
const char modeMenuAppsItem6[] PROGMEM = "Svaston";
const char modeMenuAppsItem7[] PROGMEM = "< Back";
#endif
#ifdef LANG_RU
const char modeMenuAppsItem1[] PROGMEM = "Отладка";
const char modeMenuAppsItem2[] PROGMEM = "Мелодии";
const char modeMenuAppsItem3[] PROGMEM = "Секундомер";
const char modeMenuAppsItem4[] PROGMEM = "Будильник";
const char modeMenuAppsItem5[] PROGMEM = "Зрада";
const char modeMenuAppsItem6[] PROGMEM = "Свастон";
const char modeMenuAppsItem7[] PROGMEM = "< Назад";
#endif

const char* const modeMenuAppsItems[] PROGMEM = {
  modeMenuAppsItem1,
  modeMenuAppsItem2,
  modeMenuAppsItem3,
  modeMenuAppsItem4,
  modeMenuAppsItem5,
  modeMenuAppsItem6,
  modeMenuAppsItem7
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
    setMode(MODE_DEBUG_SCREEN1);
    return;
  }
  
  if (index == 1) { //Melodies
    setMode(MODE_MENU_MELODIES);
    return;
  }
  
  if (index == 2) { //Stopwatch
    setMode(MODE_STOPWATCH);
    return;
  }
  
  if (index == 3) { //alarm
    setMode(MODE_SET_ALARM);
  }
  
  if (index == 4) { //Zrada
    displayMessage(F("В разработке!"));
  }
  
  if (index == 5) { //Svaston
    displayMessage(F("В разработке!"));
  } 
  
  if (index == 6) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
