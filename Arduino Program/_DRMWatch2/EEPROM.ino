#include <EEPROM.h>
#define eepromAddressSleepTime 10 
#define eepromAddressSilentMode 11
#define eepromAddressButtonSound 12 

byte eepromReadSleepTime(){
  byte result = 1;
  EEPROM.get(eepromAddressSleepTime, result);
  return result;
}
void eepromSaveSleepTime(byte data){
  EEPROM.put(eepromAddressSleepTime, data);
}
