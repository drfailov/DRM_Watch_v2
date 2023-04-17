#define MENU_SETTINS_SELECTED_BACK 0
#define MENU_SETTINS_SELECTED_SILENT 1
#define MENU_SETTINS_SELECTED_FLIP 2
#define MENU_SETTINS_SELECTED_WATCHFACE 3
#define MENU_SETTINS_SELECTED_TIME 4
bool selectingWatchface = false;


void modeMenuSettingsSetup() {
  genericMenuSetup();
}

void modeMenuSettingsLoop() {
  if(genericMenuRoutine(modeMenuSettingsSelected, 5))return;
  if(selected != MENU_SETTINS_SELECTED_WATCHFACE)
    selectingWatchface = false;
  
  
#ifdef LANG_EN
  const __FlashStringHelper* settingsSilent = F("Silent");
  const __FlashStringHelper* settingsFlip = F("Flip");
  const __FlashStringHelper* settingsTime = F("Time");
  const __FlashStringHelper* settingsWTF = F("WTF");
#endif
#ifdef LANG_RU
  const __FlashStringHelper* settingsSilent = F("Бeззвyчный");
  const __FlashStringHelper* settingsFlip = F("Пoвopoт");
  const __FlashStringHelper* settingsTime = F("Bpeмя");
  const __FlashStringHelper* settingsWTF = F("Цифepблaт");
#endif
#ifdef LANG_UA
  const __FlashStringHelper* settingsSilent = F("Тиша");
  const __FlashStringHelper* settingsFlip = F("Поворот");
  const __FlashStringHelper* settingsTime = F("Час");
  const __FlashStringHelper* settingsWTF = F("Цифepблaт");
#endif

  if(selected  == MENU_SETTINS_SELECTED_WATCHFACE && selectingWatchface){
    displayClear();
    byte wtfIndex = eepromReadWatchface();
    if(wtfIndex > watchfacesCount) wtfIndex = 0;
    if(wfs[wtfIndex] != 0)
      wfs[wtfIndex](/*hour*/0, /*minute*/0, /*second*/0, /*day*/0, /*month*/0, /*year*/0, /*dayOfWeek*/0, /*animate*/0);
    displayUpdate();
    return;
  }
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_BACK, /*icon*/displayDrawBackIcon, /*text*/(__FlashStringHelper*)menuItemBack, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_SILENT, /*icon*/(eepromReadSilentMode()?displayDrawSilentModeIcon:displayDrawSilentModeOffIcon), /*text*/settingsSilent, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_FLIP, /*icon*/displayDrawIconFlip, /*text*/settingsFlip, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_WATCHFACE, /*icon*/displayDrawIconWatchface, /*text*/settingsWTF, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_TIME, /*icon*/displayDrawIconTime, /*text*/settingsTime, /*animate*/animate);
  displayUpdate();
  animate = false;
}

void modeMenuSettingsSelected() {
  //variable is: selected
  if (selected == MENU_SETTINS_SELECTED_BACK) { //Back
    setMode(MODE_MENU_MAIN);
  }
  else if (selected == MENU_SETTINS_SELECTED_WATCHFACE) { //Select WTF
    if(selectingWatchface == false){
      selectingWatchface = true;
      return;
    }
    byte wtfIndex = eepromReadWatchface()+1;
    if(wtfIndex >= watchfacesCount) wtfIndex = 0;
    eepromSaveWatchface(wtfIndex);
  }
  else if (selected == MENU_SETTINS_SELECTED_SILENT) { //Set silent mode
    eepromSaveSilentMode(!eepromReadSilentMode());
  }
  else if (selected == MENU_SETTINS_SELECTED_TIME) { //Set time
    setMode(MODE_MENU_SET_TIME); 
  }
  else if (selected == MENU_SETTINS_SELECTED_FLIP) { //Flip screen
    eepromSaveFlipScreen(!eepromReadFlipScreen());
  }
}
