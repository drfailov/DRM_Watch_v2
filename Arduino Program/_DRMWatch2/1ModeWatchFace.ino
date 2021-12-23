/*Screen with main watchface*/
long modeWatchFace1BacklightTimeout = 10000;
long modeWatchFace1BacklightEnabledTime = millis();

void modeWatchFace1Setup() {
  displayInit();
  modeWatchFace1BacklightEnabledTime = millis();    
  attachInterrupt(1, modeWatchFace1ButtonUp, HIGH); //up
  attachInterrupt(0, wakeUp, HIGH);  //down
}

void modeWatchFace1Loop() {
  if (isButtonDownPressed()) {
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  }
  displayClear();

  { //time
    int hour = rtcGetHours();
    int minute = rtcGetMinutes();
    int second = rtcGetSeconds();
    int hour1 = hour / 10;
    int hour2 = hour - (hour1 * 10);
    int minute1 = minute / 10;
    int minute2 = minute - (minute1 * 10);
    int second1 = second / 10;
    int second2 = second - (second1 * 10);
    
    displayDrawNumber(hour1   ,  5, 20, 3, 4);
    displayDrawNumber(hour2   , 19, 20, 3, 4);
    displayDrawNumber(10      , 34, 20, 3, 4); // :
    displayDrawNumber(minute1 , 40, 20, 3, 4);
    displayDrawNumber(minute2 , 54, 20, 3, 4);
    displayDrawNumber(10      , 70, 25, 2, 3); // :
    displayDrawNumber(second1 , 75, 25, 2, 3);
    displayDrawNumber(second2 , 85, 25, 2, 3);
  }
  
  {//date
    int day = rtcGetDay();
    int month = rtcGetMonth();
    int year = rtcGetYear();

    char chars[11];
    sprintf(chars, "%02d.%02d.%04d", day, month, year);
    displayDrawText(0, 0, 1, chars);
  }
  
  {//Temperature
    float temp = rtcGetTemp();
    char chars[8];
    /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
    dtostrf(temp, 4, 1, chars);
    sprintf(chars, "%sC", chars);
    displayDrawText(0, 61, 1, chars);
  }
  
  {//battery
    float voltage = batteryVoltage();
    bool isCharging = batteryIsCharging();
    bool isLowPower = batteryIsLowPower();
    byte level = 0;
    if(voltage > 3.40) level = 1;
    if(voltage > 3.65) level = 2;
    if(voltage > 3.85) level = 3;
    if(voltage > 4.00) level = 4;
  
    displayDrawBattery(78, 0, level, isCharging, isLowPower);
  }
  if(eepromReadSilentMode()){ 
    displayDrawSilentModeIcon(85, 60, 1);
  }

  displayUpdate();
  { //Baclight
    if(millis() - modeWatchFace1BacklightEnabledTime < modeWatchFace1BacklightTimeout)
      displayBacklightOn();
    else
      displayBacklightOff();
  }

  
  byte sleepTime = eepromReadSleepTime();

  if(batteryIsLowPower()) //если разряжен, то макс интервал
    sleepTime = 8;
  Serial.flush();
  Serial.end();
  delay(5);
  if(sleepTime == eepromSleepTime05sec){
    setMillis(millis() + 500);
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime1sec){
    setMillis(millis() + 1000);
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime2sec){
    setMillis(millis() + 2000);
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime4sec){
    setMillis(millis() + 4000);
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime8sec){
    setMillis(millis() + 8000);
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  else{ //if some garbage in memory
    setMillis(millis() + 1000);
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  }
  Serial.begin(115200);
}

void modeWatchFace1Finish() {
  detachInterrupt(0);
  detachInterrupt(1);
}

void modeWatchFace1ButtonUp(){
  modeWatchFace1BacklightEnabledTime = millis();
  beep();
}

void wakeUp(){ //to react for button
  
}
