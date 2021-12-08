int debugScreen1Counter = 10;
int debugScreen1BacklightCounter = 0; //сколько секунд осталось подсветке светить. 0 = выключена

void modeDebugScreen1Setup() {
  debugScreen1Counter = 10;
}

void modeDebugScreen1Loop() {
  if(isButtonUpPressed()){
    beep();
    debugScreen1BacklightCounter = 10;
  }
  
  if(isButtonDownPressed()){
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  }
  displayClear();
  float voltage = batteryVoltage();
  bool isCharging = batteryIsCharging();
  bool isChargeComplete = batteryIsChargeComplete();
  
  debugScreen1Counter ++;
  {
    displayDrawText(0, 0, 1, "Volt: ");
    char chars[10];
    dtostrf(voltage, 4, 2, chars);
    displayDrawText(40, 0, 1, chars);
    displayDrawText(40 + (strlen(chars) * 6), 0, 1, " v");
  }
  {
    displayDrawText(0, 10, 1, "Charging: ");
    if (isCharging)
      displayDrawText(60, 10, 1, "Yes");
    else
      displayDrawText(60, 10, 1, "No");
  }
  {
    displayDrawText(0, 20, 1, "Cnt: ");
    char chars[10];
    ltoa(debugScreen1Counter, chars, DEC);
    displayDrawText(35 + (strlen(chars) * 6), 20, 1, " pcs");
    displayDrawText(35, 20, 1, chars);
  }
  {
    displayDrawText(0, 30, 1, "Complete: ");
    if (isChargeComplete)
      displayDrawText(60, 30, 1, "HIGH");
    else
      displayDrawText(60, 30, 1, "LOW");
  }
  displayUpdate();

  debugScreen1BacklightCounter --;
  if(debugScreen1BacklightCounter < 0) debugScreen1BacklightCounter = 0;
  if(debugScreen1BacklightCounter > 0) 
    digitalWrite(pinLcdBacklight, HIGH);
  else 
    digitalWrite(pinLcdBacklight, LOW);

  
  Serial.flush();
  delay(50);
  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
}

void modeDebugScreen1Finish() {

}
