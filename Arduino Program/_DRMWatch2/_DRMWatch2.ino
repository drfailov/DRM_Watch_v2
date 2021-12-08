#include "lcd1202.h"
#include <LowPower.h>

const byte pinButtonDown = 2; //active high
const byte pinButtonUp = 3; //active high
const byte pinLcdRst = 5;
const byte pinLcdCs = 6;
const byte pinLcdMosi = 7;
const byte pinUsbVoltage = 9;
const byte pinChargeCompletePin = 10;
const byte pinLcdSck = 11;
const byte pinBuzzer = 12; //passive
const byte pinLed = 13;  //active high
const byte pinLcdBacklight = 15;  //A1, active high
// A4 - RTC SDA
// A5 - RTC SCL




const byte MODE_INIT = 0;
const byte MODE_WATCHFACE1 = 1;
const byte MODE_MENU_MAIN = 2;
const byte MODE_DEBUG_SCREEN1 = 3;
const byte MODE_MENU_MELODIES = 4;
const byte MODE_MENU_SETTINGS = 5;
const byte MODE_MENU_SET_TIME = 6;


byte _mode = -1;

void setup() {
  Serial.begin(115200);
  Serial.print(F("\nStarting DRM Watch program\n"));
  Serial.print(F("- Compiled with c++ version "));
  Serial.print(F(__VERSION__));
  Serial.print(F("\n- On "));
  Serial.print(F(__DATE__));
  Serial.print(F(" at "));
  Serial.print(F(__TIME__));
  Serial.print(F("\n"));
  
  setMode(MODE_INIT);
}

void loop() {
  if (_mode == MODE_INIT) modeInitLoop();
  if (_mode == MODE_WATCHFACE1) modeWatchFace1Loop();
  if (_mode == MODE_MENU_MAIN ) modeMenuMainLoop();
  if (_mode == MODE_DEBUG_SCREEN1 ) modeDebugScreen1Loop();
  if (_mode == MODE_MENU_MELODIES ) modeMenuMelodiesLoop();
  if (_mode == MODE_MENU_SETTINGS ) modeMenuSettingsLoop();
  if (_mode == MODE_MENU_SET_TIME ) modeMenuSetTimeLoop();
}

void setMode(int _modeNew) {
  if (_mode == _modeNew)
    return;
  Serial.print(F("Update mode "));
  Serial.print(_mode);
  Serial.print(F(" -> "));
  Serial.print(_modeNew);
  Serial.println(F(" ..."));

  //finish old
  if (_mode == MODE_INIT) modeInitFinish();
  if (_mode == MODE_WATCHFACE1) modeWatchFace1Finish();
  if (_mode == MODE_MENU_MAIN ) modeMenuMainFinish();
  if (_mode == MODE_DEBUG_SCREEN1 ) modeDebugScreen1Finish();
  if (_mode == MODE_MENU_MELODIES ) modeMenuMelodiesFinish();
  if (_mode == MODE_MENU_SETTINGS ) modeMenuSettingsFinish();
  if (_mode == MODE_MENU_SET_TIME ) modeMenuSetTimeFinish();
  

  //init new
  if (_modeNew == MODE_INIT) modeInitSetup();
  if (_modeNew == MODE_WATCHFACE1) modeWatchFace1Setup();
  if (_modeNew == MODE_MENU_MAIN ) modeMenuMainSetup();
  if (_modeNew == MODE_DEBUG_SCREEN1 ) modeDebugScreen1Setup();
  if (_modeNew == MODE_MENU_MELODIES ) modeMenuMelodiesSetup();
  if (_modeNew == MODE_MENU_SETTINGS ) modeMenuSettingsSetup();
  if (_modeNew == MODE_MENU_SET_TIME ) modeMenuSetTimeSetup();

  _mode = _modeNew;
}

//переключить на режим выбранного в меню вотчфейса из любого места программы
void goToWatchface(){
  setMode(MODE_WATCHFACE1);
}
