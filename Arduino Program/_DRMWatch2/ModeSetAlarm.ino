#include "Display.cpp"
#include "Buttons.cpp"
#include "RTC.cpp"
#include "Generic.cpp"
#include "Buzzer.cpp"

/*Screen allows to set time*/

#define MODE_SET_ALARM_SELECTED_HOUR 0
#define MODE_SET_ALARM_SELECTED_MINUTE 1
#define MODE_SET_ALARM_SELECTED_MELODY 2
#define MODE_SET_ALARM_SELECTED_SAVE  3
#define MODE_SET_ALARM_SELECTED_DISABLE 4
#define MODE_SET_ALARM_SELECTED_BACK 5


byte modeSetAlarmHour = 00;
byte modeSetAlarmMinute = 00;
byte modeSetAlarmMelody = 00;


void modeSetAlarmSetup(){
  modeSetAlarmHour = MyEEPROM.eepromReadAlertHour();
  modeSetAlarmMinute = MyEEPROM.eepromReadAlertMinute();
  modeSetAlarmMelody = MyEEPROM.eepromReadAlertMelodyIndex();
  if(modeSetAlarmMelody >= getMelodiesCount()) modeSetAlarmMelody = 0;
  digitalWrite(pinLcdBacklight, HIGH);
  Generic.selected = 0;
}

void modeSetAlarmLoop(){
  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonDown.isButtonPressed():ButtonUp.isButtonPressed()){
    Buzzer.beep();
    //change value
    if(Generic.selected == MODE_SET_ALARM_SELECTED_HOUR) {//hours
      modeSetAlarmHour ++;
      if(modeSetAlarmHour > 23) modeSetAlarmHour = 0;
    }
    if(Generic.selected == MODE_SET_ALARM_SELECTED_MINUTE) {//Minutes
      modeSetAlarmMinute ++;
      if(modeSetAlarmMinute > 59) modeSetAlarmMinute = 0;
    }
    if(Generic.selected == MODE_SET_ALARM_SELECTED_MELODY) {//melody
      modeSetAlarmMelody ++;
      if(modeSetAlarmMelody >= getMelodiesCount()) modeSetAlarmMelody = 0;
    }
    
    if(Generic.selected == MODE_SET_ALARM_SELECTED_SAVE) {//SAVE
      byte hour = RTC.rtcGetHours();
      byte minute = RTC.rtcGetMinutes();
      byte day = RTC.rtcGetDay();
      MyEEPROM.eepromSaveAlertEnabled(true);
      MyEEPROM.eepromSaveAlertMelodyIndex(modeSetAlarmMelody);
      MyEEPROM.eepromSaveAlertHour(modeSetAlarmHour);
      MyEEPROM.eepromSaveAlertMinute(modeSetAlarmMinute);
      if((hour == modeSetAlarmHour && minute >= modeSetAlarmMinute) || (hour > modeSetAlarmHour))
        MyEEPROM.eepromSaveAlertLastDayRun(day);
      else
        MyEEPROM.eepromSaveAlertLastDayRun(0);
      Display.displayMessage((const __FlashStringHelper*)textSaved);
      goToWatchface();
      return;
    }
    if(Generic.selected == MODE_SET_ALARM_SELECTED_DISABLE) {//OFF
      MyEEPROM.eepromSaveAlertEnabled(false);
#ifdef LANG_EN
      Display.displayMessage(F("Alert OFF"));
#endif
#ifdef LANG_RU
      Display.displayMessage(F("Bыключeнo."));
#endif
      goToWatchface();
      return;
    }
    if(Generic.selected == MODE_SET_ALARM_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_APPS);
      return;
    }
  }

  if (/*flip*/MyEEPROM.eepromReadFlipScreen()?ButtonUp.isButtonPressed():ButtonDown.isButtonPressed()){
    Buzzer.beep();
    //move next
    Generic.selected ++;
    if(Generic.selected > 5) Generic.selected = 0;
  }

  
  Display.displayClear();
#ifdef LANG_EN
  Display.displayDrawText(15, 2, 1, F("Alarm set"));
#endif
#ifdef LANG_RU
  Display.displayDrawText(15, 2, 1, F("Бyдильник"));
#endif
  if(Generic.selected == MODE_SET_ALARM_SELECTED_SAVE || Generic.selected == MODE_SET_ALARM_SELECTED_DISABLE || Generic.selected == MODE_SET_ALARM_SELECTED_BACK)
    Display.displayDrawCheck(/*X*/1, /*Y*/2, 1);
  else
    Display.displayDrawText(/*X*/1, /*Y*/2, /*C*/1, "+");
  Display.displayDrawArrowRight(/*X*/1, /*Y*/59, 1);
  
  Display.displayDrawText(35, 19, 1, ":");
  //hours
  Display.displayDraw2DigitNumberWithFrame(/*x*/15, /*y*/15, /*number*/modeSetAlarmHour, /*selected*/Generic.selected == MODE_SET_ALARM_SELECTED_HOUR); 
  //minutes
  Display.displayDraw2DigitNumberWithFrame(/*x*/40, /*y*/15, /*number*/modeSetAlarmMinute, /*selected*/Generic.selected == MODE_SET_ALARM_SELECTED_MINUTE); 
  
  { //melody
    byte x = 15;
    byte y = 33;
    //strlcpy_P(buffer, pgm_read_word(getMelodyName(modeSetAlarmMelody)), BUFFER_SIZE);
    //strcpy_P(Generic.buffer, getMelodyName(modeSetAlarmMelody));
    strlcpy_P(Generic.buffer, getMelodyName(modeSetAlarmMelody), BUFFER_SIZE);
    if(Generic.selected == MODE_SET_ALARM_SELECTED_MELODY){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/80, /*h*/15, /*c*/1);
      Display.displayDrawText(x+4, y+4, 0, Generic.buffer);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/80, /*h*/15, /*c*/1);
      Display.displayDrawText(x+4, y+4, 1, Generic.buffer);
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
    if(Generic.selected == MODE_SET_ALARM_SELECTED_SAVE){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x+4, y+4, 1, chars);
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
    if(Generic.selected == MODE_SET_ALARM_SELECTED_DISABLE){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/30, /*h*/15, /*c*/1);
      Display.displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  { //BACK
    byte x = 83;
    byte y = 53;
    const __FlashStringHelper* chars = F("<");
    if(Generic.selected == MODE_SET_ALARM_SELECTED_BACK){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/13, /*h*/15, /*c*/1);
      Display.displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/13, /*h*/15, /*c*/1);
      Display.displayDrawText(x+4, y+4, 1, chars);
    }
  }
  
  Display.displayUpdate();
}

void modeSetAlarmFinish(){
}
