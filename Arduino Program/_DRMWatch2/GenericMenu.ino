#include "Display.cpp"
#include "Buttons.cpp"
#include "Buzzer.cpp"
#include "Generic.h"

/*
 * Code contains basic functionality for every list menu in device.
 * Every menu is passes its items as arguments to loop() function.
*/
const byte genericMenuViewCount = 5; //сколько на экран помещается
const long genericMenuAutoExitTimeout = 120000; //MS Время до автоматического выхода с меню

byte genericMenuSelectPosition = 0; //текущий выделенный элемени
byte genericMenuViewPosition = 0; //первый элемент который сейчас на экране отображается
long genericMenuLastActionTime = 0; //последнее действие кнопками, нужно для автоматического выхода


void genericMenuSetup(){
  Display.displayInit();
  Display.displayBacklightOn();
  genericMenuSelectPosition = 0;
  genericMenuViewPosition = 0;
  genericMenuLastActionTime = millis();
}


/* genericMenuItemsCount - number of items in array.
 * genericMenuItems[] - Array of addresses to strings stored in PROGMEM
 * (*onSelected)(byte index) - Pointer to function which will be called when user selects item.
 * progmemArray - Text has to be stored in progmem. But array can be stored in RAM or in PROGMEM. Pass true if your array stored in PROGMEM.
*/
void genericMenuLoop(const int genericMenuItemsCount, const char* const genericMenuItems[], void (*onSelected)(byte index), bool progmemArray){
  if (ButtonUp.isButtonPressed()) {
    genericMenuLastActionTime = millis();
    Buzzer.beep();
    onSelected (genericMenuSelectPosition);
    return;
  }

  if (ButtonDown.isButtonPressed()) {
    genericMenuLastActionTime = millis();
    Buzzer.beep();
    genericMenuSelectPosition ++;
    if (genericMenuSelectPosition >= genericMenuItemsCount) genericMenuSelectPosition = 0;
    while (genericMenuSelectPosition >= genericMenuViewPosition + genericMenuViewCount) genericMenuViewPosition ++;
    while (genericMenuSelectPosition < genericMenuViewPosition) genericMenuViewPosition --;
  }
  //auto exit
  if (millis() - genericMenuLastActionTime > genericMenuAutoExitTimeout) {
    goToWatchface();
    return;
  }

  //draw
  Display.displayClear();
  for (int i = 0; i < genericMenuViewCount; i++) {
    int index = genericMenuViewPosition + i;
    if (index < genericMenuItemsCount) {
      if(progmemArray)
        strcpy_P(Generic.buffer, pgm_read_word(&(genericMenuItems[index])));  //for PROGMEM arrays
      else
        strcpy_P(Generic.buffer, (genericMenuItems[index]));      //for RAM arrays
      if (index == genericMenuSelectPosition) {
        Display.displayFillRect(/*x*/11, /*y*/1 + 13 * i, /*w*/81, /*h*/13, /*c*/1);
        Display.displayDrawText(/*X*/15, /*Y*/4 + 13 * i, /*C*/0, Generic.buffer);
      }
      else {
        Display.displayDrawText(/*X*/15, /*Y*/4 + 13 * i, /*C*/1, Generic.buffer);
      }
    }
  }
  { //scrollbar
    float h = 66;
    Display.displayDrawLine(/*X1*/94, /*Y1*/0, /*X2*/94, /*Y2*/h, /*C*/1);
    float barHeight = h / genericMenuItemsCount;
    float barPosition = barHeight * genericMenuSelectPosition;
    Display.displayFillRect(/*x*/93, /*y*/barPosition, /*w*/3, /*h*/barHeight, /*c*/1);
  }
  Display.displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
  Display.displayDrawCheck(/*X*/2, /*Y*/2, 1);
  Display.displayDrawArrowDown(/*X*/1, /*Y*/59, 1);
  Display.displayUpdate();
}

void genericMenuFinish(){
}
