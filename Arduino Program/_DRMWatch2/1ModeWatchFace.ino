/*Screen with main watchface*/
long modeWatchFaceBacklightTimeout = 15000;
long modeWatchFaceBacklightEnabledTime = millis();

void modeWatchFaceSetup() {
  displayInit();
  modeWatchFaceBacklightEnabledTime = millis();
  attachInterrupt(1, modeWatchFaceButtonUp, HIGH); //up
  attachInterrupt(0, wakeUp, HIGH);  //down
  modeWatchFaceLoop(true);
}

void modeWatchFaceLoop(bool animate) {
  if (isButtonDownPressed()) {
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  }

  byte hour = rtcGetHours();
  byte minute = rtcGetMinutes();
  byte second = rtcGetSeconds();
  byte dayOfWeek = rtcGetDayOfWeek();
  byte day = rtcGetDay();
  byte month = rtcGetMonth();
  int year = rtcGetYear();

  { //alert
    //play melody and mark this day as playen if:
    //-alert enabled
    //-in this day was not playen
    //-this is right time to play

    bool alertIsEnabled = eepromReadAlertEnabled();
    byte alertLastRunDay = eepromReadAlertLastDayRun();
    byte alertTimeHour = eepromReadAlertHour();
    byte alertTimeMinute = eepromReadAlertMinute();
    byte alertMelodyIndex = eepromReadAlertMelodyIndex();

    if (alertIsEnabled) {
      if (alertLastRunDay != day) {
        if ((hour == alertTimeHour && minute >= alertTimeMinute) || (hour > alertTimeHour)) {
          eepromSaveAlertLastDayRun(day);
          long timeStarted = millis();
          long playTime = 120000;
          displayBacklightOn();
          while (melodyPlayerPlayMelody(getMelodyByIndex(alertMelodyIndex)) && millis() - timeStarted < playTime);
        }
      }
    }
  }

  byte wtf = eepromReadWatchface();
  if (wtf == 3) {
    drawWatchFace3(hour, minute, second, day, month, year, dayOfWeek, animate?5:0);
  }
  else if (wtf == 2) {
    drawWatchFace2(hour, minute, second, day, month, year, dayOfWeek, animate?5:0);
  }
  else if (wtf == 4) {
    drawWatchFace4(hour, minute, second, day, month, year, dayOfWeek, animate?5:0);
  }
  else {
    drawWatchFace1(hour, minute, second, day, month, year, dayOfWeek, animate?5:0);
  }

  { //Baclight
    if (millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceBacklightTimeout)
      displayBacklightOn();
    else
      displayBacklightOff();
  }

  byte sleepTime = eepromReadSleepTime();
  if (batteryIsLowPower()) //если разряжен, то макс интервал
    sleepTime = 8;
#ifdef LOG
  Serial.flush();
  Serial.end();
#endif
  delay(5);
  if (sleepTime == eepromSleepTime05sec) {
    setMillis(millis() + 500);
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime1sec) {
    setMillis(millis() + 1000);
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime2sec) {
    setMillis(millis() + 2000);
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime4sec) {
    setMillis(millis() + 4000);
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }
  else if (sleepTime == eepromSleepTime8sec) {
    setMillis(millis() + 8000);
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  else { //if some garbage in memory
    setMillis(millis() + 1000);
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
  }
#ifdef LOG
  Serial.begin(115200);
#endif
}

void modeWatchFaceFinish() {
  detachInterrupt(0);
  detachInterrupt(1);
}

void modeWatchFaceButtonUp() {
  modeWatchFaceBacklightEnabledTime = millis();
}

void wakeUp() { //to react for button

}

void modeWatchFaceDrawBattery(byte x, byte y) {
  float voltage = batteryVoltage();
  bool isCharging = batteryIsCharging();
  bool isLowPower = batteryIsLowPower();
  byte level = 0;
  if (voltage > 3.40) level = 1;
  if (voltage > 3.65) level = 2;
  if (voltage > 3.85) level = 3;
  if (voltage > 4.00) level = 4;

  displayDrawBattery(x, y, level, isCharging, isLowPower);
}

void modeWatchFaceDrawDayOfWeek(byte x, byte y, byte dayOfWeek, bool color) { //
  __FlashStringHelper* txt;
#ifdef LANG_RU
  if (dayOfWeek == 1) txt = F("Пн");
  if (dayOfWeek == 2) txt = F("Вт");
  if (dayOfWeek == 3) txt = F("Ср");
  if (dayOfWeek == 4) txt = F("Чт");
  if (dayOfWeek == 5) txt = F("Пт");
  if (dayOfWeek == 6) txt = F("Сб");
  if (dayOfWeek == 0) txt = F("Вс");
#endif
#ifdef LANG_EN
  if (dayOfWeek == 1) txt = F("Mon");
  if (dayOfWeek == 2) txt = F("Tue");
  if (dayOfWeek == 3) txt = F("Wed");
  if (dayOfWeek == 4) txt = F("Thu");
  if (dayOfWeek == 5) txt = F("Fri");
  if (dayOfWeek == 6) txt = F("Sat");
  if (dayOfWeek == 0) txt = F("Sun");
#endif
  displayDrawText(x, y, color, txt);
}
