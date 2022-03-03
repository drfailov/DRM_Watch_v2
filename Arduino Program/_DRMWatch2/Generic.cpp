/*Данные, которые требуется по всей программе*/

#ifndef GENERIC_H
#define GENERIC_H
#include <Arduino.h>




//Базовые константы
#define version F("v1.20")   //Версию менять здесь
//#define LANG_EN  //Раскомментировать чтобы использовать английский язык меню
#define LANG_RU   //Раскомментировать чтобы использовать русский язык меню
#define LOG   //Закомментировать чтобы отключило логи
#define  AUTO_EXIT_TIMEOUT 120000 //MS  //Время до автоматического выхода с менюшек

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

//размер текстового буфера. Чем меньше тем экономнее.
#define BUFFER_SIZE 25

  
//Здесь определенл, которое используется во всех меню, для экономии памяти
#ifdef LANG_RU
const char menuItemBack[] PROGMEM = "< Haзaд";
const char textSaved[] PROGMEM = "Coxpaнeнo";
#endif
#ifdef LANG_EN
const char menuItemBack[] PROGMEM = "< Back";
const char textSaved[] PROGMEM = "Saved";
#endif

class Generic_{
  
  public:
  
  const char* getMenuItemBack(){ 
    return menuItemBack;
  }
  static const char* getTextSaved(){ 
    return menuItemBack;
  }

  //последнее действие кнопками, нужно для автоматического выхода
  long genericMenuLastActionTime = 0;   
  //общий на всю программу текстовый буфер чтобы не объявлять каждый раз локальную.
  char buffer[BUFFER_SIZE]; 
  //Общий на всю программу счётчик для выбора элементов из списка
  byte selected = 0;
  //Общий формат вывода данных много где используется
  char* getDateFormat(){return "%02d.%02d.%04d";}
  

};

static Generic_ Generic;

#endif
