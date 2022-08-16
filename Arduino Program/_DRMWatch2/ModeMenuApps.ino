/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuAppsItemsCount = 7; //сколько пунктов меню в массиве

//Максимальная длина строки:              |          |
#ifdef LANG_EN
const char modeMenuAppsItemStopwatch[] PROGMEM = "Stopwatch";
const char modeMenuAppsItem2[] PROGMEM = "Alarm";
const char modeMenuAppsItem3[] PROGMEM = "Zrada";
const char modeMenuAppsItem4[] PROGMEM = "Melodies";
const char modeMenuAppsItem5[] PROGMEM = "Life";
const char modeMenuAppsItemMeow[] PROGMEM = "Meow";
#endif
#ifdef LANG_RU
const char modeMenuAppsItemStopwatch[] PROGMEM = "Ceкyндoмep";
const char modeMenuAppsItem2[] PROGMEM = "Бyдильник";
const char modeMenuAppsItem3[] PROGMEM = "Зpaдa";
const char modeMenuAppsItem4[] PROGMEM = "Meлoдии";
const char modeMenuAppsItem5[] PROGMEM = "Жизнь";
const char modeMenuAppsItemMeow[] PROGMEM = "Mяy";
#endif

const char* modeMenuAppsItems[] = {
  Generic.getMenuItemBack(),
  modeMenuAppsItemStopwatch,
  modeMenuAppsItem2,
  modeMenuAppsItem3,
  modeMenuAppsItem4,
  modeMenuAppsItem5,
  modeMenuAppsItemMeow
};


void modeMenuAppsSetup() {
  genericMenuSetup();
}

void modeMenuAppsLoop() {
  genericMenuLoop(modeMenuAppsItemsCount, modeMenuAppsItems, modeMenuAppsSelected, false);
}

void modeMenuAppsFinish() {
  genericMenuFinish();
}

void modeMenuAppsSelected(byte index) {
  if (index == 0) { //Back
    setMode(MODE_MENU_MAIN);
  }
  else if (index == 1) { //Stopwatch
    setMode(MODE_STOPWATCH);
  }
  else if (index == 2) { //alarm
    setMode(MODE_SET_ALARM);
  }
  else if (index == 3) { //Zrada
    if(millis()%2==0){
      Display.displayMessage(F("3paдa"));
    }
    else{
      Display.displayMessage(F("Пepeмoгa"));
    }
  }
  else if (index == 4) { //Melodies
    setMode(MODE_MENU_MELODIES);
  }
  else if (index == 5) { //life
    setMode(MODE_GAME_OF_LIFE);
  }
  else if (index == 6) { //Meow
    meow();
  }
}

void meow(){
  Display.displayClear();
  Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/25, /*y*/5, /*animate*/0, /*color*/1);
  Display.displayDrawText(35, 58, 1, "MEOW");
  Display.displayUpdate();
  while(1){
    byte meowLength = 8;
    int meowData[] = {2012, 2544, 2742, 2556, 2416, 2128, 1920, 1874, -1000};
    float meowCoef = 0.4f + ((millis()%50)*0.01f);
    float meowOffset = 700+(millis()%600);
    float meowTime = 5 + (millis()%2);
    float meowValue = meowData[0];
    float meowSpeed = 0;
    meowValue *= meowCoef;
    meowValue += meowOffset;
    pinMode(pinBuzzer, OUTPUT);
    for(byte i=1; i<meowLength; i++){
      float meowValueNext = meowData[i];
      meowValueNext *= meowCoef;
      meowValueNext += meowOffset;
      meowValueNext += millis()%150;
      for(int j=0; j<7; j++){
        meowSpeed += (meowValueNext-meowValue)*0.1f;
        meowSpeed *= 0.7f;
        meowValue += meowSpeed;
        tone(pinBuzzer, meowValue); 
        delay(meowTime);
      }
    }
    noTone(pinBuzzer);      // не пищать
    pinMode(pinBuzzer, INPUT);   
    if(isButtonUpPressed()) return; 
    delay(300 + (millis()%1000));
  }
}
