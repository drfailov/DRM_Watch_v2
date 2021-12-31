/*Screen with main watchface*/
long modeWatchFaceBacklightTimeout = 10000;
long modeWatchFaceBacklightEnabledTime = millis();

void modeWatchFaceSetup() {
  displayInit();
  modeWatchFaceBacklightEnabledTime = millis();    
  attachInterrupt(1, modeWatchFaceButtonUp, HIGH); //up
  attachInterrupt(0, wakeUp, HIGH);  //down
}

void modeWatchFaceLoop() {
  if (isButtonDownPressed()) {
    beep();
    setMode(MODE_MENU_MAIN);
    return;
  }
  
  byte hour = rtcGetHours();
  byte minute = rtcGetMinutes();
  byte second = rtcGetSeconds();
  byte day = rtcGetDay();
  byte month = rtcGetMonth();
  int year = rtcGetYear();

  {//alert
    //play melody and mark this day as playen if:
    //-alert enabled
    //-in this day was not playen
    //-this is right time to play

    bool alertIsEnabled = eepromReadAlertEnabled();
    byte alertLastRunDay = eepromReadAlertLastDayRun();
    byte alertTimeHour = eepromReadAlertHour();
    byte alertTimeMinute = eepromReadAlertMinute();
    byte alertMelodyIndex = eepromReadAlertMelodyIndex();
    
    if(alertIsEnabled){
      if(alertLastRunDay != day){
        if((hour == alertTimeHour && minute >= alertTimeMinute) || (hour > alertTimeHour)){
          eepromSaveAlertLastDayRun(day);
          long timeStarted = millis();
          long playTime = 120000;
          displayBacklightOn();
          while(melodyPlayerPlayMelody(getMelodyByIndex(alertMelodyIndex)) && millis() - timeStarted < playTime);
        }
      }
    }
  }

  byte wtf = eepromReadWatchface();
  if(wtf == 3){
    drawWatchFace3(hour, minute, second, day, month, year);
  }
  else if(wtf == 2){
    drawWatchFace2(hour, minute, second, day, month, year);
  }
  else{
    drawWatchFace1(hour, minute, second, day, month, year);
  }
  
  { //Baclight
    if(millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceBacklightTimeout)
      displayBacklightOn();
    else
      displayBacklightOff();
  }

  byte sleepTime = eepromReadSleepTime();
  if(batteryIsLowPower()) //если разряжен, то макс интервал
    sleepTime = 8;
#ifdef LOG
  Serial.flush();
  Serial.end();
#endif  
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
#ifdef LOG  
  Serial.begin(115200);
#endif
}

void modeWatchFaceFinish() {
  detachInterrupt(0);
  detachInterrupt(1);
}

void modeWatchFaceButtonUp(){
  modeWatchFaceBacklightEnabledTime = millis();
}

void wakeUp(){ //to react for button
  
}
