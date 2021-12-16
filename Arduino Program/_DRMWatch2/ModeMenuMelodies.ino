/*Show menu with melodies by triggerimg GenericMenu*/
const byte modeMenuMelodiesItemsCount = 5; //сколько пунктов меню в массиве

//Максимальная длина строки:                  |          |
const char modeMenuMelodiesItem1[] PROGMEM = "Nokia Tune";
const char modeMenuMelodiesItem2[] PROGMEM = "Badinerie";
const char modeMenuMelodiesItem3[] PROGMEM = "Mozart";
const char modeMenuMelodiesItem4[] PROGMEM = "Mario";
const char modeMenuMelodiesItem5[] PROGMEM = "< Back";

const char* const modeMenuMelodiesItems[] PROGMEM = {
  modeMenuMelodiesItem1,
  modeMenuMelodiesItem2,
  modeMenuMelodiesItem3,
  modeMenuMelodiesItem4,
  modeMenuMelodiesItem5
};


void modeMenuMelodiesSetup() {
  genericMenuSetup();
}

void modeMenuMelodiesLoop() {
  genericMenuLoop(modeMenuMelodiesItemsCount, modeMenuMelodiesItems, modeMenuMelodiesSelected);
}

void modeMenuMelodiesFinish() {
  genericMenuFinish();
}

