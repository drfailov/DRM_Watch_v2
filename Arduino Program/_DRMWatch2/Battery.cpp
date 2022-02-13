/*Global functions related to power control and monitoring.
*/
#ifndef BATTERYCPP
#define BATTERYCPP

#include <Arduino.h>
#include "Generic.cpp"

class Battery_{
  public:  
  
  bool batteryIsLowPower() {
    return batteryRawVoltage() < 3650;
  }
  
  bool batteryIsCharging() {
    pinMode(pinUsbVoltage, INPUT);
    int sum = 0;
    for (int i = 0; i < 10; i++)
      if (digitalRead(pinUsbVoltage) == HIGH)
        sum += 1;
  
    return sum > 5;
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

};
static Battery_ Battery;
#endif
