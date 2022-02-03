/*Show settings menu by triggerimg GenericMenu*/
#include "Generic.cpp"

const byte modeMenuSettingsItemsCount = 8; //сколько пунктов меню в массиве
#define MENU_SETTINS_SELECTED_BACK 0
#define MENU_SETTINS_SELECTED_REBOOT 1
#define MENU_SETTINS_SELECTED_WATCHFACE 2

//Максимальная длина строки:                  |          |
//
//#ifdef LANG_EN
//const char modeMenuSettingsItem1[] PROGMEM = "Reboot";
//const char modeMenuSettingsItem2[] PROGMEM = "Select WTF";
//const char modeMenuSettingsItem3[] PROGMEM = "Set silent";
//const char modeMenuSettingsItem4[] PROGMEM = "Set sleep";
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
    Buzzer.beep();
    modeMenuSettingsSelected (Generic.selected);
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
  Display.displayDrawIconWithFrame(/*x*/20, /*y*/3, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_BACK);
  
  //REBOOT
  Display.displayDrawIconWithFrame(/*x*/45, /*y*/3, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconReboot, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_REBOOT);
  
  //WATCHFACE
  byte wtfIndex = MyEEPROM.eepromReadWatchface();
  if(wtfIndex > watchfacesCount) wtfIndex = 0;
  if(watchfaces[wtfIndex] == 0)
    strcpy_P(Generic.buffer, (char*)F("-"));      //for RAM arrays
  else
    strcpy_P(Generic.buffer, watchfaces[wtfIndex]->name());
  Display.displayDrawIconWithFrame(/*x*/20, /*y*/20, /*additionalWidth*/55, /*drawIcon(x,y,color)*/Display.displayDrawIconWatchface, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_WATCHFACE);
  Display.displayDrawText(/*X*/38, /*Y*/24, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_WATCHFACE, /*text*/Generic.buffer);

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
  
  if (index == 3) { //Set silent
    setMode(MODE_MENU_SET_SILENT_MODE); 
    return;
  }

  if (index == 4) { //Set sleep
    setMode(MODE_MENU_SET_SLEEP_TIME); 
    return;
  }
  
  if (index == 5) { //Set sound
    setMode(MODE_MENU_SET_BEEP_SOUND); 
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
