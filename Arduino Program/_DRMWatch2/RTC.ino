#include <DS3231M.h>  // Include the DS3231M RTC library

const uint32_t SERIAL_SPEED{115200};     ///< Set the baud rate for Serial I/O
const uint8_t  SPRINTF_BUFFER_SIZE{2};  ///< Buffer size for sprintf()
const uint8_t  LED_PIN{13};              ///< Built-in Arduino green LED pin

DS3231M_Class DS3231M;  ///< Create an instance of the DS3231M class
bool rtcReady = false;

void rtcInit() {
  pinMode(LED_PIN, OUTPUT);  // Make the LED light an output pin
  Serial.print(F("Init DS3231M RTC..."));
  Wire.setWireTimeout(3000, true); //timeout value in uSec - SBWire uses 100 uSec, so 1000 should be OK
  while (!DS3231M.begin())  // Initialize RTC communications
  {
    Serial.println(F("Unable to find DS3231MM. Checking again in 3s."));
    delay(3000);
  }                         // of loop until device is located
  DS3231M.pinSquareWave();  // Make INT/SQW pin toggle at 1Hz
  rtcReady = true;
  Serial.print(F("OK"));
  //DS3231M.adjust();  // Set to library compile Date/Time
  Serial.print(F("DS3231M chip temperature is "));
  Serial.print(DS3231M.temperature() / 100.0, 1);  // Value is in 100ths of a degree
  Serial.println(
      "\xC2\xB0"
      "C");
  Serial.println(F("\nEnter the following serial command:"));
  Serial.println(F("SETDATE yyyy-mm-dd hh:mm:ss"));
}  // of method setup()

void readCommand() {
  /*!
   @brief    Read incoming data from the Serial port
   @details  This function checks the serial port to see if there has been any input. If there is
             data it is read until a terminator is discovered and then the command is parsed and
             acted upon
   @return   void
  */
  static char    text_buffer[SPRINTF_BUFFER_SIZE];  ///< Buffer for sprintf()/sscanf()
  static uint8_t text_index = 0;                    ///< Variable for buffer position
  while (Serial.available())                        // Loop while there is incoming serial data
  {
    text_buffer[text_index] = Serial.read();  // Get the next byte of data
    // keep on reading until a newline shows up or the buffer is full
    if (text_buffer[text_index] != '\n' && text_index < SPRINTF_BUFFER_SIZE) {
      text_index++;
    } else {
      text_buffer[text_index] = 0;              // Add the termination character
      for (uint8_t i = 0; i < text_index; i++)  // Convert the whole input buffer to uppercase
      {
        text_buffer[i] = toupper(text_buffer[i]);
      }  // for-next all characters in buffer
      Serial.print(F("\nCommand \""));
      Serial.write(text_buffer);
      Serial.print(F("\" received.\n"));
      /*********************************************************************************************
      ** Parse the single-line command and perform the appropriate action. The current list of    **
      ** commands understood are as follows:                                                      **
      **                                                                                          **
      ** SETDATE      - Set the device time                                                       **
      **                                                                                          **
      *********************************************************************************************/
      enum commands { SetDate, Unknown_Command };  // enumerate all commands
      commands command;                            // declare enumerated type
      char     workBuffer[SPRINTF_BUFFER_SIZE];    // Buffer to hold string compare
      sscanf(text_buffer, "%s %*s", workBuffer);   // Parse the string for first word
      if (!strcmp(workBuffer, "SETDATE")) {
        command = SetDate;  // Set command number when found
      } else {
        command = Unknown_Command;  // Otherwise set to not found
      }                             // if-then-else a known command
      unsigned int tokens, year, month, day, hour, minute,
          second;  // Variables to hold parsed date/time
      switch (command) {
        /*********************************
        ** Set the device time and date **
        *********************************/
        case SetDate:
          // Use sscanf() to parse the date/time into component variables
          tokens = sscanf(text_buffer, "%*s %u-%u-%u %u:%u:%u;", &year, &month, &day, &hour,
                          &minute, &second);
          if (tokens != 6)  // Check to see if it was parsed correctly
          {
            Serial.print(F("Unable to parse date/time\n"));
          } else {
            DS3231M.adjust(DateTime(year, month, day, hour, minute, second));  // Adjust the RTC date/time
            Serial.print(F("Date has been set."));
          }  
          break;
        /********************
        ** Unknown command **
        ********************/
        case Unknown_Command:  // Show options on bad command
        default:
          Serial.println(F("Unknown command. Valid commands are:"));
          Serial.println(F("SETDATE yyyy-mm-dd hh:mm:ss"));
      }                // of switch statement to execute commands
      text_index = 0;  // reset the counter
    }                  // of if-then-else we've received full command
  }                    // of if-then there is something in our input buffer
}  // of method readCommand

void rtcSetTime(int year, byte month, byte day, byte hour, byte minute){
  DS3231M.adjust(DateTime(year, month, day, hour, minute, 0));  // Adjust the RTC date/time
}

void rtcloop() {
  static uint8_t secs;
  DateTime       now = DS3231M.now();  // get the current time from device
  if (secs != now.second())            // Output if seconds have changed
  {
    // Use sprintf() to pretty print the date/time with leading zeros
    char output_buffer[SPRINTF_BUFFER_SIZE];  ///< Temporary buffer for sprintf()
    sprintf(output_buffer, "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    Serial.println(output_buffer);
    secs = now.second();  // Set the counter variable
  }                       // of if the seconds have changed
  readCommand();          // See if serial port has incoming data
}  

byte rtcGetSeconds(){
  if(!rtcReady)
    return rand()%60;
  DateTime now = DS3231M.now(); 
  return now.second();
}
byte rtcGetMinutes(){
  if(!rtcReady)
    return rand()%60;
  DateTime now = DS3231M.now(); 
  return now.minute();
}
byte rtcGetHours(){
  if(!rtcReady)
    return rand()%60;
  DateTime now = DS3231M.now(); 
  return now.hour();
}
byte rtcGetDay(){
  if(!rtcReady)
    return rand()%30;
  DateTime now = DS3231M.now(); 
  return now.day();
}
byte rtcGetMonth(){
  if(!rtcReady)
    return rand()%12;
  DateTime now = DS3231M.now(); 
  return now.month();
}
int rtcGetYear(){
  if(!rtcReady)
    return rand()%3000;
  DateTime now = DS3231M.now(); 
  return now.year();
}
float rtcGetTemp(){
  if(!rtcReady)
    return (rand()%3000) / 100.0;
  return DS3231M.temperature() / 100.0;
}
