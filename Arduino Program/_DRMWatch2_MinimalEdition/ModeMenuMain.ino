/*Show main menu */
const byte modeMenuMainItemsCount = 3; //сколько пунктов меню в массиве

#define MAIN_MENU_SELECTED_BACK 0
#define MAIN_MENU_SELECTED_APPS 1
#define MAIN_MENU_SELECTED_SETTINGS 2
#define MAIN_MENU_SELECTED_ABOUT 3

void modeMenuMainSetup() {
  genericMenuSetup();
}

void modeMenuMainLoop() {
  if (isButtonUpPressed()){
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
    return;
  }
  
  if(isButtonDownPressed()){
    Generic.genericMenuLastActionTime = millis();
    Buzzer.beep();
    Generic.selected ++;
    if(Generic.selected >= modeMenuMainItemsCount) 
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
  Display.displayDrawIconWithFrame(/*x*/xOffset+2, /*y*/30, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_BACK);
  //APPS
  Display.displayDrawIconWithFrame(/*x*/xOffset+32, /*y*/30, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawAppsIcon, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_APPS);
  //SETTINGS
  Display.displayDrawIconWithFrame(/*x*/xOffset+62, /*y*/30, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconSettings, /*selected*/Generic.selected  == MAIN_MENU_SELECTED_SETTINGS);


  //LEGEND
  Display.drawLegend();
  
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
  else if (index == 2) { //Exit
    goToWatchface();
  }
}
