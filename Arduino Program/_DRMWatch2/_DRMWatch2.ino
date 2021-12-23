#include "lcd1202.h"
#include <LowPower.h>
#define version F("v0.20")
//#define LANG_EN
#define LANG_RU

//Pins
#define pinButtonDown (byte)2 //active high
#define pinButtonUp (byte)3 //active high
#define pinLcdRst (byte)5
#define pinLcdCs (byte)6
#define pinLcdMosi (byte)7
#define pinUsbVoltage (byte)9
#define pinLcdPower (byte)10
#define pinLcdSck (byte)11
#define pinBuzzer (byte)12 //passive
#define pinLed (byte)13  //active high
#define pinLcdBacklight (byte)15  //A1, active high
// A4 - RTC SDA
// A5 - RTC SCL


//sleep times
#define eepromSleepTime05sec (byte)0 
#define eepromSleepTime1sec (byte)1 
#define eepromSleepTime2sec (byte)2 
#define eepromSleepTime4sec (byte)4 
#define eepromSleepTime8sec (byte)8 

//beep sounds
#define eepromBeepSoundBeep (byte)0
#define eepromBeepSoundClick (byte)1
#define eepromBeepSoundTone (byte)2
#define eepromBeepSoundWhistle (byte)3
#define eepromBeepSoundNone (byte)4



/* Program contains several screens (menus, watchfaces...).
 * Every screen is a separate mode. Every mode contains of: modeSetup(), modeLoop(), modeFinish().
 * Screens can work independently. Modes divided into different files to ease.
 * Function loop() is routing loop() co correct dcreen according to active mode.
 * Also setMode() function is triggering modeSetup() and modeFinish() for every mode.
 * To change mode call: setMode(MODE_INIT);
 * When adding new mode, it needs to be declared: 
 *    - define constant for it,
 *    - loop() call for modeLoop()
 *    - call its setup() from setMode()
 *    - call its finish() from setMode()
*/
//Modes
#define MODE_INIT (byte)0
#define MODE_WATCHFACE1 (byte)1
#define MODE_MENU_MAIN (byte)2
#define MODE_DEBUG_SCREEN1 (byte)3
#define MODE_MENU_MELODIES (byte)4
#define MODE_MENU_SETTINGS (byte)5
#define MODE_MENU_SET_TIME (byte)6
#define MODE_MENU_SET_SLEEP_TIME (byte)7
#define MODE_ABOUT (byte)8
#define MODE_MENU_SET_BEEP_SOUND (byte)9
#define MODE_MENU_SET_SILENT_MODE (byte)10
#define MODE_MENU_APPS (byte)11
#define MODE_STOPWATCH (byte)12


byte _mode = -1;
//размер буфера. Чем меньше тем экономнее
#define BUFFER_SIZE 26
//общий на всю программу текстовый буфер чтобы не объявлять каждый раз локальную
char buffer[BUFFER_SIZE]; 

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
  if (_mode == MODE_MENU_SET_SLEEP_TIME ) modeMenuSetSleepTimeLoop();
  if (_mode == MODE_ABOUT ) modeAboutLoop();
  if (_mode == MODE_MENU_SET_BEEP_SOUND ) modeMenuSetBeepSoundLoop();
  if (_mode == MODE_MENU_SET_SILENT_MODE ) modeMenuSetSilentModeLoop();
  if (_mode == MODE_MENU_APPS ) modeMenuAppsLoop();
  if (_mode == MODE_STOPWATCH ) modeStopwatchLoop();
  
}

void setMode(int _modeNew) {
  if (_mode == _modeNew)
    return;
  Serial.print(F("Update mode "));
  Serial.print(_mode);
  Serial.print(F(" -> "));
  Serial.print(_modeNew);
  Serial.println(F(" ..."));
  
  Serial.print(F("Free ram: "));
  Serial.print(freeRam());
  Serial.println(F(" bytes."));

  //finish old
  if (_mode == MODE_INIT) modeInitFinish();
  if (_mode == MODE_WATCHFACE1) modeWatchFace1Finish();
  if (_mode == MODE_MENU_MAIN ) modeMenuMainFinish();
  if (_mode == MODE_DEBUG_SCREEN1 ) modeDebugScreen1Finish();
  if (_mode == MODE_MENU_MELODIES ) modeMenuMelodiesFinish();
  if (_mode == MODE_MENU_SETTINGS ) modeMenuSettingsFinish();
  if (_mode == MODE_MENU_SET_TIME ) modeMenuSetTimeFinish();
  if (_mode == MODE_MENU_SET_SLEEP_TIME ) modeMenuSetSleepTimeFinish();
  if (_mode == MODE_ABOUT ) modeAboutFinish();
  if (_mode == MODE_MENU_SET_BEEP_SOUND ) modeMenuSetBeepSoundFinish();
  if (_mode == MODE_MENU_SET_SILENT_MODE ) modeMenuSetSilentModeFinish();
  if (_mode == MODE_MENU_APPS ) modeMenuAppsFinish();
  if (_mode == MODE_STOPWATCH ) modeStopwatchFinish();
  

  //init new
  if (_modeNew == MODE_INIT) modeInitSetup();
  if (_modeNew == MODE_WATCHFACE1) modeWatchFace1Setup();
  if (_modeNew == MODE_MENU_MAIN ) modeMenuMainSetup();
  if (_modeNew == MODE_DEBUG_SCREEN1 ) modeDebugScreen1Setup();
  if (_modeNew == MODE_MENU_MELODIES ) modeMenuMelodiesSetup();
  if (_modeNew == MODE_MENU_SETTINGS ) modeMenuSettingsSetup();
  if (_modeNew == MODE_MENU_SET_TIME ) modeMenuSetTimeSetup();
  if (_modeNew == MODE_MENU_SET_SLEEP_TIME ) modeMenuSetSleepTimeSetup();
  if (_modeNew == MODE_ABOUT ) modeAboutSetup();
  if (_modeNew == MODE_MENU_SET_BEEP_SOUND ) modeMenuSetBeepSoundSetup();
  if (_modeNew == MODE_MENU_SET_SILENT_MODE ) modeMenuSetSilentModeSetup();
  if (_modeNew == MODE_MENU_APPS ) modeMenuAppsSetup();
  if (_modeNew == MODE_STOPWATCH ) modeStopwatchSetup();
  

  _mode = _modeNew;
}

//переключить на режим выбранного в меню вотчфейса из любого места программы
void goToWatchface(){
  setMode(MODE_WATCHFACE1);
}

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
