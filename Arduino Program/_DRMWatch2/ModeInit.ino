#include "Display.cpp"

/*Mode is initial. Needed to init modules and welcome message.*/

void modeInitSetup(){
  Display.displayInit();
  Display.displayBacklightOn();
  Display.displaySimpleMessage("RTC Init");
  RTC.rtcInit();
  Display.displayClear();
  Display.displayDrawText(67, 61, 1, version);
  Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/25, /*y*/10, /*animate*/false, /*color*/1);
  Display.displayUpdate();
  Buzzer.beepConfirm();
  for(byte x=25; x > 0; x -= 5){
    Display.displayClear();
    Display.displayDrawText(67, 61, 1, version);
    Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/x, /*y*/10, /*animate*/false, /*color*/1);
    Display.displayUpdate();
  }
  Display.displayClear();
  Display.displayDrawText(67, 61, 1, version);
  Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/0, /*y*/10, /*animate*/false, /*color*/1);
  Display.displayDrawVector(/*path*/Display.getPathDrmWatch(), /*x*/48, /*y*/15, /*animate*/4, /*color*/1);
  Display.displayUpdate();

//  for(int i=0; i< 5; i++){
//    Display.displayMessage (F("Срочно"));
//    Display.displayMessage (F("Иди нахуй"));
//  }

    //MyEEPROM.eepromFIllByOnes();
}

void modeInitLoop(){
  delay(200);
  goToWatchface();
}

void modeInitFinish(){
  
}
