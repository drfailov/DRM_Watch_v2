/*Screen with main watchface*/
const long modeWatchFaceBacklightTimeout = 7000; //мс, Сколько времени после последнего действия будет светить подстветка
const long modeWatchFaceAminationTimeout = 20000; //мс, сколько времени после последнего действия будет идти анимация и часы не будт спать
long modeWatchFaceBacklightEnabledTime;

void modeWatchFaceSetup() {
  displayInit();
  modeWatchFaceBacklightEnabledTime = millis();
  attachInterrupt(1, wakeUp, HIGH); //down
  attachInterrupt(0, wakeUp, HIGH);  //up
  modeWatchFaceLoop(true);
}

void modeWatchFaceLoop(bool animate) {
  //Обработка подстветки
  if (isButtonDownPressed())
    modeWatchFaceBacklightEnabledTime = millis(); 
  
  bool backlight = millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceBacklightTimeout;
  if(backlight)
    displayBacklightOn();
  else
    displayBacklightOff();
    

  //Загрузка данных
  byte hour = rtcGetHours();
  byte minute = rtcGetMinutes();
  byte second = rtcGetSeconds();
  byte dayOfWeek = rtcGetDayOfWeek();
  byte day = rtcGetDay();
  byte month = rtcGetMonth();
  int year = rtcGetYear();

  //Обработка будильника
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
          long playTime = 180000;
          displayBacklightOn();
          while (melodyPlayerPlayMelody(getMelodyByIndex(alertMelodyIndex)) && millis() - timeStarted < playTime);
        }
      }
    }
  }

  //Отрисовка циферблата
  byte wtf = eepromReadWatchface(); //Номер выбранного циферблата из памяти
  if (wtf >= watchfacesCount) wtf = 0;
  if(wfs[wtf] != 0)
    wfs[wtf](hour, minute, second, day, month, year, dayOfWeek, animate ? 5 : 0);
  displayUpdate();

  //Обработка сна
  bool sleepInThisFrame = true;
  if (millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceAminationTimeout) sleepInThisFrame = false; //первые ... секунд не спать чтобы шла анимация. А потом часы идут в сон.
  if (animate) sleepInThisFrame = false; //После первой отрисовки не впадать в сон, чтобы сразу отрисовался второй раз. Чтобы кнопки инициализировались.
  if (backlight) sleepInThisFrame = false; //если нажата кнопка вниз, не спать 
  
  

  if (sleepInThisFrame) {
    #ifdef LOG
      Serial.flush();
      Serial.end();
    #endif
    delay(5);
    setMillis(millis() + 8000);
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    #ifdef LOG
      Serial.begin(115200);
    #endif
  }



  //Обработка кнопок
  if (isButtonUpPressed()) {
    if (isButtonUpHold()) {
      powerOff();
      return;
    }
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  }
}

void modeWatchFaceFinish() {
  detachInterrupt(0);
  detachInterrupt(1);
}

void wakeUp() { //to react for button
  displayBacklightOn();
  modeWatchFaceBacklightEnabledTime = millis();
}
