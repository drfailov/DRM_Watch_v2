void modeMenuMelodiesSetup() {
  genericMenuSetup();
}

void modeMenuMelodiesLoop() {
  if(genericMenuRoutine(modeMenuMelodiesSelected, getMelodyCount()+1))return;
  
  drawMenuItem(/*index*/0, /*icon*/displayDrawBackIcon, /*text*/(__FlashStringHelper*)menuItemBack, /*animate*/animate);
  for(byte i=0; i<getMelodyCount();i++)
    drawMenuItem(/*index*/i+1, /*icon*/displayDrawMelodiesSign, /*text*/(__FlashStringHelper*)getMelodyName(i), /*animate*/animate);
  displayUpdate();
  animate = false;
}


void modeMenuMelodiesSelected() {
  delay(200);
  if (selected == 0) { //Back
    setMode(MODE_MENU_APPS);
    return;
  }
  else{
    melodyPlayerPlayMelody(getMelodyByIndex(selected-1));
  }
}
