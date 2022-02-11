/*Show main menu */
const byte modeMenuMainItemsCount = 4; //сколько пунктов меню в массиве

#define MAIN_MENU_SELECTED_BACK 0
#define MAIN_MENU_SELECTED_APPS 1
#define MAIN_MENU_SELECTED_SETTINGS 2
#define MAIN_MENU_SELECTED_ABOUT 3

////Максимальная длина строки:             |          |
//#ifdef LANG_EN
//const char modeMenuMainItem1[] PROGMEM = "Apps";
//const char modeMenuMainItem2[] PROGMEM = "Settings";
//const char modeMenuMainItem3[] PROGMEM = "About";
//#endif
//#ifdef LANG_RU
//const char modeMenuMainItem1[] PROGMEM = "Пpилoжeния";
//const char modeMenuMainItem2[] PROGMEM = "Hacтpoйки";
//const char modeMenuMainItem3[] PROGMEM = "O пpoгpaммe";
//#endif
//
//const char* const modeMenuMainItems[] PROGMEM = {
//  modeMenuMainItem1,
//  modeMenuMainItem2,
//  modeMenuMainItem3,
//  menuItemBack
//};


void modeMenuMainSetup() {
  genericMenuSetup();
}

void modeMenuMainLoop() {
  //genericMenuLoop(modeMenuMainItemsCount, modeMenuMainItems, modeMenuMainSelected, true);
  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonDown.isButtonPressed():ButtonUp.isButtonPressed()) {
    genericMenuLastActionTime = millis();
    Buzzer.beep();
    //onSelected (genericMenuSelectPosition);
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
    Buzzer.beep();
    Generic.selected ++;
    if(Generic.selected > 3) 
      Generic.selected = 0;
    return;
  }
  
  Display.displayClear();
  byte xOffset = MyEEPROM.eepromReadFlipScreen()? 0 : 13;
  
  //Display.displayDrawLine(/*X1*/10, /*Y1*/9, /*X2*/96, /*Y2*/9, /*C*/1);

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
  
  Display.displayDrawIconWithFrame(/*x*/xOffset+7, /*y*/17, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_BACK);
  Display.displayDrawIconWithFrame(/*x*/xOffset+7, /*y*/35, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawAppsIcon, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_APPS);
  Display.displayDrawIconWithFrame(/*x*/xOffset+32, /*y*/35, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconSettings, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_SETTINGS);
  Display.displayDrawIconWithFrame(/*x*/xOffset+57, /*y*/35, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconAbout, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_ABOUT);
  
  if(MyEEPROM.eepromReadFlipScreen()){
    Display.displayDrawLine(/*X1*/86, /*Y1*/0, /*X2*/86, /*Y2*/68, /*C*/1);
    Display.displayDrawCheck(/*X*/89, /*Y*/2, 1);
    Display.displayDrawArrowDown(/*X*/89, /*Y*/59, 1);
  }
  else{
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
