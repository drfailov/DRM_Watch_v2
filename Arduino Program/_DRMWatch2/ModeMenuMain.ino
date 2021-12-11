/*Show main menu by triggerimg GenericMenu*/
const int modeMenuMainItemsCount = 4; //сколько пунктов меню в массиве

//Максимальная длина строки:    |          |
const char modeMenuMainItem1[] PROGMEM = "Debug view";
const char modeMenuMainItem2[] PROGMEM = "Melodies";
const char modeMenuMainItem3[] PROGMEM = "Settings";
const char modeMenuMainItem4[] PROGMEM = "Exit";

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
  if (index == 0) { //Debug screen
    setMode(MODE_DEBUG_SCREEN1);
    return;
  }
  
  if (index == 1) { //Melodies
    setMode(MODE_MENU_MELODIES);
    return;
  }

  if (index == 2) { //Settings
    setMode(MODE_MENU_SETTINGS);
    return;
  }

  if (index == 3) { //Exit
    goToWatchface();
    return;
  }
}
