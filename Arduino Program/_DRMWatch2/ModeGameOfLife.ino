
#include "Buttons.cpp"


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
  
  for(byte x = 0; x < LCD_X; x++){
    for(byte y = 0; y < LCD_Y; y++)
      lastCol[y] = currCol[y];
    for(byte y = 0; y < LCD_Y; y++)
      currCol[y] = displayGetPixel(x,y);
      
    for(byte y = 0; y < LCD_Y; y++){
      bool topleft = lastCol[y-1];
      bool top = currCol[y-1];
      bool topright = displayGetPixel(x + 1, y-1);
      
      bool left = lastCol[y];
      bool current = currCol[y];
      bool right = displayGetPixel(x + 1, y);
      
      bool bottomleft = lastCol[y+1];
      bool bottom = currCol[y+1];
      bool bottomright = displayGetPixel(x + 1, y+1);

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
