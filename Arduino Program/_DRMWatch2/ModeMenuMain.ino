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
  if (MyEEPROM.eepromReadFlipScreen()?ButtonDown.isButtonPressed():ButtonUp.isButtonPressed()) {
    Generic.genericMenuLastActionTime = millis();
    Buzzer.beep();
    if(Generic.selected == MAIN_MENU_SELECTED_BACK){
      goToWatchface();
    }
    else if (Generic.selected == MAIN_MENU_SELECTED_APPS){
      setMode(MODE_MENU_APPS);
    }
    else if (Generic.selected == MAIN_MENU_SELECTED_SETTINGS){
      setMode(MODE_MENU_SETTINGS);
    }
    else if (Generic.selected == MAIN_MENU_SELECTED_ABOUT){
      setMode(MODE_ABOUT);
    }
    return;
  }
  
  if(/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonUp.isButtonPressed():ButtonDown.isButtonPressed()){
    Generic.genericMenuLastActionTime = millis();
    Buzzer.beep();
    Generic.selected ++;
    if(Generic.selected > 3) 
      Generic.selected = 0;
  }
  //auto exit
  if (millis() - Generic.genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }
  
  Display.displayClear();
  byte xOffset = MyEEPROM.eepromReadFlipScreen()? 0 : 13;

  {//Temperature
    float temp = RTC.rtcGetTemp();
    dtostrf(/*value*/temp, /*mininum width*/4, /*precision*/1, /*buffer*/Generic.buffer);
    sprintf(Generic.buffer, "%sC", Generic.buffer);
    Display.displayDrawText(xOffset+0, 0, 1, Generic.buffer);
  }
  
  byte X = xOffset+83; //96 total
  const byte Y = 0;
  
  {//battery
    X -= 17;
    Display.displayDrawBattery(/*x*/X, /*y*/0);
    if(!Battery.batteryIsCharging() && !Battery.batteryIsLowPower()) X += 5;
  }
  
  //Silent mode sign
  if(MyEEPROM.eepromReadSilentMode()){ 
    X -= 10;
    Display.displayDrawSilentModeIcon(/*x*/X, /*y*/0, /*color*/1);
  }
  
  //Alert sign
  if(MyEEPROM.eepromReadAlertEnabled()){ 
    X-= 11;
    Display.displayDrawAlertSign(/*x*/X, /*y*/0, /*color*/1);
  }


  //back
  Display.displayDrawIconWithFrame(/*x*/xOffset+9, /*y*/15, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_BACK);
  
  //APPS
  Display.displayDrawIconWithFrame(/*x*/xOffset+9, /*y*/34, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawAppsIcon, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_APPS);
  //SETTINGS
  Display.displayDrawIconWithFrame(/*x*/xOffset+33, /*y*/34, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconSettings, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_SETTINGS);
  //ABOUT
  Display.displayDrawIconWithFrame(/*x*/xOffset+57, /*y*/34, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconAbout, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_ABOUT);


  //LABEL
#ifdef LANG_RU
  if(Generic.selected  == MAIN_MENU_SELECTED_BACK) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/(__FlashStringHelper*)menuItemBack);
  else if(Generic.selected  == MAIN_MENU_SELECTED_APPS) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Пpилoжeния"));
  else if(Generic.selected  == MAIN_MENU_SELECTED_SETTINGS) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Hacтpoйки"));
  else if(Generic.selected  == MAIN_MENU_SELECTED_ABOUT) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("O пpoгpaммe"));
#endif
#ifdef LANG_EN
  if(Generic.selected  == MAIN_MENU_SELECTED_BACK) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/(__FlashStringHelper*)menuItemBack);
  else if(Generic.selected  == MAIN_MENU_SELECTED_APPS) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Apps"));
  else if(Generic.selected  == MAIN_MENU_SELECTED_SETTINGS) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Settings"));
  else if(Generic.selected  == MAIN_MENU_SELECTED_ABOUT) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("About"));
#endif

  //LEGEND
  if(MyEEPROM.eepromReadFlipScreen()){ //flip
    Display.displayDrawLine(/*X1*/96-11, /*Y1*/0, /*X2*/96-11, /*Y2*/68, /*C*/1);
    Display.displayDrawCheck(/*X*/96-8, /*Y*/2, 1);
    Display.displayDrawArrowDown(/*X*/96-8, /*Y*/59, 1);
  }
  else{  //no flip
    Display.displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
    Display.displayDrawCheck(/*X*/2, /*Y*/2, 1);
    Display.displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  }
  Display.displayUpdate();
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
