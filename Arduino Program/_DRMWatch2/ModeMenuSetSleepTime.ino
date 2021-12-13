/*Show sleep time menu by triggerimg GenericMenu*/

const byte modeMenuSetSleepTimeItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:                     |          |
const char modeMenuSetSleepTimeItem1[] PROGMEM = "0.5 sec";
const char modeMenuSetSleepTimeItem2[] PROGMEM = "1 sec";
const char modeMenuSetSleepTimeItem3[] PROGMEM = "2 sec";
const char modeMenuSetSleepTimeItem4[] PROGMEM = "4 sec";
const char modeMenuSetSleepTimeItem5[] PROGMEM = "8 sec";
const char modeMenuSetSleepTimeItem6[] PROGMEM = "< Back";

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
}

void modeMenuSetSleepTimeLoop() {
  genericMenuLoop(modeMenuSetSleepTimeItemsCount, modeMenuSetSleepTimeItems, modeMenuSetSleepTimeSelected);
}

void modeMenuSetSleepTimeFinish() {
  genericMenuFinish();
}

void modeMenuSetSleepTimeSelected(byte index) {
  if (index == 0) { //0.5 sec
    eepromSaveSleepTime(0);
    displayMessage("Saved: 0.5 sec");
    return;
  }
  
  if (index == 1) { //1 s
    eepromSaveSleepTime(1);
    displayMessage("Saved: 1 sec");
    return;
  }

  if (index == 2) { //2s
    eepromSaveSleepTime(2);
    displayMessage("Saved: 2 sec");
    return;
  } 
  
  if (index == 3) { //4s
    eepromSaveSleepTime(4);
    displayMessage("Saved: 4 sec");
    return;
  }
  
  if (index == 4) { //8s
    eepromSaveSleepTime(8);
    displayMessage("Saved: 8 sec");
    return;
  }

  if (index == 5) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
