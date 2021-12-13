/*Global functions related to display. 
 * Init, draw primitives, draw text...
 * Every call to display has to be done by some call from this file.
 * It needed to make migration to other display easier.
*/


LCD1202 lcd(pinLcdRst, pinLcdCs, pinLcdMosi, pinLcdSck);  // RST, CS, MOSI, SCK

/*
 * Display workflow:
 * 
 * > displayInit();
 *       V
 * > displayClear();
 *       V
 * > displayDrawLine(...)
 * > displayFillRect(...)
 * > displayDrawText(...)
 *   ...
 *       V
 * > displayUpdate() 
 *       V
 * > displayClear();
 *   ...
 *
*/


static const PROGMEM byte pathZubat[] = { 42,
   0, 36,     4, 35,    20,  3,    23,  0,    36,  0, //контур
  34,  3,    34,  8,    23,  8,    16, 24,    35, 24,
  35, 35,    33, 37,     0, 37,   255,255,    16, 43,//лапы
  18, 41,    20, 43,    18, 41,    18, 37,    26, 37,
  26, 41,    24, 43,    26, 41,    28, 43,   255,255,
  33,  9,    29, 17,    28,  9,    23, 17,    23,  8, //зубы
  20, 16,    23, 23,    27, 15,    29, 23,    33, 15,
  34, 23,   255,255,    31,  2,    31,  4,    31,  3, //глаз
  32,  3,    30,  3
}; 

static const PROGMEM byte pathDrmWatch[] = { 57,
   0,  0,     7,  0,    10,  3,    10, 13,     7, 16,  //D
   0, 16,     0,  0,   255,255,    13, 16,    13,  0,  //R
  20,  0,    22,  2,    22,  6,    20,  8,    14,  8,
  22, 16,   255,255,    25, 16,    25,  0,    33,  8,  //M
  41,  0,    41, 16,   255,255,     1, 23,     4, 34,  //W
   6, 28,     8, 34,    11, 22,   255,255,    11, 34,  //A
  15, 22,    17, 29,    14, 29,    17, 29,    19, 34,
 255,255,    20, 22,    26, 22,    23, 22,    23, 34,  //T
 255,255,    36, 24,    34, 22,    31, 22,    29, 24,  //C
  29, 32,    31, 34,    34, 34,    36, 32,   255,255,
  39, 22,    39, 34,    39, 30,    41, 28,    43, 28,  //H
  45, 30,    45, 34
};  

static const PROGMEM byte pathBubble[] = { 12,
  39, 28,    53, 18,    89, 18,    95, 15,    95,  3,  
  89,  0,    5,   0,     0,  3,     0, 15,     5, 18,
  40, 18,   37,  29
}; 

void displayInit(){
  Serial.print(F("LCD Init..."));
  lcd.Inicialize();  //Инициализация дисплея
  lcd.Clear_LCD();  //Очистка дисплея  
  displayUpdate();
  Serial.println("OK");
  displayBacklightOff();
}

void displayBacklightOn(){
  Serial.println(F("LCD Backlight ON"));
  pinMode(pinLcdBacklight, OUTPUT);
  digitalWrite(pinLcdBacklight, HIGH);
}

void displayBacklightOff(){
  Serial.println(F("LCD Backlight OFF"));
  pinMode(pinLcdBacklight, OUTPUT);
  digitalWrite(pinLcdBacklight, LOW);
}

void displayClear(){
  lcd.Clear_LCD();
}

void displayUpdate(){
  lcd.Update();
}

void displayDrawLine(byte x0, byte y0, byte x1, byte y1, boolean color){
  lcd.drawLine(/*X1*/x0, /*Y1*/y0, /*X2*/x1, /*Y2*/y1, /*C*/color);
}

void displayDrawRect(byte x, byte y, byte w, byte h, boolean color){
  lcd.drawRect(/*x*/x, /*y*/y, /*w*/w, /*h*/h, /*c*/color);
}

void displayFillRect(byte x, byte y, byte w, byte h, boolean color){
  lcd.fillRect(/*x*/x, /*y*/y, /*w*/w, /*h*/h, /*c*/color);
}

void displayDrawText(int X, int Y, int color, const char* text){
  //1 is black, 0 is white
  lcd.print(X, Y, color, text);
}

//-------- Display independent functions
  
