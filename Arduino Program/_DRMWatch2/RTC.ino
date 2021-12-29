/*Global RTC-related functions*/

#include <DS3231M.h>  // Include the DS3231M RTC library

DS3231M_Class DS3231M;  ///< Create an instance of the DS3231M class
bool rtcReady = false;



void rtcInit() {
#ifdef LOG
  Serial.print(F("Init DS3231M..."));
#endif
  Wire.setWireTimeout(3000, true); //timeout value in uSec - SBWire uses 100 uSec, so 1000 should be OK
  while (!DS3231M.begin())  // Initialize RTC communications
  {
#ifdef LOG
    Serial.println(F("DS3231M error..."));
#endif
#ifdef LANG_EN
    displayMessage(F("RTC FAIL."));
#endif
#ifdef LANG_RU
    displayMessage(F("Ошибка RTC."));
#endif
    delay(300);
  }                         // of loop until device is located
  DS3231M.pinSquareWave();  // Make INT/SQW pin toggle at 1Hz
  rtcReady = true;
#ifdef LOG
  Serial.println(F("OK"));
  Serial.print(F("DS3231M temp: "));
  Serial.print(DS3231M.temperature() / 100.0, 1);  // Value is in 100ths of a degree
  Serial.println("\xC2\xB0""C");
#endif
}

void rtcSetTime(int year, byte month, byte day, byte hour, byte minute) {
  DS3231M.adjust(DateTime(year, month, day, hour, minute, 0));  // Adjust the RTC date/time
}

byte rtcGetSeconds() {
  if (!rtcReady)
    return rand() % 60;
  DateTime now = DS3231M.now();
  delayMicroseconds(100);
  return now.second();
}
byte rtcGetMinutes() {
  if (!rtcReady)
    return rand() % 60;
  DateTime now = DS3231M.now();
  delayMicroseconds(100);
  return now.minute();
}
byte rtcGetHours() {
  if (!rtcReady)
    return rand() % 60;
  DateTime now = DS3231M.now();
  delayMicroseconds(100);
  return now.hour();
}
byte rtcGetDay() {
  if (!rtcReady)
    return rand() % 30;
  DateTime now = DS3231M.now();
  delayMicroseconds(100);
  return now.day();
}
byte rtcGetMonth() {
  if (!rtcReady)
    return rand() % 12;
  DateTime now = DS3231M.now();
  delayMicroseconds(100);
  return now.month();
}
int rtcGetYear() {
  if (!rtcReady)
    return rand() % 3000;
  DateTime now = DS3231M.now();
  delayMicroseconds(100);
  return now.year();
}
float rtcGetTemp() {
  if (!rtcReady)
    return (rand() % 3000) / 100.0;
  float temp =  DS3231M.temperature() / 100.0;
  delayMicroseconds(100);
  return temp;
}
