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
      { //fix alarm
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
#ifdef LANG_EN
      displayMessage(F("Time saved"));
#endif
#ifdef LANG_RU
      displayMessage(F("Bpeмя coxp."));
#endif
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

  
  displayClear();
#ifdef LANG_EN
  displayDrawText(15, 2, 1, F("Set time"));
#endif
#ifdef LANG_RU
  displayDrawText(15, 2, 1, F("Зaдaть вpeмя"));
#endif
  if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_SAVE || modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_BACK)
    displayDrawCheck(/*X*/1, /*Y*/2, 1);
  else
    displayDrawText(/*X*/1, /*Y*/2, /*C*/1, "+");
  displayDrawArrowRight(/*X*/1, /*Y*/59, 1);
  
  displayDrawText(35, 19, 1, ":");
  { //hours
    byte x = 15;
    byte y = 15;
    char chars[4];
    sprintf(chars, "%02d", modeMenuSetTimeHours);
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_HOUR){
      displayFillRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  { //minutes
    byte x = 40;
    byte y = 15;
    char chars[4];
    sprintf(chars, "%02d", modeMenuSetTimeMinutes);
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_MINUTE){
      displayFillRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }


  displayDrawText(35, 39, 1, ".");
  displayDrawText(60, 39, 1, ".");
  { //days
    byte x = 15;
    byte y = 33;
    char chars[4];
    sprintf(chars, "%02d", modeMenuSetTimeDays);
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_DAY){
      displayFillRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  { //months
    byte x = 40;
    byte y = 33;
    char chars[4];
    sprintf(chars, "%02d", modeMenuSetTimeMonths);
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_MONTH){
      displayFillRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  { //Year
    byte x = 65;
    byte y = 33;
    char chars[5];
    sprintf(chars, "%04d", modeMenuSetTimeYears);
    if(modeMenuSetTimeSelected == MENU_SET_TIME_SELECTED_YEAR){
      displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }

  
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
      displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
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
      displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  displayUpdate();
}

void modeMenuSetTimeFinish(){
  //digitalWrite(pinLcdBacklight, LOW);
}
