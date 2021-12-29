/*Used to test new functionality*/

void modeStatusSetup() {
  displayInit();
}

void modeStatusLoop() {
  if(isButtonDownPressed()){
    beep();
    goToWatchface();
    return;
  } 
    
  displayClear();
  drawParameter(00, 00, F("VLT"), _batteryRawVoltage());
  drawParameter(65, 00, F("CHG"), batteryIsCharging());
  drawParameter(00, 10, F("RAM"), freeRam());
  drawParameter(00, 20, F("SLP"), eepromReadSleepTime());
  drawParameter(50, 20, F("SLN"), eepromReadSilentMode());
  drawParameter(00, 30, F("BEE"), eepromReadBeepSound());
  drawParameter(50, 30, F("aEN"), eepromReadAlertEnabled());
  drawParameter(00, 40, F("aHR"), eepromReadAlertHour());
  drawParameter(50, 40, F("aMI"), eepromReadAlertMinute());
  drawParameter(00, 50, F("aLD"), eepromReadAlertLastDayRun());
  drawParameter(50, 50, F("aME"), eepromReadAlertMelodyIndex());
  drawParameter(50, 60, F("WTF"), eepromReadWatchface());

  displayDrawCheck(0, 61, 1);
  displayUpdate();
  
}

void drawParameter(byte x, byte y, const __FlashStringHelper* name, int value){
  int ram = freeRam();
  displayDrawText(x, y, 1, name);
  ltoa(value, buffer, DEC);
  displayDrawText(x+6+strlen_P((PGM_P)name)*6, y, 1, buffer);
  displayDrawText(x+strlen_P((PGM_P)name)*6, y, 1, F(":"));
}

void modeStatusFinish() {

}
