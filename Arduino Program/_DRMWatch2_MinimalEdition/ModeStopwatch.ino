#include "Display.cpp"
#include "Buttons.cpp"
#include "Buzzer.cpp"

/*Stopwatch functionality*/
#define MODE_STOPWATCH_SELECTED_BACK 2
#define MODE_STOPWATCH_SELECTED_START 0
#define MODE_STOPWATCH_SELECTED_RESET 1

long modeStopwatchStartedTime = 0;
long modeStopwatchFinishedTime = 0;
bool modeStopwatchIsRunning = false;

void modeStopwatchSetup() {
  genericMenuSetup();
  modeStopwatchStartedTime = 0;
  modeStopwatchFinishedTime = 0;
  modeStopwatchIsRunning = false;
}

void modeStopwatchLoop() {
  if (isButtonUpPressed()){ //UP
    if (isButtonUpHold()){ //if hold - reset
      Buzzer.beep();
      goToWatchface();
      return;
    }
    Buzzer.beep();
    if(modeStopwatchIsRunning == false){
      modeStopwatchStartedTime = millis() - (modeStopwatchFinishedTime-modeStopwatchStartedTime);
    }
    else{
      modeStopwatchFinishedTime = millis();
    }
    modeStopwatchIsRunning = !modeStopwatchIsRunning;
  }
  
  if (isButtonDownPressed()){ //DOWN
    Buzzer.beep();
    modeStopwatchStartedTime = modeStopwatchFinishedTime = millis();
    return;
  } 
  
  
  Display.displayClear();
  byte xOffset = 11;
  if(MyEEPROM.eepromReadFlipScreen())
    xOffset = 0;

    
  { //time
    long difference = 0;
    long minute = 0;
    long second = 0;
    long millisecond = 0;

    if(modeStopwatchIsRunning == true){
      difference = millis() - modeStopwatchStartedTime;     
    }
    if(modeStopwatchIsRunning == false){
      difference = modeStopwatchFinishedTime - modeStopwatchStartedTime;     
    }
    
    minute = (difference) / 1000 / 60;                         //3710100/1000/60 = 3710/60 = 61.83 = 61
    second = (difference - (minute * 1000 * 60)) / 1000;       //(3710100 - (61*1000*60)) /1000 = (3710100-3660000) /1000 = 50100 /1000 = 5.01 = 5
    millisecond = (difference - (minute * 1000 * 60) - (second * 1000)) / 10;
      
    byte minute1 = minute / 10;
    byte minute2 = minute - (minute1 * 10);
    byte second1 = second / 10;
    byte second2 = second - (second1 * 10);
    byte millisecond1 = millisecond / 10;
    byte millisecond2 = millisecond - (millisecond1 * 10);
    byte y = 22;
    Display.displayDrawNumber(minute1 , /*x*/5, /*y*/y, /*w*/3, /*h*/4, /*animate*/false);
    Display.displayDrawNumber(minute2 , /*x*/19, /*y*/y, /*w*/3, /*h*/4, /*animate*/false);
    Display.displayDrawNumber(10      , /*x*/33, /*y*/y, /*w*/3, /*h*/4, /*animate*/false); // :
    Display.displayDrawNumber(second1 , /*x*/38, /*y*/y, /*w*/3, /*h*/4, /*animate*/false);
    Display.displayDrawNumber(second2 , /*x*/52, /*y*/y, /*w*/3, /*h*/4, /*animate*/false);
    Display.displayDrawNumber(10      , /*x*/66, /*y*/y+5, /*w*/2, /*h*/3, /*animate*/false); // :
    Display.displayDrawNumber(millisecond1 , /*x*/70, /*y*/y+5, /*w*/2, /*h*/3, /*animate*/false);
    Display.displayDrawNumber(millisecond2 , /*x*/80, /*y*/y+5, /*w*/2, /*h*/3, /*animate*/false);
  }

  if(modeStopwatchIsRunning)
    Display.displayDrawPauseSign(/*X*/MyEEPROM.eepromReadFlipScreen()?89:2, /*Y*/2, /*c*/1);
  else
    Display.displayDrawPlaySign(/*X*/MyEEPROM.eepromReadFlipScreen()?89:2, /*Y*/2, /*c*/1);
  Display.displayDrawIconReboot(/*x*/MyEEPROM.eepromReadFlipScreen()?88:0, /*Y*/61, /*c*/1);
    
  Display.displayUpdate();
}

void modeStopwatchFinish() {

}
