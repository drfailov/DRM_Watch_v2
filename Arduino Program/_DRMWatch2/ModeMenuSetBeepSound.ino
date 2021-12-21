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
const char modeMenuSetBeepSoundItem1[] PROGMEM = "Писк";
const char modeMenuSetBeepSoundItem2[] PROGMEM = "Клик";
const char modeMenuSetBeepSoundItem3[] PROGMEM = "Тон";
const char modeMenuSetBeepSoundItem4[] PROGMEM = "Свист";
const char modeMenuSetBeepSoundItem5[] PROGMEM = "Без звука";
const char modeMenuSetBeepSoundItem6[] PROGMEM = "< Назад";
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
    displayMessage(F("Сохр: писк"));
#endif
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 1) { //Click
    eepromSaveBeepSound(eepromBeepSoundClick);
#ifdef LANG_EN
    displayMessage(F("Saved click"));
#endif
#ifdef LANG_RU
    displayMessage(F("Сохр: клик"));
#endif
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 2) { //Tone
    eepromSaveBeepSound(eepromBeepSoundTone);
#ifdef LANG_EN
    displayMessage(F("Saved tone"));
#endif
#ifdef LANG_EN
    displayMessage(F("Сохр: тон"));
#endif
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 3) { //Whiste
    eepromSaveBeepSound(eepromBeepSoundWhistle);
#ifdef LANG_EN
    displayMessage(F("Saved whistle"));
#endif
#ifdef LANG_RU
    displayMessage(F("Сохр: свист"));
#endif
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 4) { //None
    eepromSaveBeepSound(eepromBeepSoundNone);
#ifdef LANG_EN
    displayMessage(F("Saved none"));
#endif
#ifdef LANG_RU
    displayMessage(F("Сохр: беззв."));
#endif
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 5) { //Back
    setMode(MODE_MENU_SETTINGS);
    return;
  }
}
