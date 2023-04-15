


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
  //auto exit
  if (millis() - genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }

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
  { //scrollbar
    float h = 66;
    displayDrawLine(/*X1*/xOffset+83, /*Y1*/0, /*X2*/xOffset+83, /*Y2*/h, /*C*/1);
    float barHeight = h / genericMenuItemsCount;
    float barPosition = barHeight * selected;
    displayFillRect(/*x*/xOffset+82, /*y*/barPosition, /*w*/3, /*h*/barHeight, /*c*/1);
  }
  if(eepromReadFlipScreen()){ //flip
    //displayDrawLine(/*X1*/96-11, /*Y1*/0, /*X2*/96-11, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/96-8, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/96-8, /*Y*/59, 1);
  }
  else{  //no flip
    displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
    displayDrawCheck(/*X*/2, /*Y*/2, 1);
    displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  }
  displayUpdate();
}

void genericMenuFinish(){
}
