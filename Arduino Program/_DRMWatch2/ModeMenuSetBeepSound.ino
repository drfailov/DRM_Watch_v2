/*Show beep sound menu by triggerimg GenericMenu*/

const byte modeMenuSetBeepSoundItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:                     |          |
#ifdef LANG_EN
const char modeMenuSetBeepSoundItem1[] PROGMEM = "Beep";
const char modeMenuSetBeepSoundItem2[] PROGMEM = "Click";
const char modeMenuSetBeepSoundItem3[] PROGMEM = "Tone";
const char modeMenuSetBeepSoundItem4[] PROGMEM = "Whistle";
const char modeMenuSetBeepSoundItem5[] PROGMEM = "None";
#endif
#ifdef LANG_RU
const char modeMenuSetBeepSoundItem1[] PROGMEM = "Пиcк";
const char modeMenuSetBeepSoundItem2[] PROGMEM = "Kлик";
const char modeMenuSetBeepSoundItem3[] PROGMEM = "Toн";
const char modeMenuSetBeepSoundItem4[] PROGMEM = "Cвиcт";
const char modeMenuSetBeepSoundItem5[] PROGMEM = "Бeз звyкa";
#endif

const char* const modeMenuSetBeepSoundItems[] PROGMEM = {
  modeMenuSetBeepSoundItem1,
  modeMenuSetBeepSoundItem2,
  modeMenuSetBeepSoundItem3,
  modeMenuSetBeepSoundItem4,
  modeMenuSetBeepSoundItem5,
  menuItemBack
};


void modeMenuSetBeepSoundSetup() {
  genericMenuSetup();
  byte selected = MyEEPROM.eepromReadBeepSound();
  if(selected < 0 || selected > 4) selected = 0;
  genericMenuSelectPosition = selected;
}

void modeMenuSetBeepSoundLoop() {
  genericMenuLoop(modeMenuSetBeepSoundItemsCount, modeMenuSetBeepSoundItems, modeMenuSetBeepSoundSelected, true);
}

void modeMenuSetBeepSoundFinish() {
  genericMenuFinish();
}

void modeMenuSetBeepSoundSelected(byte index) {
  if (index == 0) { //beep
    MyEEPROM.eepromSaveBeepSound(eepromBeepSoundBeep);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetBeepSoundItem1);
    goToWatchface();
    return;
  }

  if (index == 1) { //Click
    MyEEPROM.eepromSaveBeepSound(eepromBeepSoundClick);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetBeepSoundItem2);
    goToWatchface();
    return;
  }

  if (index == 2) { //Tone
    MyEEPROM.eepromSaveBeepSound(eepromBeepSoundTone);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetBeepSoundItem3);
    goToWatchface();
    return;
  }

  if (index == 3) { //Whiste
    MyEEPROM.eepromSaveBeepSound(eepromBeepSoundWhistle);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetBeepSoundItem4);
    goToWatchface();
    return;
  }

  if (index == 4) { //None
    MyEEPROM.eepromSaveBeepSound(eepromBeepSoundNone);
    Display.displayMessage((__FlashStringHelper*)modeMenuSetBeepSoundItem5);
    goToWatchface();
    return;
  }

  if (index == 5) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
