
#include "Buttons.cpp"

/*Screen allows to set time*/

#define MODE_SET_ALARM_SELECTED_BACK 0
#define MODE_SET_ALARM_SELECTED_TOGGLE 1
#define MODE_SET_ALARM_SELECTED_HOUR 2
#define MODE_SET_ALARM_SELECTED_MINUTE 3
#define MODE_SET_ALARM_SELECTED_MELODY 4


void modeSetAlarmSetup(){
  genericMenuSetup();
}

void modeSetAlarmLoop(){
  if (isButtonUpPressed()){ //change value
    beep();
    if(selected == MODE_SET_ALARM_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_APPS);
      return;
    }
    else if(selected == MODE_SET_ALARM_SELECTED_TOGGLE) {//ON/OFF
      eepromSaveAlertEnabled(!eepromReadAlertEnabled());
      resetAlertMetadata();
    }
    else if(selected == MODE_SET_ALARM_SELECTED_HOUR) {//hours
      eepromSaveAlertHour(eepromReadAlertHour() + 1);
      resetAlertMetadata();
    }
    else if(selected == MODE_SET_ALARM_SELECTED_MINUTE) {//Minutes
      eepromSaveAlertMinute(eepromReadAlertMinute() + 1);
      resetAlertMetadata();
    }
    else if(selected == MODE_SET_ALARM_SELECTED_MELODY) {//melody
      eepromSaveAlertMelodyIndex(eepromReadAlertMelodyIndex() + 1);
    }
  }

  if (isButtonDownPressed()){ ////move next
    beep();
    selected ++;
    if(selected > 4) selected = 0;
  }

  
  displayClear();
  byte xOffset = 13;
  if(/*flip*/eepromReadFlipScreen())
    xOffset = 0;

  //BACK
  displayDrawIconWithFrame(/*x*/xOffset, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/displayDrawArrowLeft, /*selected*/selected == MODE_SET_ALARM_SELECTED_BACK);

  //TITLE
#ifdef LANG_EN
  displayDrawText(xOffset+25, 4, 1, F("Alarm"));
#endif
#ifdef LANG_RU
  displayDrawText(xOffset+25, 4, 1, F("Бyдильник"));
#endif
#ifdef LANG_UA
  displayDrawText(xOffset+25, 4, 1, F("Бyдильник"));
#endif
  

  //ENABLE \ DISABLE
  displayDrawIconWithFrame(/*x*/xOffset, /*y*/25, /*additionalWidth*/0, /*drawIcon(x,y,color)*/(eepromReadAlertEnabled()?displayDrawSilentModeOffIcon:displayDrawSilentModeIcon), /*selected*/selected == MODE_SET_ALARM_SELECTED_TOGGLE);
  
  
  //hours
  displayDraw2DigitNumberWithFrame(/*x*/xOffset+39, /*y*/25, /*number*/eepromReadAlertHour(), /*selected*/selected == MODE_SET_ALARM_SELECTED_HOUR); 
  //:
  displayDrawText(xOffset+59, 29, 1, ":");
  //minutes
  displayDraw2DigitNumberWithFrame(/*x*/xOffset+64, /*y*/25, /*number*/eepromReadAlertMinute(), /*selected*/selected == MODE_SET_ALARM_SELECTED_MINUTE); 
  
  { //melody
    strlcpy_P(buffer, getMelodyName(eepromReadAlertMelodyIndex()), BUFFER_SIZE);
    if(selected == MODE_SET_ALARM_SELECTED_MELODY){
      displayFillRect(/*x*/xOffset+0, /*y*/44, /*w*/83, /*h*/15, /*c*/1);
      displayDrawText(xOffset+4, 48, 0, buffer);
    }
    else{
      displayDrawRect(/*x*/xOffset+0, /*y*/44, /*w*/83, /*h*/15, /*c*/1);
      displayDrawText(xOffset+4, 48, 1, buffer);
    }
  }

  
  
  
  

  drawLegend();
  
  displayUpdate();
}

//fix alarm, предотвращение включения будильника сразу в момент установки
void resetAlertMetadata(){
  byte hour = rtcGetHours();
  byte minute = rtcGetMinutes();
  byte day = rtcGetDay();
  if((hour == eepromReadAlertHour() && minute >= eepromReadAlertMinute()) || (hour > eepromReadAlertHour()))
    eepromSaveAlertLastDayRun(day);
  else
    eepromSaveAlertLastDayRun(0);
}

void modeSetAlarmFinish(){
}
