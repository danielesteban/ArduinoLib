/*
  Buttons.h - Library for push buttons.
  Created by Daniel Esteban, October 5, 2012.
  Released into the public domain.
*/

#ifndef Buttons_h
#define Buttons_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <stdlib.h>
#include <WProgram.h>
#endif

typedef void (*buttonEvent)(byte pin); 

typedef struct button { 
  byte pin;
  byte status;
  byte read;
  unsigned long debounce;
  buttonEvent onPush;
  buttonEvent onDown;
  struct button * next;
} button;

class Buttons {
  public:
    Buttons(buttonEvent onPush = NULL, buttonEvent onDown = NULL);
    void setup(byte pin, buttonEvent onPush = NULL, buttonEvent onDown = NULL);
    void read();
    button * get(byte pin);
  private:
    button * _buttons;
    buttonEvent _onPush;
    buttonEvent _onDown;
};
 
#endif
