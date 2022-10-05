#include "lcd1202.h"
#include <DS3231M.h>
#include <EEPROM.h>

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
DS3231M_Class DS3231M;




void setup() {
  Serial.begin(115200);
  Serial.println(F("======================="));
  Serial.println(F("DRM Watch V2 FactoryTest"));
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
  lcd.print(/*X*/10, /*Y*/15, /*color*/1, /*text*/ "DRM Watch");
  lcd.print(/*X*/5, /*Y*/30, /*color*/1, /*text*/ "FACTORY TEST");
  lcd.Update(/*flip*/false);  //true is flip 180, false is no flip
  Serial.println(F("OK"));

  Serial.print(F("LCD Backlight ON..."));
  pinMode(pinLcdBacklight, OUTPUT);
  digitalWrite(pinLcdBacklight, HIGH);
  Serial.println(F("OK"));

  //==================================-------------------------------------

  Serial.print(F("Test BUZZER..."));
  pinMode(pinBuzzer, OUTPUT);
  for(byte i=2; i<3; i++){
    tone(pinBuzzer, i*1000); 
    delay(100);
    noTone(pinBuzzer);      // не пищать
    delay(100);
  }
  for(byte i=0; i<7; i++){
    digitalWrite(pinLcdBacklight, LOW);
    tone(pinBuzzer, 5000);  
    delay(30);
    digitalWrite(pinLcdBacklight, HIGH);
    noTone(pinBuzzer);      // не пищать
    delay(30);
  }
  pinMode(pinBuzzer, INPUT);
  Serial.println(F("OK"));
  
  //==================================-------------------------------------

  delay(1000);  
}

void loop() {
  lcd.Clear_LCD();
  
  //==================================-------------------------------------
  
  Serial.print(F("Test BATTERY..."));
  lcd.print(/*X*/0, /*Y*/0, /*color*/1, /*text*/ "Battery:");
  lcd.print(/*X*/60, /*Y*/0, /*color*/1, /*text*/ batteryRawVoltage());
  Serial.println(F("OK"));
  
  //==================================-------------------------------------

  Serial.print(F("Test CHARGER..."));  
  if(digitalRead(pinUsbVoltage) == HIGH)
    lcd.print(/*X*/0, /*Y*/8, /*color*/1, /*text*/ "Charger: YES");
  if(digitalRead(pinUsbVoltage) == LOW)
    lcd.print(/*X*/0, /*Y*/8, /*color*/1, /*text*/ "Charger: NO");    
  Serial.println(F("OK"));

  //==================================-------------------------------------

  Serial.print(F("Test DS3231M..."));
  Wire.setWireTimeout(3000, true); //timeout value in uSec - SBWire uses 100 uSec, so 1000 should be OK
  lcd.print(/*X*/0, /*Y*/16, /*color*/1, /*text*/ "RTC:");
  if(!DS3231M.begin())
    lcd.print(/*X*/40, /*Y*/16, /*color*/1, /*text*/ "FAIL");
  else{
    DateTime now = DS3231M.now();
    lcd.print(/*X*/40, /*Y*/16, /*color*/1, /*text*/ now.hour());
    lcd.print(/*X*/60, /*Y*/16, /*color*/1, /*text*/ now.minute());
    lcd.print(/*X*/80, /*Y*/16, /*color*/1, /*text*/ now.second());
  }
  Serial.println(F("OK"));
  
  //==================================-------------------------------------

  Serial.print(F("Test BUTTONS..."));
  lcd.print(/*X*/0, /*Y*/24, /*color*/1, /*text*/ "Buttons:");
  if(digitalRead(pinButtonUp) == HIGH)
    lcd.print(/*X*/55, /*Y*/24, /*color*/1, /*text*/ "YES");
  if(digitalRead(pinButtonUp) == LOW)
    lcd.print(/*X*/55, /*Y*/24, /*color*/1, /*text*/ "NO");
    
  if(digitalRead(pinButtonDown) == HIGH)
    lcd.print(/*X*/79, /*Y*/24, /*color*/1, /*text*/ "YES");
  if(digitalRead(pinButtonDown) == LOW)
    lcd.print(/*X*/79, /*Y*/24, /*color*/1, /*text*/ "NO");
    
  Serial.println(F("OK"));
  
  //==================================-------------------------------------

  Serial.print(F("Test BUZZER..."));
  pinMode(pinBuzzer, OUTPUT);
  if(digitalRead(pinButtonUp) == HIGH)
    tone(pinBuzzer, 5000); 
  if(digitalRead(pinButtonUp) == LOW)
    noTone(pinBuzzer); 
  Serial.println(F("OK"));
  
  //==================================-------------------------------------

  Serial.print(F("Test BACKLIGHT..."));
  digitalWrite(pinLcdBacklight, !digitalRead(pinButtonDown));
  Serial.println(F("OK"));
  
  //==================================-------------------------------------

  Serial.print(F("Test EEPROM..."));
  lcd.print(/*X*/0, /*Y*/43, /*color*/1, /*text*/ "EEPROM");
  int startByte = 10 * ((millis()/2000)%100);
  lcd.print(/*X*/40, /*Y*/43, /*color*/1, /*text*/ startByte);
  lcd.print(/*X*/61, /*Y*/43, /*color*/1, /*text*/ "-");
  lcd.print(/*X*/70, /*Y*/43, /*color*/1, /*text*/ startByte+10);
  for(int i=0; i<10; i++){
    byte result;
    EEPROM.get(startByte + i, result);
    lcd.print(/*X*/19*(i%5), /*Y*/52+9*(i/5), /*color*/1, /*text*/ (int)result);
  }
  Serial.println(F("OK"));
  
  //==================================-------------------------------------

  Serial.println(F("========="));
  lcd.Update(/*flip*/false);  //true is flip 180, false is no flip
}



long batteryRawVoltage() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1125300L / result; // Back-calculate AVcc in mV
  return result;
}
