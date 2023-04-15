/*Show main menu */
const byte modeMenuMainItemsCount = 4; //сколько пунктов меню в массиве

#define MAIN_MENU_SELECTED_BACK 0
#define MAIN_MENU_SELECTED_APPS 1
#define MAIN_MENU_SELECTED_SETTINGS 2
#define MAIN_MENU_SELECTED_ABOUT 3

void modeMenuMainSetup() {
  genericMenuSetup();
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
  //auto exit
  if (millis() - genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }
  
  displayClear();
  byte xOffset = eepromReadFlipScreen()? 0 : 13;

  {//Temperature
    float temp = rtcGetTemp();
    dtostrf(/*value*/temp, /*mininum width*/4, /*precision*/1, /*buffer*/buffer);
    sprintf(buffer, "%sC", buffer);
    displayDrawText(xOffset+0, 0, 1, buffer);
  }
  
  byte X = xOffset+83; //96 total
  const byte Y = 0;
  
  {//battery
    X -= 17;
    displayDrawBattery(/*x*/X, /*y*/0);
    if(!batteryIsCharging() && !batteryIsLowPower()) X += 5;
  }
  
  //Silent mode sign
  if(eepromReadSilentMode()){ 
    X -= 10;
    displayDrawSilentModeIcon(/*x*/X, /*y*/0, /*color*/1);
  }
  
  //Alert sign
  if(eepromReadAlertEnabled()){ 
    X-= 11;
    displayDrawAlertSign(/*x*/X, /*y*/0, /*color*/1);
  }


  //back
  displayDrawIconWithFrame(/*x*/xOffset+9, /*y*/15, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawArrowLeft, /*selected*/selected  == MAIN_MENU_SELECTED_BACK);
  
  //APPS
  displayDrawIconWithFrame(/*x*/xOffset+9, /*y*/34, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawAppsIcon, /*selected*/selected  == MAIN_MENU_SELECTED_APPS);
  //SETTINGS
  displayDrawIconWithFrame(/*x*/xOffset+33, /*y*/34, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawIconSettings, /*selected*/selected  == MAIN_MENU_SELECTED_SETTINGS);
  //ABOUT
  displayDrawIconWithFrame(/*x*/xOffset+57, /*y*/34, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawIconAbout, /*selected*/selected  == MAIN_MENU_SELECTED_ABOUT);


  //LABEL
#ifdef LANG_RU
  if(selected  == MAIN_MENU_SELECTED_BACK) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/(__FlashStringHelper*)menuItemBack);
  else if(selected  == MAIN_MENU_SELECTED_APPS) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Пpилoжeния"));
  else if(selected  == MAIN_MENU_SELECTED_SETTINGS) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Hacтpoйки"));
  else if(selected  == MAIN_MENU_SELECTED_ABOUT) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Cпpaвкa"));
#endif
#ifdef LANG_EN
  if(selected  == MAIN_MENU_SELECTED_BACK) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/(__FlashStringHelper*)menuItemBack);
  else if(selected  == MAIN_MENU_SELECTED_APPS) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Apps"));
  else if(selected  == MAIN_MENU_SELECTED_SETTINGS) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Settings"));
  else if(selected  == MAIN_MENU_SELECTED_ABOUT) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("About"));
#endif

  //LEGEND
  if(eepromReadFlipScreen()){ //flip
    displayDrawLine(/*X1*/96-11, /*Y1*/0, /*X2*/96-11, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/96-8, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/96-8, /*Y*/59, 1);
  }
  else{  //no flip
    displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/2, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  }
  displayUpdate();
}

void modeMenuMainFinish() {
  genericMenuFinish();
}

void modeMenuMainSelected(byte index) {
  if (index == 0) { //Apps
    setMode(MODE_MENU_APPS);
  }
  else if (index == 1) { //Settings
    setMode(MODE_MENU_SETTINGS);
  }
  else if (index == 2) { //About
    setMode(MODE_ABOUT);
  }
  else if (index == 3) { //Exit
    goToWatchface();
  }
}
