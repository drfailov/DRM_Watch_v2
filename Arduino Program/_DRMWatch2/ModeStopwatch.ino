#include "Display.cpp"

/*Stopwatch functionality*/
#define MODE_STOPWATCH_SELECTED_START 0
#define MODE_STOPWATCH_SELECTED_RESET 1
#define MODE_STOPWATCH_SELECTED_BACK 2

byte modeStopwatchSelectedItem = 0;
long modeStopwatchStartedTime = 0;
long modeStopwatchFinishedTime = 0;
bool modeStopwatchIsRunning = false;

void modeStopwatchSetup() {
  Display.displayInit();
  modeStopwatchSelectedItem = 0;
  modeStopwatchStartedTime = 0;
  modeStopwatchFinishedTime = 0;
  modeStopwatchIsRunning = false;
}

void modeStopwatchLoop() {
  if(isButtonUpPressed()){
    beep();
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_START){
      if(modeStopwatchIsRunning == false){
        modeStopwatchStartedTime = millis() - (modeStopwatchFinishedTime-modeStopwatchStartedTime);
        modeStopwatchIsRunning = true;
      }
      else if(modeStopwatchIsRunning == true){
        modeStopwatchFinishedTime = millis();
        modeStopwatchIsRunning = false;
      }
    }
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_RESET){
      modeStopwatchStartedTime = millis();
      modeStopwatchFinishedTime = millis();
    }
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_BACK){
      goToWatchface();
      return;
    }
  }
  if(isButtonDownPressed()){
    beep();
    modeStopwatchSelectedItem ++;
    if(modeStopwatchSelectedItem > 2) 
      modeStopwatchSelectedItem = 0;
    return;
  } 
  
  
  Display.displayClear();
  
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
    
    Display.displayDrawNumber(minute1 , 13, 10, 3, 4, false);
    Display.displayDrawNumber(minute2 , 27, 10, 3, 4, false);
    Display.displayDrawNumber(10      , 41, 10, 3, 4, false); // :
    Display.displayDrawNumber(second1 , 46, 10, 3, 4, false);
    Display.displayDrawNumber(second2 , 60, 10, 3, 4, false);
    Display.displayDrawNumber(10      , 74, 15, 2, 3, false); // :
    Display.displayDrawNumber(millisecond1 , 78, 15, 2, 3, false);
    Display.displayDrawNumber(millisecond2 , 88, 15, 2, 3, false);
  }

  
  { //Start
    byte x = 17;
    byte y = 43;
    if(modeStopwatchIsRunning == false){
      if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_START){
        Display.displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        Display.displayDrawPlaySign(x + 7, y+4, 0);
      }
      else{
        Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        Display.displayDrawPlaySign(x + 7, y+4, 1);
      }
    }
    if(modeStopwatchIsRunning == true){
      if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_START){
        Display.displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        Display.displayDrawPauseSign(x + 6, y+4, 0);
      }
      else{
        Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        Display.displayDrawPauseSign(x + 6, y+4, 1);
      }
    }
  }

  
  { //Reset
    byte x = 44;
    byte y = 43;
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_RESET){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      Display.displayDrawResetIcon(x + 8, y+4, 0);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      Display.displayDrawResetIcon(x + 8, y+4, 1);
    }
  }
    
  { //Back
    byte x = 70;
    byte y = 43;
    const __FlashStringHelper* chars = F("<");
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_BACK){
      Display.displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      Display.displayDrawText(x + 8, y+4, 0, chars);
    }
    else{
      Display.displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      Display.displayDrawText(x+8, y+4, 1, chars);
    }
  }
  
  Display.displayDrawArrowRight(0, 61, 1);
  Display.displayDrawCheck(/*X*/2, /*Y*/2, 1);
  Display.displayUpdate();
  
}

void modeStopwatchFinish() {

}
