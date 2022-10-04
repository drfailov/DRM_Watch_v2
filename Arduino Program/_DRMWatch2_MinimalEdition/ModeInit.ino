#include "Display.cpp"

/*Mode is initial. Needed to init modules and welcome message.*/

void modeInitSetup(){
  Display.displayInit();
  Display.displayBacklightOn();

  //------------------ DRM WATCH PLAYGROUND


  //------------------ END DRM WATCH PLAYGROUND
  
  Display.displaySimpleMessage("RTC...");
  RTC.rtcInit();
  Display.displayClear();
  Display.displayDrawText(67, 61, 1, version);
  Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/25, /*y*/10, /*animate*/6, /*color*/1);
  Display.displayUpdate();
  
  Buzzer.beepConfirm();
  Display.displayUpdate();

  //uncomment this to reset arduino to factiry state
  //MyEEPROM.eepromFIllByOnes();
}

void modeInitLoop(){
  delay(200);
  goToWatchface();
}

void modeInitFinish(){
  
}
