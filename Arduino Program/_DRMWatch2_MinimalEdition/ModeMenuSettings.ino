/*Show settings menu by triggerimg GenericMenu*/
#include "Generic.cpp"

#define modeMenuSettingsItemsCount 5 //сколько пунктов меню в массиве

#define MENU_SETTINS_SELECTED_BACK 0
#define MENU_SETTINS_SELECTED_SILENT 1
#define MENU_SETTINS_SELECTED_FLIP 2
#define MENU_SETTINS_SELECTED_WATCHFACE 4
#define MENU_SETTINS_SELECTED_TIME 3


void modeMenuSettingsSetup() {
  genericMenuSetup();
}

void modeMenuSettingsLoop() {
  if (isButtonUpPressed()){ //upper button
    if(isButtonUpHold()){
      Buzzer.beep();
      goToWatchface();
      return;
    }
    Generic.genericMenuLastActionTime = millis();
    modeMenuSettingsSelected (Generic.selected);
    Buzzer.beep();
    return;
  }

  if (isButtonDownPressed()) { //down button
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

  byte xOffset = 12;
  if(/*flip*/MyEEPROM.eepromReadFlipScreen())
    xOffset = 0;
  Display.displayClear();

  //BACK
  Display.displayDrawIconWithFrame(/*x*/xOffset+2, /*y*/2, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_BACK);

  //SILENT MODE
  Display.displayDrawIconWithFrame(/*x*/xOffset+2, /*y*/22, /*additionalWidth*/1, /*drawIcon(x,y,color)*/(MyEEPROM.eepromReadSilentMode()?Display.displayDrawSilentModeIcon:Display.displayDrawSilentModeOffIcon), /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_SILENT);

  //FLIP
  Display.displayDrawIconWithFrame(/*x*/xOffset+32, /*y*/22, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconFlip, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_FLIP);

  //SET TIME
  Display.displayDrawIconWithFrame(/*x*/xOffset+62, /*y*/22, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawIconTime, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_TIME);

  
  //WATCHFACE
  byte wtfIndex = MyEEPROM.eepromReadWatchface();
  if(wtfIndex > watchfacesCount) wtfIndex = 0;
  if(watchfaces[wtfIndex] == 0)
    strcpy_P(Generic.buffer, (char*)F("-"));      //for RAM arrays
  else
    strcpy_P(Generic.buffer, watchfaces[wtfIndex]->name());
  Display.displayDrawIconWithFrame(/*x*/xOffset+7, /*y*/42, /*additionalWidth*/49, /*drawIcon(x,y,color)*/Display.displayDrawIconWatchface, /*selected*/Generic.selected  == MENU_SETTINS_SELECTED_WATCHFACE);
  Display.displayDrawText(/*X*/xOffset+25, /*Y*/46, /*C*/Generic.selected  != MENU_SETTINS_SELECTED_WATCHFACE, /*text*/Generic.buffer);




  //ITEM NAME
  if(Generic.selected  == MENU_SETTINS_SELECTED_BACK) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/(__FlashStringHelper*)menuItemBack);
  else if(Generic.selected  == MENU_SETTINS_SELECTED_SILENT) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Silent"));
  else if(Generic.selected  == MENU_SETTINS_SELECTED_FLIP) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Flip"));
  else if(Generic.selected  == MENU_SETTINS_SELECTED_TIME) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Time"));
  else if(Generic.selected  == MENU_SETTINS_SELECTED_WATCHFACE) 
    Display.displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("WTF"));


  //LEGEND
  Display.drawLegend();
  
  
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
    if(wtfIndex < watchfacesCount -1){
      MyEEPROM.eepromSaveWatchface(++wtfIndex);
    }
    else{
      MyEEPROM.eepromSaveWatchface(0);
    }
    return;
  }

  if (index == MENU_SETTINS_SELECTED_SILENT) { //Set silent mode
    MyEEPROM.eepromSaveSilentMode(!MyEEPROM.eepromReadSilentMode());
    return;
  }

  if (index == MENU_SETTINS_SELECTED_TIME) { //Set time
    setMode(MODE_MENU_SET_TIME); 
    return;
  }
  
  if (index == MENU_SETTINS_SELECTED_FLIP) { //Flip screen
    MyEEPROM.eepromSaveFlipScreen(!MyEEPROM.eepromReadFlipScreen());
    return;
  }
}
