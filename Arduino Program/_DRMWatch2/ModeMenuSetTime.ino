#include "Display.cpp"
#include "Buttons.cpp"
#include "RTC.cpp"
#include "Buzzer.cpp"
/*Screen allows to set time*/

#define MENU_SET_TIME_SELECTED_HOUR 0
#define MENU_SET_TIME_SELECTED_MINUTE 1
#define MENU_SET_TIME_SELECTED_DAY 2
#define MENU_SET_TIME_SELECTED_MONTH  3
#define MENU_SET_TIME_SELECTED_YEAR 4
#define MENU_SET_TIME_SELECTED_SAVE 5
#define MENU_SET_TIME_SELECTED_BACK 6


byte modeMenuSetTimeHours = 00;
byte modeMenuSetTimeMinutes = 00;
byte modeMenuSetTimeSeconds = 00;

byte modeMenuSetTimeDays = 01;
byte modeMenuSetTimeMonths = 01;
int modeMenuSetTimeYears = 2021;


void modeMenuSetTimeSetup(){
  Generic.selected = MENU_SET_TIME_SELECTED_HOUR;
  modeMenuSetTimeHours = RTC.rtcGetHours();
  modeMenuSetTimeMinutes = RTC.rtcGetMinutes();
  modeMenuSetTimeDays = RTC.rtcGetDay();
  modeMenuSetTimeMonths = RTC.rtcGetMonth();
  modeMenuSetTimeYears = RTC.rtcGetYear();
  digitalWrite(pinLcdBacklight, HIGH);
}

void modeMenuSetTimeLoop(){
  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonDown.isButtonPressed():ButtonUp.isButtonPressed()){
    Buzzer.beep();
    //change value
    if(Generic.selected == MENU_SET_TIME_SELECTED_HOUR) {//hours
      modeMenuSetTimeHours ++;
      if(modeMenuSetTimeHours > 23) modeMenuSetTimeHours = 0;
    }
    if(Generic.selected == MENU_SET_TIME_SELECTED_MINUTE) {//Minutes
      modeMenuSetTimeMinutes ++;
      if(modeMenuSetTimeMinutes > 59) modeMenuSetTimeMinutes = 0;
    }
    if(Generic.selected == MENU_SET_TIME_SELECTED_DAY) {//Day
      modeMenuSetTimeDays ++;
      if(modeMenuSetTimeDays > 31) modeMenuSetTimeDays = 0;
    }
    if(Generic.selected == MENU_SET_TIME_SELECTED_MONTH) {//Month
      modeMenuSetTimeMonths ++;
      if(modeMenuSetTimeMonths > 12) modeMenuSetTimeMonths = 0;
    }
    if(Generic.selected == MENU_SET_TIME_SELECTED_YEAR) {//Month
      modeMenuSetTimeYears ++;
      if(modeMenuSetTimeYears > 2050) modeMenuSetTimeYears = 2020;
    }
    
    if(Generic.selected == MENU_SET_TIME_SELECTED_SAVE) {//SAVE
      RTC.rtcSetTime(modeMenuSetTimeYears, modeMenuSetTimeMonths, modeMenuSetTimeDays, modeMenuSetTimeHours, modeMenuSetTimeMinutes);
      { //fix alarm, предотвращение включения будильника сразу в момент установки
        byte hour = RTC.rtcGetHours();
        byte minute = RTC.rtcGetMinutes();
        byte day = RTC.rtcGetDay();
        
        byte modeSetAlarmHour = MyEEPROM.eepromReadAlertHour();
        byte modeSetAlarmMinute = MyEEPROM.eepromReadAlertMinute();
        if((hour == modeSetAlarmHour && minute >= modeSetAlarmMinute) || (hour > modeSetAlarmHour))
          MyEEPROM.eepromSaveAlertLastDayRun(day);
        else
          MyEEPROM.eepromSaveAlertLastDayRun(0);
      } 
      Display.displayMessage((const __FlashStringHelper*)textSaved);
      goToWatchface();
      return;
    }
    if(Generic.selected == MENU_SET_TIME_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_SETTINGS);
      return;
    }
  }

  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonUp.isButtonPressed():ButtonDown.isButtonPressed()){
    Buzzer.beep();
    //move next
    Generic.selected ++;
    if(Generic.selected > 6) Generic.selected = 0;
  }


  //draw
  Display.displayClear();
  byte xOffset = 15;
  if (/*flip*/MyEEPROM.eepromReadFlipScreen())
    xOffset = 5;

#ifdef LANG_EN
  Display.displayDrawText(xOffset+0, /*y*/2, /*c*/1, F("Set time"));
#endif
#ifdef LANG_RU
  Display.displayDrawText(xOffset+0, /*y*/2, /*c*/1, F("Зaдaть вpeмя"));
#endif
  
  
  Display.displayDrawText(xOffset+20, 19, 1, ":");
  //hours
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+0, /*y*/15, /*number*/modeMenuSetTimeHours, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_HOUR);
  //minutes
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+25, /*y*/15, /*number*/modeMenuSetTimeMinutes, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_MINUTE);
  

  Display.displayDrawText(xOffset+20, 39, 1, ".");
  Display.displayDrawText(xOffset+45, 39, 1, ".");
  //days
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+0, /*y*/33, /*number*/modeMenuSetTimeDays, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_DAY);
  //months
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+25, /*y*/33, /*number*/modeMenuSetTimeMonths, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_MONTH); 
  //Year
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+50, /*y*/33, /*number*/modeMenuSetTimeYears%2000, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_YEAR); 

  
  //Save
  Display.displayDrawIconWithFrame(/*x*/xOffset+0, /*y*/53, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawCheck, /*selected*/Generic.selected  == MENU_SET_TIME_SELECTED_SAVE);
  //BACK
  Display.displayDrawIconWithFrame(/*x*/xOffset+25, /*y*/53, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected  == MENU_SET_TIME_SELECTED_BACK);
    

  //button icons
  if(Generic.selected == MENU_SET_TIME_SELECTED_SAVE || Generic.selected == MENU_SET_TIME_SELECTED_BACK)
    Display.displayDrawCheck(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/2, 1);
  else
    Display.displayDrawText(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/2, /*C*/1, "+");
  Display.displayDrawArrowRight(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/59, 1);
  
  Display.displayUpdate();
}

void modeMenuSetTimeFinish(){
  //digitalWrite(pinLcdBacklight, LOW);
}
