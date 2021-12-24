/*Screen allows to set time*/

#define MODE_SET_ALARM_SELECTED_HOUR 0
#define MODE_SET_ALARM_SELECTED_MINUTE 1
#define MODE_SET_ALARM_SELECTED_DAY 2
#define MODE_SET_ALARM_SELECTED_MONTH  3
#define MODE_SET_ALARM_SELECTED_YEAR 4
#define MODE_SET_ALARM_SELECTED_SAVE 5
#define MODE_SET_ALARM_SELECTED_BACK 6
int modeSetAlarmSelected = MODE_SET_ALARM_SELECTED_HOUR;


byte modeSetAlarmHours = 00;
byte modeSetAlarmMinutes = 00;
byte modeSetAlarmSeconds = 00;

byte modeSetAlarmDays = 01;
byte modeSetAlarmMonths = 01;
int modeSetAlarmYears = 2021;


void modeSetAlarmSetup(){
  modeSetAlarmHours = rtcGetHours();
  modeSetAlarmMinutes = rtcGetMinutes();
  modeSetAlarmDays = rtcGetDay();
  modeSetAlarmMonths = rtcGetMonth();
  modeSetAlarmYears = rtcGetYear();
  digitalWrite(pinLcdBacklight, HIGH);
  modeSetAlarmSelected = 0;
}

void modeSetAlarmLoop(){
  if (isButtonUpPressed()) {
    beep();
    //change value
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_HOUR) {//hours
      modeSetAlarmHours ++;
      if(modeSetAlarmHours > 23) modeSetAlarmHours = 0;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MINUTE) {//Minutes
      modeSetAlarmMinutes ++;
      if(modeSetAlarmMinutes > 59) modeSetAlarmMinutes = 0;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_DAY) {//Day
      modeSetAlarmDays ++;
      if(modeSetAlarmDays > 31) modeSetAlarmDays = 0;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MONTH) {//Month
      modeSetAlarmMonths ++;
      if(modeSetAlarmMonths > 12) modeSetAlarmMonths = 0;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_YEAR) {//Month
      modeSetAlarmYears ++;
      if(modeSetAlarmYears > 2050) modeSetAlarmYears = 2020;
    }
    
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_SAVE) {//SAVE
      rtcSetTime(modeSetAlarmYears, modeSetAlarmMonths, modeSetAlarmDays, modeSetAlarmHours, modeSetAlarmMinutes);
#ifdef LANG_EN
      displayMessage(F("Time saved"));
#endif
#ifdef LANG_RU
      displayMessage(F("Время сохр."));
#endif
      delay(500);
      goToWatchface();
      return;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_SETTINGS);
      return;
    }
  }

  if (isButtonDownPressed()) {
    beep();
    //move next
    modeSetAlarmSelected ++;
    if(modeSetAlarmSelected > 6) modeSetAlarmSelected = 0;
  }

  
  displayClear();
#ifdef LANG_EN
  displayDrawText(15, 2, 1, F("Set time"));
#endif
#ifdef LANG_RU
  displayDrawText(15, 2, 1, F("Задать время"));
#endif
  if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_SAVE || modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_BACK)
    displayDrawCheck(/*X*/1, /*Y*/2, 1);
  else
    displayDrawText(/*X*/1, /*Y*/2, /*C*/1, "+");
  displayDrawArrowRight(/*X*/1, /*Y*/59, 1);
  
  displayDrawText(35, 19, 1, ":");
  { //hours
    byte x = 15;
    byte y = 15;
    char chars[4];
    sprintf(chars, "%02d", modeSetAlarmHours);
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_HOUR){
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
    sprintf(chars, "%02d", modeSetAlarmMinutes);
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MINUTE){
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
    sprintf(chars, "%02d", modeSetAlarmDays);
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_DAY){
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
    sprintf(chars, "%02d", modeSetAlarmMonths);
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MONTH){
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
    sprintf(chars, "%04d", modeSetAlarmYears);
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_YEAR){
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
    const __FlashStringHelper* chars = F("Сохр");    
#endif
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_SAVE){
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
    const __FlashStringHelper* chars = F("Назд");
#endif
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_BACK){
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

void modeSetAlarmFinish(){
  //digitalWrite(pinLcdBacklight, LOW);
}
