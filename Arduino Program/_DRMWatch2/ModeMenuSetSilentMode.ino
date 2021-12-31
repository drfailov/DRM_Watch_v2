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
  genericMenuLoop(modeMenuSetSilentModeItemsCount, modeMenuSetSilentModeItems, modeMenuSetSilentModeSelected);
}

void modeMenuSetSilentModeFinish() {
  genericMenuFinish();
}

void modeMenuSetSilentModeSelected(byte index) {
  if (index == 0) { //Sound ON
    eepromSaveSilentMode(false);
#ifdef LANG_EN
    displayMessage(F("Sound ON"));
#endif
#ifdef LANG_RU
    displayMessage(F("Звyк BKЛ"));
#endif
    goToWatchface();
    return;
  }
  
  if (index == 1) { //Sound OFF
    eepromSaveSilentMode(true);
#ifdef LANG_EN
    displayMessage(F("Sound OFF"));
#endif
#ifdef LANG_RU
    displayMessage(F("Звyк BЫKЛ"));
#endif
    goToWatchface();
    return;
  }

  if (index == 2) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
