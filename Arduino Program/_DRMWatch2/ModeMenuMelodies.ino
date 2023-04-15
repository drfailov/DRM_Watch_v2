/*Show menu with melodies by triggerimg GenericMenu*/
//const byte modeMenuMelodiesItemsCount = 8; //сколько пунктов меню в массиве

//Максимальная длина строки:                  |          |
const char modeMenuMelodiesItem1[] PROGMEM = "Entertainer";
const char modeMenuMelodiesItem2[] PROGMEM = "Badinerie";
const char modeMenuMelodiesItem3[] PROGMEM = "Nokia Tune";
const char modeMenuMelodiesItem4[] PROGMEM = "Mozart";
const char modeMenuMelodiesItem5[] PROGMEM = "Mario";
const char modeMenuMelodiesItem6[] PROGMEM = "Groovy Blue";
const char modeMenuMelodiesItem7[] PROGMEM = "Ukraine";
const char modeMenuMelodiesItem8[] PROGMEM = "Blue";

byte getMelodyCount(){ return 8;}
const char* const modeMenuMelodiesItems[] PROGMEM = {
  menuItemBack,
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
  genericMenuLoop(getMelodyCount() + 1, modeMenuMelodiesItems, modeMenuMelodiesSelected, true);
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
  return pgm_read_word(&modeMenuMelodiesItems[index+1]);
}

const byte* const getMelodyByIndex(byte index){
  if (index == 0) 
    return getMelodyEntertainer();
  if (index == 1)  
    return getMelodyBadinerie();
  if (index == 2)  
    return getMelodyNokiaTune();
  if (index == 3) 
    return getMelodyMozart();
  if (index == 4) 
    return getMelodyMario();
  if (index == 5) 
    return getMelodyGroovyBlue();
  if (index == 6) 
    return getMelodyUkraine();
  if (index == 7) 
    return getMelodyBlue();    
}
