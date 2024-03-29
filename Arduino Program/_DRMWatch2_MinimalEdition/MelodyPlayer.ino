#include "Display.cpp"


//Number of melodies is located in myEEPROM.cpp, variable eepromMelodyCount

const byte badinerie[] PROGMEM = {
  125,
  0b01010111, 0b10011010, 0b10010111, 0b01010010, 0b10010111,
  0b10010010, 0b01001110, 0b10010010, 0b10001110, 0b00001011,
  0b10000110, 0b10001011, 0b10001110, 0b10001011, 0b10001101,
  0b10001011, 0b10001101, 0b10001011, 0b10001010, 0b10001101,
  0b10010000, 0b10001101, 0b01001110, 0b01001011, 0b01010111,
  0b10011010, 0b10010111, 0b01010010, 0b10010111, 0b10010010,
  0b01001110, 0b10010010, 0b10001110, 0b00001011, 0b01001110,
  0b01001110, 0b01001110, 0b01001110, 0b01010111, 0b01001110,
  0b11001110, 0b11001101, 0b11001110, 0b11001101, 0b01001101,
  0b01010010, 0b01010010, 0b01010010, 0b01010010, 0b01011010,
  0b01010010, 0b11010010, 0b11010001, 0b11010010, 0b11010001,
  0b01010001, 0b10001101, 0b10010010, 0b10010101, 0b10010010,
  0b10010100, 0b10010010, 0b10010100, 0b10010010, 0b10010001,
  0b10010100, 0b10010111, 0b10010100, 0b10010101, 0b10010100,
  0b10010101, 0b10010100, 0b10010010, 0b10010101, 0b10010010,
  0b10010001, 0b10010010, 0b10010111, 0b10010010, 0b10010001,
  0b10010010, 0b10011001, 0b10010010, 0b10010001, 0b10010010,
  0b10011010, 0b10010010, 0b10010001, 0b10010010, 0b10011010,
  0b10011001, 0b10010111, 0b10011001, 0b10010101, 0b10010100,
  0b10010010, 0b01010101, 0b01010100, 0b00010010, 0b11111111,
};
const byte* const getMelodyBadinerie() {
  return badinerie;
}

const byte mozart[] PROGMEM = {
  240,
  0b01010101, 0b10010100, 0b10100100, 0b01010100, 0b01100100,
  0b01010101, 0b10010100, 0b10100100, 0b01010100, 0b01100100,
  0b01010101, 0b10010100, 0b10100100, 0b00010100, 0b00011100,
  0b00100100, 0b10100100, 0b01011100, 0b10011011, 0b10100100,
  0b01011001, 0b01100100, 0b01011001, 0b10010111, 0b10100100,
  0b01010101, 0b01100100, 0b01010101, 0b11100100, 0b10010100,
  0b10100100, 0b01010010, 0b01100100, 0b01010010, 0b00100100,
  0b01100100, 0b01010100, 0b11100100, 0b01010010, 0b11100100,
  0b01010010, 0b01100100, 0b01010100, 0b10010010, 0b10100100,
  0b01010010, 0b01100100, 0b01010100, 0b10010010, 0b10100100,
  0b00010010, 0b01011011, 0b00100100, 0b01100100, 0b01011011,
  0b01011001, 0b01011000, 0b01100100, 0b01011000, 0b01010101,
  0b01010100, 0b01100100, 0b11100100, 0b01010100, 0b01010010,
  0b01010000, 0b01100100, 0b01010000, 0b00100100, 0b01100100,
  0b01011100, 0b10011011, 0b10100100, 0b00011011, 0b00011110,
  0b00011000, 0b00011011, 0b00011001, 0b00010100, 0b00100100,
  0b01011100, 0b11100100, 0b10011011, 0b10100100, 0b00011011,
  0b00011110, 0b00011000, 0b00011011, 0b00011001, 0b00011100,
  0b01011011, 0b01011001, 0b01010111, 0b01010101, 0b00010100,
  0b00010011, 0b00010100, 0b00100100, 0b10001000, 0b10100100,
  0b10001000, 0b10100100, 0b00001000, 0b00100100, 0b10001000,
  0b10100100, 0b10001000, 0b10100100, 0b00001000, 0b00100100,
  0b10001000, 0b10100100, 0b10001000, 0b10100100, 0b01001000,
  0b01100100, 0b10001000, 0b10100100, 0b10001000, 0b10100100,
  0b01001000, 0b01100100, 0b10001000, 0b10100100, 0b10001000,
  0b10100100, 0b00001000, 0b11111111,
};
const byte* const getMelodyMozart() {
  return mozart;
}



