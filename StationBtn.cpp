#include "StationBtn.h"
#include <Arduino.h>

StationBtn::StationBtn(int btnPin, int LEDPin, int hrPin, int chPin)
    : btnPin(btnPin), LEDPin(LEDPin), handrestPin(hrPin), chPin(chPin), Active(false), Watch(false) {

    pinMode(btnPin, INPUT);
    pinMode(handrestPin, INPUT);
    
    pinMode(LEDPin, OUTPUT);
    pinMode(chPin, OUTPUT);
}

bool StationBtn::Similar(StationBtn *other) {
  return other->chPin == chPin || other->handrestPin == handrestPin;
}

void StationBtn::Activate() {
  setLED(HIGH);
  Active = true;
}

void StationBtn::Deactivate() {
  setLED(LOW);
  Active = false;
}

void StationBtn::setLED(bool state) {
  digitalWrite(LEDPin, state);
}

