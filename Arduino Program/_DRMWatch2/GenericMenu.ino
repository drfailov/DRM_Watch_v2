/*
 * код формирующий меню общий для всех меню в программе
*/
const int genericMenuViewCount = 5; //сколько на экран помещается
const int genericMenuMaxTextLength = 12; //размер буфера. Чем меньше тем экономнее
const long genericMenuAutoExitTimeout = 60000; //MS Время до автоматического выхода с меню

byte genericMenuSelectPosition = 0; //текущий выделенный элемени
byte genericMenuViewPosition = 0; //первый элемент который сейчас на экране отображается
long genericMenuLastActionTime = 0; //последнее действие кнопками, нужно для автоматического выхода


void genericMenuSetup(){
  digitalWrite(pinLcdBacklight, HIGH);
  genericMenuSelectPosition = 0;
  genericMenuViewPosition = 0;
  genericMenuLastActionTime = millis();
}

void genericMenuLoop(const int genericMenuItemsCount, const char* const genericMenuItems[], void (*onSelected)(byte index)){
  if (isButtonUpPressed()) {
    genericMenuLastActionTime = millis();
    beep();

    onSelected (genericMenuSelectPosition);
  }

  if (isButtonDownPressed()) {
    genericMenuLastActionTime = millis();
    beep();
    genericMenuSelectPosition ++;
    if (genericMenuSelectPosition >= genericMenuItemsCount) genericMenuSelectPosition = 0;
    while (genericMenuSelectPosition >= genericMenuViewPosition + genericMenuViewCount) genericMenuViewPosition ++;
    while (genericMenuSelectPosition < genericMenuViewPosition) genericMenuViewPosition --;
  }
  //auto exit
  if (millis() - genericMenuLastActionTime > genericMenuAutoExitTimeout) {
    goToWatchface();
    return;
  }

  //draw
  displayClear();
  for (int i = 0; i < genericMenuViewCount; i++) {
    int index = genericMenuViewPosition + i;
    if (index < genericMenuItemsCount) {
      if (index == genericMenuSelectPosition) {
        displayFillRect(/*x*/11, /*y*/1 + 13 * i, /*w*/81, /*h*/13, /*c*/1);
        char arrayBuf[genericMenuMaxTextLength];  // создаём буфер
        strcpy_P(arrayBuf, pgm_read_word(&(genericMenuItems[index])));
        displayDrawText(/*X*/15, /*Y*/4 + 13 * i, /*C*/0, arrayBuf);
      }
      else {
        char arrayBuf[genericMenuMaxTextLength];  // создаём буфер
        strcpy_P(arrayBuf, pgm_read_word(&(genericMenuItems[index])));
        displayDrawText(/*X*/15, /*Y*/4 + 13 * i, /*C*/1, arrayBuf);
      }
    }
  }
  { //scrollbar
    float h = 66;
    displayDrawLine(/*X1*/94, /*Y1*/0, /*X2*/94, /*Y2*/h, /*C*/1);
    float barHeight = h / genericMenuItemsCount;
    float barPosition = barHeight * genericMenuSelectPosition;
    displayFillRect(/*x*/93, /*y*/barPosition, /*w*/3, /*h*/barHeight, /*c*/1);
  }
  displayDrawLine(/*X1*/10, /*Y1*/0, /*X2*/10, /*Y2*/68, /*C*/1);
  displayDrawText(/*X*/2, /*Y*/2, /*C*/1, "+");
  displayDrawText(/*X*/2, /*Y*/59, /*C*/1, "v");
  displayUpdate();
}

void genericMenuFinish(){
  digitalWrite(pinLcdBacklight, LOW);
}
