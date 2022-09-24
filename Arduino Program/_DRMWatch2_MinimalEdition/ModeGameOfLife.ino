#include "Display.cpp"
#include "Buttons.cpp"
#include "Buzzer.cpp"


long modeGameOfLifeStartedTime = 0;
long modeGameOfLifeFinishedTime = 0;
bool modeGameOfLifeIsRunning = false;

void modeGameOfLifeSetup() {
  genericMenuSetup();
}

void modeGameOfLifeLoop() {
  if (isButtonUpPressed()){ //PRESS
    if (isButtonUpHold()){ //if hold - reset
      Buzzer.beep();
      goToWatchface();
      return;
    }
    Buzzer.beep();
    randomScreen();
  }

  lifeStep();
  Display.displayUpdate();
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
      currCol[y] = Display.displayGetPixel(x,y);
      
    for(byte y = 0; y < LCD_Y; y++){
      bool topleft = lastCol[y-1];
      bool top = currCol[y-1];
      bool topright = Display.displayGetPixel(x + 1, y-1);
      
      bool left = lastCol[y];
      bool current = currCol[y];
      bool right = Display.displayGetPixel(x + 1, y);
      
      bool bottomleft = lastCol[y+1];
      bool bottom = currCol[y+1];
      bool bottomright = Display.displayGetPixel(x + 1, y+1);

      byte neighbours = topleft+top+topright+left+right+bottomleft+bottom+bottomright;
      
      bool c;
      if(current)
        c = (neighbours == 2 || neighbours == 3);
      else
        c = neighbours == 3;
      Display.displaySetPixel(x, y, c);
    }
  }
}

void randomScreen(){
  for(byte x = 0; x < LCD_X; x++){
    for(byte y = 0; y < LCD_Y; y++){
      bool c = micros()%3 == 0;
      Display.displaySetPixel(x,y, c);
    }
  }
}
