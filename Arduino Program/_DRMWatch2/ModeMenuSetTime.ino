#define MENU_SET_TIME_SELECTED_BACK 0
#define MENU_SET_TIME_SELECTED_HOUR 1
#define MENU_SET_TIME_SELECTED_MINUTE 2
#define MENU_SET_TIME_SELECTED_DAY 3
#define MENU_SET_TIME_SELECTED_MONTH  4
#define MENU_SET_TIME_SELECTED_YEAR 5
#define MENU_SET_TIME_SELECTED_SAVE 6

byte modeMenuSetTimeHours;
byte modeMenuSetTimeMinutes;
byte modeMenuSetTimeSeconds;
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
  if(genericMenuRoutine(modeMenuSetTimeSelected, 7))return;  
  
  if(modeMenuSetTimeHours > 23) modeMenuSetTimeHours = 0;
  if(modeMenuSetTimeMinutes > 59) modeMenuSetTimeMinutes = 0;
  if(modeMenuSetTimeDays > 31) modeMenuSetTimeDays = 0;
  if(modeMenuSetTimeMonths > 12) modeMenuSetTimeMonths = 0;
  if(modeMenuSetTimeYears < 2020 || modeMenuSetTimeYears > 2040) modeMenuSetTimeYears = 2020;

  const byte xOffset = eepromReadFlipScreen()? 7 : 20;
  byte y=13;

  displayDrawText(xOffset+20, y+4, 1, ":");
  displayDraw2DigitNumberWithFrame(MENU_SET_TIME_SELECTED_HOUR, /*x*/xOffset, /*y*/y, /*number*/modeMenuSetTimeHours);
  displayDraw2DigitNumberWithFrame(MENU_SET_TIME_SELECTED_MINUTE, /*x*/xOffset+25, /*y*/y, /*number*/modeMenuSetTimeMinutes);  
  y+=19;
  displayDrawText(xOffset+20, y+5, 1, ".");
  displayDraw2DigitNumberWithFrame(MENU_SET_TIME_SELECTED_DAY, /*x*/xOffset, /*y*/y, /*number*/modeMenuSetTimeDays);
  displayDraw2DigitNumberWithFrame(MENU_SET_TIME_SELECTED_MONTH, /*x*/xOffset+25, /*y*/y, /*number*/modeMenuSetTimeMonths); 
  displayDraw2DigitNumberWithFrame(MENU_SET_TIME_SELECTED_YEAR, /*x*/xOffset+50, /*y*/y, /*number*/modeMenuSetTimeYears%2000); 
  y+=19;
  displayDrawIconWithFrame(MENU_SET_TIME_SELECTED_BACK, /*x*/xOffset, /*y*/y, /*Icon*/displayDrawBackIcon);
  displayDrawIconWithFrame(MENU_SET_TIME_SELECTED_SAVE, /*x*/xOffset+25, /*y*/y, /*drawIcon*/displayDrawCheck);
  
  displayUpdate();
}

void modeMenuSetTimeSelected(){
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
