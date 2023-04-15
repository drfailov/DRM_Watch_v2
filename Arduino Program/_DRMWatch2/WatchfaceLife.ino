int steps = 0;

void WatchfaceLife(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate)
{
  //loop every 200 steps
  if(animate) steps = 0;
  if(steps > 200) steps = 0;
  
  //if first step, fill screen with random pattern
  if(steps == 0){
    displayClear();
    for(byte x = 0; x < LCD_X; x++){
      for(byte y = 0; y < LCD_Y; y++){
        bool c = micros()%3 == 0;
        displaySetPixel(x,y, c);
      }
    }
  }

  //draw
  lifeStep();
  steps ++;
  drawTime (hour, minute);
  displayUpdate();
}

void drawTime(byte hour, byte minute){
  displayFillRect(/*x*/ 29, /*y*/ 20, /*w*/ 42, /*h*/ 29, /*color*/ 0);
  displayDrawRect(/*x*/ 30, /*y*/ 21, /*w*/ 40, /*h*/ 27, /*color*/ 1);
  sprintf(buffer, "%02d:%02d", hour, minute);
  displayDrawText(35, 25, 1, buffer);
  displayDrawBattery(39, 38);
}
