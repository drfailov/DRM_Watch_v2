/*Show watchfacw menu by triggerimg GenericMenu*/

void modeMenuSetWatchfaceSetup() {
  genericMenuSetup();
  //Выбор стандартного выбранного пункта меню исходя из текущей настройки в памяти
  
  
  byte value = MyEEPROM.eepromReadWatchface();
  if(value > watchfacesCount) value = 0;
  genericMenuSelectPosition = value;

}

void modeMenuSetWatchfaceLoop() {
  char* modeMenuSetWatchfaceItems[watchfacesCount + 1];
  for(byte i = 0; i < watchfacesCount; i++){
    modeMenuSetWatchfaceItems[i] = watchfaces[i]->name();
  }
  modeMenuSetWatchfaceItems[watchfacesCount] = menuItemBack;
  
  genericMenuLoop(watchfacesCount + 1, modeMenuSetWatchfaceItems, modeMenuSetWatchfaceSelected, false);
}

void modeMenuSetWatchfaceFinish() {
  genericMenuFinish();
}

void modeMenuSetWatchfaceSelected(byte index) {
  if(index < watchfacesCount){
    MyEEPROM.eepromSaveWatchface(index);
    Display.displayMessage((const __FlashStringHelper*)(watchfaces[index] -> name()));
    goToWatchface();
  }
  else{
    setMode(MODE_MENU_SETTINGS);
  }
}
