/*Show beep sound menu by triggerimg GenericMenu*/

const byte modeMenuSetSilentModeItemsCount = 3; //сколько пунктов меню в массиве

//Максимальная длина строки:                       |          |

#ifdef LANG_EN
const char modeMenuSetSilentModeItem1[] PROGMEM = "Sound ON";
const char modeMenuSetSilentModeItem2[] PROGMEM = "Sound OFF";
#endif
#ifdef LANG_RU
const char modeMenuSetSilentModeItem1[] PROGMEM = "Звyк BKЛ";
const char modeMenuSetSilentModeItem2[] PROGMEM = "Звyк BЫKЛ";
#endif

const char* const modeMenuSetSilentModeItems[] PROGMEM = {
  modeMenuSetSilentModeItem1,
  modeMenuSetSilentModeItem2,
  menuItemBack
};


void modeMenuSetSilentModeSetup() {
  genericMenuSetup();
  bool silent = eepromReadSilentMode();
  if(silent == true)
    genericMenuSelectPosition = 1;
  if(silent == false)
    genericMenuSelectPosition = 0;
}

void modeMenuSetSilentModeLoop() {
  genericMenuLoop(modeMenuSetSilentModeItemsCount, modeMenuSetSilentModeItems, modeMenuSetSilentModeSelected, true);
}

void modeMenuSetSilentModeFinish() {
  genericMenuFinish();
}

void modeMenuSetSilentModeSelected(byte index) {
  if (index == 0) { //Sound ON
    eepromSaveSilentMode(false);
    displayMessage((__FlashStringHelper*)modeMenuSetSilentModeItem1);
    goToWatchface();
    return;
  }
  
  if (index == 1) { //Sound OFF
    eepromSaveSilentMode(true);
    displayMessage((__FlashStringHelper*)modeMenuSetSilentModeItem2);
    goToWatchface();
    return;
  }

  if (index == 2) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
