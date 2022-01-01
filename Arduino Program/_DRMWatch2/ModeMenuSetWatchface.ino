/*Show watchfacw menu by triggerimg GenericMenu*/

const byte modeMenuSetWatchfaceItemsCount = 5; //сколько пунктов меню в массиве

//Максимальная длина строки:                       |          |

#ifdef LANG_EN
const char modeMenuSetWatchfaceItem1[] PROGMEM = "WTF 1";
const char modeMenuSetWatchfaceItem2[] PROGMEM = "WTF 2";
const char modeMenuSetWatchfaceItem3[] PROGMEM = "WTF 3";
const char modeMenuSetWatchfaceItem4[] PROGMEM = "WTF 4";
#endif
#ifdef LANG_RU
const char modeMenuSetWatchfaceItem1[] PROGMEM = "Циф 1";
const char modeMenuSetWatchfaceItem2[] PROGMEM = "Циф 2";
const char modeMenuSetWatchfaceItem3[] PROGMEM = "Циф 3";
const char modeMenuSetWatchfaceItem4[] PROGMEM = "Циф 4";
#endif

const char* const modeMenuSetWatchfaceItems[] PROGMEM = {
  modeMenuSetWatchfaceItem1,
  modeMenuSetWatchfaceItem2,
  modeMenuSetWatchfaceItem3,
  modeMenuSetWatchfaceItem4,
  menuItemBack
};


void modeMenuSetWatchfaceSetup() {
  genericMenuSetup();
  byte value = eepromReadWatchface();
  genericMenuSelectPosition = 0;
  if(value == 1)
    genericMenuSelectPosition = 0;
  else if(value == 2)
    genericMenuSelectPosition = 1;
  else if(value == 3)
    genericMenuSelectPosition = 2;
  else if(value == 4)
    genericMenuSelectPosition = 3;
}

void modeMenuSetWatchfaceLoop() {
  genericMenuLoop(modeMenuSetWatchfaceItemsCount, modeMenuSetWatchfaceItems, modeMenuSetWatchfaceSelected);
}

void modeMenuSetWatchfaceFinish() {
  genericMenuFinish();
}

void modeMenuSetWatchfaceSelected(byte index) {
  if (index == 0) { //WTF 1
    eepromSaveWatchface(1);
    displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItem1);
    goToWatchface();
    return;
  }

  if (index == 1) { //WTF 2
    eepromSaveWatchface(2);
    displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItem2);
    goToWatchface();
    return;
  }

  if (index == 2) { //WTF 3
    eepromSaveWatchface(3);
    displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItem3);
    goToWatchface();
    return;
  }

  if (index == 3) { //WTF 4
    eepromSaveWatchface(4);
    displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItem4);
    goToWatchface();
    return;
  }

  if (index == 3) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
