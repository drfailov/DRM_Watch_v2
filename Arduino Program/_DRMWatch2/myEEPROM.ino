/* EN:
 * This fila contains function to save and read EEPROM parameters
 * Default values for new arduino board is 255, 255, 255 ....
 * RU:
 * Этот файл содержит функции для записи и чтения EEPROM параметров
 * Стандартные состояния переменных на новой ардуинке такие: 255, 255, 255 ....
*/

#include <EEPROM.h>

  
#define eepromAddressSilentMode (byte)11
bool eepromReadSilentMode(){
  byte result;
  EEPROM.get(eepromAddressSilentMode, result);
  return result == 1;
}
void eepromSaveSilentMode(bool data){
  EEPROM.put(eepromAddressSilentMode, (byte)data);
}




//beep sounds
byte eepromReadBeepSound(){
  byte result;
  EEPROM.get(eepromAddressBeepSound, result);
  return result;
}
void eepromSaveBeepSound(byte data){
  EEPROM.put(eepromAddressBeepSound, data);
}


#define eepromAddressAlertEnabled (byte)13
bool eepromReadAlertEnabled(){
  byte result;
  EEPROM.get(eepromAddressAlertEnabled, result);
  return result == 1;
}
void eepromSaveAlertEnabled(bool data){
  EEPROM.put(eepromAddressAlertEnabled, (byte)data);
}


#define eepromAddressAlertHour (byte)14
byte eepromReadAlertHour(){
  byte result;
  EEPROM.get(eepromAddressAlertHour, result);
  if(result > 23) result = 0;
  return result;
}
void eepromSaveAlertHour(byte data){
  EEPROM.put(eepromAddressAlertHour, data);
}


#define eepromAddressAlertMinute (byte)15
byte eepromReadAlertMinute(){
  byte result;
  EEPROM.get(eepromAddressAlertMinute, result);
  if(result > 59) result = 0;
  return result;
}
void eepromSaveAlertMinute(byte data){
  EEPROM.put(eepromAddressAlertMinute, data);
}


#define eepromAddressAlertLastDayRun (byte)16
byte eepromReadAlertLastDayRun(){
  byte result;
  EEPROM.get(eepromAddressAlertLastDayRun, result);
  return result;
}
void eepromSaveAlertLastDayRun(byte data){
  EEPROM.put(eepromAddressAlertLastDayRun, data);
}


#define eepromAddressAlertMelodyIndex (byte)17
byte eepromReadAlertMelodyIndex(){
  byte result;
  EEPROM.get(eepromAddressAlertMelodyIndex, result);
  if(result >= getMelodyCount()) result = 0;
  return result;
}
void eepromSaveAlertMelodyIndex(byte data){
  EEPROM.put(eepromAddressAlertMelodyIndex, data);
}



#define eepromAddressWatchface (byte)18
byte eepromReadWatchface(){
  byte result;
  EEPROM.get(eepromAddressWatchface, result);
  return result;
}
void eepromSaveWatchface(byte data){
  EEPROM.put(eepromAddressWatchface, data);
}



#define eepromAddressFlipScreen (byte)19
bool eepromReadFlipScreen(){
  byte result;
  EEPROM.get(eepromAddressFlipScreen, result);
  return result == 1;
}
void eepromSaveFlipScreen(bool data){
  EEPROM.put(eepromAddressFlipScreen, data);
}




void eepromReadToBuffer(){
  for(int i=0; i<BUFFER_SIZE; i++){
    EEPROM.get(i, buffer[i]);
  }
}

//  void eepromFIllByZeros(){
//    for(int i=0; i<1000; i++){
//      EEPROM.put(i, 0b00000000);
//    }
//  }
//  void eepromFIllByOnes(){
//    for(int i=0; i<1000; i++){
//      EEPROM.put(i, 0b11111111);
//    }
//  }
