/*Show settings menu by triggerimg GenericMenu*/

const byte modeMenuSettingsItemsCount = 8; //сколько пунктов меню в массиве

//Максимальная длина строки:                  |          |

#ifdef LANG_EN
const char modeMenuSettingsItem1[] PROGMEM = "Reboot";
const char modeMenuSettingsItem2[] PROGMEM = "Select WTF";
const char modeMenuSettingsItem3[] PROGMEM = "Set silent";
const char modeMenuSettingsItem4[] PROGMEM = "Set sleep";
const char modeMenuSettingsItem5[] PROGMEM = "Set sound";
const char modeMenuSettingsItem6[] PROGMEM = "Set time";
const char modeMenuSettingsItem7[] PROGMEM = "Hard reset";
const char modeMenuSettingsItem8[] PROGMEM = "< Back";
#endif
#ifdef LANG_RU
const char modeMenuSettingsItem1[] PROGMEM = "Пepeзaгpyзкa";
const char modeMenuSettingsItem2[] PROGMEM = "Цифepблaт";
const char modeMenuSettingsItem3[] PROGMEM = "Бeззвyчный";
const char modeMenuSettingsItem4[] PROGMEM = "Bpeмя cнa";
const char modeMenuSettingsItem5[] PROGMEM = "Звyк кнoпoк";
const char modeMenuSettingsItem6[] PROGMEM = "Зaдaть вpeмя";
const char modeMenuSettingsItem7[] PROGMEM = "Пoлный cбpoc";
const char modeMenuSettingsItem8[] PROGMEM = "< Haзaд";
#endif

const char* const modeMenuSettingsItems[] PROGMEM = {
  modeMenuSettingsItem1,
  modeMenuSettingsItem2,
  modeMenuSettingsItem3,
  modeMenuSettingsItem4,
  modeMenuSettingsItem5,
  modeMenuSettingsItem6,
  modeMenuSettingsItem7,
  modeMenuSettingsItem8
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
  if (index == 0) { //Reboot
#ifdef LANG_EN
    displayMessage(F("Rebooting..."));
#endif
#ifdef LANG_RU
    displayMessage(F("Перезагрузка"));
#endif    
    displayPowerOff();
    delay(1000);
    resetFunc(); //вызываем reset
    return;
  }
  
  if (index == 1) { //Select WTF
    setMode(MODE_MENU_SET_WATCHFACE); 
    return;
  }
  
  if (index == 2) { //Set silent
    setMode(MODE_MENU_SET_SILENT_MODE); 
    return;
  }

  if (index == 3) { //Set sleep
    setMode(MODE_MENU_SET_SLEEP_TIME); 
    return;
  }
  
  if (index == 4) { //Set sound
    setMode(MODE_MENU_SET_BEEP_SOUND); 
    return;
  }

  if (index == 5) { //Set time
    setMode(MODE_MENU_SET_TIME); 
    return;
  }

  if (index == 6) { //Hard Reset
#ifdef LANG_EN
    displayMessage(F("RESET!!!"));
#endif
#ifdef LANG_RU
    displayMessage(F("CБPOC!!!"));
#endif    
    displayPowerOff();
    eepromFIllByZeros();
    delay(5000);
    resetFunc(); //вызываем reset
    return;
  }
  
  if (index == 7) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
