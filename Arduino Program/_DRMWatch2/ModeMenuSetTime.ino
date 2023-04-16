
#include "Buttons.cpp"
/*Screen allows to set time*/

#define MENU_SET_TIME_SELECTED_BACK 0
#define MENU_SET_TIME_SELECTED_HOUR 1
#define MENU_SET_TIME_SELECTED_MINUTE 2
#define MENU_SET_TIME_SELECTED_DAY 3
#define MENU_SET_TIME_SELECTED_MONTH  4
#define MENU_SET_TIME_SELECTED_YEAR 5
#define MENU_SET_TIME_SELECTED_SAVE 6


byte modeMenuSetTimeHours = 00;
byte modeMenuSetTimeMinutes = 00;
byte modeMenuSetTimeSeconds = 00;

byte modeMenuSetTimeDays;
byte modeMenuSetTimeMonths;
int modeMenuSetTimeYears;


void modeMenuSetTimeSetup(){
  genericMenuSetup();
  modeMenuSetTimeHours = rtcGetHours();
  modeMenuSetTimeMinutes = rtcGetMinutes();
  modeMenuSetTimeDays = rtcGetDay();
  modeMenuSetTimeMonths = rtcGetMonth();
  modeMenuSetTimeYears = rtcGetYear();
}

void modeMenuSetTimeLoop(){
  if (isButtonUpPressed()){ 
    beep();
    //change value
    if(selected == MENU_SET_TIME_SELECTED_HOUR) //hours
      modeMenuSetTimeHours ++;
    if(selected == MENU_SET_TIME_SELECTED_MINUTE) //Minutes
      modeMenuSetTimeMinutes ++;  
    if(selected == MENU_SET_TIME_SELECTED_DAY) //Day
      modeMenuSetTimeDays ++;  
    if(selected == MENU_SET_TIME_SELECTED_MONTH) //Month
      modeMenuSetTimeMonths ++;  
    if(selected == MENU_SET_TIME_SELECTED_YEAR) //Month
      modeMenuSetTimeYears ++;
    
    if(selected == MENU_SET_TIME_SELECTED_SAVE) {//SAVE
      rtcSetTime(modeMenuSetTimeYears, modeMenuSetTimeMonths, modeMenuSetTimeDays, modeMenuSetTimeHours, modeMenuSetTimeMinutes);
      //fix alarm, предотвращение включения будильника сразу в момент установки
      resetAlertMetadata();
      displayMessage((const __FlashStringHelper*)textSaved);
      goToWatchface();
      return;
    }
    if(selected == MENU_SET_TIME_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_SETTINGS);
      return;
    }
  }

  if (isButtonDownPressed()){
    beep();
    selected ++;
  }
  
  if(selected > 6) selected = 0;
  if(modeMenuSetTimeHours > 23) modeMenuSetTimeHours = 0;
  if(modeMenuSetTimeMinutes > 59) modeMenuSetTimeMinutes = 0;
  if(modeMenuSetTimeDays > 31) modeMenuSetTimeDays = 0;
  if(modeMenuSetTimeMonths > 12) modeMenuSetTimeMonths = 0;
  if(modeMenuSetTimeYears < 2020 || modeMenuSetTimeYears > 2040) modeMenuSetTimeYears = 2020;


  //draw
  displayClear();
  byte xOffset = 15;
  if (/*flip*/eepromReadFlipScreen())
    xOffset = 0;


  //BACK
  displayDrawIconWithFrame(/*x*/xOffset, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawArrowLeft, /*selected*/selected == MENU_SET_TIME_SELECTED_BACK);

  //TITLE
#ifdef LANG_EN
  displayDrawText(xOffset+25, 4, 1, F("Time"));
#endif
#ifdef LANG_RU
  displayDrawText(xOffset+25, 4, 1, F("Bpeмя"));
#endif
#ifdef LANG_RU
  displayDrawText(xOffset+25, 4, 1, F("Час"));
#endif


  
  
  displayDrawText(xOffset+20, 21, 1, ":");
  //hours
  displayDraw2DigitNumberWithFrame(/*x*/xOffset+10, /*y*/17, /*number*/modeMenuSetTimeHours, /*selected*/selected == MENU_SET_TIME_SELECTED_HOUR);
  //minutes
  displayDraw2DigitNumberWithFrame(/*x*/xOffset+35, /*y*/17, /*number*/modeMenuSetTimeMinutes, /*selected*/selected == MENU_SET_TIME_SELECTED_MINUTE);
  

  displayDrawText(xOffset+30, 41, 1, ".");
  displayDrawText(xOffset+55, 41, 1, ".");
  //days
  displayDraw2DigitNumberWithFrame(/*x*/xOffset+10, /*y*/35, /*number*/modeMenuSetTimeDays, /*selected*/selected == MENU_SET_TIME_SELECTED_DAY);
  //months
  displayDraw2DigitNumberWithFrame(/*x*/xOffset+35, /*y*/35, /*number*/modeMenuSetTimeMonths, /*selected*/selected == MENU_SET_TIME_SELECTED_MONTH); 
  //Year
  displayDraw2DigitNumberWithFrame(/*x*/xOffset+60, /*y*/35, /*number*/modeMenuSetTimeYears%2000, /*selected*/selected == MENU_SET_TIME_SELECTED_YEAR); 

  
  //Save
  displayDrawIconWithFrame(/*x*/xOffset+30, /*y*/53, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawCheck, /*selected*/selected  == MENU_SET_TIME_SELECTED_SAVE);
    

  
  drawLegend();
  
  displayUpdate();
}

void modeMenuSetTimeFinish(){
  //digitalWrite(pinLcdBacklight, LOW);
}
