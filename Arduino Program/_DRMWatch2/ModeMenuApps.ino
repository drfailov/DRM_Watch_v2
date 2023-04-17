#define APPS_MENU_SELECTED_BACK 0
#define APPS_MENU_SELECTED_STOPWATCH 1
#define APPS_MENU_SELECTED_ALARM 2
#define APPS_MENU_SELECTED_ZRADA 3
#define APPS_MENU_SELECTED_MELODIES 4
#define APPS_MENU_SELECTED_LIFE 5
#define APPS_MENU_SELECTED_MEOW 6

void modeMenuAppsSetup() {
  genericMenuSetup();
}

void modeMenuAppsLoop() {
  if(genericMenuRoutine(modeMenuAppsSelected, 7))return;

#ifdef LANG_EN
  const __FlashStringHelper* textStopwatch = F("Stopwatch");
  const __FlashStringHelper* textAlarm = F("Alarm");
  const __FlashStringHelper* textZrada = F("Zrada");
  const __FlashStringHelper* textMelodies = F("Melodies");
  const __FlashStringHelper* textLife = F("Life");
  const __FlashStringHelper* textMeow = F("Meow");
#endif
#ifdef LANG_RU
  const __FlashStringHelper* textStopwatch = F("Ceкyндoмep");
  const __FlashStringHelper* textAlarm = F("Бyдильник");
  const __FlashStringHelper* textZrada = F("3paдa");
  const __FlashStringHelper* textMelodies = F("Meлoдии");
  const __FlashStringHelper* textLife = F("Жизнь");
  const __FlashStringHelper* textMeow = F("Mяy");
#endif
#ifdef LANG_UA
  const __FlashStringHelper* textStopwatch = F("Ceкyндoмip");
  const __FlashStringHelper* textAlarm = F("Бyдильник");
  const __FlashStringHelper* textZrada = F("3paдa");
  const __FlashStringHelper* textMelodies = F("Myзикa");
  const __FlashStringHelper* textLife = F("Життя");
  const __FlashStringHelper* textMeow = F("Mяy");
#endif
  
  drawMenuItem(/*index*/APPS_MENU_SELECTED_BACK, /*icon*/displayDrawBackIcon, /*text*/(__FlashStringHelper*)menuItemBack, /*animate*/animate);
  drawMenuItem(/*index*/APPS_MENU_SELECTED_STOPWATCH, /*icon*/displayDrawIconStopwatch, /*text*/textStopwatch, /*animate*/animate);
  drawMenuItem(/*index*/APPS_MENU_SELECTED_ALARM, /*icon*/displayDrawAlertSign, /*text*/textAlarm, /*animate*/animate);
  drawMenuItem(/*index*/APPS_MENU_SELECTED_ZRADA, /*icon*/displayDrawZradaSign, /*text*/textZrada, /*animate*/animate);
  drawMenuItem(/*index*/APPS_MENU_SELECTED_MELODIES, /*icon*/displayDrawMelodiesSign, /*text*/textMelodies, /*animate*/animate);
  drawMenuItem(/*index*/APPS_MENU_SELECTED_LIFE, /*icon*/displayDrawLifeSign, /*text*/textLife, /*animate*/animate);
  drawMenuItem(/*index*/APPS_MENU_SELECTED_MEOW, /*icon*/displayDrawCatSign, /*text*/textMeow, /*animate*/animate);
  
  displayUpdate();
  animate = false;
}

void modeMenuAppsSelected(){
  //variable is: selected
  if(selected == APPS_MENU_SELECTED_BACK){
      setMode(MODE_MENU_MAIN);
    }
    else if(selected == APPS_MENU_SELECTED_STOPWATCH){
      setMode(MODE_STOPWATCH);
    }
    else if(selected == APPS_MENU_SELECTED_ALARM){
      setMode(MODE_SET_ALARM);
    }
    else if(selected == APPS_MENU_SELECTED_ZRADA){
      if(millis()%2==0){
        displayMessage(F("3paдa"));
      }
      else{
        displayMessage(F("Пepeмoгa"));
      }
    }
    else if(selected == APPS_MENU_SELECTED_MELODIES){
      setMode(MODE_MENU_MELODIES);
    }
    else if(selected == APPS_MENU_SELECTED_LIFE){
      setMode(MODE_GAME_OF_LIFE);
      
    }
    else if(selected == APPS_MENU_SELECTED_MEOW){
      meow(); 
    }
}


void meow(){
  displayClear();
  displayDrawVector(/*path*/getPathZubat(), /*x*/25, /*y*/5, /*animate*/0, /*color*/1);
  displayDrawText(35, 58, 1, "MEOW");
  displayUpdate();
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
    //pinMode(pinBuzzer, OUTPUT);
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
