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
  if (watchface != 0) {
    watchface->drawWatchface(hour, minute, second, day, month, year, dayOfWeek, animate ? 5 : 0);
  }
  else {
    Display.displayDrawText(20, 30, 1, F("Select WTF"));
    Display.displayUpdate();
  }

  //Обработка сна
  byte sleepTime = 8;
  if (millis() - modeWatchFaceBacklightEnabledTime < modeWatchFaceAminationTimeout) sleepTime = 0; //первые ... секунд не спать чтобы шла анимация. А потом часы идут в сон.
  if (animate) sleepTime = 0; //После первой отрисовки не впадать в сон, чтобы сразу отрисовался второй раз. Чтобы кнопки инициализировались.
  if (/*flip*/MyEEPROM.eepromReadFlipScreen() ? ButtonUp.readDebounce() : ButtonDown.readDebounce()) sleepTime = 0; //если нажата кнопка вниз, не спать 
  
  

  if (sleepTime != 0) {
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
