/*Used to test new functionality*/

void modeDebugScreen1Setup() {
  displayInit();
}

void modeDebugScreen1Loop() {
  if(isButtonUpPressed()){
    beep();
    displayMessage(F("Иди нахуй."));
  }
  if(isButtonDownPressed()){
    beep();
    goToWatchface();
    return;
  } 
  
  
  
  displayClear();
  { 
    float voltage = batteryVoltage();
    displayDrawText(0, 0, 1, F("Volt: "));
    char chars[10];
    dtostrf(voltage, 4, 2, chars);
    displayDrawText(40, 0, 1, chars);
    displayDrawText(40 + (strlen(chars) * 6), 0, 1, F(" v"));
  }
  {
    bool isCharging = batteryIsCharging();
    displayDrawText(0, 10, 1, F("Charging: "));
    if (isCharging)
      displayDrawText(60, 10, 1, F("Yes"));
    else
      displayDrawText(60, 10, 1, F("No"));
  }
  { 
    int ram = freeRam();
    displayDrawText(0, 20, 1, F("RAM: "));
    char chars[10];
    ltoa(ram, chars, DEC);
    displayDrawText(35 + (strlen(chars) * 6), 20, 1, F(" bytes"));
    displayDrawText(35, 20, 1, chars);
  }
//  {
//    bool isChargeComplete = batteryIsChargeComplete();
//    displayDrawText(0, 30, 1, F("Complete: "));
//    if (isChargeComplete)
//      displayDrawText(60, 30, 1, F("HIGH"));
//    else
//      displayDrawText(60, 30, 1, F("LOW"));
//  }
  displayDrawCheck(0, 61, 1);
  displayUpdate();
  
}

void modeDebugScreen1Finish() {

}
