#include "Display.cpp"
/*Screen allows to set time*/

#define MENU_SET_TIME_SELECTED_HOUR 0
#define MENU_SET_TIME_SELECTED_MINUTE 1
#define MENU_SET_TIME_SELECTED_DAY 2
#define MENU_SET_TIME_SELECTED_MONTH  3
#define MENU_SET_TIME_SELECTED_YEAR 4
#define MENU_SET_TIME_SELECTED_SAVE 5
#define MENU_SET_TIME_SELECTED_BACK 6
int modeMenuSetTimeSelected = MENU_SET_TIME_SELECTED_HOUR;


byte modeMenuSetTimeHours = 00;
byte modeMenuSetTimeMinutes = 00;
byte modeMenuSetTimeSeconds = 00;

byte modeMenuSetTimeDays = 01;
byte modeMenuSetTimeMonths = 01;
int modeMenuSetTimeYears = 2021;


void modeMenuSetTimeSetup(){
  modeMenuSetTimeHours = rtcGetHours();
  modeMenuSetTimeMinutes = rtcGetMinutes();
  modeMenuSetTimeDays = rtcGetDay();
  modeMenuSetTimeMonths = rtcGetMonth();
  modeMenuSetTimeYears = rtcGetYear();
  digitalWrite(pinLcdBacklight, HIGH);
  modeMenuSetTimeSelected = 0;
}

void modeMenuSetTimeLoop(){
  if (isButtonUpPressed()) {
    beep();
    //change value
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_HOUR) {//hours
      modeMenuSetTimeHours ++;
      if(modeMenuSetTimeHours > 23) modeMenuSetTimeHours = 0;
    }
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_MINUTE) {//Minutes
      modeMenuSetTimeMinutes ++;
      if(modeMenuSetTimeMinutes > 59) modeMenuSetTimeMinutes = 0;
    }
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_DAY) {//Day
      modeMenuSetTimeDays ++;
      if(modeMenuSetTimeDays > 31) modeMenuSetTimeDays = 0;
    }
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_MONTH) {//Month
      modeMenuSetTimeMonths ++;
      if(modeMenuSetTimeMonths > 12) modeMenuSetTimeMonths = 0;
    }
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_YEAR) {//Month
      modeMenuSetTimeYears ++;
      if(modeMenuSetTimeYears > 2050) modeMenuSetTimeYears = 2020;
    }
    
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_SAVE) {//SAVE
      rtcSetTime(modeMenuSetTimeYears, modeMenuSetTimeMonths, modeMenuSetTimeDays, modeMenuSetTimeHours, modeMenuSetTimeMinutes);
      { //fix alarm, предотвращение включения будильника сразу в момент установки
        byte hour = rtcGetHours();
        byte minute = rtcGetMinutes();
        byte day = rtcGetDay();
        
        byte modeSetAlarmHour = eepromReadAlertHour();
        byte modeSetAlarmMinute = eepromReadAlertMinute();
        if((hour == modeSetAlarmHour && minute >= modeSetAlarmMinute) || (hour > modeSetAlarmHour))
          eepromSaveAlertLastDayRun(day);
        else
          eepromSaveAlertLastDayRun(0);
      } 
      Display.displayMessage((const __FlashStringHelper*)textSaved);
      goToWatchface();
      return;
    }
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_SETTINGS);
      return;
    }
  }

  if (isButtonDownPressed()) {
    beep();
    //move next
    modeMenuSetTimeSelected ++;
    if(modeMenuSetTimeSelected > 6) modeMenuSetTimeSelected = 0;
  }

  
  Display.displayClear();
#ifdef LANG_EN
  Display.displayDrawText(15, 2, 1, F("Set time"));
#endif
#ifdef LANG_RU
  Display.displayDrawText(15, 2, 1, F("Зaдaть вpeмя"));
#endif
  if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_SAVE || modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_BACK)
    Display.displayDrawCheck(/*X*/1, /*Y*/2, 1);
  else
    Display.displayDrawText(/*X*/1, /*Y*/2, /*C*/1, "+");
  Display.displayDrawArrowRight(/*X*/1, /*Y*/59, 1);
  
  Display.displayDrawText(35, 19, 1, ":");
  //hours
  Display.displayDraw2DigitNumberWithFrame(/*x*/15, /*y*/15, /*number*/modeMenuSetTimeHours, /*selected*/modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_HOUR);
  //minutes
  Display.displayDraw2DigitNumberWithFrame(/*x*/40, /*y*/15, /*number*/modeMenuSetTimeMinutes, /*selected*/modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_MINUTE);
  

  Display.displayDrawText(35, 39, 1, ".");
  Display.displayDrawText(60, 39, 1, ".");
  //days
  Display.displayDraw2DigitNumberWithFrame(/*x*/15, /*y*/33, /*number*/modeMenuSetTimeDays, /*selected*/modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_DAY);
  //months
  Display.displayDraw2DigitNumberWithFrame(/*x*/40, /*y*/33, /*number*/modeMenuSetTimeMonths, /*selected*/modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_MONTH); 
  //Year
  Display.displayDraw2DigitNumberWithFrame(/*x*/65, /*y*/33, /*number*/modeMenuSetTimeYears%2000, /*selected*/modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_YEAR); 

  
  { //Save
    byte x = 15;
    byte y = 53;
#ifdef LANG_EN
    const __FlashStringHelper* chars = F("Save");    
#endif
#ifdef LANG_RU
    const __FlashStringHelper* chars = F("Coxp");    
#endif
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_SAVE){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x+4, y+4, 1, chars);
    }
  }
  { //BACK
    byte x = 50;
    byte y = 53;
#ifdef LANG_EN
    const __FlashStringHelper* chars = F("Back");
#endif
#ifdef LANG_RU
    const __FlashStringHelper* chars = F("Haзд");
#endif
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_BACK){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  Display.displayUpdate();
}

void modeMenuSetTimeFinish(){
  //digitalWrite(pinLcdBacklight, LOW);
}
