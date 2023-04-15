

//Общий формат вывода данных много где используется
const char* getDateFormat(){return "%02d.%02d.%04d";}
const char* getTimeFormat(){return "%02d:%02d";}

  
//Здесь определенл, которое используется во всех меню, для экономии памяти
#ifdef LANG_RU
const char menuItemBack[] PROGMEM = "< Haзaд";
const char textSaved[] PROGMEM = "Coxpaнeнo";
#endif
#ifdef LANG_EN
const char menuItemBack[] PROGMEM = "< Back";
const char textSaved[] PROGMEM = "Saved";
#endif


const char* getMenuItemBack(){ 
  return menuItemBack;
}
static const char* getTextSaved(){ 
  return menuItemBack;
}


  


#include "Buttons.cpp"

Button_ ButtonUp(pinButtonUp);
Button_ ButtonDown(pinButtonDown);

static bool isButtonUpPressed(){
  return eepromReadFlipScreen()?ButtonDown.isButtonPressed():ButtonUp.isButtonPressed();
}
static bool isButtonDownPressed(){
  return eepromReadFlipScreen()?ButtonUp.isButtonPressed():ButtonDown.isButtonPressed();
}
static bool isButtonUpHold(){
  return /*flip*/eepromReadFlipScreen() ? ButtonDown.waitHold() : ButtonUp.waitHold();
}
static bool isButtonDownNowPressed(){
  return /*flip*/eepromReadFlipScreen() ? ButtonUp.readDebounce() : ButtonDown.readDebounce();
}
