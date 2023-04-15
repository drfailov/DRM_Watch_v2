long modeGameOfLifeStartedTime = 0;
long modeGameOfLifeFinishedTime = 0;
bool modeGameOfLifeIsRunning = false;

void modeGameOfLifeSetup() {
  genericMenuSetup();
}

void modeGameOfLifeLoop() {
  if (isButtonUpPressed()){ //PRESS
    if (isButtonUpHold()){ //if hold - reset
      beep();
      goToWatchface();
      return;
    }
    beep();
    randomScreen();
  }

  lifeStep();
  displayUpdate();
}

void modeGameOfLifeFinish() {

}


void lifeStep(){
  bool lastCol [LCD_Y];
  bool currCol [LCD_Y];
  for(byte y = 0; y < LCD_Y; y++)
      currCol[y] = false;
  
  for(byte x = 0; x < LCD_X; x++){
    for(byte y = 0; y < LCD_Y; y++)
      lastCol[y] = currCol[y];
    for(byte y = 0; y < LCD_Y; y++)
      currCol[y] = displayGetPixel(x,y);
      
    for(byte y = 0; y < LCD_Y; y++){
      bool topleft = y==0?false:lastCol[y-1];
      bool top = y==0?false:currCol[y-1];
      bool topright = y==0?false:displayGetPixel(x + 1, y-1);
      
      bool left = lastCol[y];
      bool current = currCol[y];
      bool right = x>=LCD_X-1?false:displayGetPixel(x + 1, y);
      
      bool bottomleft = y>=LCD_Y-1?false:lastCol[y+1];
      bool bottom = y>=LCD_Y-1?false:currCol[y+1];
      bool bottomright = y>=LCD_Y-1?false:displayGetPixel(x + 1, y+1);

      byte neighbours = topleft+top+topright+left+right+bottomleft+bottom+bottomright;
      
      bool c;
      if(current)
        c = (neighbours == 2 || neighbours == 3);
      else
        c = neighbours == 3;
      displaySetPixel(x, y, c);
    }
  }
}

void randomScreen(){
  for(byte x = 0; x < LCD_X; x++){
    for(byte y = 0; y < LCD_Y; y++){
      bool c = micros()%3 == 0;
      displaySetPixel(x,y, c);
    }
  }
}
