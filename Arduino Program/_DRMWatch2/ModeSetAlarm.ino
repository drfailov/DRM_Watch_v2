#define MODE_SET_ALARM_SELECTED_BACK 0
#define MODE_SET_ALARM_SELECTED_TOGGLE 1
#define MODE_SET_ALARM_SELECTED_HOUR 2
#define MODE_SET_ALARM_SELECTED_MINUTE 3
#define MODE_SET_ALARM_SELECTED_MELODY 4

void modeSetAlarmSetup(){
  genericMenuSetup();
}

void modeSetAlarmLoop(){//y:13, 32, 
  if(genericMenuRoutine(modeSetAlarmSelected, 5))return;  
  
  const byte xOffset = eepromReadFlipScreen()? 0 : 13;
  byte y=13;
  displayDrawIconWithFrame(/*index*/MODE_SET_ALARM_SELECTED_BACK, /*x*/xOffset, /*y*/y, /*icon*/displayDrawBackIcon);   //BACK
  y+=19;
  displayDrawIconWithFrame(/*index*/MODE_SET_ALARM_SELECTED_TOGGLE, /*x*/xOffset, /*y*/y, /*icon*/(eepromReadAlertEnabled()?displayDrawSilentModeOffIcon:displayDrawSilentModeIcon)); //ENABLE \ DISABLE
  displayDraw2DigitNumberWithFrame(MODE_SET_ALARM_SELECTED_HOUR, /*x*/xOffset+39, /*y*/y, /*number*/eepromReadAlertHour());  //hours
  displayDrawText(xOffset+59, y+4, 1, ":"); //:
  displayDraw2DigitNumberWithFrame(MODE_SET_ALARM_SELECTED_MINUTE, /*x*/xOffset+64, /*y*/y, /*number*/eepromReadAlertMinute());  //minutes
  y+=19;
  { //melody
    strlcpy_P(buffer, getMelodyName(eepromReadAlertMelodyIndex()), BUFFER_SIZE);
    (selected == MODE_SET_ALARM_SELECTED_MELODY?displayFillRect:displayDrawRect)(/*x*/xOffset+0, /*y*/y, /*w*/83, /*h*/15, /*c*/1);
    displayDrawText(xOffset+4, y+4, selected != MODE_SET_ALARM_SELECTED_MELODY, buffer);
  }  
  displayUpdate();
}

void modeSetAlarmSelected(){
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
