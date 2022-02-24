#include <Arduino.h>
#include "Generic.cpp"
#include "Display.cpp"
#include "Buzzer.cpp"
#include "Buttons.cpp"
/*Used to test new functionality*/

void modeStatusSetup() {
  modeStatusDraw(); 
  genericMenuSetup();
}

void modeStatusLoop() {
  if(ButtonDown.isButtonPressed() || ButtonUp.isButtonPressed() ){
    Buzzer.beep();
    goToWatchface();
    return;
  } 
  
  modeStatusDraw();  
}

void modeStatusDraw(){
  Display.displayClear();
  
  drawParameter(00, 00, F("VLT"), Battery.batteryRawVoltage());
  drawParameter(00, 10, F("RAM"), freeRam());
  drawParameter(00, 20, F("CHG"), Battery.batteryIsCharging());
  drawParameter(00, 30, F("aLD"), MyEEPROM.eepromReadAlertLastDayRun());
  drawParameter(00, 40, F("WTF"), MyEEPROM.eepromReadWatchface());

  Display.displayUpdate();
}

void drawParameter(byte x, byte y, const __FlashStringHelper* name, int value){
  int ram = freeRam();
  Display.displayDrawText(x, y, 1, name);
  ltoa(value, Generic.buffer, DEC);
  Display.displayDrawText(x+6+strlen_P((PGM_P)name)*6, y, 1, Generic.buffer);
  Display.displayDrawText(x+strlen_P((PGM_P)name)*6, y, 1, F(":"));
}

void modeStatusFinish() {

}
