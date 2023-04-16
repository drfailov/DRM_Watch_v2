void modeMenuMelodiesSetup() {
  genericMenuSetup();
}

void modeMenuMelodiesLoop() {
  if (isButtonUpPressed()){
    genericMenuLastActionTime = millis();
    beep();
    if(selected == 0){
      setMode(MODE_MENU_APPS);
    }
    else{
      melodyPlayerPlayMelody(getMelodyByIndex(selected-1));
    }
    return;
  }
  
  if(isButtonDownPressed()){
    genericMenuLastActionTime = millis();
    beep();
    selected ++;
    if(selected > getMelodyCount()) 
      selected = 0;
  }
  doAutoExit();
  


  displayClear();
  drawLegend();
  drawStatusBar();
  drawMenuItem(/*index*/0, /*icon*/displayDrawBackIcon, /*text*/(__FlashStringHelper*)menuItemBack, /*animate*/animate);
  for(byte i=0; i<getMelodyCount();i++)
    drawMenuItem(/*index*/i+1, /*icon*/displayDrawMelodiesSign, /*text*/(__FlashStringHelper*)getMelodyName(i), /*animate*/animate);
  displayUpdate();
  animate = false;
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
