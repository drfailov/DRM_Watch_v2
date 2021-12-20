/*Global functions related to control buttons.
*/

bool buttonLastValueUp = false;
long lastTimePushDownTimeForButtonUp = 0;
bool buttonLastValueDown = false;
long lastTimePushDownTimeForButtonDown = 0;


bool isButtonUpPressed(){
  pinMode(pinButtonUp, INPUT);
  delay(1);
  int sum = 0;
  for(int i=0; i<10; i++)
    if(digitalRead(pinButtonUp) == HIGH)
      sum += 1;
  bool value = sum > 5;
  bool lastValue = buttonLastValueUp;
  buttonLastValueUp = value;
  bool isButtonPressDown = value && !lastValue;

  if(isButtonPressDown)
    lastTimePushDownTimeForButtonUp = millis();
  if(isButtonPressDown)
    return true;
  if(value && lastValue && millis()-lastTimePushDownTimeForButtonUp > 500)
    return true;
  return false;
}

bool isButtonDownPressed(){
  pinMode(pinButtonDown, INPUT);
  delay(1);
  int sum = 0;
  for(int i=0; i<10; i++)
    if(digitalRead(pinButtonDown) == HIGH)
      sum += 1;
  bool value = sum > 5;
  bool lastValue = buttonLastValueDown;
  buttonLastValueDown = value;
  bool isButtonPressDown = value && !lastValue;
  if(isButtonPressDown)
    lastTimePushDownTimeForButtonDown = millis();
  if(isButtonPressDown)
    return true;
  if(value && lastValue && millis()-lastTimePushDownTimeForButtonDown > 500)
    return true;
  return false;
}
