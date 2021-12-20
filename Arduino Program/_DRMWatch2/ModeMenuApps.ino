/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuAppsItemsCount = 6; //сколько пунктов меню в массиве

//Максимальная длина строки:              |          |
const char modeMenuAppsItem1[] PROGMEM = "Debug view";
const char modeMenuAppsItem2[] PROGMEM = "Melodies";
const char modeMenuAppsItem3[] PROGMEM = "Stopwatch";
const char modeMenuAppsItem4[] PROGMEM = "Zrada";
const char modeMenuAppsItem5[] PROGMEM = "Svaston";
const char modeMenuAppsItem6[] PROGMEM = "< Back";

const char* const modeMenuAppsItems[] PROGMEM = {
  modeMenuAppsItem1,
  modeMenuAppsItem2,
  modeMenuAppsItem3,
  modeMenuAppsItem4,
  modeMenuAppsItem5,
  modeMenuAppsItem6
};


void modeMenuAppsSetup() {
  genericMenuSetup();
}

void modeMenuAppsLoop() {
  genericMenuLoop(modeMenuAppsItemsCount, modeMenuAppsItems, modeMenuAppsSelected);
}

void modeMenuAppsFinish() {
  genericMenuFinish();
}

void modeMenuAppsSelected(byte index) {
  
  if (index == 0) { //Debug screen
    setMode(MODE_DEBUG_SCREEN1);
    return;
  }
  
  if (index == 1) { //Melodies
    setMode(MODE_MENU_MELODIES);
    return;
  }
  
  if (index == 2) { //Stopwatch
    
  }
  
  if (index == 3) { //Zrada
    
  }
  
  if (index == 4) { //Svaston
    
  } 
  
  if (index == 5) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
