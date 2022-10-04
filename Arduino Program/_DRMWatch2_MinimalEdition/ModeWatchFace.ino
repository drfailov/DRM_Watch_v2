#include "Display.cpp"
#include "Buttons.cpp"
#include "Battery.cpp"
#include "Buzzer.cpp"
#include "RTC.cpp"
#include "MyEEPROM.cpp"
#include "Generic.cpp"

/*Screen with main watchface*/
const long modeWatchFaceBacklightTimeout = 7000; //мс, Сколько времени после последнего действия будет светить подстветка
const long modeWatchFaceAminationTimeout = 20000; //мс, сколько времени после последнего действия будет идти анимация и часы не будт спать
long modeWatchFaceBacklightEnabledTime;

void modeWatchFaceSetup() {
  Display.displayInit();
  modeWatchFaceBacklightEnabledTime = millis();
  if (/*flip*/MyEEPROM.eepromReadFlipScreen()) {
    attachInterrupt(1, wakeUp, HIGH); //down
    attachInterrupt(0, wakeUp, HIGH);  //up
  }
  else {
    attachInterrupt(0, wakeUp, HIGH); //down
    attachInterrupt(1, wakeUp, HIGH);  //up
  }
  modeWatchFaceLoop(true);
}

void modeWatchFaceLoop(bool animate) {
  //Обработка подстветки
  if (/*flip*/MyEEPROM.eepromReadFlipScreen() ? ButtonUp.readDebounce() : ButtonDown.readDebounce())  //если нажата кнопка вниз, не тушить подсветку
    modeWatchFaceBacklightEnabledTime = millis(); 
  
  bool backlight = millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceBacklightTimeout;
  if(backlight)
    Display.displayBacklightOn();
  else
    Display.displayBacklightOff();
    

  //Загрузка данных
  byte hour = RTC.rtcGetHours();
  byte minute = RTC.rtcGetMinutes();
  byte second = RTC.rtcGetSeconds();
  byte dayOfWeek = RTC.rtcGetDayOfWeek();
  byte day = RTC.rtcGetDay();
  byte month = RTC.rtcGetMonth();
  int year = RTC.rtcGetYear();

  //Обработка будильника
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
          long playTime = 180000;
          Display.displayBacklightOn();
          while (melodyPlayerPlayMelody(getMelodyByIndex(alertMelodyIndex)) && millis() - timeStarted < playTime);
        }
      }
    }
  }

  //Отрисовка циферблата
  //Номер выбранного циферблата из памяти
  byte wtf = MyEEPROM.eepromReadWatchface();
  if (wtf >= watchfacesCount) wtf = 0;
  GenericWatchface *watchface = watchfaces[wtf];
  if (watchface != 0) {
    watchface->drawWatchface(hour, minute, second, day, month, year, dayOfWeek, animate ? 5 : 0);
  }

  //Обработка сна
  bool sleepInThisFrame = true;
  if (millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceAminationTimeout) sleepInThisFrame = false; //первые ... секунд не спать чтобы шла анимация. А потом часы идут в сон.
  if (animate) sleepInThisFrame = false; //После первой отрисовки не впадать в сон, чтобы сразу отрисовался второй раз. Чтобы кнопки инициализировались.
  if (backlight) sleepInThisFrame = false; //если нажата кнопка вниз, не спать 
  
  

  if (sleepInThisFrame) {
    delay(5);
    setMillis(millis() + 8000);
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }



  //Обработка кнопок
  if (isButtonUpPressed()) {
    if (isButtonUpHold()) {
      reboot();
      return;
    }
    Buzzer.beep();
    setMode(MODE_MENU_MAIN);
    return;
  }
}

void modeWatchFaceFinish() {
  detachInterrupt(0);
  detachInterrupt(1);
}

void wakeUp() { //to react for button
  modeWatchFaceBacklightEnabledTime = millis();
}
