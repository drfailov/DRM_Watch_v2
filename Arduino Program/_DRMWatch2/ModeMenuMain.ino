/*Show main menu */
const byte modeMenuMainItemsCount = 4; //сколько пунктов меню в массиве

#define MAIN_MENU_SELECTED_BACK 0
#define MAIN_MENU_SELECTED_APPS 1
#define MAIN_MENU_SELECTED_SETTINGS 2
#define MAIN_MENU_SELECTED_ABOUT 3

void modeMenuMainSetup() {
  genericMenuSetup();
  animate = true;
}

void modeMenuMainLoop() {
  if (isButtonUpPressed()){
    genericMenuLastActionTime = millis();
    beep();
    if(selected == MAIN_MENU_SELECTED_BACK){
      goToWatchface();
    }
    else if (selected == MAIN_MENU_SELECTED_APPS){
      setMode(MODE_MENU_APPS);
    }
    else if (selected == MAIN_MENU_SELECTED_SETTINGS){
      setMode(MODE_MENU_SETTINGS);
    }
    else if (selected == MAIN_MENU_SELECTED_ABOUT){
      setMode(MODE_ABOUT);
    }
    return;
  }
  
  if(isButtonDownPressed()){
    genericMenuLastActionTime = millis();
    beep();
    selected ++;
    if(selected > 3) 
      selected = 0;
  }
  doAutoExit();
  
#ifdef LANG_EN
  const __FlashStringHelper* menuApps = F("Apps");
  const __FlashStringHelper* menuSettings = F("Settings");
  const __FlashStringHelper* menuAbout = F("About");
#endif
#ifdef LANG_RU
  const __FlashStringHelper* menuApps = F("Пpилoжeния");
  const __FlashStringHelper* menuSettings = F("Hacтpoйки");
  const __FlashStringHelper* menuAbout = F("Cпpaвкa");
#endif

  displayClear();
  drawLegend();
  drawStatusBar();
  drawMenuItem(/*index*/MAIN_MENU_SELECTED_BACK, /*icon*/displayDrawArrowLeft, /*text*/(__FlashStringHelper*)menuItemBack, /*animate*/animate);
  drawMenuItem(/*index*/MAIN_MENU_SELECTED_APPS, /*icon*/displayDrawAppsIcon, /*text*/menuApps, /*animate*/animate);
  drawMenuItem(/*index*/MAIN_MENU_SELECTED_SETTINGS, /*icon*/displayDrawIconSettings, /*text*/menuSettings, /*animate*/animate);
  drawMenuItem(/*index*/MAIN_MENU_SELECTED_ABOUT, /*icon*/displayDrawIconAbout, /*text*/menuAbout, /*animate*/animate);
  displayUpdate();
  animate = false;
}

void modeMenuMainFinish() {
  
}
