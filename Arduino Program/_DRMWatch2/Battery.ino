/*Global functions related to power control and monitoring.
*/
bool batteryIsLowPower() {
  return batteryRawVoltage() < 3600;
}

byte batteryBars(){
  int voltage = batteryRawVoltage();
  byte level = 0;
  if (voltage >= 3350) level = 1;
  if (voltage >= 3650) level = 2;
  if (voltage >= 3850) level = 3;
  if (voltage >= 3950) level = 4;
  return level;
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