void displayDrawVectorLogo(){
  displayDrawVector(pathZubat, 0, 20, false);
  displayDrawVector(pathBubble, 0, 0, false);
  displayDrawVector(pathDrmWatch, 48, 25, true);
}

//max number of points for one path is 255.
//Array type: const PROGMEM byte path[] = {...);
//Array format: {numberOfPoints, x0, y0, x1, y1, x2, y2, ...}
//255,255 coordinates is skipped, so it can be used for separate paths
void displayDrawVector(const byte* data_array, byte X, byte Y, bool animate){
  byte numberOfPoints = pgm_read_byte(&data_array[0]);
  byte lx = pgm_read_byte(&data_array[1]);
  byte ly = pgm_read_byte(&data_array[2]);
  int currentIndex = 3;
  for(byte i=1; i < numberOfPoints; i++){
    byte x = pgm_read_byte(&data_array[currentIndex]);
    byte y = pgm_read_byte(&data_array[currentIndex + 1]);
    if(x != 255 && y != 255 && lx != 255 && ly != 255)
      displayDrawLine(/*X1*/lx + X, /*Y1*/ly + Y, /*X2*/x + X, /*Y2*/y + Y, /*C*/1);
    if(animate && i%2==0)
      displayUpdate();
    currentIndex += 2;
    lx = x;
    ly = y;
  }
}

void displayMessage(const char* text){
  displayClear();
  displayDrawText(10, 30, 1, text);
  displayUpdate();
}

void displaySimpleMessage(const char* text){
  displayClear();
  displayDrawText(10, 30, 1, text);
  displayUpdate();
}

void displayDrawCheck(byte x, byte y){
  displayDrawLine(/*X1*/x+0, /*Y1*/y+3, /*X2*/x+1, /*Y2*/y+6, /*C*/1);
  displayDrawLine(/*X1*/x+0, /*Y1*/y+3, /*X2*/x+2, /*Y2*/y+5, /*C*/1);
  displayDrawLine(/*X1*/x+1, /*Y1*/y+6, /*X2*/x+5, /*Y2*/y+0, /*C*/1);
  displayDrawLine(/*X1*/x+2, /*Y1*/y+6, /*X2*/x+5, /*Y2*/y+0, /*C*/1);
}

void displayDrawArrowDown(byte x, byte y){
  displayDrawLine(/*X1*/x+0, /*Y1*/y+0, /*X2*/x+6, /*Y2*/y+0, /*C*/1);
  displayDrawLine(/*X1*/x+1, /*Y1*/y+1, /*X2*/x+5, /*Y2*/y+1, /*C*/1);
  displayDrawLine(/*X1*/x+1, /*Y1*/y+2, /*X2*/x+5, /*Y2*/y+2, /*C*/1);
  displayDrawLine(/*X1*/x+2, /*Y1*/y+3, /*X2*/x+4, /*Y2*/y+3, /*C*/1);
  displayDrawLine(/*X1*/x+2, /*Y1*/y+4, /*X2*/x+4, /*Y2*/y+4, /*C*/1);
  displayDrawLine(/*X1*/x+3, /*Y1*/y+5, /*X2*/x+3, /*Y2*/y+5, /*C*/1);
}

void displayDrawArrowRight(byte x, byte y){
  displayDrawLine(/*X1*/x+0, /*Y1*/y+0, /*X2*/x+0, /*Y2*/y+0, /*C*/1);
  displayDrawLine(/*X1*/x+0, /*Y1*/y+1, /*X2*/x+2, /*Y2*/y+1, /*C*/1);
  displayDrawLine(/*X1*/x+0, /*Y1*/y+2, /*X2*/x+4, /*Y2*/y+2, /*C*/1);
  displayDrawLine(/*X1*/x+0, /*Y1*/y+3, /*X2*/x+6, /*Y2*/y+3, /*C*/1);
  displayDrawLine(/*X1*/x+0, /*Y1*/y+4, /*X2*/x+4, /*Y2*/y+4, /*C*/1);
  displayDrawLine(/*X1*/x+0, /*Y1*/y+5, /*X2*/x+2, /*Y2*/y+5, /*C*/1);
  displayDrawLine(/*X1*/x+0, /*Y1*/y+6, /*X2*/x+0, /*Y2*/y+6, /*C*/1);
}
