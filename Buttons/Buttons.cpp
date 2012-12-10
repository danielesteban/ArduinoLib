/*
  Buttons.h - Library for push buttons.
  Created by Daniel Esteban, October 5, 2012.
  Released into the public domain.
*/

#include "Buttons.h"

Buttons::Buttons(buttonEvent onPush, buttonEvent onDown) {
  _onPush = onPush;
  _onDown = onDown;
  _buttons = NULL;
}

void Buttons::setup(byte pin, buttonEvent onPush, buttonEvent onDown) {
  button * b = (button *) malloc(sizeof(button));
  b->pin = pin;
  b->status = HIGH;
  b->read = HIGH;
  b->debounce = 0;
  b->onPush = onPush;
  b->onDown = onDown;
  b->next = _buttons;
  _buttons = b;
  pinMode(pin, INPUT_PULLUP);
}

void Buttons::read() {
  button * b = _buttons;
  while(b) {
    byte read = digitalRead(b->pin);
    unsigned long t = millis();
    b->read != read && (b->debounce = t);
    b->read = read;
    if(b->status != read && (t - b->debounce) > 25) {
      b->status = read;
      if(read == HIGH) {
        if(b->onPush != NULL) b->onPush(b->pin);
        else if(_onPush != NULL) _onPush(b->pin);
      } else if(b->onDown != NULL) b->onDown(b->pin);
      else if(_onDown != NULL) _onDown(b->pin);
    }
    b = b->next;
  }
}

button * Buttons::get(byte pin) {
  button * b = _buttons;
  while(b) {
    if(b->pin == pin) return b;
    b = b->next;
  }
}
