/*Show beep sound menu by triggerimg GenericMenu*/

const byte modeMenuSetSilentModeItemsCount = 3; //сколько пунктов меню в массиве

//Максимальная длина строки:                       |          |
const char modeMenuSetSilentModeItem1[] PROGMEM = "Sound ON";
const char modeMenuSetSilentModeItem2[] PROGMEM = "Sound OFF";
const char modeMenuSetSilentModeItem3[] PROGMEM = "< Back";

const char* const modeMenuSetSilentModeItems[] PROGMEM = {
  modeMenuSetSilentModeItem1,
  modeMenuSetSilentModeItem2,
  modeMenuSetSilentModeItem3
};


void modeMenuSetSilentModeSetup() {
  genericMenuSetup();
}

void modeMenuSetSilentModeLoop() {
  genericMenuLoop(modeMenuSetSilentModeItemsCount, modeMenuSetSilentModeItems, modeMenuSetSilentModeSelected);
}

void modeMenuSetSilentModeFinish() {
  genericMenuFinish();
}

void modeMenuSetSilentModeSelected(byte index) {
  if (index == 0) { //Sound ON
    eepromSaveSilentMode(false);
    displayMessage(F("Sound ON"));
    delay(500);
    goToWatchface();
    return;
  }
  
  if (index == 1) { //Sound OFF
    eepromSaveSilentMode(true);
    displayMessage(F("Sound OFF"));
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 2) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
