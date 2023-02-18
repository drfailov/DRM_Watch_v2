#include "lcd1202.h"

//Распиновка
#define pinButtonDown (byte)2 //active high
#define pinButtonUp (byte)3 //active high
#define pinLcdRst (byte)5
#define pinLcdCs (byte)6
#define pinLcdMosi (byte)7
#define pinLcdSck (byte)8   
#define pinLcdPower (byte)10
#define pinUsbVoltage (byte)11  
#define pinBuzzer (byte)12 //passive
#define pinLed (byte)13  //active high
#define pinLcdBacklight (byte)15  //A1, active high
// A4 - RTC SDA
// A5 - RTC SCL


#define LCD_X        96
#define LCD_Y        68
LCD1202 lcd(pinLcdRst, pinLcdCs, pinLcdMosi, pinLcdSck);


void setup() {
  //LCD PWR ON
  pinMode(pinLcdPower, OUTPUT);
  digitalWrite(pinLcdPower, HIGH);
  pinMode(pinLcdBacklight, OUTPUT);
  digitalWrite(pinLcdBacklight, HIGH);
  delay(100);
  lcd.Inicialize();  
}




float tx = 20;
float ty = 40;
float cx = -20;
float cy = 100;
float vx = 0;
float vy = 0;

unsigned long last = 0;


void loop() {  
  float dx = tx-cx;
  float dy = ty-cy;
  float ax = dx*0.3;
  float ay = dy*0.3;
  vx += ax;
  vy += ay;
  cx += vx;
  cy += vy;
  vx *= 0.2;
  vy *= 0.2;
  
  lcd.Clear_LCD();
  lcd.print(/*X*/cx, /*Y*/cy, /*color*/1, /*text*/ "DRM Watch");
  lcd.Update(/*flip*/false);  //true is flip 180, false is no flip
  if(millis()-last > 2000){
    last = millis();
    tx = rand() % 80;
    ty = rand() % 64;
  }
}
