#include "Display.cpp"
#include "Buttons.cpp"
#include "Battery.cpp"
#include "Buzzer.cpp"
#include "RTC.cpp"
#include "MyEEPROM.cpp"
#include "Generic.cpp"

/*Screen with main watchface*/
const long modeWatchFaceBacklightTimeout = 7000;
long modeWatchFaceBacklightEnabledTime = millis();
byte modeWatchFaceFramesCounter = 0; //used to count frames and draw animation without sleep

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
  //  ButtonUp.isButtonPressed();
  //  ButtonDown.isButtonPressed();
  modeWatchFaceLoop(true);
}

void modeWatchFaceLoop(bool animate) {
  //Обработка подстветки
  { //Baclight
    bool backlight = millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceBacklightTimeout;
    if (/*flip*/MyEEPROM.eepromReadFlipScreen() ? ButtonUp.readDebounce() : ButtonDown.readDebounce()) backlight = true; //если нажата кнопка вниз, не тушить подсветку
    
    if (backlight)
      Display.displayBacklightOn();
    else
      Display.displayBacklightOff();
  }

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
          long playTime = 120000;
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
  byte updateMode = WATCHFACE_UPDATE_MODE_8S_1FRAME;
  if (watchface != 0) {
    updateMode = watchface->updateMode();
    watchface->drawWatchface(hour, minute, second, day, month, year, dayOfWeek, animate ? 5 : 0);
  }
  else {
    Display.displayDrawText(20, 30, 1, F("Select WTF"));
    Display.displayUpdate();
  }

  //Обработка сна
  modeWatchFaceFramesCounter ++;
  if (modeWatchFaceFramesCounter > 10) modeWatchFaceFramesCounter = 0;
  byte sleepTime = 8;
  if (updateMode == WATCHFACE_UPDATE_MODE_8S_1FRAME || updateMode == WATCHFACE_UPDATE_MODE_8S_10FRAMES) sleepTime = 8;
  if (updateMode == WATCHFACE_UPDATE_MODE_1S_1FRAME || updateMode == WATCHFACE_UPDATE_MODE_1S_10FRAMES) sleepTime = 1;
  if ((updateMode == WATCHFACE_UPDATE_MODE_8S_10FRAMES || updateMode == WATCHFACE_UPDATE_MODE_1S_10FRAMES) && modeWatchFaceFramesCounter != 10) sleepTime = 0; //в режимах на 10 кадров не спать на всех кадрах кроме одного
  if (updateMode == WATCHFACE_UPDATE_MODE_NO_SLEEP) sleepTime = 0; //Если режим работы текущего циферблата не предусматривает сон, не спать
  if (animate) sleepTime = 0; //После первой отрисовки не впадать в сон, чтобы сразу отрисовался второй раз. Чтобы кнопки инициализировались.
  if (Battery.batteryIsLowPower()) sleepTime = 8; //если разряжен, то макс интервал
  if (/*flip*/MyEEPROM.eepromReadFlipScreen() ? ButtonUp.readDebounce() : ButtonDown.readDebounce()) sleepTime = 0; //если нажата кнопка вниз, не спать

  if (sleepTime != 0) {
#ifdef LOG
    Serial.flush();
    Serial.end();
#endif
    delay(5);
    if (sleepTime == 1) {
      setMillis(millis() + 1000);
      LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
    }
    else {
      setMillis(millis() + 8000);
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }
#ifdef LOG
    Serial.begin(115200);
#endif
  }



  //Обработка кнопок
  //if(! animate){ //не обрабатывать кнопки если это анимированный вывод на экран (предотвращает блокировку кнопками первой отрисовки экрана)
  if (/*flip*/MyEEPROM.eepromReadFlipScreen() ? ButtonDown.isButtonPressed() : ButtonUp.isButtonPressed()) {
    if (/*flip*/MyEEPROM.eepromReadFlipScreen() ? ButtonDown.waitHold() : ButtonUp.waitHold()) {
      reboot();
      return;
    }
    Buzzer.beep();
    setMode(MODE_MENU_MAIN);
    return;
  }
  //}
}

void modeWatchFaceFinish() {
  detachInterrupt(0);
  detachInterrupt(1);
}

void wakeUp() { //to react for button
  modeWatchFaceBacklightEnabledTime = millis();
}
