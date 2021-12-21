/*Show main menu by triggerimg GenericMenu*/
const int modeMenuMainItemsCount = 4; //сколько пунктов меню в массиве

//Максимальная длина строки:             |          |
#ifdef LANG_EN
const char modeMenuMainItem1[] PROGMEM = "Apps";
const char modeMenuMainItem2[] PROGMEM = "Settings";
const char modeMenuMainItem3[] PROGMEM = "About";
const char modeMenuMainItem4[] PROGMEM = "< Exit";
#endif
#ifdef LANG_RU
const char modeMenuMainItem1[] PROGMEM = "Приложения";
const char modeMenuMainItem2[] PROGMEM = "Настройки";
const char modeMenuMainItem3[] PROGMEM = "О программе";
const char modeMenuMainItem4[] PROGMEM = "< Выход";
#endif

const char* const modeMenuMainItems[] PROGMEM = {
  modeMenuMainItem1,
  modeMenuMainItem2,
  modeMenuMainItem3,
  modeMenuMainItem4
};


void modeMenuMainSetup() {
  genericMenuSetup();
}

void modeMenuMainLoop() {
  genericMenuLoop(modeMenuMainItemsCount, modeMenuMainItems, modeMenuMainSelected);
}

void modeMenuMainFinish() {
  genericMenuFinish();
}

void modeMenuMainSelected(byte index) {
  if (index == 0) { //Apps
    setMode(MODE_MENU_APPS);
    return;
  }

  if (index == 1) { //Settings
    setMode(MODE_MENU_SETTINGS);
    return;
  }

  if (index == 2) { //About
    setMode(MODE_ABOUT);
    return;
  }

  if (index == 3) { //Exit
    goToWatchface();
    return;
  }
}
