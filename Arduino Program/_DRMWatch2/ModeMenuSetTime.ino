int modeMenuSetTimeSelected = 0;

byte modeMenuSetTimeHours = 01;
byte modeMenuSetTimeMinutes = 01;
byte modeMenuSetTimeSeconds = 01;

byte modeMenuSetTimeDays = 01;
byte modeMenuSetTimeMonths = 01;
int modeMenuSetTimeYears = 2021;


void modeMenuSetTimeSetup(){
  //load data from RTC
  digitalWrite(pinLcdBacklight, HIGH);
  modeMenuSetTimeSelected = 0;
}

void modeMenuSetTimeLoop(){
  if (isButtonUpPressed()) {
    beep();
    //change value
    if(modeMenuSetTimeSelected == 0) {//hours
      modeMenuSetTimeHours ++;
      if(modeMenuSetTimeHours > 23) modeMenuSetTimeHours = 1;
    }
  }

  if (isButtonDownPressed()) {
    beep();
    //move next
    modeMenuSetTimeSelected ++;
  }

  
  displayClear();


  
  { //hours
    byte x = 30;
    byte y = 15;
    char chars[4];
    sprintf(chars, "%02d", modeMenuSetTimeHours);
    if(modeMenuSetTimeSelected == 0){
      displayFillRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x + 4, y+4, 0, chars);
    }
    else{
      displayDrawRect(/*x*/x, /*y*/y, /*w*/19, /*h*/15, /*c*/1);
      displayDrawText(x+4, y+4, 1, chars);
    }
  }
  displayUpdate();
}

void modeMenuSetTimeFinish(){
  digitalWrite(pinLcdBacklight, LOW);
}
