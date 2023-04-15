/*Show settings menu by triggerimg GenericMenu*/

#define modeMenuSettingsItemsCount 6 //сколько пунктов меню в массиве

#define MENU_SETTINS_SELECTED_BACK 0
#define MENU_SETTINS_SELECTED_SILENT 1
#define MENU_SETTINS_SELECTED_FLIP 2
#define MENU_SETTINS_SELECTED_WATCHFACE 3
#define MENU_SETTINS_SELECTED_BEEP 4
#define MENU_SETTINS_SELECTED_TIME 5


void modeMenuSettingsSetup() {
  genericMenuSetup();
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
    selected ++;
    if (selected >= modeMenuSettingsItemsCount) selected = 0;
  }
  
  //auto exit
  if (millis() - genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }

  byte xOffset = 12;
  if(/*flip*/eepromReadFlipScreen())
    xOffset = 0;
  displayClear();

  //BACK
  displayDrawIconWithFrame(/*x*/xOffset+7, /*y*/3, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawArrowLeft, /*selected*/selected  == MENU_SETTINS_SELECTED_BACK);

  //SILENT MODE
  displayDrawIconWithFrame(/*x*/xOffset+31, /*y*/3, /*additionalWidth*/1, /*drawIcon(x,y,color)*/(eepromReadSilentMode()?displayDrawSilentModeIcon:displayDrawSilentModeOffIcon), /*selected*/selected  == MENU_SETTINS_SELECTED_SILENT);

  //FLIP
  displayDrawIconWithFrame(/*x*/xOffset+56, /*y*/3, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawIconFlip, /*selected*/selected  == MENU_SETTINS_SELECTED_FLIP);


  
  //WATCHFACE
  byte wtfIndex = eepromReadWatchface();
  if(wtfIndex > watchfacesCount) wtfIndex = 0;
  if(wfs[wtfIndex] != 0){
    wfs[wtfIndex](/*hour*/0, /*minute*/0, /*second*/0, /*day*/0, /*month*/0, /*year*/0, /*dayOfWeek*/0, /*animate*/0);
  }
  displayDrawIconWithFrame(/*x*/xOffset+7, /*y*/21, /*additionalWidth*/49, /*drawIcon(x,y,color)*/displayDrawIconWatchface, /*selected*/selected  == MENU_SETTINS_SELECTED_WATCHFACE);
  displayDrawText(/*X*/xOffset+25, /*Y*/25, /*C*/selected  != MENU_SETTINS_SELECTED_WATCHFACE, /*text*/buffer);



  //BEEP
  byte beepCurrent = eepromReadBeepSound();
  ltoa(beepCurrent, buffer, DEC);
  buffer[1] = '\0';
  displayDrawIconWithFrame(/*x*/xOffset+7, /*y*/39, /*additionalWidth*/7, /*drawIcon(x,y,color)*/displayDrawIconBeep, /*selected*/selected  == MENU_SETTINS_SELECTED_BEEP);
  displayDrawText(/*X*/xOffset+24, /*Y*/43, /*C*/selected  != MENU_SETTINS_SELECTED_BEEP, /*text*/buffer);

  //SET TIME
  displayDrawIconWithFrame(/*x*/xOffset+38, /*y*/39, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawIconTime, /*selected*/selected  == MENU_SETTINS_SELECTED_TIME);



  //ITEM NAME
#ifdef LANG_RU
  if(selected  == MENU_SETTINS_SELECTED_BACK) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/(__FlashStringHelper*)menuItemBack);
  else if(selected  == MENU_SETTINS_SELECTED_SILENT) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Бeззвyчный"));
  else if(selected  == MENU_SETTINS_SELECTED_FLIP) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Пepeвopoт"));
  else if(selected  == MENU_SETTINS_SELECTED_TIME) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Bpeмя"));
  else if(selected  == MENU_SETTINS_SELECTED_WATCHFACE) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Цифepблaт"));
  else if(selected  == MENU_SETTINS_SELECTED_BEEP) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("3вyк кнoпoк"));
  
#endif
#ifdef LANG_EN
  if(selected  == MENU_SETTINS_SELECTED_BACK) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/(__FlashStringHelper*)menuItemBack);
  else if(selected  == MENU_SETTINS_SELECTED_SILENT) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Silent"));
  else if(selected  == MENU_SETTINS_SELECTED_FLIP) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Flip"));
  else if(selected  == MENU_SETTINS_SELECTED_TIME) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Time"));
  else if(selected  == MENU_SETTINS_SELECTED_WATCHFACE) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("WTF"));
  else if(selected  == MENU_SETTINS_SELECTED_BEEP) 
    displayDrawText(/*X*/xOffset+0, /*Y*/60, /*C*/1, /*text*/F("Beep"));
#endif


  //LEGEND
  if(/*flip*/eepromReadFlipScreen()){
    displayDrawLine(/*X1*/96-11, /*Y1*/0, /*X2*/96-11, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/96-8, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/96-8, /*Y*/59, 1);    
  }
  else{/*no flip*/
    displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/2, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  }
  
  displayUpdate();
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
  
  if (index == MENU_SETTINS_SELECTED_BEEP) { //Set sound
    //setMode(MODE_MENU_SET_BEEP_SOUND); 
    byte beepCurrent = eepromReadBeepSound();
    beepCurrent++;
    if(beepCurrent > 4) beepCurrent = 0;
    eepromSaveBeepSound(beepCurrent);
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
