#include "Display.cpp"
#include "Buttons.cpp"
#include "RTC.cpp"
#include "Generic.cpp"
#include "Buzzer.cpp"

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
    Buzzer.beep();
    if(Generic.selected == MODE_SET_ALARM_SELECTED_BACK) {//BACK
      setMode(MODE_MENU_APPS);
      return;
    }
    else if(Generic.selected == MODE_SET_ALARM_SELECTED_TOGGLE) {//ON/OFF
      MyEEPROM.eepromSaveAlertEnabled(!MyEEPROM.eepromReadAlertEnabled());
      resetAlertMetadata();
    }
    else if(Generic.selected == MODE_SET_ALARM_SELECTED_HOUR) {//hours
      MyEEPROM.eepromSaveAlertHour(MyEEPROM.eepromReadAlertHour() + 1);
      resetAlertMetadata();
    }
    else if(Generic.selected == MODE_SET_ALARM_SELECTED_MINUTE) {//Minutes
      MyEEPROM.eepromSaveAlertMinute(MyEEPROM.eepromReadAlertMinute() + 1);
      resetAlertMetadata();
    }
    else if(Generic.selected == MODE_SET_ALARM_SELECTED_MELODY) {//melody
      MyEEPROM.eepromSaveAlertMelodyIndex(MyEEPROM.eepromReadAlertMelodyIndex() + 1);
    }
  }

  if (isButtonDownPressed()){ ////move next
    Buzzer.beep();
    Generic.selected ++;
    if(Generic.selected > 4) Generic.selected = 0;
  }

  
  Display.displayClear();
  byte xOffset = 13;
  if(/*flip*/MyEEPROM.eepromReadFlipScreen())
    xOffset = 0;

  //BACK
  Display.displayDrawIconWithFrame(/*x*/xOffset, /*y*/0, /*additionalWidth*/0, /*drawIcon(x,y,color)*/Display.displayDrawArrowLeft, /*selected*/Generic.selected == MODE_SET_ALARM_SELECTED_BACK);

  //TITLE
#ifdef LANG_EN
  Display.displayDrawText(xOffset+25, 4, 1, F("Alarm"));
#endif
#ifdef LANG_RU
  Display.displayDrawText(xOffset+25, 4, 1, F("Бyдильник"));
#endif
  

  //ENABLE \ DISABLE
  Display.displayDrawIconWithFrame(/*x*/xOffset, /*y*/25, /*additionalWidth*/0, /*drawIcon(x,y,color)*/(MyEEPROM.eepromReadAlertEnabled()?Display.displayDrawSilentModeOffIcon:Display.displayDrawSilentModeIcon), /*selected*/Generic.selected == MODE_SET_ALARM_SELECTED_TOGGLE);
  
  
  //hours
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+39, /*y*/25, /*number*/MyEEPROM.eepromReadAlertHour(), /*selected*/Generic.selected == MODE_SET_ALARM_SELECTED_HOUR); 
  //:
  Display.displayDrawText(xOffset+59, 29, 1, ":");
  //minutes
  Display.displayDraw2DigitNumberWithFrame(/*x*/xOffset+64, /*y*/25, /*number*/MyEEPROM.eepromReadAlertMinute(), /*selected*/Generic.selected == MODE_SET_ALARM_SELECTED_MINUTE); 
  
  { //melody
    strlcpy_P(Generic.buffer, getMelodyName(MyEEPROM.eepromReadAlertMelodyIndex()), BUFFER_SIZE);
    if(Generic.selected == MODE_SET_ALARM_SELECTED_MELODY){
      Display.displayFillRect(/*x*/xOffset+0, /*y*/44, /*w*/83, /*h*/15, /*c*/1);
      Display.displayDrawText(xOffset+4, 48, 0, Generic.buffer);
    }
    else{
      Display.displayDrawRect(/*x*/xOffset+0, /*y*/44, /*w*/83, /*h*/15, /*c*/1);
      Display.displayDrawText(xOffset+4, 48, 1, Generic.buffer);
    }
  }

  
  
  
  

  //LEGEND
  if(Generic.selected <= MODE_SET_ALARM_SELECTED_TOGGLE)
    Display.displayDrawCheck(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/2, 1);
  else
    Display.displayDrawText(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/2, /*C*/1, "+");
  Display.displayDrawArrowRight(/*X*/MyEEPROM.eepromReadFlipScreen()?89:1, /*Y*/59, 1);
  
  Display.displayUpdate();
}

//fix alarm, предотвращение включения будильника сразу в момент установки
void resetAlertMetadata(){
  byte hour = RTC.rtcGetHours();
  byte minute = RTC.rtcGetMinutes();
  byte day = RTC.rtcGetDay();
  if((hour == MyEEPROM.eepromReadAlertHour() && minute >= MyEEPROM.eepromReadAlertMinute()) || (hour > MyEEPROM.eepromReadAlertHour()))
    MyEEPROM.eepromSaveAlertLastDayRun(day);
  else
    MyEEPROM.eepromSaveAlertLastDayRun(0);
}

void modeSetAlarmFinish(){
}
