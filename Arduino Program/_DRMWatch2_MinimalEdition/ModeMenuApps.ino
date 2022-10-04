/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuAppsItemsCount = 4; //сколько пунктов меню в массиве

//Максимальная длина строки:              |          |
const char modeMenuAppsItemStopwatch[] PROGMEM = "Stopwatch";
const char modeMenuAppsItemAlarm[] PROGMEM = "Alarm";
const char modeMenuAppsItemMelodies[] PROGMEM = "Melodies";

const char* modeMenuAppsItems[] = {
  Generic.getMenuItemBack(),
  modeMenuAppsItemStopwatch,
  modeMenuAppsItemAlarm,
  modeMenuAppsItemMelodies
};


void modeMenuAppsSetup() {
  genericMenuSetup();
}

void modeMenuAppsLoop() {
  genericMenuLoop(modeMenuAppsItemsCount, modeMenuAppsItems, modeMenuAppsSelected, false);
}

void modeMenuAppsFinish() {
  genericMenuFinish();
}

void modeMenuAppsSelected(byte index) {
  if (index == 0) { //Back
    setMode(MODE_MENU_MAIN);
  }
  else if (index == 1) { //Stopwatch
    setMode(MODE_STOPWATCH);
  }
  else if (index == 2) { //alarm
    setMode(MODE_SET_ALARM);
  }
  else if (index == 3) { //Melodies
    setMode(MODE_MENU_MELODIES);
  }
}
