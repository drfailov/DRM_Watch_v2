/*Show beep sound menu by triggerimg GenericMenu*/

const byte modeMenuSetSilentModeItemsCount = 3; //сколько пунктов меню в массиве

//Максимальная длина строки:                       |          |

#ifdef LANG_EN
const char modeMenuSetSilentModeItem1[] PROGMEM = "Sound ON";
const char modeMenuSetSilentModeItem2[] PROGMEM = "Sound OFF";
const char modeMenuSetSilentModeItem3[] PROGMEM = "< Back";
#endif
#ifdef LANG_RU
const char modeMenuSetSilentModeItem1[] PROGMEM = "Звук ВКЛ";
const char modeMenuSetSilentModeItem2[] PROGMEM = "Звук ВЫКЛ";
const char modeMenuSetSilentModeItem3[] PROGMEM = "< Назад";
#endif

const char* const modeMenuSetSilentModeItems[] PROGMEM = {
  modeMenuSetSilentModeItem1,
  modeMenuSetSilentModeItem2,
  modeMenuSetSilentModeItem3
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
    displayMessage(F("Звук ВКЛ"));
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
    displayMessage(F("Звук ВЫКЛ"));
#endif
    goToWatchface();
    return;
  }

  if (index == 2) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
