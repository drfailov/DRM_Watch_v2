#include "GenericWatchface.cpp"
#include "1WatchfaceDrmWatch.cpp"
#include <util/atomic.h>
#include <LowPower.h>
void(* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0


GenericWatchface* watchfaces[] = {
  new WatchfaceDrmWatch()
};

//Включение и выключение цифкрблатов
#define WATCHFACE_DRMWATCH 1   //Это циферблат по умолчанию. Закомментировать чтобы отключило циферблат
#define WATCHFACE_DRMLITE 2   //Закомментировать чтобы отключило циферблат
#define WATCHFACE_NOMENS 3   //Закомментировать чтобы отключило циферблат
#define WATCHFACE_ZUBAT 4   //Закомментировать чтобы отключило циферблат
#define WATCHFACE_NOKIA 5   //Закомментировать чтобы отключило циферблат


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
//Значения констант режимов
#define MODE_INIT (byte)0
#define MODE_WATCHFACE (byte)1
#define MODE_MENU_MAIN (byte)2
#define MODE_STATUS (byte)3
#define MODE_MENU_MELODIES (byte)4
#define MODE_MENU_SETTINGS (byte)5
#define MODE_MENU_SET_TIME (byte)6
#define MODE_MENU_SET_SLEEP_TIME (byte)7
#define MODE_ABOUT (byte)8
#define MODE_MENU_SET_BEEP_SOUND (byte)9
#define MODE_MENU_SET_SILENT_MODE (byte)10
#define MODE_MENU_APPS (byte)11
#define MODE_STOPWATCH (byte)12
#define MODE_SET_ALARM (byte)13
#define MODE_MENU_SET_WATCHFACE (byte)14
#define MODE_ZRADA (byte)15

//Переменная в которой хранится текущий режим
byte _mode = -1;



void setup() {
#ifdef LOG
  Serial.begin(115200);
  Serial.println(F("\nDRM Watch V2"));
  Serial.println(version);
  Serial.print(F("- Date "));
  Serial.print(F(__DATE__));
  Serial.print(F(" at "));
  Serial.println(F(__TIME__));
#endif  
  setMode(MODE_INIT);
}

void loop() {
  if (_mode == MODE_INIT) modeInitLoop();
  if (_mode == MODE_WATCHFACE) modeWatchFaceLoop(false);
  if (_mode == MODE_MENU_MAIN ) modeMenuMainLoop();
  if (_mode == MODE_STATUS ) modeStatusLoop();
  if (_mode == MODE_MENU_MELODIES ) modeMenuMelodiesLoop();
  if (_mode == MODE_MENU_SETTINGS ) modeMenuSettingsLoop();
  if (_mode == MODE_MENU_SET_TIME ) modeMenuSetTimeLoop();
  if (_mode == MODE_MENU_SET_SLEEP_TIME ) modeMenuSetSleepTimeLoop();
  if (_mode == MODE_ABOUT ) modeAboutLoop();
  if (_mode == MODE_MENU_SET_BEEP_SOUND ) modeMenuSetBeepSoundLoop();
  if (_mode == MODE_MENU_SET_SILENT_MODE ) modeMenuSetSilentModeLoop();
  if (_mode == MODE_MENU_APPS ) modeMenuAppsLoop();
  if (_mode == MODE_STOPWATCH ) modeStopwatchLoop();
  if (_mode == MODE_SET_ALARM ) modeSetAlarmLoop();
  if (_mode == MODE_MENU_SET_WATCHFACE ) modeMenuSetWatchfaceLoop();
  if (_mode == MODE_ZRADA ) modeZradaLoop();
}

void setMode(int _modeNew) {
  if (_mode == _modeNew)
    return;
#ifdef LOG
  Serial.print(F("Mode "));
  Serial.print(_mode);
  Serial.print(F(" -> "));
  Serial.println(_modeNew);
  
  Serial.print(F("RAM: "));
  Serial.println(freeRam());
#endif
  //finish old
  if (_mode == MODE_INIT) modeInitFinish();
  if (_mode == MODE_WATCHFACE) modeWatchFaceFinish();
  if (_mode == MODE_MENU_MAIN ) modeMenuMainFinish();
  if (_mode == MODE_STATUS ) modeStatusFinish();
  if (_mode == MODE_MENU_MELODIES ) modeMenuMelodiesFinish();
  if (_mode == MODE_MENU_SETTINGS ) modeMenuSettingsFinish();
  if (_mode == MODE_MENU_SET_TIME ) modeMenuSetTimeFinish();
  if (_mode == MODE_MENU_SET_SLEEP_TIME ) modeMenuSetSleepTimeFinish();
  if (_mode == MODE_ABOUT ) modeAboutFinish();
  if (_mode == MODE_MENU_SET_BEEP_SOUND ) modeMenuSetBeepSoundFinish();
  if (_mode == MODE_MENU_SET_SILENT_MODE ) modeMenuSetSilentModeFinish();
  if (_mode == MODE_MENU_APPS ) modeMenuAppsFinish();
  if (_mode == MODE_STOPWATCH ) modeStopwatchFinish();
  if (_mode == MODE_SET_ALARM ) modeSetAlarmFinish();
  if (_mode == MODE_MENU_SET_WATCHFACE ) modeMenuSetWatchfaceFinish();
  if (_mode == MODE_ZRADA) modeZradaFinish();
  
  //init new
  if (_modeNew == MODE_INIT) modeInitSetup();
  if (_modeNew == MODE_WATCHFACE) modeWatchFaceSetup();
  if (_modeNew == MODE_MENU_MAIN ) modeMenuMainSetup();
  if (_modeNew == MODE_STATUS ) modeStatusSetup();
  if (_modeNew == MODE_MENU_MELODIES ) modeMenuMelodiesSetup();
  if (_modeNew == MODE_MENU_SETTINGS ) modeMenuSettingsSetup();
  if (_modeNew == MODE_MENU_SET_TIME ) modeMenuSetTimeSetup();
  if (_modeNew == MODE_MENU_SET_SLEEP_TIME ) modeMenuSetSleepTimeSetup();
  if (_modeNew == MODE_ABOUT ) modeAboutSetup();
  if (_modeNew == MODE_MENU_SET_BEEP_SOUND ) modeMenuSetBeepSoundSetup();
  if (_modeNew == MODE_MENU_SET_SILENT_MODE ) modeMenuSetSilentModeSetup();
  if (_modeNew == MODE_MENU_APPS ) modeMenuAppsSetup();
  if (_modeNew == MODE_STOPWATCH ) modeStopwatchSetup();
  if (_modeNew == MODE_SET_ALARM ) modeSetAlarmSetup();
  if (_modeNew == MODE_MENU_SET_WATCHFACE ) modeMenuSetWatchfaceSetup();
  if (_modeNew == MODE_ZRADA) modeZradaSetup();
  
  
  _mode = _modeNew;
}

//Выплнить всю последовательность действий требуемых для выполнения перезагрузки.
void reboot(){
#ifdef LANG_EN
  Display.displayMessage(F("Rebooting..."));
#endif
#ifdef LANG_RU
  Display.displayMessage(F("Перезагрузка"));
#endif    
  Display.displayPowerOff();
  delay(1000);
  resetFunc(); //вызываем reset
}

//переключить на режим выбранного в меню вотчфейса из любого места программы
void goToWatchface(){
  setMode(MODE_WATCHFACE);
}

//объём свободной оперативки нужен для отладки
int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

//обновляем счётчик миллисекунд во время сна чтобы не ломались счётчики
void setMillis(unsigned long ms){
    extern unsigned long timer0_millis;
    ATOMIC_BLOCK (ATOMIC_RESTORESTATE) {
        timer0_millis = ms;
    }
}
