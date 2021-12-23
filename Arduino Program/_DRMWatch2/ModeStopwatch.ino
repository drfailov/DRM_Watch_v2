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
  
  
  displayClear();
  
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
      
    int minute1 = minute / 10;
    int minute2 = minute - (minute1 * 10);
    int second1 = second / 10;
    int second2 = second - (second1 * 10);
    int millisecond1 = millisecond / 10;
    int millisecond2 = millisecond - (millisecond1 * 10);
    
    displayDrawNumber(minute1 , 13, 10, 3, 4);
    displayDrawNumber(minute2 , 27, 10, 3, 4);
    displayDrawNumber(10      , 41, 10, 3, 4); // :
    displayDrawNumber(second1 , 46, 10, 3, 4);
    displayDrawNumber(second2 , 60, 10, 3, 4);
    displayDrawNumber(10      , 74, 15, 2, 3); // :
    displayDrawNumber(millisecond1 , 78, 15, 2, 3);
    displayDrawNumber(millisecond2 , 88, 15, 2, 3);
  }

  
  { //Start
    byte x = 17;
    byte y = 43;
    if(modeStopwatchIsRunning == false){
      if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_START){
        displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        displayDrawArrowRight(x + 7, y+4, 0);
      }
      else{
        displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        displayDrawArrowRight(x + 7, y+4, 1);
      }
    }
    if(modeStopwatchIsRunning == true){
      if(modeStopwatchSelectedItem == MODE_STOPWATCH_SELECTED_START){
        displayFillRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        displayDrawPauseSign(x + 6, y+4, 0);
      }
      else{
        displayDrawRect(/*x*/x, /*y*/y, /*w*/20, /*h*/15, /*c*/1);
        displayDrawPauseSign(x + 6, y+4, 1);
      }
    }
  }

  
  { //Reset
    byte x = 44;
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
    byte x = 70;
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
  displayDrawCheck(/*X*/2, /*Y*/2, 1);
  displayUpdate();
  
}

void modeStopwatchFinish() {

}
