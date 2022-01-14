/*Show sleep time menu by triggerimg GenericMenu*/

const byte modeMenuSetSleepTimeItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:                     |          |
#ifdef LANG_EN
const char modeMenuSetSleepTimeItem1[] PROGMEM = "Slp .5 sec";
const char modeMenuSetSleepTimeItem2[] PROGMEM = "Slp 1 sec";
const char modeMenuSetSleepTimeItem3[] PROGMEM = "Slp 2 sec";
const char modeMenuSetSleepTimeItem4[] PROGMEM = "Slp 4 sec";
const char modeMenuSetSleepTimeItem5[] PROGMEM = "Slp 8 sec";
#endif
#ifdef LANG_RU
const char modeMenuSetSleepTimeItem1[] PROGMEM = "Coн .5 ceк";
const char modeMenuSetSleepTimeItem2[] PROGMEM = "Coн 1 ceк";
const char modeMenuSetSleepTimeItem3[] PROGMEM = "Coн 2 ceк";
const char modeMenuSetSleepTimeItem4[] PROGMEM = "Coн 4 ceк";
const char modeMenuSetSleepTimeItem5[] PROGMEM = "Coн 8 ceк";
#endif

const char* const modeMenuSetSleepTimeItems[] PROGMEM = {
  modeMenuSetSleepTimeItem1,
  modeMenuSetSleepTimeItem2,
  modeMenuSetSleepTimeItem3,
  modeMenuSetSleepTimeItem4,
  modeMenuSetSleepTimeItem5,
  menuItemBack
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
  genericMenuLoop(modeMenuSetSleepTimeItemsCount, modeMenuSetSleepTimeItems, modeMenuSetSleepTimeSelected, true);
}

void modeMenuSetSleepTimeFinish() {
  genericMenuFinish();
}

void modeMenuSetSleepTimeSelected(byte index) {
  if (index == 0) { //0.5 sec
    eepromSaveSleepTime(eepromSleepTime05sec);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetSleepTimeItem1);
    goToWatchface();
    return;
  }
  
  if (index == 1) { //1 s
    eepromSaveSleepTime(eepromSleepTime1sec);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetSleepTimeItem2);
    goToWatchface();
    return;
  }

  if (index == 2) { //2s
    eepromSaveSleepTime(eepromSleepTime2sec);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetSleepTimeItem3);
    goToWatchface();
    return;
  } 
  
  if (index == 3) { //4s
    eepromSaveSleepTime(eepromSleepTime4sec);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetSleepTimeItem4);
    goToWatchface();
    return;
  }
  
  if (index == 4) { //8s
    eepromSaveSleepTime(eepromSleepTime8sec);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetSleepTimeItem5);
    goToWatchface();
    return;
  }

  if (index == 5) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
