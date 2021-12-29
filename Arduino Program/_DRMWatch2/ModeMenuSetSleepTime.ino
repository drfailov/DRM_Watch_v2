/*Show sleep time menu by triggerimg GenericMenu*/

const byte modeMenuSetSleepTimeItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:                     |          |
#ifdef LANG_EN
const char modeMenuSetSleepTimeItem1[] PROGMEM = "0.5 sec";
const char modeMenuSetSleepTimeItem2[] PROGMEM = "1 sec";
const char modeMenuSetSleepTimeItem3[] PROGMEM = "2 sec";
const char modeMenuSetSleepTimeItem4[] PROGMEM = "4 sec";
const char modeMenuSetSleepTimeItem5[] PROGMEM = "8 sec";
const char modeMenuSetSleepTimeItem6[] PROGMEM = "< Back";
#endif
#ifdef LANG_RU
const char modeMenuSetSleepTimeItem1[] PROGMEM = "0.5 ceк";
const char modeMenuSetSleepTimeItem2[] PROGMEM = "1 ceк";
const char modeMenuSetSleepTimeItem3[] PROGMEM = "2 ceк";
const char modeMenuSetSleepTimeItem4[] PROGMEM = "4 ceк";
const char modeMenuSetSleepTimeItem5[] PROGMEM = "8 ceк";
const char modeMenuSetSleepTimeItem6[] PROGMEM = "< Haзaд";
#endif

const char* const modeMenuSetSleepTimeItems[] PROGMEM = {
  modeMenuSetSleepTimeItem1,
  modeMenuSetSleepTimeItem2,
  modeMenuSetSleepTimeItem3,
  modeMenuSetSleepTimeItem4,
  modeMenuSetSleepTimeItem5,
  modeMenuSetSleepTimeItem6
};


void modeMenuSetSleepTimeSetup() {
  genericMenuSetup();
  byte selected = eepromReadSleepTime();
  if(selected == eepromSleepTime05sec) genericMenuSelectPosition = 0;
  if(selected == eepromSleepTime1sec) genericMenuSelectPosition = 1;
  if(selected == eepromSleepTime2sec) genericMenuSelectPosition = 2;
  if(selected == eepromSleepTime4sec) genericMenuSelectPosition = 3;
  if(selected == eepromSleepTime8sec) genericMenuSelectPosition = 4;  
}

void modeMenuSetSleepTimeLoop() {
  genericMenuLoop(modeMenuSetSleepTimeItemsCount, modeMenuSetSleepTimeItems, modeMenuSetSleepTimeSelected);
}

void modeMenuSetSleepTimeFinish() {
  genericMenuFinish();
}

void modeMenuSetSleepTimeSelected(byte index) {
  if (index == 0) { //0.5 sec
    eepromSaveSleepTime(eepromSleepTime05sec);
#ifdef LANG_EN
    displayMessage(F("Saved .5 sec"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: .5 ceк"));
#endif
    goToWatchface();
    return;
  }
  
  if (index == 1) { //1 s
    eepromSaveSleepTime(eepromSleepTime1sec);
#ifdef LANG_EN
    displayMessage(F("Saved 1 sec"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: 1 ceк"));
#endif
    goToWatchface();
    return;
  }

  if (index == 2) { //2s
    eepromSaveSleepTime(eepromSleepTime2sec);
#ifdef LANG_EN
    displayMessage(F("Saved 2 sec"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: 2 ceк"));
#endif
    goToWatchface();
    return;
  } 
  
  if (index == 3) { //4s
    eepromSaveSleepTime(eepromSleepTime4sec);
#ifdef LANG_EN
    displayMessage(F("Saved 4 sec"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: 4 ceк"));
#endif
    goToWatchface();
    return;
  }
  
  if (index == 4) { //8s
    eepromSaveSleepTime(eepromSleepTime8sec);
#ifdef LANG_EN
    displayMessage(F("Saved 8 sec"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: 8 ceк"));
#endif
    goToWatchface();
    return;
  }

  if (index == 5) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
