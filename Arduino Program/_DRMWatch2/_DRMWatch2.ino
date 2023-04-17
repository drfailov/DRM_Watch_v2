//#include "GenericWatchface.cpp"
//#include "WatchfaceDrmWatch.cpp"
//#include "WatchfaceDrmLite.cpp"
//#include "WatchfaceNomens.cpp"
//#include "WatchfaceMatrix.cpp"
//#include "WatchfaceMinimal.cpp"
//#include "WatchfaceLife.cpp"
//#include "WatchfaceThermo.cpp"

#include <util/atomic.h>
#include <LowPower.h>

/*Данные, которые требуется по всей программе*/
//Базовые константы
#define version F("v1.32")   //Версию менять здесь
//#define LANG_EN  //Раскомментировать чтобы использовать английский язык меню
//#define LANG_RU   //Раскомментировать чтобы использовать русский язык меню
#define LANG_UA   //Розкоментувати щоб використовувати українську мову в меню
//#define LOG   //Закомментировать чтобы отключило логи
#define  AUTO_EXIT_TIMEOUT 120000 //MS  //Время до автоматического выхода с менюшек

//Распиновка
#define pinButtonDown (byte)2 //active high
#define pinButtonUp (byte)3 //active high
#define pinLcdRst (byte)5
#define pinLcdCs (byte)6
#define pinLcdMosi (byte)7
#define pinLcdSck (byte)8   
#define pinLcdPower (byte)10
#define pinUsbVoltage (byte)11  
#define pinBuzzer (byte)12 //passive
#define pinLed (byte)13  //active high
#define pinLcdBacklight (byte)15  //A1, active high
// A4 - RTC SDA
// A5 - RTC SCL

//размер текстового буфера. Чем меньше тем экономнее.
#define BUFFER_SIZE 25
//последнее действие кнопками, нужно для автоматического выхода
long genericMenuLastActionTime = 0;   
//общий на всю программу текстовый буфер чтобы не объявлять каждый раз локальную.
char buffer[BUFFER_SIZE]; 
//Общий на всю программу счётчик для выбора элементов из списка
byte selected = 0;
//используется на экранах с анимацией
bool animate;

//Общий формат вывода данных много где используется
const char* dateFormat = "%02d.%02d.%04d";
const char* timeFormat = "%02d:%02d";



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
#define MODE_ABOUT (byte)8
#define MODE_MENU_APPS (byte)11
#define MODE_STOPWATCH (byte)12
#define MODE_SET_ALARM (byte)13
#define MODE_GAME_OF_LIFE (byte)14
#define MODE_OFF (byte)15
//Переменная в которой хранится текущий режим
byte _mode = -1;

//Набор циферблатов 
typedef void (*WF) (const byte hour, const byte minute, const byte second, const byte day, const byte month, const int year, const byte dayOfWeek, const byte animate);
const byte watchfacesCount = 4;
WF wfs[watchfacesCount];

void setup() {
  byte i=0;
  //Набор циферблатов следует менять именно здесь. 
  //number of WFs here need to less or equal than watchfacesCount, otherwise will crash
  //wfs[i++] = watchfaceZubat;
  wfs[i++] = watchfaceCalibri;
  //wfs[i++] = watchfaceXelibri;
  wfs[i++] = WatchfaceDrmLite;
  wfs[i++] = WatchfaceDrmWatch;
  //wfs[i++] = WatchfaceLife;
  //wfs[i++] = WatchfaceMinimal;
  //wfs[i++] = WatchfaceMatrix;
  //wfs[i++] = WatchfaceThermo;
  wfs[i++] = WatchfaceNomens;
  
   
#ifdef LOG
  Serial.begin(115200);
  Serial.println(F("DRM Watch V2"));
  Serial.println(version);
  Serial.print(F(__DATE__));
  Serial.print(F(" "));
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
  if (_mode == MODE_ABOUT ) modeAboutLoop();
  if (_mode == MODE_MENU_APPS ) modeMenuAppsLoop();
  if (_mode == MODE_STOPWATCH ) modeStopwatchLoop();
  if (_mode == MODE_SET_ALARM ) modeSetAlarmLoop();
  if (_mode == MODE_GAME_OF_LIFE ) modeGameOfLifeLoop();
  if (_mode == MODE_OFF ) modeOffLoop();
}

void setMode(int _modeNew) {
  if (_mode == _modeNew)
    return;
#ifdef LOG
  Serial.print(F("Mode "));
  Serial.print(_mode);
  Serial.print(F("->"));
  Serial.println(_modeNew);
  
  Serial.print(F("RAM: "));
  Serial.println(freeRam());
#endif
  //animate transition
  displayTransition();
  //finish old
  if (_mode == MODE_INIT) modeInitFinish();
  if (_mode == MODE_WATCHFACE) modeWatchFaceFinish();
  if (_mode == MODE_STATUS ) modeStatusFinish();
  if (_mode == MODE_MENU_SET_TIME ) modeMenuSetTimeFinish();
  if (_mode == MODE_ABOUT ) modeAboutFinish();
  if (_mode == MODE_STOPWATCH ) modeStopwatchFinish();
  if (_mode == MODE_SET_ALARM ) modeSetAlarmFinish();
  if (_mode == MODE_GAME_OF_LIFE ) modeGameOfLifeFinish();
  
  //init new
  if (_modeNew == MODE_INIT) modeInitSetup();
  if (_modeNew == MODE_WATCHFACE) modeWatchFaceSetup();
  if (_modeNew == MODE_MENU_MAIN ) modeMenuMainSetup();
  if (_modeNew == MODE_STATUS ) modeStatusSetup();
  if (_modeNew == MODE_MENU_MELODIES ) modeMenuMelodiesSetup();
  if (_modeNew == MODE_MENU_SETTINGS ) modeMenuSettingsSetup();
  if (_modeNew == MODE_MENU_SET_TIME ) modeMenuSetTimeSetup();
  if (_modeNew == MODE_ABOUT ) modeAboutSetup();
  if (_modeNew == MODE_MENU_APPS ) modeMenuAppsSetup();
  if (_modeNew == MODE_STOPWATCH ) modeStopwatchSetup();
  if (_modeNew == MODE_SET_ALARM ) modeSetAlarmSetup();  
  if (_modeNew == MODE_GAME_OF_LIFE ) modeGameOfLifeSetup(); 
  if (_modeNew == MODE_OFF ) modeOffInit();  
  
  
  _mode = _modeNew;
}

//Выплнить всю последовательность действий требуемых для выполнения перезагрузки.
void powerOff(){
  setMode(MODE_OFF);
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
