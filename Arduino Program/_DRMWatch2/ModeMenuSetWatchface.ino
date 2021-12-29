/*Show watchfacw menu by triggerimg GenericMenu*/

const byte modeMenuSetWatchfaceItemsCount = 4; //сколько пунктов меню в массиве

//Максимальная длина строки:                       |          |

#ifdef LANG_EN
const char modeMenuSetWatchfaceItem1[] PROGMEM = "WTF 1";
const char modeMenuSetWatchfaceItem2[] PROGMEM = "WTF 2";
const char modeMenuSetWatchfaceItem3[] PROGMEM = "WTF 3";
const char modeMenuSetWatchfaceItem4[] PROGMEM = "< Back";
#endif
#ifdef LANG_RU
const char modeMenuSetWatchfaceItem1[] PROGMEM = "Циф 1";
const char modeMenuSetWatchfaceItem2[] PROGMEM = "Циф 2";
const char modeMenuSetWatchfaceItem3[] PROGMEM = "Циф 3";
const char modeMenuSetWatchfaceItem4[] PROGMEM = "< Haзaд";
#endif

const char* const modeMenuSetWatchfaceItems[] PROGMEM = {
  modeMenuSetWatchfaceItem1,
  modeMenuSetWatchfaceItem2,
  modeMenuSetWatchfaceItem3,
  modeMenuSetWatchfaceItem4
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
#ifdef LANG_EN
    displayMessage(F("WTF Set 1."));
#endif
#ifdef LANG_RU
    displayMessage(F("Циф = 1."));
#endif
    goToWatchface();
    return;
  }

  if (index == 1) { //WTF 2
    eepromSaveWatchface(2);
#ifdef LANG_EN
    displayMessage(F("WTF Set 2."));
#endif
#ifdef LANG_RU
    displayMessage(F("Циф = 2."));
#endif
    goToWatchface();
    return;
  }

  if (index == 2) { //WTF 3
    eepromSaveWatchface(3);
#ifdef LANG_EN
    displayMessage(F("WTF Set 3."));
#endif
#ifdef LANG_RU
    displayMessage(F("Циф = 3."));
#endif
    goToWatchface();
    return;
  }

  if (index == 3) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
