/*Show settings menu by triggerimg GenericMenu*/

const byte modeMenuSettingsItemsCount = 4; //сколько пунктов меню в массиве

//Максимальная длина строки:             |          |
const char modeMenuSettingsItem1[] PROGMEM = "Set time";
const char modeMenuSettingsItem2[] PROGMEM = "Select WTF";
const char modeMenuSettingsItem3[] PROGMEM = "Test 1";
const char modeMenuSettingsItem4[] PROGMEM = "< Back";

const char* const modeMenuSettingsItems[] PROGMEM = {
  modeMenuSettingsItem1,
  modeMenuSettingsItem2,
  modeMenuSettingsItem3,
  modeMenuSettingsItem4
};


void modeMenuSettingsSetup() {
  genericMenuSetup();
}

void modeMenuSettingsLoop() {
  genericMenuLoop(modeMenuSettingsItemsCount, modeMenuSettingsItems, modeMenuSettingsSelected);
}

void modeMenuSettingsFinish() {
  genericMenuFinish();
}

void modeMenuSettingsSelected(byte index) {
  if (index == 0) { //Set time
    setMode(MODE_MENU_SET_TIME); 
    return;
  }
  
  if (index == 1) { //Select WTF
    
    return;
  }

  if (index == 2) { //Test 1
    
    return;
  }

  if (index == 3) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
