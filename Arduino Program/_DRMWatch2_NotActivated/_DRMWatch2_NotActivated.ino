#include "lcd1202.h"

/*Firmware to test hardware fuctionality.
Minimal function calls, you can use this code also as basis to your owm firmware.*/

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
  Serial.begin(115200);
  Serial.println(F("======================="));
  Serial.println(F("DRM Watch V2 Activate"));
  Serial.print(F(__DATE__));
  Serial.print(F(" "));
  Serial.println(F(__TIME__));

  //==================================-------------------------------------

  Serial.print(F("LCD PWR ON..."));
  pinMode(pinLcdPower, OUTPUT);
  digitalWrite(pinLcdPower, HIGH);
  delay(100);
  Serial.println(F("OK"));

  Serial.print(F("LCD Init..."));
  //lcd = LCD1202(pinLcdRst, pinLcdCs, pinLcdMosi, pinLcdSck);  // RST, CS, MOSI, SCK
  lcd.Inicialize();  
  lcd.Clear_LCD();
  lcd.print(/*X*/15, /*Y*/0, /*color*/1, /*text*/ "DRM Watch");
  lcd.print(/*X*/5, /*Y*/10, /*color*/1, /*text*/ "NOT ACTIVATED.");
  
  lcd.print(/*X*/5, /*Y*/30, /*color*/1, /*text*/ "Connect to");
  lcd.print(/*X*/5, /*Y*/40, /*color*/1, /*text*/ "Arduino IDE");
  lcd.print(/*X*/5, /*Y*/50, /*color*/1, /*text*/ "to activate.");
  lcd.Update(/*flip*/false);  //true is flip 180, false is no flip
  Serial.println(F("OK"));

}

void loop() {
  
}