const byte entertainer[] PROGMEM = {
  140,
  0b01001110, 0b01001111, 0b01010000, 0b00011000, 0b01010000,
  0b00011000, 0b01010000, 0b00011000, 0b01011000, 0b01011010,
  0b01011011, 0b01011100, 0b01011000, 0b01011010, 0b00011100,
  0b01010111, 0b00011010, 0b00011000, 0b00100100, 0b01001110,
  0b01001111, 0b01010000, 0b00011000, 0b01010000, 0b00011000,
  0b01010000, 0b00011000, 0b01100100, 0b01010101, 0b01010011,
  0b01010010, 0b01010101, 0b01011000, 0b00011100, 0b01011010,
  0b01011000, 0b01010101, 0b00011010, 0b11111111,
};
const byte* const getMelodyEntertainer() {
  return entertainer;
}



bool melodyPlayerLoopMelody = false;

//return true if was played completely or false if interrupted
bool melodyPlayerPlayMelody(const byte* const melody) {
  melodyPlayerLoopMelody = false;
  do{
    melodyPlayerDrawScreen();
    pinMode(pinBuzzer, OUTPUT);
    byte length = melodyPlayerGetLength(melody);
    float tempo = pgm_read_byte(&melody[0]);
    float whole_notes_per_second = tempo / 240.0;
    for (byte i = 1; i < length - 1; i++) {
      byte b = pgm_read_byte(&melody[i]);
      byte duration = 0;
      if (bitRead(b, 7) == 0 && bitRead(b, 6) == 0) duration = 4;
      if (bitRead(b, 7) == 0 && bitRead(b, 6) == 1) duration = 8;
      if (bitRead(b, 7) == 1 && bitRead(b, 6) == 0) duration = 16;
      if (bitRead(b, 7) == 1 && bitRead(b, 6) == 1) duration = 32;
      float timeMs = 1000.0 / (whole_notes_per_second * duration);
      byte noteNumberByte = 0;
      for (byte i = 0; i < 6; i++)
        bitWrite(noteNumberByte, i, bitRead(b, i));
      float noteNumber = noteNumberByte;
      // Note frequency is calculated as (F*2^(n/12)),
      // We can use C2=65.41, or C3=130.81. C2 is a bit shorter.
      float frequency = 0;
      //290 is ok
      if (noteNumber < 36)
        frequency = 250.0 * pow(2.0, (noteNumber / 12.0));
  
      if (frequency != 0){
        Display.displayBacklightOn();
        tone(pinBuzzer, frequency);
      }
      else{
        noTone(pinBuzzer);
      }
      long noteStarted = millis();
      while(millis() - noteStarted < timeMs);
      noTone(pinBuzzer);
      Display.displayBacklightOff();
      delay(13);
      
      if (isButtonUpPressed()){
        if(isButtonUpHold()){
          melodyPlayerLoopMelody = !melodyPlayerLoopMelody;
          melodyPlayerDrawScreen();
        }
        else{
          Display.displayBacklightOn();
          return false;
        }
      }
    }
    
    noTone(pinBuzzer);
    pinMode(pinBuzzer, INPUT);
    delay(1000);
  }while(melodyPlayerLoopMelody);
  Display.displayBacklightOn();
  return true;
}

void melodyPlayerDrawScreen() {
  Display.displayClear();
  Display.displayDrawVector(/*path*/Display.getPathZubat(), /*x*/24, /*y*/20, /*animate*/false, /*color*/1);

  if(!melodyPlayerLoopMelody){
    byte hour = RTC.rtcGetHours();
    byte minute = RTC.rtcGetMinutes();
    sprintf(Generic.buffer, Generic.getTimeFormat(), hour, minute);
    Display.displayDrawText(0, 0, 1, Generic.buffer);
  }
  else{
    Display.displayDrawIconFlip(0, 0, 1);
  }
  
  Display.displayDrawBattery(79, 0);
  Display.displayUpdate();
}


int melodyPlayerGetLength(const byte* const melody) {
  for (byte i = 0; i < 254; i++) {
    byte b = pgm_read_byte(&melody[i]);
    if (b == 0b11111111) {
      return i + 1;
    }
  }
}
