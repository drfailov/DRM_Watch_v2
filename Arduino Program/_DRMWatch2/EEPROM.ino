#include <EEPROM.h>


#define eepromAddressSleepTime (byte)10 
byte eepromReadSleepTime(){
  byte result = 1;
  EEPROM.get(eepromAddressSleepTime, result);
  return result;
}
void eepromSaveSleepTime(byte data){
  EEPROM.put(eepromAddressSleepTime, data);
}


#define eepromAddressSilentMode (byte)11
bool eepromReadSilentMode(){
  byte result = 1;
  EEPROM.get(eepromAddressSilentMode, result);
  return result == 1;
}
void eepromSaveSilentMode(bool data){
  EEPROM.put(eepromAddressSilentMode, (byte)data);
}


#define eepromAddressBeepSound (byte)12 
byte eepromReadBeepSound(){
  byte result = 1;
  EEPROM.get(eepromAddressBeepSound, result);
  return result;
}
void eepromSaveBeepSound(byte data){
  EEPROM.put(eepromAddressBeepSound, data);
}


#define eepromAddressAlertEnabled (byte)13
bool eepromReadAlertEnabled(){
  byte result = 0;
  EEPROM.get(eepromAddressAlertEnabled, result);
  return result == 1;
}
void eepromSaveAlertEnabled(bool data){
  EEPROM.put(eepromAddressAlertEnabled, (byte)data);
}


#define eepromAddressAlertHour (byte)14
byte eepromReadAlertHour(){
  byte result = 0;
  EEPROM.get(eepromAddressAlertHour, result);
  if(result > 23) result = 0;
  return result;
}
void eepromSaveAlertHour(byte data){
  EEPROM.put(eepromAddressAlertHour, data);
}


#define eepromAddressAlertMinute (byte)15
byte eepromReadAlertMinute(){
  byte result = 0;
  EEPROM.get(eepromAddressAlertMinute, result);
  if(result > 59) result = 0;
  return result;
}
void eepromSaveAlertMinute(byte data){
  EEPROM.put(eepromAddressAlertMinute, data);
}


#define eepromAddressAlertLastDayRun (byte)16
byte eepromReadAlertLastDayRun(){
  byte result = 0;
  EEPROM.get(eepromAddressAlertLastDayRun, result);
  return result;
}
void eepromSaveAlertLastDayRun(byte data){
  EEPROM.put(eepromAddressAlertLastDayRun, data);
}


#define eepromAddressAlertMelodyIndex (byte)17
byte eepromReadAlertMelodyIndex(){
  byte result = 0;
  if(result > getMelodiesCount()) result = 0;
  EEPROM.get(eepromAddressAlertMelodyIndex, result);
  return result;
}
void eepromSaveAlertMelodyIndex(byte data){
  EEPROM.put(eepromAddressAlertMelodyIndex, data);
}
