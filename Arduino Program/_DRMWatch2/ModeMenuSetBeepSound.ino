/*Show beep sound menu by triggerimg GenericMenu*/

const byte modeMenuSetBeepSoundItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:                     |          |
#ifdef LANG_EN
const char modeMenuSetBeepSoundItem1[] PROGMEM = "Beep";
const char modeMenuSetBeepSoundItem2[] PROGMEM = "Click";
const char modeMenuSetBeepSoundItem3[] PROGMEM = "Tone";
const char modeMenuSetBeepSoundItem4[] PROGMEM = "Whistle";
const char modeMenuSetBeepSoundItem5[] PROGMEM = "None";
const char modeMenuSetBeepSoundItem6[] PROGMEM = "< Back";
#endif
#ifdef LANG_RU
const char modeMenuSetBeepSoundItem1[] PROGMEM = "Пиcк";
const char modeMenuSetBeepSoundItem2[] PROGMEM = "Kлик";
const char modeMenuSetBeepSoundItem3[] PROGMEM = "Toн";
const char modeMenuSetBeepSoundItem4[] PROGMEM = "Cвиcт";
const char modeMenuSetBeepSoundItem5[] PROGMEM = "Бeз звyкa";
const char modeMenuSetBeepSoundItem6[] PROGMEM = "< Haзaд";
#endif

const char* const modeMenuSetBeepSoundItems[] PROGMEM = {
  modeMenuSetBeepSoundItem1,
  modeMenuSetBeepSoundItem2,
  modeMenuSetBeepSoundItem3,
  modeMenuSetBeepSoundItem4,
  modeMenuSetBeepSoundItem5,
  modeMenuSetBeepSoundItem6
};


void modeMenuSetBeepSoundSetup() {
  genericMenuSetup();
  byte selected = eepromReadBeepSound();
  if(selected < 0 || selected > 4) selected = 0;
  genericMenuSelectPosition = selected;
}

void modeMenuSetBeepSoundLoop() {
  genericMenuLoop(modeMenuSetBeepSoundItemsCount, modeMenuSetBeepSoundItems, modeMenuSetBeepSoundSelected);
}

void modeMenuSetBeepSoundFinish() {
  genericMenuFinish();
}

void modeMenuSetBeepSoundSelected(byte index) {
  if (index == 0) { //beep
    eepromSaveBeepSound(eepromBeepSoundBeep);
#ifdef LANG_EN
    displayMessage(F("Saved beep"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: пиcк"));
#endif
    goToWatchface();
    return;
  }

  if (index == 1) { //Click
    eepromSaveBeepSound(eepromBeepSoundClick);
#ifdef LANG_EN
    displayMessage(F("Saved click"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: клик"));
#endif
    goToWatchface();
    return;
  }

  if (index == 2) { //Tone
    eepromSaveBeepSound(eepromBeepSoundTone);
#ifdef LANG_EN
    displayMessage(F("Saved tone"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: тoн"));
#endif
    goToWatchface();
    return;
  }

  if (index == 3) { //Whiste
    eepromSaveBeepSound(eepromBeepSoundWhistle);
#ifdef LANG_EN
    displayMessage(F("Saved whistle"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: cвиcт"));
#endif
    goToWatchface();
    return;
  }

  if (index == 4) { //None
    eepromSaveBeepSound(eepromBeepSoundNone);
#ifdef LANG_EN
    displayMessage(F("Saved none"));
#endif
#ifdef LANG_RU
    displayMessage(F("Coxp: бeззв."));
#endif
    goToWatchface();
    return;
  }

  if (index == 5) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
