/*Screen allows to set time*/

#define MODE_SET_ALARM_SELECTED_HOUR 0
#define MODE_SET_ALARM_SELECTED_MINUTE 1
#define MODE_SET_ALARM_SELECTED_MELODY 2
#define MODE_SET_ALARM_SELECTED_SAVE  3
#define MODE_SET_ALARM_SELECTED_DISABLE 4
#define MODE_SET_ALARM_SELECTED_BACK 5
int modeSetAlarmSelected = MODE_SET_ALARM_SELECTED_HOUR;


byte modeSetAlarmHour = 00;
byte modeSetAlarmMinute = 00;
byte modeSetAlarmMelody = 00;


void modeSetAlarmSetup(){
  modeSetAlarmHour = eepromReadAlertHour();
  modeSetAlarmMinute = eepromReadAlertMinute();
  modeSetAlarmMelody = eepromReadAlertMelodyIndex();
  digitalWrite(pinLcdBacklight, HIGH);
  modeSetAlarmSelected = 0;
}

void modeSetAlarmLoop(){
  if (isButtonUpPressed()) {
    beep();
    //change value
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_HOUR) {//hours
      modeSetAlarmHour ++;
      if(modeSetAlarmHour > 23) modeSetAlarmHour = 0;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MINUTE) {//Minutes
      modeSetAlarmMinute ++;
      if(modeSetAlarmMinute > 59) modeSetAlarmMinute = 0;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MELODY) {//melody
      modeSetAlarmMelody ++;
      if(modeSetAlarmMelody >= getMelodiesCount()) modeSetAlarmMelody = 0;
    }
    
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_SAVE) {//SAVE
      byte hour = rtcGetHours();
      byte minute = rtcGetMinutes();
      byte day = rtcGetDay();
      eepromSaveAlertEnabled(true);
      eepromSaveAlertMelodyIndex(modeSetAlarmMelody);
      eepromSaveAlertHour(modeSetAlarmHour);
      eepromSaveAlertMinute(modeSetAlarmMinute);
      if((hour == modeSetAlarmHour && minute >= modeSetAlarmMinute) || (hour > modeSetAlarmHour))
          eepromSaveAlertLastDayRun(day);
      else
        eepromSaveAlertLastDayRun(0);
      displayMessage((const __FlashStringHelper*)textSaved);
      goToWatchface();
      return;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_DISABLE) {//OFF
      eepromSaveAlertEnabled(false);
#ifdef LANG_EN
      displayMessage(F("Alert OFF"));
#endif
#ifdef LANG_RU
      displayMessage(F("Bыключeнo."));
#endif
      goToWatchface();
      return;
    }
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_APPS);
      return;
    }
  }

  if (isButtonDownPressed()) {
    beep();
    //move next
    modeSetAlarmSelected ++;
    if(modeSetAlarmSelected > 5) modeSetAlarmSelected = 0;
  }

  
  displayClear();
#ifdef LANG_EN
  displayDrawText(15, 2, 1, F("Alarm set"));
#endif
#ifdef LANG_RU
  displayDrawText(15, 2, 1, F("Бyдильник"));
#endif
  if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_SAVE || modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_DISABLE || modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_BACK)
    displayDrawCheck(/*X*/1, /*Y*/2, 1);
  else
    displayDrawText(/*X*/1, /*Y*/2, /*C*/1, "+");
  displayDrawArrowRight(/*X*/1, /*Y*/59, 1);
  
  displayDrawText(35, 19, 1, ":");
  //hours
  displayDraw2DigitNumberWithFrame(/*x*/15, /*y*/15, /*number*/modeSetAlarmHour, /*selected*/modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_HOUR); 
  //minutes
  displayDraw2DigitNumberWithFrame(/*x*/40, /*y*/15, /*number*/modeSetAlarmMinute, /*selected*/modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MINUTE); 
  
  { //melody
    byte x = 15;
    byte y = 33;
    //strlcpy_P(buffer, pgm_read_word(getMelodyName(modeSetAlarmMelody)), BUFFER_SIZE);
    strlcpy_P(buffer, getMelodyName(modeSetAlarmMelody), BUFFER_SIZE);
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_MELODY){
      displayFillRect(/*x*/x, /*y*/y, /*w*/80, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 0, buffer);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/80, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, buffer);
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
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_SAVE){
      displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  { //OFF
    byte x = 49;
    byte y = 53;
#ifdef LANG_EN
    const __FlashStringHelper* chars = F("OFF");
#endif
#ifdef LANG_RU
    const __FlashStringHelper* chars = F("Bыкл");
#endif
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_DISABLE){
      displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  { //BACK
    byte x = 83;
    byte y = 53;
    const __FlashStringHelper* chars = F("<");
    if(modeSetAlarmSelected == MODE_SET_ALARM_SELECTED_BACK){
      displayFillRect(/*x*/x, /*y*/y, /*w*/13, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/13, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  displayUpdate();
}

void modeSetAlarmFinish(){
}
