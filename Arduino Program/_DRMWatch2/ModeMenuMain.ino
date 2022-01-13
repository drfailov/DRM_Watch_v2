/*Show main menu by triggerimg GenericMenu*/
const int modeMenuMainItemsCount = 4; //сколько пунктов меню в массиве

//Максимальная длина строки:             |          |
#ifdef LANG_EN
const char modeMenuMainItem1[] PROGMEM = "Apps";
const char modeMenuMainItem2[] PROGMEM = "Settings";
const char modeMenuMainItem3[] PROGMEM = "About";
#endif
#ifdef LANG_RU
const char modeMenuMainItem1[] PROGMEM = "Пpилoжeния";
const char modeMenuMainItem2[] PROGMEM = "Hacтpoйки";
const char modeMenuMainItem3[] PROGMEM = "O пpoгpaммe";
#endif

const char* const modeMenuMainItems[] PROGMEM = {
  modeMenuMainItem1,
  modeMenuMainItem2,
  modeMenuMainItem3,
  menuItemBack
};


void modeMenuMainSetup() {
  genericMenuSetup();
}

void modeMenuMainLoop() {
  genericMenuLoop(modeMenuMainItemsCount, modeMenuMainItems, modeMenuMainSelected, true);
}

void modeMenuMainFinish() {
  genericMenuFinish();
}

void modeMenuMainSelected(byte index) {
  if (index == 0) { //Apps
    setMode(MODE_MENU_APPS);
  }
  else if (index == 1) { //Settings
    setMode(MODE_MENU_SETTINGS);
  }
  else if (index == 2) { //About
    setMode(MODE_ABOUT);
  }
  else if (index == 3) { //Exit
    goToWatchface();
  }
}
