#include "Display.cpp"
#include "Buttons.cpp"
#include "Buzzer.cpp"
#include "Generic.cpp"

/*
 * Code contains basic functionality for every list menu in device.
 * Every menu is passes its items as arguments to loop() function.
*/
const byte genericMenuViewCount = 5; //сколько на экран помещается

byte genericMenuViewPosition = 0; //первый элемент который сейчас на экране отображается


void genericMenuSetup(){
  Display.displayBacklightOn();
  Generic.selected = 0;
  genericMenuViewPosition = 0;
  Generic.genericMenuLastActionTime = millis();
}


/* genericMenuItemsCount - number of items in array.
 * genericMenuItems[] - Array of addresses to strings stored in PROGMEM
 * (*onSelected)(byte index) - Pointer to function which will be called when user selects item.
 * progmemArray - Text has to be stored in progmem. But array can be stored in RAM or in PROGMEM. Pass true if your array stored in PROGMEM.
*/
void genericMenuLoop(const int genericMenuItemsCount, const char* const genericMenuItems[], void (*onSelected)(byte index), bool progmemArray){
  if (isButtonUpPressed()){  
    if(isButtonUpHold()){
      Buzzer.beep();
      goToWatchface();
      return;
    }
    Generic.genericMenuLastActionTime = millis();
    Buzzer.beep();
    onSelected (Generic.selected);
    return;
  }

  if (isButtonDownPressed()) { 
    Generic.genericMenuLastActionTime = millis();
    Buzzer.beep();
    Generic.selected ++;
    if (Generic.selected >= genericMenuItemsCount) Generic.selected = 0;
    while (Generic.selected >= genericMenuViewPosition + genericMenuViewCount) genericMenuViewPosition ++;
    while (Generic.selected < genericMenuViewPosition) genericMenuViewPosition --;
  }
  //auto exit
  if (millis() - Generic.genericMenuLastActionTime > AUTO_EXIT_TIMEOUT) {
    goToWatchface();
    return;
  }

  //draw
  Display.displayClear();
  byte xOffset = 11;
  if (/*flip*/MyEEPROM.eepromReadFlipScreen())
    xOffset = 0;
  for (int i = 0; i < genericMenuViewCount; i++) {
    int index = genericMenuViewPosition + i;
    if (index < genericMenuItemsCount) {
      if(progmemArray)
        strcpy_P(Generic.buffer, pgm_read_word(&(genericMenuItems[index])));  //for PROGMEM arrays
      else
        strcpy_P(Generic.buffer, (genericMenuItems[index]));      //for RAM arrays
      if (index == Generic.selected) {
        Display.displayFillRect(/*x*/xOffset+0, /*y*/1 + 13 * i, /*w*/81, /*h*/13, /*c*/1);
        Display.displayDrawText(/*X*/xOffset+4, /*Y*/4 + 13 * i, /*C*/0, Generic.buffer);
      }
      else {
        Display.displayDrawText(/*X*/xOffset+4, /*Y*/4 + 13 * i, /*C*/1, Generic.buffer);
      }
    }
  }
  { //scrollbar
    float h = 66;
    Display.displayDrawLine(/*X1*/xOffset+83, /*Y1*/0, /*X2*/xOffset+83, /*Y2*/h, /*C*/1);
    float barHeight = h / genericMenuItemsCount;
    float barPosition = barHeight * Generic.selected;
    Display.displayFillRect(/*x*/xOffset+82, /*y*/barPosition, /*w*/3, /*h*/barHeight, /*c*/1);
  }
  if(MyEEPROM.eepromReadFlipScreen()){ //flip
    //Display.displayDrawLine(/*X1*/96-11, /*Y1*/0, /*X2*/96-11, /*Y2*/68, /*C*/1);
    Display.displayDrawCheck(/*X*/96-8, /*Y*/2, 1);
    Display.displayDrawArrowDown(/*X*/96-8, /*Y*/59, 1);
  }
  else{  //no flip
    Display.displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
    Display.displayDrawCheck(/*X*/2, /*Y*/2, 1);
    Display.displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  }
  Display.displayUpdate();
}

void genericMenuFinish(){
}
