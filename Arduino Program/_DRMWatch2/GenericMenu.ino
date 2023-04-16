


/*
 * Code contains basic functionality for every list menu in device.
 * Every menu is passes its items as arguments to loop() function.
*/
const byte genericMenuViewCount = 5; //сколько на экран помещается

byte genericMenuViewPosition = 0; //первый элемент который сейчас на экране отображается


void genericMenuSetup(){
  displayBacklightOn();
  selected = 0;
  genericMenuViewPosition = 0;
  genericMenuLastActionTime = millis();
}


/* genericMenuItemsCount - number of items in array.
 * genericMenuItems[] - Array of addresses to strings stored in PROGMEM
 * (*onSelected)(byte index) - Pointer to function which will be called when user selects item.
 * progmemArray - Text has to be stored in progmem. But array can be stored in RAM or in PROGMEM. Pass true if your array stored in PROGMEM.
*/
void genericMenuLoop(const int genericMenuItemsCount, const char* const genericMenuItems[], void (*onSelected)(byte index), bool progmemArray){
  if (isButtonUpPressed()){  
    if(isButtonUpHold()){
      beep();
      goToWatchface();
      return;
    }
    genericMenuLastActionTime = millis();
    beep();
    onSelected (selected);
    return;
  }

  if (isButtonDownPressed()) { 
    genericMenuLastActionTime = millis();
    beep();
    selected ++;
    if (selected >= genericMenuItemsCount) selected = 0;
    while (selected >= genericMenuViewPosition + genericMenuViewCount) genericMenuViewPosition ++;
    while (selected < genericMenuViewPosition) genericMenuViewPosition --;
  }
  doAutoExit();

  //draw
  displayClear();
  byte xOffset = 11;
  if (/*flip*/eepromReadFlipScreen())
    xOffset = 0;
  for (int i = 0; i < genericMenuViewCount; i++) {
    int index = genericMenuViewPosition + i;
    if (index < genericMenuItemsCount) {
      if(progmemArray)
        strcpy_P(buffer, pgm_read_word(&(genericMenuItems[index])));  //for PROGMEM arrays
      else
        strcpy_P(buffer, (genericMenuItems[index]));      //for RAM arrays
      if (index == selected) {
        displayFillRect(/*x*/xOffset+0, /*y*/1 + 13 * i, /*w*/81, /*h*/13, /*c*/1);
        displayDrawText(/*X*/xOffset+4, /*Y*/4 + 13 * i, /*C*/0, buffer);
      }
      else {
        displayDrawText(/*X*/xOffset+4, /*Y*/4 + 13 * i, /*C*/1, buffer);
      }
    }
  }
  
  drawLegend();
  displayUpdate();
}

void genericMenuFinish(){
}





void doAutoExit(){
  //auto exit
  if (millis() - genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }
}

//icon size: 9x7px
void drawMenuItem(byte index, void (*drawIcon)(byte x,byte y,bool color), const __FlashStringHelper* name, bool animate){
  const byte xOffset = eepromReadFlipScreen()? 0 : 13;
  const byte yOffset = 16;
  const byte width=21;
  const byte height=15;
  const byte margin = 4;
  byte x = xOffset + 6 + (width+margin) * (index%3);
  byte y = yOffset + (height+margin) * (index/3);
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
    X -= 10;
    displayDrawSilentModeIcon(/*x*/X, /*y*/0, /*color*/1);
  }
  
  //Alert sign
  if(eepromReadAlertEnabled()){ 
    X-= 11;
    displayDrawAlertSign(/*x*/X, /*y*/0, /*color*/1);
  }
}
