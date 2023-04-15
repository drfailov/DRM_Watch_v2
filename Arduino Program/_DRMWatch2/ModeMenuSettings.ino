/*Show settings menu by triggerimg GenericMenu*/

#define modeMenuSettingsItemsCount 5 //сколько пунктов меню в массиве

#define MENU_SETTINS_SELECTED_BACK 0
#define MENU_SETTINS_SELECTED_SILENT 1
#define MENU_SETTINS_SELECTED_FLIP 2
#define MENU_SETTINS_SELECTED_WATCHFACE 3
#define MENU_SETTINS_SELECTED_TIME 4
bool selectingWatchface = false;
bool animate;


void modeMenuSettingsSetup() {
  genericMenuSetup();
  animate = true;
}

void modeMenuSettingsLoop() {
  if (isButtonUpPressed()){ //upper button
    if(isButtonUpHold()){
      beep();
      goToWatchface();
      return;
    }
    genericMenuLastActionTime = millis();
    modeMenuSettingsSelected (selected);
    beep();
    return;
  }

  if (isButtonDownPressed()) { //down button
    genericMenuLastActionTime = millis();
    beep();
    selectingWatchface = false;
    selected ++;
    if (selected >= modeMenuSettingsItemsCount) selected = 0;
  }
  
  doAutoExit();
  
#ifdef LANG_EN
  const __FlashStringHelper* settingsSilent = F("Silent");
  const __FlashStringHelper* settingsFlip = F("Flip");
  const __FlashStringHelper* settingsTime = F("Time");
  const __FlashStringHelper* settingsWTF = F("WTF");
#endif
#ifdef LANG_RU
  const __FlashStringHelper* settingsSilent = F("Бeззвyчный");
  const __FlashStringHelper* settingsFlip = F("Пepeвopoт");
  const __FlashStringHelper* settingsTime = F("Bpeмя");
  const __FlashStringHelper* settingsWTF = F("Цифepблaт");
#endif

  displayClear();
  if(selected  == MENU_SETTINS_SELECTED_WATCHFACE && selectingWatchface){
    byte wtfIndex = eepromReadWatchface();
    if(wtfIndex > watchfacesCount) wtfIndex = 0;
    if(wfs[wtfIndex] != 0)
      wfs[wtfIndex](/*hour*/0, /*minute*/0, /*second*/0, /*day*/0, /*month*/0, /*year*/0, /*dayOfWeek*/0, /*animate*/0);
    displayUpdate();
    return;
  }
  drawLegend();
  drawStatusBar();
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_BACK, /*icon*/displayDrawArrowLeft, /*text*/(__FlashStringHelper*)menuItemBack, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_SILENT, /*icon*/(eepromReadSilentMode()?displayDrawSilentModeIcon:displayDrawSilentModeOffIcon), /*text*/settingsSilent, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_FLIP, /*icon*/displayDrawIconFlip, /*text*/settingsFlip, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_WATCHFACE, /*icon*/displayDrawIconWatchface, /*text*/settingsWTF, /*animate*/animate);
  drawMenuItem(/*index*/MENU_SETTINS_SELECTED_TIME, /*icon*/displayDrawIconTime, /*text*/settingsTime, /*animate*/animate);
  displayUpdate();
  animate = false;
}

void modeMenuSettingsFinish() {
  genericMenuFinish();
}

void modeMenuSettingsSelected(byte index) {
  if (index == MENU_SETTINS_SELECTED_BACK) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
  
  if (index == MENU_SETTINS_SELECTED_WATCHFACE) { //Select WTF
    if(selectingWatchface == false){
      selectingWatchface = true;
      return;
    }
    byte wtfIndex = eepromReadWatchface();
    Serial.print(wtfIndex);
    if(wtfIndex < watchfacesCount -1){
      eepromSaveWatchface(++wtfIndex);
    }
    else{
      eepromSaveWatchface(0);
    }
    return;
  }

  if (index == MENU_SETTINS_SELECTED_SILENT) { //Set silent mode
    eepromSaveSilentMode(!eepromReadSilentMode());
    return;
  }

  if (index == MENU_SETTINS_SELECTED_TIME) { //Set time
    setMode(MODE_MENU_SET_TIME); 
    return;
  }
  
  if (index == MENU_SETTINS_SELECTED_FLIP) { //Flip screen
    eepromSaveFlipScreen(!eepromReadFlipScreen());
    return;
  }
}
