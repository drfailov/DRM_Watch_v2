#include "Display.cpp"
#include "Buttons.cpp"
#include "Battery.cpp"
#include "Buzzer.cpp"
#include "RTC.cpp"
#include "MyEEPROM.cpp"
#include "Generic.cpp"

/*Screen with main watchface*/
const long modeWatchFaceBacklightTimeout = 15000;
long modeWatchFaceBacklightEnabledTime = millis();

void modeWatchFaceSetup() {
  Display.displayInit();
  modeWatchFaceBacklightEnabledTime = millis();
  if(/*flip*/MyEEPROM.eepromReadFlipScreen()){
    attachInterrupt(1, modeWatchFaceTriggerBacklight, HIGH); //down
    attachInterrupt(0, wakeUp, HIGH);  //up
  }
  else{
    attachInterrupt(0, modeWatchFaceTriggerBacklight, HIGH); //down
    attachInterrupt(1, wakeUp, HIGH);  //up
  }
  modeWatchFaceLoop(true);
}

void modeWatchFaceLoop(bool animate) {
  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonDown.isButtonPressed():ButtonUp.isButtonPressed()) {
    Buzzer.beep();
    setMode(MODE_MENU_MAIN);
    return;
  }

  byte hour = RTC.rtcGetHours();
  byte minute = RTC.rtcGetMinutes();
  byte second = RTC.rtcGetSeconds();
  byte dayOfWeek = RTC.rtcGetDayOfWeek();
  byte day = RTC.rtcGetDay();
  byte month = RTC.rtcGetMonth();
  int year = RTC.rtcGetYear();

  { //alert
    //play melody and mark this day as playen if:
    //-alert enabled
    //-in this day was not playen
    //-this is right time to play

    bool alertIsEnabled = MyEEPROM.eepromReadAlertEnabled();
    byte alertLastRunDay = MyEEPROM.eepromReadAlertLastDayRun();
    byte alertTimeHour = MyEEPROM.eepromReadAlertHour();
    byte alertTimeMinute = MyEEPROM.eepromReadAlertMinute();
    byte alertMelodyIndex = MyEEPROM.eepromReadAlertMelodyIndex();

    if (alertIsEnabled) {
      if (alertLastRunDay != day) {
        if ((hour == alertTimeHour && minute >= alertTimeMinute) || (hour > alertTimeHour)) {
          MyEEPROM.eepromSaveAlertLastDayRun(day);
          long timeStarted = millis();
          long playTime = 120000;
          Display.displayBacklightOn();
          while (melodyPlayerPlayMelody(getMelodyByIndex(alertMelodyIndex)) && millis() - timeStarted < playTime);
        }
      }
    }
  }

  //Номер выбранного циферблата из памяти
  byte wtf = MyEEPROM.eepromReadWatchface();
  if(wtf >= watchfacesCount) wtf = 0;
  GenericWatchface *watchface = watchfaces[wtf]; 
  if(watchface != 0){
    watchface->drawWatchface(hour, minute, second, day, month, year, dayOfWeek, animate?5:0);
  }
  else{
    Display.displayDrawText(20, 30, 1, F("Select WTF"));
    Display.displayUpdate();
  }


  { //Baclight
    if (millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceBacklightTimeout)
      Display.displayBacklightOn();
    else
      Display.displayBacklightOff();
  }

  byte sleepTime = MyEEPROM.eepromReadSleepTime();
  if (Battery.batteryIsLowPower()) //если разряжен, то макс интервал
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

void modeWatchFaceTriggerBacklight() {
  modeWatchFaceBacklightEnabledTime = millis();
}

void wakeUp() { //to react for button

}
