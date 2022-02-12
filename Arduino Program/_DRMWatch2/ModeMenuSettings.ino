/*Show settings menu by triggerimg GenericMenu*/
#include "Generic.cpp"

#define modeMenuSettingsItemsCount 7 //сколько пунктов меню в массиве
#define MENU_SETTINS_SELECTED_BACK 0
//#define MENU_SETTINS_SELECTED_REBOOT 1
#define MENU_SETTINS_SELECTED_SILENT 1
#define MENU_SETTINS_SELECTED_WATCHFACE 2
#define MENU_SETTINS_SELECTED_BEEP 3
#define MENU_SETTINS_SELECTED_TIME 4
#define MENU_SETTINS_SELECTED_RESET 5
#define MENU_SETTINS_SELECTED_FLIP 6

void modeMenuSettingsSetup() {
  genericMenuSetup();
}

void modeMenuSettingsLoop() {
  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonDown.isButtonPressed():ButtonUp.isButtonPressed()) {
    Generic.genericMenuLastActionTime = millis();
    modeMenuSettingsSelected (Generic.selected);
    Buzzer.beep();
    return;
  }

  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonUp.isButtonPressed():ButtonDown.isButtonPressed()) {
    Generic.genericMenuLastActionTime = millis();
    Buzzer.beep();
    Generic.selected ++;
    if (Generic.selected >= modeMenuSettingsItemsCount) Generic.selected = 0;
  }
  
  //auto exit
  if (millis() - Generic.genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }

  byte xOffset = 20;
  if(/*flip*/MyEEPROM.eepromReadFlipScreen())
    xOffset = 5;
  Display.displayClear();

  //BACK
  Display.displayDrawIconWithFrame(/*x*/xOffset+0, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_BACK);
  
  //REBOOT
  //Display.displayDrawIconWithFrame(/*x*/xOffset+25, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconReboot, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_REBOOT);

  //SILENT MODE
  Display.displayDrawIconWithFrame(/*x*/xOffset+50, /*y*/0, /*additionalWidth*/1, /*drawIcon(x,y,color)*/(MyEEPROM.eepromReadSilentMode()?Display.displayDrawSilentModeIcon:Display.displayDrawSilentModeOffIcon), /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_SILENT);
  
  //WATCHFACE
  byte wtfIndex = MyEEPROM.eepromReadWatchface();
  if(wtfIndex > watchfacesCount) wtfIndex = 0;
  if(watchfaces[wtfIndex] == 0)
    strcpy_P(Generic.buffer, (char*)F("-"));      //for RAM arrays
  else
    strcpy_P(Generic.buffer, watchfaces[wtfIndex]->name());
  Display.displayDrawIconWithFrame(/*x*/xOffset+0, /*y*/16, /*additionalWidth*/55, /*drawIcon(x,y,color)*/Display.displayDrawIconWatchface, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_WATCHFACE);
  Display.displayDrawText(/*X*/xOffset+18, /*Y*/20, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_WATCHFACE, /*text*/Generic.buffer);

  //SLEEP
//  byte sleepTimeCurrent = MyEEPROM.eepromReadSleepTime();
//  ltoa(sleepTimeCurrent, Generic.buffer, DEC);
//  Generic.buffer[1] = 's';
//  Generic.buffer[2] = '\0';
//  Display.displayDrawIconWithFrame(/*x*/xOffset+0, /*y*/32, /*additionalWidth*/13, /*drawIcon(x,y,color)*/Display.displayDrawIconSleep, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_SLEEP);
//  Display.displayDrawText(/*X*/xOffset+18, /*Y*/36, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_SLEEP, /*text*/Generic.buffer);

  //BEEP
  byte beepCurrent = MyEEPROM.eepromReadBeepSound();
  ltoa(beepCurrent, Generic.buffer, DEC);
  Generic.buffer[1] = '\0';
  Display.displayDrawIconWithFrame(/*x*/xOffset+37, /*y*/32, /*additionalWidth*/13, /*drawIcon(x,y,color)*/Display.displayDrawIconBeep, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_BEEP);
  Display.displayDrawText(/*X*/xOffset+55, /*Y*/36, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_BEEP, /*text*/Generic.buffer);

  //SET TIME
  Display.displayDrawIconWithFrame(/*x*/xOffset+0, /*y*/48, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconTime, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_TIME);

  //RESET
  Display.displayDrawIconWithFrame(/*x*/xOffset+25, /*y*/48, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconReset, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_RESET);

  //FLIP
  Display.displayDrawIconWithFrame(/*x*/xOffset+50, /*y*/48, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconFlip, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_FLIP);
  

  //UPADTE
  if(/*flip*/MyEEPROM.eepromReadFlipScreen()){
    Display.displayDrawLine(/*X1*/96-11, /*Y1*/0, /*X2*/96-11, /*Y2*/68, /*C*/1);
    Display.displayDrawCheck(/*X*/96-8, /*Y*/2, 1);
    Display.displayDrawArrowDown(/*X*/96-8, /*Y*/59, 1);    
  }
  else{/*no flip*/
    Display.displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
    Display.displayDrawCheck(/*X*/2, /*Y*/2, 1);
    Display.displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  }
  Display.displayUpdate();
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
    byte wtfIndex = MyEEPROM.eepromReadWatchface();
    Serial.print(wtfIndex);
    if(wtfIndex < watchfacesCount -1){
      MyEEPROM.eepromSaveWatchface(++wtfIndex);
    }
    else{
      MyEEPROM.eepromSaveWatchface(0);
    }
    //setMode(MODE_MENU_SET_WATCHFACE); 
    return;
  }
  
//  if (index == MENU_SETTINS_SELECTED_SLEEP) { //sleep time
//    byte sleepTimeCurrent = MyEEPROM.eepromReadSleepTime();
//    if(sleepTimeCurrent == eepromSleepTime05sec) sleepTimeCurrent = eepromSleepTime1sec;
//    else if(sleepTimeCurrent == eepromSleepTime1sec) sleepTimeCurrent = eepromSleepTime2sec;
//    else if(sleepTimeCurrent == eepromSleepTime2sec) sleepTimeCurrent = eepromSleepTime4sec;
//    else if(sleepTimeCurrent == eepromSleepTime4sec) sleepTimeCurrent = eepromSleepTime8sec;
//    else sleepTimeCurrent = eepromSleepTime05sec;
//    MyEEPROM.eepromSaveSleepTime(sleepTimeCurrent);
//    return;
//  }
  

  if (index == MENU_SETTINS_SELECTED_SILENT) { //Set silent mode
    MyEEPROM.eepromSaveSilentMode(!MyEEPROM.eepromReadSilentMode());
    return;
  }
  
  if (index == MENU_SETTINS_SELECTED_BEEP) { //Set sound
    //setMode(MODE_MENU_SET_BEEP_SOUND); 
    byte beepCurrent = MyEEPROM.eepromReadBeepSound();
    beepCurrent++;
    if(beepCurrent > 4) beepCurrent = 0;
    MyEEPROM.eepromSaveBeepSound(beepCurrent);
    return;
  }

  if (index == MENU_SETTINS_SELECTED_TIME) { //Set time
    setMode(MODE_MENU_SET_TIME); 
    return;
  }

  if (index == MENU_SETTINS_SELECTED_RESET) { //Hard Reset
    //eepromFIllByZeros();
    MyEEPROM.eepromFIllByOnes();
    reboot();
  }

  
  if (index == MENU_SETTINS_SELECTED_FLIP) { //Flip screen
    MyEEPROM.eepromSaveFlipScreen(!MyEEPROM.eepromReadFlipScreen());
    return;
  }
}
