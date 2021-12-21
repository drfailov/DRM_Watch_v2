/*Stopwatch functionality*/
#define MODE_STOPWATCH_SELECTED_START 0
#define MODE_STOPWATCH_SELECTED_RESET 1
#define MODE_STOPWATCH_SELECTED_BACK 2

byte modeStopwatchSelectedItem = 0;
long modeStopwatchStartedTime = 0;
long modeStopwatchFinishedTime = 0;
bool modeStopwatchIsRunning = false;

void modeStopwatchSetup() {
  displayInit();
}

void modeStopwatchLoop() {
  if(isButtonUpPressed()){
    beep();
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_START){
      modeStopwatchStartedTime = millis();
      modeStopwatchIsRunning = true;
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
  
  
  
  displayClear();
  
  { //time
    int hour = 0;
    int minute = 0;
    int second = 0;
    int hour1 = hour / 10;
    int hour2 = hour - (hour1 * 10);
    int minute1 = minute / 10;
    int minute2 = minute - (minute1 * 10);
    int second1 = second / 10;
    int second2 = second - (second1 * 10);
    
    displayDrawNumber(hour1   ,  5, 10, 3, 4);
    displayDrawNumber(hour2   , 19, 10, 3, 4);
    displayDrawNumber(10      , 34, 10, 3, 4); // :
    displayDrawNumber(minute1 , 40, 10, 3, 4);
    displayDrawNumber(minute2 , 54, 10, 3, 4);
    displayDrawNumber(10      , 70, 15, 2, 3); // :
    displayDrawNumber(second1 , 75, 15, 2, 3);
    displayDrawNumber(second2 , 85, 15, 2, 3);
  }

  
  { //Start
    byte x = 12;
    byte y = 43;
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_START){
      displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      displayDrawArrowRight(x + 7, y+4, 0);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      displayDrawArrowRight(x + 7, y+4, 1);
    }
  }

  
  { //Reset
    byte x = 39;
    byte y = 43;
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_RESET){
      displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      displayDrawResetIcon(x + 8, y+4, 0);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      displayDrawResetIcon(x + 8, y+4, 1);
    }
  }
    
  { //Back
    byte x = 65;
    byte y = 43;
    const __FlashStringHelper* chars = F("<");
    if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_BACK){
      displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      displayDrawText(x + 8, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
      displayDrawText(x+8, y+4, 1, chars);
    }
  }
  
  displayDrawArrowRight(0, 61, 1);
  displayUpdate();
  
}

void modeStopwatchFinish() {

}