void modeMenuMelodiesSelected(byte index) {
  delay(200);
  if (index == 0) { //Nokia Tune
    //tempo: 112

    //Note: 16g3, tonS: g, durS: 16, octS: 3, nAoS: g3
    //NoteNumber: 31, timeMs: 133,92857, frq: 783,974194904955
    tone(pinBuzzer, 783);
    delay(133);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f3, tonS: f, durS: 16, octS: 3, nAoS: f3
    //NoteNumber: 29, timeMs: 133,92857, frq: 698,4416052959286
    tone(pinBuzzer, 698);
    delay(133);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8a2, tonS: a, durS: 8, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 267,85715, frq: 439,9906403173536
    tone(pinBuzzer, 439);
    delay(267);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b2, tonS: b, durS: 8, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 267,85715, frq: 493,8727953675693
    tone(pinBuzzer, 493);
    delay(267);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16e3, tonS: e, durS: 16, octS: 3, nAoS: e3
    //NoteNumber: 28, timeMs: 133,92857, frq: 659,2410901469934
    tone(pinBuzzer, 659);
    delay(133);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d3, tonS: d, durS: 16, octS: 3, nAoS: d3
    //NoteNumber: 26, timeMs: 133,92857, frq: 587,3170421573963
    tone(pinBuzzer, 587);
    delay(133);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8f2, tonS: f, durS: 8, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 267,85715, frq: 349,2208026479644
    tone(pinBuzzer, 349);
    delay(267);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8g2, tonS: g, durS: 8, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 267,85715, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(267);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d3, tonS: d, durS: 16, octS: 3, nAoS: d3
    //NoteNumber: 26, timeMs: 133,92857, frq: 587,3170421573963
    tone(pinBuzzer, 587);
    delay(133);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16c3, tonS: c, durS: 16, octS: 3, nAoS: c3
    //NoteNumber: 24, timeMs: 133,92857, frq: 523,24
    tone(pinBuzzer, 523);
    delay(133);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8e2, tonS: e, durS: 8, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 267,85715, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(267);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8g2, tonS: g, durS: 8, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 267,85715, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(267);
    noTone(pinBuzzer);
    delay(10);

    //Note: 4.c3, tonS: c, durS: 4, octS: 3, nAoS: c3
    //NoteNumber: 24, timeMs: 1071,4286, frq: 523,24
    tone(pinBuzzer, 523);
    delay(1071);
    noTone(pinBuzzer);
    delay(10);


  }


  if (index == 1) { //Badinerie
    //tempo: 125

    //Note: 8b2, tonS: b, durS: 8, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 240,00002, frq: 5096,921288481145
    //noteData: [01010111]
    tone(pinBuzzer, 5096);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d3, tonS: d, durS: 16, octS: 3, nAoS: d3
    //NoteNumber: 26, timeMs: 120,00001, frq: 6061,295060870613
    //noteData: [10011010]
    tone(pinBuzzer, 6061);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b2, tonS: b, durS: 16, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 120,00001, frq: 5096,921288481145
    //noteData: [10010111]
    tone(pinBuzzer, 5096);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#f2, tonS: #f, durS: 8, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 240,00002, frq: 3818,376618407357
    //noteData: [01010010]
    tone(pinBuzzer, 3818);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b2, tonS: b, durS: 16, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 120,00001, frq: 5096,921288481145
    //noteData: [10010111]
    tone(pinBuzzer, 5096);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d2, tonS: d, durS: 16, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 120,00001, frq: 3030,647530435307
    //noteData: [10001110]
    tone(pinBuzzer, 3030);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 4b1, tonS: b, durS: 4, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 480,00003, frq: 2548,4606442405725
    //noteData: [00001011]
    tone(pinBuzzer, 2548);
    delay(480);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f1, tonS: #f, durS: 16, octS: 1, nAoS: #f1
    //NoteNumber: 6, timeMs: 120,00001, frq: 1909,1883092036785
    //noteData: [10000110]
    tone(pinBuzzer, 1909);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b1, tonS: b, durS: 16, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 120,00001, frq: 2548,4606442405725
    //noteData: [10001011]
    tone(pinBuzzer, 2548);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d2, tonS: d, durS: 16, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 120,00001, frq: 3030,647530435307
    //noteData: [10001110]
    tone(pinBuzzer, 3030);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b1, tonS: b, durS: 16, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 120,00001, frq: 2548,4606442405725
    //noteData: [10001011]
    tone(pinBuzzer, 2548);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c2, tonS: #c, durS: 16, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 120,00001, frq: 2860,5503547700973
    //noteData: [10001101]
    tone(pinBuzzer, 2860);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b1, tonS: b, durS: 16, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 120,00001, frq: 2548,4606442405725
    //noteData: [10001011]
    tone(pinBuzzer, 2548);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c2, tonS: #c, durS: 16, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 120,00001, frq: 2860,5503547700973
    //noteData: [10001101]
    tone(pinBuzzer, 2860);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b1, tonS: b, durS: 16, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 120,00001, frq: 2548,4606442405725
    //noteData: [10001011]
    tone(pinBuzzer, 2548);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#a1, tonS: #a, durS: 16, octS: 1, nAoS: #a1
    //NoteNumber: 10, timeMs: 120,00001, frq: 2405,426538978916
    //noteData: [10001010]
    tone(pinBuzzer, 2405);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c2, tonS: #c, durS: 16, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 120,00001, frq: 2860,5503547700973
    //noteData: [10001101]
    tone(pinBuzzer, 2860);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16e2, tonS: e, durS: 16, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 120,00001, frq: 3401,7868347161575
    //noteData: [10010000]
    tone(pinBuzzer, 3401);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c2, tonS: #c, durS: 16, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 120,00001, frq: 2860,5503547700973
    //noteData: [10001101]
    tone(pinBuzzer, 2860);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b1, tonS: b, durS: 8, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 240,00002, frq: 2548,4606442405725
    //noteData: [01001011]
    tone(pinBuzzer, 2548);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b2, tonS: b, durS: 8, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 240,00002, frq: 5096,921288481145
    //noteData: [01010111]
    tone(pinBuzzer, 5096);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d3, tonS: d, durS: 16, octS: 3, nAoS: d3
    //NoteNumber: 26, timeMs: 120,00001, frq: 6061,295060870613
    //noteData: [10011010]
    tone(pinBuzzer, 6061);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b2, tonS: b, durS: 16, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 120,00001, frq: 5096,921288481145
    //noteData: [10010111]
    tone(pinBuzzer, 5096);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#f2, tonS: #f, durS: 8, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 240,00002, frq: 3818,376618407357
    //noteData: [01010010]
    tone(pinBuzzer, 3818);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b2, tonS: b, durS: 16, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 120,00001, frq: 5096,921288481145
    //noteData: [10010111]
    tone(pinBuzzer, 5096);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d2, tonS: d, durS: 16, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 120,00001, frq: 3030,647530435307
    //noteData: [10001110]
    tone(pinBuzzer, 3030);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 4b1, tonS: b, durS: 4, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 480,00003, frq: 2548,4606442405725
    //noteData: [00001011]
    tone(pinBuzzer, 2548);
    delay(480);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b2, tonS: b, durS: 8, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 240,00002, frq: 5096,921288481145
    //noteData: [01010111]
    tone(pinBuzzer, 5096);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d2, tonS: d, durS: 8, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 240,00002, frq: 3030,647530435307
    //noteData: [01001110]
    tone(pinBuzzer, 3030);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32d2, tonS: d, durS: 32, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 60,000004, frq: 3030,647530435307
    //noteData: [11001110]
    tone(pinBuzzer, 3030);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32#c2, tonS: #c, durS: 32, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 60,000004, frq: 2860,5503547700973
    //noteData: [11001101]
    tone(pinBuzzer, 2860);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32d2, tonS: d, durS: 32, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 60,000004, frq: 3030,647530435307
    //noteData: [11001110]
    tone(pinBuzzer, 3030);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32#c2, tonS: #c, durS: 32, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 60,000004, frq: 2860,5503547700973
    //noteData: [11001101]
    tone(pinBuzzer, 2860);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#c2, tonS: #c, durS: 8, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 240,00002, frq: 2860,5503547700973
    //noteData: [01001101]
    tone(pinBuzzer, 2860);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#f2, tonS: #f, durS: 8, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 240,00002, frq: 3818,376618407357
    //noteData: [01010010]
    tone(pinBuzzer, 3818);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#f2, tonS: #f, durS: 8, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 240,00002, frq: 3818,376618407357
    //noteData: [01010010]
    tone(pinBuzzer, 3818);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#f2, tonS: #f, durS: 8, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 240,00002, frq: 3818,376618407357
    //noteData: [01010010]
    tone(pinBuzzer, 3818);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#f2, tonS: #f, durS: 8, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 240,00002, frq: 3818,376618407357
    //noteData: [01010010]
    tone(pinBuzzer, 3818);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8d3, tonS: d, durS: 8, octS: 3, nAoS: d3
    //NoteNumber: 26, timeMs: 240,00002, frq: 6061,295060870613
    //noteData: [01011010]
    tone(pinBuzzer, 6061);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#f2, tonS: #f, durS: 8, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 240,00002, frq: 3818,376618407357
    //noteData: [01010010]
    tone(pinBuzzer, 3818);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32#f2, tonS: #f, durS: 32, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 60,000004, frq: 3818,376618407357
    //noteData: [11010010]
    tone(pinBuzzer, 3818);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32f2, tonS: f, durS: 32, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 60,000004, frq: 3604,067606259093
    //noteData: [11010001]
    tone(pinBuzzer, 3604);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32#f2, tonS: #f, durS: 32, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 60,000004, frq: 3818,376618407357
    //noteData: [11010010]
    tone(pinBuzzer, 3818);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32f2, tonS: f, durS: 32, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 60,000004, frq: 3604,067606259093
    //noteData: [11010001]
    tone(pinBuzzer, 3604);
    delay(60);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8f2, tonS: f, durS: 8, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 240,00002, frq: 3604,067606259093
    //noteData: [01010001]
    tone(pinBuzzer, 3604);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c2, tonS: #c, durS: 16, octS: 2, nAoS: #c2
    //NoteNumber: 13, timeMs: 120,00001, frq: 2860,5503547700973
    //noteData: [10001101]
    tone(pinBuzzer, 2860);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16a2, tonS: a, durS: 16, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 120,00001, frq: 4540,840642370058
    //noteData: [10010101]
    tone(pinBuzzer, 4540);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#g2, tonS: #g, durS: 16, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 120,00001, frq: 4285,982840314139
    //noteData: [10010100]
    tone(pinBuzzer, 4285);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#g2, tonS: #g, durS: 16, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 120,00001, frq: 4285,982840314139
    //noteData: [10010100]
    tone(pinBuzzer, 4285);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 120,00001, frq: 3604,067606259093
    //noteData: [10010001]
    tone(pinBuzzer, 3604);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#g2, tonS: #g, durS: 16, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 120,00001, frq: 4285,982840314139
    //noteData: [10010100]
    tone(pinBuzzer, 4285);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b2, tonS: b, durS: 16, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 120,00001, frq: 5096,921288481145
    //noteData: [10010111]
    tone(pinBuzzer, 5096);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#g2, tonS: #g, durS: 16, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 120,00001, frq: 4285,982840314139
    //noteData: [10010100]
    tone(pinBuzzer, 4285);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16a2, tonS: a, durS: 16, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 120,00001, frq: 4540,840642370058
    //noteData: [10010101]
    tone(pinBuzzer, 4540);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#g2, tonS: #g, durS: 16, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 120,00001, frq: 4285,982840314139
    //noteData: [10010100]
    tone(pinBuzzer, 4285);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16a2, tonS: a, durS: 16, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 120,00001, frq: 4540,840642370058
    //noteData: [10010101]
    tone(pinBuzzer, 4540);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#g2, tonS: #g, durS: 16, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 120,00001, frq: 4285,982840314139
    //noteData: [10010100]
    tone(pinBuzzer, 4285);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16a2, tonS: a, durS: 16, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 120,00001, frq: 4540,840642370058
    //noteData: [10010101]
    tone(pinBuzzer, 4540);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 120,00001, frq: 3604,067606259093
    //noteData: [10010001]
    tone(pinBuzzer, 3604);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b2, tonS: b, durS: 16, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 120,00001, frq: 5096,921288481145
    //noteData: [10010111]
    tone(pinBuzzer, 5096);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 120,00001, frq: 3604,067606259093
    //noteData: [10010001]
    tone(pinBuzzer, 3604);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c3, tonS: #c, durS: 16, octS: 3, nAoS: #c3
    //NoteNumber: 25, timeMs: 120,00001, frq: 5721,100709540195
    //noteData: [10011001]
    tone(pinBuzzer, 5721);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 120,00001, frq: 3604,067606259093
    //noteData: [10010001]
    tone(pinBuzzer, 3604);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d3, tonS: d, durS: 16, octS: 3, nAoS: d3
    //NoteNumber: 26, timeMs: 120,00001, frq: 6061,295060870613
    //noteData: [10011010]
    tone(pinBuzzer, 6061);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 120,00001, frq: 3604,067606259093
    //noteData: [10010001]
    tone(pinBuzzer, 3604);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d3, tonS: d, durS: 16, octS: 3, nAoS: d3
    //NoteNumber: 26, timeMs: 120,00001, frq: 6061,295060870613
    //noteData: [10011010]
    tone(pinBuzzer, 6061);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c3, tonS: #c, durS: 16, octS: 3, nAoS: #c3
    //NoteNumber: 25, timeMs: 120,00001, frq: 5721,100709540195
    //noteData: [10011001]
    tone(pinBuzzer, 5721);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16b2, tonS: b, durS: 16, octS: 2, nAoS: b2
    //NoteNumber: 23, timeMs: 120,00001, frq: 5096,921288481145
    //noteData: [10010111]
    tone(pinBuzzer, 5096);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#c3, tonS: #c, durS: 16, octS: 3, nAoS: #c3
    //NoteNumber: 25, timeMs: 120,00001, frq: 5721,100709540195
    //noteData: [10011001]
    tone(pinBuzzer, 5721);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16a2, tonS: a, durS: 16, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 120,00001, frq: 4540,840642370058
    //noteData: [10010101]
    tone(pinBuzzer, 4540);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#g2, tonS: #g, durS: 16, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 120,00001, frq: 4285,982840314139
    //noteData: [10010100]
    tone(pinBuzzer, 4285);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 120,00001, frq: 3818,376618407357
    //noteData: [10010010]
    tone(pinBuzzer, 3818);
    delay(120);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8a2, tonS: a, durS: 8, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 240,00002, frq: 4540,840642370058
    //noteData: [01010101]
    tone(pinBuzzer, 4540);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8#g2, tonS: #g, durS: 8, octS: 2, nAoS: #g2
    //NoteNumber: 20, timeMs: 240,00002, frq: 4285,982840314139
    //noteData: [01010100]
    tone(pinBuzzer, 4285);
    delay(240);
    noTone(pinBuzzer);
    delay(10);

    //Note: 4#f2, tonS: #f, durS: 4, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 480,00003, frq: 3818,376618407357
    //noteData: [00010010]
    tone(pinBuzzer, 3818);
    delay(480);
    noTone(pinBuzzer);
    delay(10);



  }

  if (index == 3) { //Mario
    //tempo: 100

    //Note: 16e2, tonS: e, durS: 16, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 150, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16e2, tonS: e, durS: 16, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 150, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 32-, tonS: -, durS: 32, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 75, frq: 1046,48
    delay(75);
    //Note: 8e2, tonS: e, durS: 8, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 300, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16c2, tonS: c, durS: 16, octS: 2, nAoS: c2
    //NoteNumber: 12, timeMs: 150, frq: 261,62
    tone(pinBuzzer, 261);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8e2, tonS: e, durS: 8, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 300, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8g2, tonS: g, durS: 8, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 300, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8-, tonS: -, durS: 8, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 300, frq: 1046,48
    delay(300);
    //Note: 8g1, tonS: g, durS: 8, octS: 1, nAoS: g1
    //NoteNumber: 7, timeMs: 300, frq: 195,9935487262387
    tone(pinBuzzer, 195);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8-, tonS: -, durS: 8, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 300, frq: 1046,48
    delay(300);
    //Note: 8c2, tonS: c, durS: 8, octS: 2, nAoS: c2
    //NoteNumber: 12, timeMs: 300, frq: 261,62
    tone(pinBuzzer, 261);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16-, tonS: -, durS: 16, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 150, frq: 1046,48
    delay(150);
    //Note: 8g1, tonS: g, durS: 8, octS: 1, nAoS: g1
    //NoteNumber: 7, timeMs: 300, frq: 195,9935487262387
    tone(pinBuzzer, 195);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16-, tonS: -, durS: 16, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 150, frq: 1046,48
    delay(150);
    //Note: 8e1, tonS: e, durS: 8, octS: 1, nAoS: e1
    //NoteNumber: 4, timeMs: 300, frq: 164,81027253674836
    tone(pinBuzzer, 164);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16-, tonS: -, durS: 16, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 150, frq: 1046,48
    delay(150);
    //Note: 8a1, tonS: a, durS: 8, octS: 1, nAoS: a1
    //NoteNumber: 9, timeMs: 300, frq: 219,9953201586768
    tone(pinBuzzer, 219);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b1, tonS: b, durS: 8, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 300, frq: 246,93639768378466
    tone(pinBuzzer, 246);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#a1, tonS: #a, durS: 16, octS: 1, nAoS: #a1
    //NoteNumber: 10, timeMs: 150, frq: 233,07692263987556
    tone(pinBuzzer, 233);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8a1, tonS: a, durS: 8, octS: 1, nAoS: a1
    //NoteNumber: 9, timeMs: 300, frq: 219,9953201586768
    tone(pinBuzzer, 219);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16.g1, tonS: g, durS: 16, octS: 1, nAoS: g1
    //NoteNumber: 7, timeMs: 300, frq: 195,9935487262387
    tone(pinBuzzer, 195);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16e2, tonS: e, durS: 16, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 150, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16g2, tonS: g, durS: 16, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 150, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8a2, tonS: a, durS: 8, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 300, frq: 439,9906403173536
    tone(pinBuzzer, 439);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 150, frq: 349,2208026479644
    tone(pinBuzzer, 349);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8g2, tonS: g, durS: 8, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 300, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8e2, tonS: e, durS: 8, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 300, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16c2, tonS: c, durS: 16, octS: 2, nAoS: c2
    //NoteNumber: 12, timeMs: 150, frq: 261,62
    tone(pinBuzzer, 261);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d2, tonS: d, durS: 16, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 150, frq: 293,6585210786982
    tone(pinBuzzer, 293);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b1, tonS: b, durS: 8, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 300, frq: 246,93639768378466
    tone(pinBuzzer, 246);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16-, tonS: -, durS: 16, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 150, frq: 1046,48
    delay(150);
    //Note: 8c2, tonS: c, durS: 8, octS: 2, nAoS: c2
    //NoteNumber: 12, timeMs: 300, frq: 261,62
    tone(pinBuzzer, 261);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16-, tonS: -, durS: 16, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 150, frq: 1046,48
    delay(150);
    //Note: 8g1, tonS: g, durS: 8, octS: 1, nAoS: g1
    //NoteNumber: 7, timeMs: 300, frq: 195,9935487262387
    tone(pinBuzzer, 195);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16-, tonS: -, durS: 16, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 150, frq: 1046,48
    delay(150);
    //Note: 8e1, tonS: e, durS: 8, octS: 1, nAoS: e1
    //NoteNumber: 4, timeMs: 300, frq: 164,81027253674836
    tone(pinBuzzer, 164);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16-, tonS: -, durS: 16, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 150, frq: 1046,48
    delay(150);
    //Note: 8a1, tonS: a, durS: 8, octS: 1, nAoS: a1
    //NoteNumber: 9, timeMs: 300, frq: 219,9953201586768
    tone(pinBuzzer, 219);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b1, tonS: b, durS: 8, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 300, frq: 246,93639768378466
    tone(pinBuzzer, 246);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#a1, tonS: #a, durS: 16, octS: 1, nAoS: #a1
    //NoteNumber: 10, timeMs: 150, frq: 233,07692263987556
    tone(pinBuzzer, 233);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8a1, tonS: a, durS: 8, octS: 1, nAoS: a1
    //NoteNumber: 9, timeMs: 300, frq: 219,9953201586768
    tone(pinBuzzer, 219);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16.g1, tonS: g, durS: 16, octS: 1, nAoS: g1
    //NoteNumber: 7, timeMs: 300, frq: 195,9935487262387
    tone(pinBuzzer, 195);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16e2, tonS: e, durS: 16, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 150, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16g2, tonS: g, durS: 16, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 150, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8a2, tonS: a, durS: 8, octS: 2, nAoS: a2
    //NoteNumber: 21, timeMs: 300, frq: 439,9906403173536
    tone(pinBuzzer, 439);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 150, frq: 349,2208026479644
    tone(pinBuzzer, 349);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8g2, tonS: g, durS: 8, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 300, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8e2, tonS: e, durS: 8, octS: 2, nAoS: e2
    //NoteNumber: 16, timeMs: 300, frq: 329,6205450734967
    tone(pinBuzzer, 329);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16c2, tonS: c, durS: 16, octS: 2, nAoS: c2
    //NoteNumber: 12, timeMs: 150, frq: 261,62
    tone(pinBuzzer, 261);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16d2, tonS: d, durS: 16, octS: 2, nAoS: d2
    //NoteNumber: 14, timeMs: 150, frq: 293,6585210786982
    tone(pinBuzzer, 293);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8b1, tonS: b, durS: 8, octS: 1, nAoS: b1
    //NoteNumber: 11, timeMs: 300, frq: 246,93639768378466
    tone(pinBuzzer, 246);
    delay(300);
    noTone(pinBuzzer);
    delay(10);

    //Note: 8-, tonS: -, durS: 8, octS: , nAoS: -
    //NoteNumber: 36, timeMs: 300, frq: 1046,48
    delay(300);
    //Note: 16g2, tonS: g, durS: 16, octS: 2, nAoS: g2
    //NoteNumber: 19, timeMs: 150, frq: 391,9870974524774
    tone(pinBuzzer, 391);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16#f2, tonS: #f, durS: 16, octS: 2, nAoS: #f2
    //NoteNumber: 18, timeMs: 150, frq: 369,98655218804913
    tone(pinBuzzer, 369);
    delay(150);
    noTone(pinBuzzer);
    delay(10);

    //Note: 16f2, tonS: f, durS: 16, octS: 2, nAoS: f2
    //NoteNumber: 17, timeMs: 150, frq: 349,2208026479644
    tone(pinBuzzer, 349);
    delay(150);
    noTone(pinBuzzer);
    delay(10);


  }


  if (index == 4) { //Back
    setMode(MODE_MENU_MAIN);
    return;
  }
}
