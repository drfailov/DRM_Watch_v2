#include <EEPROM.h>
#define eepromAddressSleepTime (byte)10 
#define eepromAddressSilentMode (byte)11
#define eepromAddressBeepSound (byte)12 


byte eepromReadSleepTime(){
  byte result = 1;
  EEPROM.get(eepromAddressSleepTime, result);
  return result;
}
void eepromSaveSleepTime(byte data){
  EEPROM.put(eepromAddressSleepTime, data);
}



byte eepromReadBeepSound(){
  byte result = 1;
  EEPROM.get(eepromAddressBeepSound, result);
  return result;
}
void eepromSaveBeepSound(byte data){
  EEPROM.put(eepromAddressBeepSound, data);
}



bool eepromReadSilentMode(){
  byte result = 1;
  EEPROM.get(eepromAddressSilentMode, result);
  return result == 1;
}
void eepromSaveSilentMode(bool data){
  EEPROM.put(eepromAddressSilentMode, (byte)data);
}
