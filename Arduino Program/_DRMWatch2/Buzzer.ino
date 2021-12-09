void beepConfirm() {
  Serial.print(F("Beep confirm..."));
  pinMode(pinBuzzer, OUTPUT);

  tone(pinBuzzer, 2000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 3000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 4000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  tone(pinBuzzer, 5000);  // пищать на пине 12, 1 кГц
  delay(30);
  noTone(pinBuzzer);      // не пищать
  delay(30);
  Serial.println(F("OK"));
}



void beepAlert() {
  Serial.print(F("Beep alert..."));
  pinMode(pinBuzzer, OUTPUT);

  tone(pinBuzzer, 1000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 2000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 3000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 4000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 3000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 2000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать
  delay(100);
  tone(pinBuzzer, 1000);  // пищать на пине 12, 1 кГц
  delay(100);
  noTone(pinBuzzer);      // не пищать

  Serial.println(F("OK"));
}

void beep() {
  //Serial.print(F("Beep..."));
  pinMode(pinBuzzer, OUTPUT);

  tone(pinBuzzer, 1500);  // пищать на пине 12, 1 кГц
  delay(80);
  noTone(pinBuzzer);
  
  //Serial.println(F("OK"));
}
