void watchfaceCalibri(byte hour, byte minute, byte second, byte day, byte month, int year, byte dayOfWeek, byte animate)
{
    displayClear();

    {//date
      sprintf(buffer, getDateFormat(), day, month, year);
      displayDrawText(0, 0, 1, buffer);
    }
    
    {//DayOfWeek
  #ifdef LANG_EN
      drawDayOfWeek(79, 0, dayOfWeek, /*color*/1);
  #endif
  #ifdef LANG_RU
      drawDayOfWeek(85, 0, dayOfWeek, /*color*/1);
  #endif
    }
    
    {//Temperature
      float temp = rtcGetTemp();
      /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
      dtostrf(temp, 4, 1, buffer);
      sprintf(buffer, "%sC", buffer);
      displayDrawText(0, 61, 1, buffer);
    }
  
    byte X = 96;
    
    {//battery
      X -= 17;
      displayDrawBattery(X, 61);
      if(!batteryIsCharging() && !batteryIsLowPower()) X += 5;
    }
    
    //Silent mode sign
    if(eepromReadSilentMode()){ 
      X -= 10;
      displayDrawSilentModeIcon(X, 61, 1);
    }
    
    //Alert sign
    if(eepromReadAlertEnabled()){ 
      X-= 11;
      displayDrawAlertSign(X, 61, 1);
    }
    
    
    { //time
      byte hour1 = hour / 10;
      byte hour2 = hour - (hour1 * 10);
      byte minute1 = minute / 10;
      byte minute2 = minute - (minute1 * 10);

      drawNumber(/*x*/8, /*y*/20, /*num*/hour1, /*animate*/ animate);
      drawNumber(/*x*/27, /*y*/20, /*num*/hour2, /*animate*/ animate);
      displayDrawNumber(/*num*/10, /*x*/46, /*y*/20, /*w*/5, /*h*/5, animate); // :
      drawNumber(/*x*/53, /*y*/20, /*num*/minute1, /*animate*/ animate);
      drawNumber(/*x*/72, /*y*/20, /*num*/minute2, /*animate*/ animate);
    }
    
}




//------------------------------------------------------------// 'calibri0', 17x23px
const unsigned char  calibri0 [] PROGMEM = {
  0x80, 0xf0, 0xfc, 0xfe, 0xfe, 0x3f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0xff, 0xfe, 0xfc, 0xf8, 
  0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x01, 0x0f, 0x1f, 0x3f, 0x7f, 0x7e, 0x78, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x7f, 0x3f, 
  0x1f, 0x0f, 0x01
};
// 'calibri1', 17x23px
const unsigned char  calibri1 [] PROGMEM = {
  0x00, 0x00, 0x78, 0x38, 0x3c, 0x1c, 0x1e, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78, 0x78, 0x78, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x78, 0x78, 
  0x78, 0x78, 0x20
};
// 'calibri2', 17x23px
const unsigned char  calibri2 [] PROGMEM = {
  0x00, 0x3c, 0x1e, 0x1e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfe, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 
  0x00, 0x00, 0x00, 0x7c, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7b, 0x79, 0x78, 0x78, 0x78, 0x78, 0x78, 
  0x78, 0x78, 0x70
};
// 'calibri3', 17x23px
const unsigned char  calibri3 [] PROGMEM = {
  0x00, 0x1c, 0x1e, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0x20, 
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c, 0x1c, 0x1e, 0x1e, 0x3f, 0x7f, 0xff, 0xff, 0xf3, 0xf1, 
  0xe0, 0x80, 0x00, 0x3c, 0x78, 0x78, 0x78, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x7f, 0x3f, 0x3f, 
  0x1f, 0x0f, 0x03
};
// 'calibri4', 17x23px
const unsigned char  calibri4 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfe, 0x3f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 
  0x00, 0xe0, 0xf8, 0xfc, 0xff, 0x9f, 0x87, 0x83, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x80, 0x80, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x7f, 0x7f, 0x7f, 0x7f, 
  0x7f, 0x03, 0x03
};
// 'calibri5', 17x23px
const unsigned char  calibri5 [] PROGMEM = {
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 
  0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x0f, 0x0e, 0x0e, 0x1e, 0x1e, 0x3e, 0xfe, 0xfc, 0xfc, 0xf8, 
  0xf0, 0x80, 0x00, 0x3c, 0x78, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x7f, 0x3f, 0x3f, 
  0x1f, 0x0f, 0x00
};
// 'calibri6', 17x23px
const unsigned char  calibri6 [] PROGMEM = {
  0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfe, 0x1e, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0e, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x1c, 0x1e, 0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0xfe, 0xfe, 0xfc, 
  0xfc, 0xf0, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 0x7f, 0x78, 0x70, 0x70, 0x70, 0x78, 0x78, 0x7f, 0x3f, 
  0x3f, 0x0f, 0x07
};
// 'calibri7', 17x23px
const unsigned char  calibri7 [] PROGMEM = {
  0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xcf, 0xff, 0xff, 0xff, 0xff, 0x3f, 
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x01, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x78, 0x7e, 0x7f, 0x7f, 0x3f, 0x0f, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00
};
// 'calibri8', 17x23px
const unsigned char  calibri8 [] PROGMEM = {
  0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x9f, 0xff, 0xfe, 0xfe, 0xfc, 
  0x00, 0x00, 0xc1, 0xe3, 0xf7, 0xf7, 0x7f, 0x3f, 0x3e, 0x1e, 0x3e, 0x3f, 0x7f, 0xff, 0xf3, 0xf1, 
  0xe0, 0x80, 0x0f, 0x1f, 0x3f, 0x7f, 0x7f, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7f, 0x7f, 
  0x3f, 0x1f, 0x0f
};
// 'calibri9', 17x23px
const unsigned char  calibri9 [] PROGMEM = {
  0xe0, 0xf8, 0xfc, 0xfe, 0xfe, 0x1f, 0x0f, 0x07, 0x07, 0x0f, 0x0f, 0x3f, 0xfe, 0xfe, 0xfc, 0xf8, 
  0x80, 0x03, 0x0f, 0x1f, 0x3f, 0x3f, 0x3c, 0x78, 0x78, 0x78, 0x38, 0x38, 0x3c, 0xff, 0xff, 0xff, 
  0xff, 0x7f, 0x00, 0x38, 0x78, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7c, 0x3f, 0x3f, 0x1f, 
  0x0f, 0x03, 0x00
};




void drawNumber(byte x, byte y, byte num, byte animate){
  if(num == 0)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri0, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 1)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri1, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 2)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri2, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 3)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri3, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 4)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri4, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 5)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri5, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 6)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri6, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 7)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri7, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 8)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri8, /*w*/17, /*h*/23, /*COLOR*/1);
  if(num == 9)
    displayDrawBitmap(/*x*/x, /*y*/y, /*bmp*/calibri9, /*w*/17, /*h*/23, /*COLOR*/1);
  if(animate)
    displayUpdate();
}
