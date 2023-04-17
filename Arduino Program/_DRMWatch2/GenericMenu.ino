


/*
 * Code contains basic functionality for every list menu in device.
 * Every menu is passes its items as arguments to loop() function.
*/
const byte genericMenuViewCount = 5; //сколько на экран помещается

byte genericMenuViewPosition = 0; //первый элемент который сейчас на экране отображается


void genericMenuSetup(){
  displayBacklightOn();
  selected = 0;
  genericMenuLastActionTime = millis();
}

//return true if function triggered exit from current menu
bool genericMenuRoutine(void (*select)(void), byte count){
  if (isButtonUpPressed()){
    genericMenuLastActionTime = millis();
    if(isButtonUpHold()){
      beep();
      goToWatchface();
      return true;
    }
    beep();
    select();
    return true;
  }
  
  if(isButtonDownPressed()){
    genericMenuLastActionTime = millis();
    beep();
    selected ++;
    if(selected >= count) 
      selected = 0;
  }
  if(doAutoExit())return true;
  displayClear();
  drawLegend();
  drawStatusBar();
  return false;
}



//return true if function triggered exit from current menu
bool doAutoExit(){
  //auto exit
  if (millis() - genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return true;
  }
  return false;
}

//icon size: 9x7px
void drawMenuItem(byte index, void (*drawIcon)(byte x,byte y,bool color), const __FlashStringHelper* name, bool animate){
  if(selected/6 != index/6) return;
  const byte xOffset = eepromReadFlipScreen()? 0 : 13;
  const byte yOffset = 16;
  const byte width=21;
  const byte height=15;
  const byte margin = 4;
  byte x = xOffset + 6 + (width+margin) * (index%3);
  byte y = yOffset + (height+margin) * ((index%6)/3);
  void(* drawR) (byte x, byte y, byte w, byte h, boolean color) = selected == index?displayFillRect:displayDrawRect;
  
  drawR(/*x*/x, /*y*/y, /*w*/width, /*h*/height, /*c*/1);
  drawIcon(x + 6, y+4, selected != index);
  if(selected == index){
    displayDrawText(/*X*/xOffset, /*Y*/60, /*C*/1, /*text*/name);
  }
  if(animate)
    displayUpdate();
}

void drawLegend(){
  //LEGEND
  if(eepromReadFlipScreen()){ //flip
    displayDrawLine(/*X1*/96-11, /*Y1*/0, /*X2*/96-11, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/96-8, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/96-8, /*Y*/59, 1);
  }
  else{  //no flip
    displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/2, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  }
}
void drawStatusBar(){
  byte xOffset = eepromReadFlipScreen()? 0 : 13;

  {//Temperature
    float temp = rtcGetTemp();
    dtostrf(/*value*/temp, /*mininum width*/4, /*precision*/1, /*buffer*/buffer);
    sprintf(buffer, "%sC", buffer);
    displayDrawText(xOffset+0, 0, 1, buffer);
  }
  
  byte X = xOffset+83; //96 total
  const byte Y = 0;
  
  {//battery
    X -= 17;
    displayDrawBattery(/*x*/X, /*y*/0);
    if(!batteryIsCharging() && !batteryIsLowPower()) X += 5;
  }
  
  //Silent mode sign
  if(eepromReadSilentMode()){ 
    X -= 11;
    displayDrawSilentModeIcon(/*x*/X, /*y*/0, /*color*/1);
  }
  
  //Alert sign
  if(eepromReadAlertEnabled()){ 
    X-= 11;
    displayDrawAlertSign(/*x*/X, /*y*/0, /*color*/1);
  }
}
