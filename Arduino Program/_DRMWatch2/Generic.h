#ifndef GENERIC_H
#define GENERIC_H

//Распиновка
#define pinButtonDown (byte)2 //active high
#define pinButtonUp (byte)3 //active high
#define pinLcdRst (byte)5
#define pinLcdCs (byte)6
#define pinLcdMosi (byte)7
#define pinUsbVoltage (byte)9    //for old boards rev.1
//#define pinUsbVoltage (byte)11  //for new boards  rev.2
#define pinLcdPower (byte)10
#define pinLcdSck (byte)11   //for old boards  rev.1
//#define pinLcdSck (byte)8    //for new boards  rev.2
#define pinBuzzer (byte)12 //passive
#define pinLed (byte)13  //active high
#define pinLcdBacklight (byte)15  //A1, active high
// A4 - RTC SDA
// A5 - RTC SCL

//размер текстового буфера. Чем меньше тем экономнее.
#define BUFFER_SIZE 25

class Generic_{
  
  public:
  //общий на всю программу текстовый буфер чтобы не объявлять каждый раз локальную.
  static char buffer[BUFFER_SIZE]; 
  static char* getBuffer(){return buffer;}

};

Generic_ Generic;

#endif
