/*Show settings menu by triggerimg GenericMenu*/
#include "Generic.cpp"

const byte modeMenuSettingsItemsCount = 8; //сколько пунктов меню в массиве
#define MENU_SETTINS_SELECTED_BACK 0
#define MENU_SETTINS_SELECTED_REBOOT 1
#define MENU_SETTINS_SELECTED_SILENT 2
#define MENU_SETTINS_SELECTED_WATCHFACE 3
#define MENU_SETTINS_SELECTED_SLEEP 4
#define MENU_SETTINS_SELECTED_BEEP 5


//Максимальная длина строки:                  |          |
//
//#ifdef LANG_EN
//+const char modeMenuSettingsItem1[] PROGMEM = "Reboot";
//+const char modeMenuSettingsItem2[] PROGMEM = "Select WTF";
//const char modeMenuSettingsItem3[] PROGMEM = "Set silent";
//+const char modeMenuSettingsItem4[] PROGMEM = "Set sleep";
//const char modeMenuSettingsItem5[] PROGMEM = "Set sound";
//const char modeMenuSettingsItem6[] PROGMEM = "Set time";
//const char modeMenuSettingsItem7[] PROGMEM = "Hard reset";
//#endif
//#ifdef LANG_RU
//const char modeMenuSettingsItem1[] PROGMEM = "Пepeзaгpyзкa";
//const char modeMenuSettingsItem2[] PROGMEM = "Цифepблaт";
//const char modeMenuSettingsItem3[] PROGMEM = "Бeззвyчный";
//const char modeMenuSettingsItem4[] PROGMEM = "Bpeмя cнa";
//const char modeMenuSettingsItem5[] PROGMEM = "Звyк кнoпoк";
//const char modeMenuSettingsItem6[] PROGMEM = "Зaдaть вpeмя";
//const char modeMenuSettingsItem7[] PROGMEM = "Пoлный cбpoc";
//#endif
//
//const char* const modeMenuSettingsItems[] PROGMEM = {
//  modeMenuSettingsItem1,
//  modeMenuSettingsItem2,
//  modeMenuSettingsItem3,
//  modeMenuSettingsItem4,
//  modeMenuSettingsItem5,
//  modeMenuSettingsItem6,
//  modeMenuSettingsItem7,
//  menuItemBack
//};


void modeMenuSettingsSetup() {
  genericMenuSetup();
}

void modeMenuSettingsLoop() {
  if (ButtonUp.isButtonPressed()) {
    genericMenuLastActionTime = millis();
    modeMenuSettingsSelected (Generic.selected);
    Buzzer.beep();
    return;
  }

  if (ButtonDown.isButtonPressed()) {
    genericMenuLastActionTime = millis();
    Buzzer.beep();
    Generic.selected ++;
    if (Generic.selected >= modeMenuSettingsItemsCount) Generic.selected = 0;
  }
  Display.displayClear();

  //BACK
  Display.displayDrawIconWithFrame(/*x*/20, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_BACK);
  
  //REBOOT
  Display.displayDrawIconWithFrame(/*x*/45, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconReboot, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_REBOOT);

  //SILENT MODE
  //bool silentMode = eepromReadSilentMode();
  //Display.displayDrawSilentModeOffIcon
  //Display.displayDrawSilentModeIcon
  Display.displayDrawIconWithFrame(/*x*/70, /*y*/0, /*additionalWidth*/1, /*drawIcon(x,y,color)*/(MyEEPROM.eepromReadSilentMode()?Display.displayDrawSilentModeIcon:Display.displayDrawSilentModeOffIcon), /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_SILENT);
  
  //WATCHFACE
  byte wtfIndex = MyEEPROM.eepromReadWatchface();
  if(wtfIndex > watchfacesCount) wtfIndex = 0;
  if(watchfaces[wtfIndex] == 0)
    strcpy_P(Generic.buffer, (char*)F("-"));      //for RAM arrays
  else
    strcpy_P(Generic.buffer, watchfaces[wtfIndex]->name());
  Display.displayDrawIconWithFrame(/*x*/20, /*y*/16, /*additionalWidth*/55, /*drawIcon(x,y,color)*/Display.displayDrawIconWatchface, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_WATCHFACE);
  Display.displayDrawText(/*X*/38, /*Y*/20, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_WATCHFACE, /*text*/Generic.buffer);

  //SLEEP
  byte sleepTimeCurrent = MyEEPROM.eepromReadSleepTime();
  ltoa(sleepTimeCurrent, Generic.buffer, DEC);
  Generic.buffer[1] = 's';
  Generic.buffer[2] = '\0';
  Display.displayDrawIconWithFrame(/*x*/20, /*y*/32, /*additionalWidth*/13, /*drawIcon(x,y,color)*/Display.displayDrawIconSleep, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_SLEEP);
  Display.displayDrawText(/*X*/38, /*Y*/36, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_SLEEP, /*text*/Generic.buffer);

  //BEEP
  byte beepCurrent = MyEEPROM.eepromReadBeepSound();
  ltoa(beepCurrent, Generic.buffer, DEC);
  Generic.buffer[1] = '\0';
  Display.displayDrawIconWithFrame(/*x*/57, /*y*/32, /*additionalWidth*/13, /*drawIcon(x,y,color)*/Display.displayDrawIconBeep, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_BEEP);
  Display.displayDrawText(/*X*/75, /*Y*/36, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_BEEP, /*text*/Generic.buffer);

  //UPADTE
  Display.displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
  Display.displayDrawCheck(/*X*/2, /*Y*/2, 1);
  Display.displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  Display.displayUpdate();
  //genericMenuLoop(modeMenuSettingsItemsCount, modeMenuSettingsItems, modeMenuSettingsSelected, true);
}

void modeMenuSettingsFinish() {
  genericMenuFinish();
}

void modeMenuSettingsSelected(byte index) {
  if (index == MENU_SETTINS_SELECTED_BACK) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
  
  if (index == MENU_SETTINS_SELECTED_REBOOT) { //Reboot
    reboot();
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
  
  if (index == MENU_SETTINS_SELECTED_SLEEP) { //sleep time
    byte sleepTimeCurrent = MyEEPROM.eepromReadSleepTime();
    if(sleepTimeCurrent == eepromSleepTime05sec) sleepTimeCurrent = eepromSleepTime1sec;
    else if(sleepTimeCurrent == eepromSleepTime1sec) sleepTimeCurrent = eepromSleepTime2sec;
    else if(sleepTimeCurrent == eepromSleepTime2sec) sleepTimeCurrent = eepromSleepTime4sec;
    else if(sleepTimeCurrent == eepromSleepTime4sec) sleepTimeCurrent = eepromSleepTime8sec;
    else sleepTimeCurrent = eepromSleepTime05sec;
    MyEEPROM.eepromSaveSleepTime(sleepTimeCurrent);
    return;
  }
  

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

  if (index == 6) { //Set time
    setMode(MODE_MENU_SET_TIME); 
    return;
  }

  if (index == 7) { //Hard Reset
    //eepromFIllByZeros();
    MyEEPROM.eepromFIllByOnes();
    reboot();
  }
}
