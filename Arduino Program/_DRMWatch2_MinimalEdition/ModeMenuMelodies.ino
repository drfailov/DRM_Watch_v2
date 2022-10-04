/*Show menu with melodies by triggerimg GenericMenu*/
//const byte modeMenuMelodiesItemsCount = 4; //сколько пунктов меню в массиве

//Максимальная длина строки:                  |          |
const char modeMenuMelodiesItemEntertainer[] PROGMEM = "Entertainer";
const char modeMenuMelodiesItemBadinerie[] PROGMEM = "Badinerie";
const char modeMenuMelodiesItemMozart[] PROGMEM = "Mozart";

const char* const modeMenuMelodiesItems[] PROGMEM = {
  menuItemBack,
  modeMenuMelodiesItemEntertainer,
  modeMenuMelodiesItemBadinerie,
  modeMenuMelodiesItemMozart
};


void modeMenuMelodiesSetup() {
  genericMenuSetup();
}

void modeMenuMelodiesLoop() {
  genericMenuLoop(eepromMelodyCount + 1, modeMenuMelodiesItems, modeMenuMelodiesSelected, true);
}

void modeMenuMelodiesFinish() {
  genericMenuFinish();
}

void modeMenuMelodiesSelected(byte index) {
  delay(200);
  if (index == 0) { //Back
    setMode(MODE_MENU_APPS);
    return;
  }
  else{
    melodyPlayerPlayMelody(getMelodyByIndex(index-1));
  }
}

const char* getMelodyName(byte index){
  uint16_t ptr = pgm_read_word(&modeMenuMelodiesItems[index+1]);
  return ptr;
}

const byte* const getMelodyByIndex(byte index){
  if (index == 0) 
    return getMelodyEntertainer();
  if (index == 1)  
    return getMelodyBadinerie();
  if (index == 2) 
    return getMelodyMozart();
}
