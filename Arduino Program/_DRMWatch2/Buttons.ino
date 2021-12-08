bool buttonLastValueUp = false;
bool buttonLastValueDown = false;


bool isButtonUpPressed(){
  pinMode(pinButtonUp, INPUT);
  delay(1);
  int sum = 0;
  for(int i=0; i<10; i++)
    if(digitalRead(pinButtonUp) == HIGH)
      sum += 1;
  bool value = sum > 5;
  bool result = value && !buttonLastValueUp;
  buttonLastValueUp = value;
  return result;
}

bool isButtonDownPressed(){
  pinMode(pinButtonDown, INPUT);
  delay(1);
  int sum = 0;
  for(int i=0; i<10; i++)
    if(digitalRead(pinButtonDown) == HIGH)
      sum += 1;
  bool value = sum > 5;
  bool result = value && !buttonLastValueDown;
  buttonLastValueDown = value;
  return result;
}
