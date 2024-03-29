#include "Display.cpp"
#include "Buttons.cpp"
#include "RTC.cpp"
#include "Buzzer.cpp"
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
  modeMenuSetTimeHours = RTC.rtcGetHours();
  modeMenuSetTimeMinutes = RTC.rtcGetMinutes();
  modeMenuSetTimeDays = RTC.rtcGetDay();
  modeMenuSetTimeMonths = RTC.rtcGetMonth();
  modeMenuSetTimeYears = RTC.rtcGetYear();
}

void modeMenuSetTimeLoop(){
  if (isButtonUpPressed()){ 
    Buzzer.beep();
    //change value
    if(Generic.selected == MENU_SET_TIME_SELECTED_HOUR) //hours
      modeMenuSetTimeHours ++;
    if(Generic.selected == MENU_SET_TIME_SELECTED_MINUTE) //Minutes
      modeMenuSetTimeMinutes ++;  
    if(Generic.selected == MENU_SET_TIME_SELECTED_DAY) //Day
      modeMenuSetTimeDays ++;  
    if(Generic.selected == MENU_SET_TIME_SELECTED_MONTH) //Month
      modeMenuSetTimeMonths ++;  
    if(Generic.selected == MENU_SET_TIME_SELECTED_YEAR) //Month
      modeMenuSetTimeYears ++;
    
    if(Generic.selected == MENU_SET_TIME_SELECTED_SAVE) {//SAVE
      RTC.rtcSetTime(modeMenuSetTimeYears, modeMenuSetTimeMonths, modeMenuSetTimeDays, modeMenuSetTimeHours, modeMenuSetTimeMinutes);
      //fix alarm, предотвращение включения будильника сразу в момент установки
      resetAlertMetadata();
      Display.displayMessage((const __FlashStringHelper*)textSaved);
      goToWatchface();
      return;
    }
    if(Generic.selected == MENU_SET_TIME_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_SETTINGS);
      return;
    }
  }

  if (isButtonDownPressed()){
    Buzzer.beep();
    Generic.selected ++;
  }
  
  if(Generic.selected > 6) Generic.selected = 0;
  if(modeMenuSetTimeHours > 23) modeMenuSetTimeHours = 0;
  if(modeMenuSetTimeMinutes > 59) modeMenuSetTimeMinutes = 0;
  if(modeMenuSetTimeDays > 31) modeMenuSetTimeDays = 0;
  if(modeMenuSetTimeMonths > 12) modeMenuSetTimeMonths = 0;
  if(modeMenuSetTimeYears < 2020 || modeMenuSetTimeYears > 2040) modeMenuSetTimeYears = 2020;


  //draw
  Display.displayClear();
  byte xOffset = 15;
  if (/*flip*/MyEEPROM.eepromReadFlipScreen())
    xOffset = 0;


  //BACK
  Display.displayDrawIconWithFrame(/*x*/xOffset, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_BACK);

  //TITLE
  Display.displayDrawText(xOffset+25, 4, 1, F("Time"));


  
  
  Display.displayDrawText(xOffset+20, 21, 1, ":");
  //hours
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+10, /*y*/17, /*number*/modeMenuSetTimeHours, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_HOUR);
  //minutes
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+35, /*y*/17, /*number*/modeMenuSetTimeMinutes, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_MINUTE);
  

  Display.displayDrawText(xOffset+30, 41, 1, ".");
  Display.displayDrawText(xOffset+55, 41, 1, ".");
  //days
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+10, /*y*/35, /*number*/modeMenuSetTimeDays, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_DAY);
  //months
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+35, /*y*/35, /*number*/modeMenuSetTimeMonths, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_MONTH); 
  //Year
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+60, /*y*/35, /*number*/modeMenuSetTimeYears%2000, /*selected*/Generic.selected == MENU_SET_TIME_SELECTED_YEAR); 

  
  //Save
  Display.displayDrawIconWithFrame(/*x*/xOffset+30, /*y*/53, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawCheck, /*selected*/Generic.selected  == MENU_SET_TIME_SELECTED_SAVE);
    

  //button icons
  Display.drawLegend();
  
//  if(Generic.selected == MENU_SET_TIME_SELECTED_SAVE || Generic.selected == MENU_SET_TIME_SELECTED_BACK)
//    Display.displayDrawCheck(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/2, 1);
//  else
//    Display.displayDrawText(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/2, /*C*/1, "+");
//  Display.displayDrawArrowRight(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/59, 1);
  
  Display.displayUpdate();
}

void modeMenuSetTimeFinish(){
  //digitalWrite(pinLcdBacklight, LOW);
}
