/*Screen with main watchface*/

int modeWatchFace1BacklightCounter = 10; //сколько секунд осталось подсветке светить. 0 = выключена

void modeWatchFace1Setup() {
  displayInit();
  byte sleepTime = eepromReadSleepTime();
  if(batteryIsLowPower()) //если разряжен, то макс интервал
    sleepTime = eepromSleepTime8sec;
  if(sleepTime == eepromSleepTime05sec) modeWatchFace1BacklightCounter = 20;
  if(sleepTime == eepromSleepTime1sec) modeWatchFace1BacklightCounter = 10;
  if(sleepTime == eepromSleepTime2sec) modeWatchFace1BacklightCounter = 5;
  if(sleepTime == eepromSleepTime4sec) modeWatchFace1BacklightCounter = 3;
  if(sleepTime == eepromSleepTime8sec) modeWatchFace1BacklightCounter = 2;
    
  attachInterrupt(0, wakeUp, HIGH);
  attachInterrupt(1, wakeUp, HIGH);
}

void modeWatchFace1Loop() {
  if (isButtonUpPressed()) {
    beep();
    byte sleepTime = eepromReadSleepTime();
    if(batteryIsLowPower()) //если разряжен, то макс интервал
      sleepTime = eepromSleepTime8sec;
    if(sleepTime == eepromSleepTime05sec) modeWatchFace1BacklightCounter = 20;
    if(sleepTime == eepromSleepTime1sec) modeWatchFace1BacklightCounter = 10;
    if(sleepTime == eepromSleepTime2sec) modeWatchFace1BacklightCounter = 5;
    if(sleepTime == eepromSleepTime4sec) modeWatchFace1BacklightCounter = 3;
    if(sleepTime == eepromSleepTime8sec) modeWatchFace1BacklightCounter = 2;
    delay(500);
  }

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
    modeWatchFace1BacklightCounter --;
    if (modeWatchFace1BacklightCounter < 0) modeWatchFace1BacklightCounter = 0;
    if (modeWatchFace1BacklightCounter > 0)
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
  if(sleepTime == eepromSleepTime05sec)
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
  else if (sleepTime == eepromSleepTime1sec)
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  else if (sleepTime == eepromSleepTime2sec)
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  else if (sleepTime == eepromSleepTime4sec)
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  else if (sleepTime == eepromSleepTime8sec)
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  else //if some garbage in memory
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  Serial.begin(115200);
}

void modeWatchFace1Finish() {
  detachInterrupt(0);
  detachInterrupt(1);
}

void wakeUp(){ //to react for button
  
}
