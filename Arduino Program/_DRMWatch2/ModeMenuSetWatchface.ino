/*Show watchfacw menu by triggerimg GenericMenu*/


//This is needed to count active watchfaces and show correct number of menu items.
byte modeMenuSetWatchfaceItemsCount(){//сколько пунктов меню в массиве
  byte cnt = 1;//1 for back item
#ifdef WATCHFACE_DRMWATCH
  cnt++;
#endif
#ifdef WATCHFACE_DRMLITE
  cnt++;
#endif
#ifdef WATCHFACE_NOMENS
  cnt++;
#endif
#ifdef WATCHFACE_ZUBAT
  cnt++;
#endif
  return cnt;
}


#ifdef WATCHFACE_DRMWATCH
//Максимальная длина строки:                            "          "
const char modeMenuSetWatchfaceItemDrmWatch[] PROGMEM = "DRM Watch";
#endif
#ifdef WATCHFACE_DRMLITE
//Максимальная длина строки:                           "          "
const char modeMenuSetWatchfaceItemDrmLite[] PROGMEM = "DRM Lite";
#endif
#ifdef WATCHFACE_NOMENS
//Максимальная длина строки:                     "          "
const char modeMenuSetWatchfaceItemNomens[] PROGMEM = "Nomens";
#endif
#ifdef WATCHFACE_ZUBAT
//Максимальная длина строки:                     "          "
const char modeMenuSetWatchfaceItemZubat[] PROGMEM = "Zubat";
#endif

const char* const modeMenuSetWatchfaceItems[] PROGMEM = {
#ifdef WATCHFACE_DRMWATCH
  modeMenuSetWatchfaceItemDrmWatch,
#endif
#ifdef WATCHFACE_DRMLITE
  modeMenuSetWatchfaceItemDrmLite,
#endif
#ifdef WATCHFACE_NOMENS
  modeMenuSetWatchfaceItemNomens,
#endif
#ifdef WATCHFACE_ZUBAT
  modeMenuSetWatchfaceItemZubat,
#endif
  menuItemBack
};


void modeMenuSetWatchfaceSetup() {
  genericMenuSetup();
  //Выбор стандартного выбранного пункта меню исходя из текущей настройки в памяти
  genericMenuSelectPosition = 0;
  byte value = eepromReadWatchface();
  byte position = 0;
#ifdef WATCHFACE_DRMWATCH
  if(value == WATCHFACE_DRMWATCH) genericMenuSelectPosition = position;
  position++;
#endif
#ifdef WATCHFACE_DRMLITE
  if(value == WATCHFACE_DRMLITE) genericMenuSelectPosition = position;
  position++;
#endif
#ifdef WATCHFACE_NOMENS
  if(value == WATCHFACE_NOMENS) genericMenuSelectPosition = position;
  position++;
#endif
#ifdef WATCHFACE_ZUBAT
  if(value == WATCHFACE_ZUBAT) genericMenuSelectPosition = position;
  position++;
#endif
}

void modeMenuSetWatchfaceLoop() {
  genericMenuLoop(modeMenuSetWatchfaceItemsCount(), modeMenuSetWatchfaceItems, modeMenuSetWatchfaceSelected, true);
}

void modeMenuSetWatchfaceFinish() {
  genericMenuFinish();
}

void modeMenuSetWatchfaceSelected(byte index) {
  byte checkingIndex = 0;
  //последовательность проверок здесь должна соответсвовать порядку пунктов в меню
  
#ifdef WATCHFACE_DRMWATCH
  if (index == checkingIndex++) {
    eepromSaveWatchface(WATCHFACE_DRMWATCH);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItemDrmWatch);
    goToWatchface();
    return;
  }
#endif

#ifdef WATCHFACE_DRMLITE
  if (index == checkingIndex++) { 
    eepromSaveWatchface(WATCHFACE_DRMLITE);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItemDrmLite);
    goToWatchface();
    return;
  }
#endif

#ifdef WATCHFACE_NOMENS
  if (index == checkingIndex++) { 
    eepromSaveWatchface(WATCHFACE_NOMENS);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItemNomens);
    goToWatchface();
    return;
  }
#endif

#ifdef WATCHFACE_ZUBAT
  if (index == checkingIndex++) { 
    eepromSaveWatchface(WATCHFACE_ZUBAT);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetWatchfaceItemZubat);
    goToWatchface();
    return;
  }
#endif

  if (index == checkingIndex++) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
