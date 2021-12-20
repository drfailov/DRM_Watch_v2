/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuMelodiesItemsCount = 8; //сколько пунктов меню в массиве

//Максимальная длина строки:                  |          |
const char modeMenuMelodiesItem1[] PROGMEM = "Entertainer";
const char modeMenuMelodiesItem2[] PROGMEM = "Badinerie";
const char modeMenuMelodiesItem3[] PROGMEM = "Nokia Tune";
const char modeMenuMelodiesItem4[] PROGMEM = "Mozart";
const char modeMenuMelodiesItem5[] PROGMEM = "Mario";
const char modeMenuMelodiesItem6[] PROGMEM = "Groovy Blue";
const char modeMenuMelodiesItem7[] PROGMEM = "Toreador";
const char modeMenuMelodiesItem8[] PROGMEM = "< Back";

const char* const modeMenuMelodiesItems[] PROGMEM = {
  modeMenuMelodiesItem1,
  modeMenuMelodiesItem2,
  modeMenuMelodiesItem3,
  modeMenuMelodiesItem4,
  modeMenuMelodiesItem5,
  modeMenuMelodiesItem6,
  modeMenuMelodiesItem7,
  modeMenuMelodiesItem8
};


void modeMenuMelodiesSetup() {
  genericMenuSetup();
}

void modeMenuMelodiesLoop() {
  genericMenuLoop(modeMenuMelodiesItemsCount, modeMenuMelodiesItems, modeMenuMelodiesSelected);
}

void modeMenuMelodiesFinish() {
  genericMenuFinish();
}

void modeMenuMelodiesSelected(byte index) {
  delay(200);
  
  if (index == 0) { 
    melodyPlayerPlayMelody(getMelodyEntertainer());
  }
  if (index == 1) { 
    melodyPlayerPlayMelody(getMelodyBadinerie());
  }
  if (index == 2) { 
    melodyPlayerPlayMelody(getMelodyNokiaTune());
  }
  if (index == 3) {
    melodyPlayerPlayMelody(getMelodyMozart());
  }
  if (index == 4) {
    melodyPlayerPlayMelody(getMelodyMario());
  }  
  if (index == 5) {
    melodyPlayerPlayMelody(getMelodyGroovyBlue());
  }  
  if (index == 6) {
    melodyPlayerPlayMelody(getMelodyToreador());
  }
  if (index == 7) { //Back
    setMode(MODE_MENU_APPS);
    return;
  }
}
