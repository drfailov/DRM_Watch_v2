#include <Arduino.h>

#include "Buttons.cpp"
/*Used to test new functionality*/

void modeStatusSetup() {
  modeStatusDraw(); 
  genericMenuSetup();
}

void modeStatusLoop() {
  if(isButtonUpPressed()){
    beep();
    goToWatchface();
    return;
  } 
  
  modeStatusDraw();  
}

void modeStatusDraw(){
  displayClear();
  
  drawParameter(00, 00, F("VLT"), batteryRawVoltage());
  drawParameter(00, 10, F("RAM"), freeRam());
  drawParameter(00, 20, F("CHG"), batteryIsCharging());
  drawParameter(00, 30, F("aLD"), eepromReadAlertLastDayRun());
  drawParameter(00, 40, F("WTF"), eepromReadWatchface());

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
