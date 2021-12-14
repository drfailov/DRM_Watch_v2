/*Show settings menu by triggerimg GenericMenu*/

const byte modeMenuSettingsItemsCount = 7; //сколько пунктов меню в массиве

//Максимальная длина строки:                  |          |
const char modeMenuSettingsItem1[] PROGMEM = "Set time";
const char modeMenuSettingsItem2[] PROGMEM = "Select WTF";
const char modeMenuSettingsItem3[] PROGMEM = "Set sleep";
const char modeMenuSettingsItem4[] PROGMEM = "Set silent";
const char modeMenuSettingsItem5[] PROGMEM = "Set sound";
const char modeMenuSettingsItem6[] PROGMEM = "Reboot";
const char modeMenuSettingsItem7[] PROGMEM = "< Back";

const char* const modeMenuSettingsItems[] PROGMEM = {
  modeMenuSettingsItem1,
  modeMenuSettingsItem2,
  modeMenuSettingsItem3,
  modeMenuSettingsItem4,
  modeMenuSettingsItem5,
  modeMenuSettingsItem6,
  modeMenuSettingsItem7
};
void(* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0


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

  if (index == 2) { //Set sleep
    setMode(MODE_MENU_SET_SLEEP_TIME); 
    return;
  }
  
  if (index == 3) { //Set silent
    
    return;
  }
  
  if (index == 4) { //Set sound
    setMode(MODE_MENU_SET_BEEP_SOUND); 
    return;
  }
  
  if (index == 5) { //Reboot
    displayMessage(F("Rebooting..."));
    resetFunc(); //вызываем reset
    return;
  }

  if (index == 6) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
