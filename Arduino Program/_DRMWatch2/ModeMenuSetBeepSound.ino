/*Show beep sound menu by triggerimg GenericMenu*/

const byte modeMenuSetBeepSoundItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:                     |          |
const char modeMenuSetBeepSoundItem1[] PROGMEM = "Beep";
const char modeMenuSetBeepSoundItem2[] PROGMEM = "Click";
const char modeMenuSetBeepSoundItem3[] PROGMEM = "Tone";
const char modeMenuSetBeepSoundItem4[] PROGMEM = "Whistle";
const char modeMenuSetBeepSoundItem5[] PROGMEM = "None";
const char modeMenuSetBeepSoundItem6[] PROGMEM = "< Back";

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
    displayMessage(F("Saved beep"));
    delay(500);
    goToWatchface();
    return;
  }
  
  if (index == 1) { //Click
    eepromSaveBeepSound(eepromBeepSoundClick);
    displayMessage(F("Saved click"));
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 2) { //Tone
    eepromSaveBeepSound(eepromBeepSoundTone);
    displayMessage(F("Saved tone"));
    delay(500);
    goToWatchface();
    return;
  } 
  
  if (index == 3) { //Whiste
    eepromSaveBeepSound(eepromBeepSoundWhistle);
    displayMessage(F("Saved whistle"));
    delay(500);
    goToWatchface();
    return;
  }
  
  if (index == 4) { //None
    eepromSaveBeepSound(eepromBeepSoundNone);
    displayMessage(F("Saved none"));
    delay(500);
    goToWatchface();
    return;
  }

  if (index == 5) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
