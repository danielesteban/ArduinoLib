/*
  AnalogInputs.cpp - Library for analog inputs.
  Created by Daniel Esteban, October 7, 2012.
  Released into the public domain.
*/

#include "AnalogInputs.h"

#if defined (__ARMEL__)
const int _resolution = 4095;
#else
const int _resolution = 1023;
#endif

AnalogInputs::AnalogInputs(analogInputEvent onChange, byte delay) {
  _onChange = onChange;
  _delay = delay;
  _analogInputs = NULL;
  _lastRead = 0;
}

void AnalogInputs::setup(byte pin, analogInputEvent onChange) {
  analogInput * a = (analogInput *) malloc(sizeof(analogInput));
  a->pin = pin;
  a->read = 0;
  a->sum = 0;
  for(byte i=0; i<analogInputsReadings; i++) {
    a->readings[i] = _resolution - analogRead(a->pin);
    a->sum += a->readings[i];
  }
  a->reading = 0;
  a->onChange = onChange;
  a->next = _analogInputs;
  _analogInputs = a;
}

void AnalogInputs::read(bool dontTriggerEvents) {
  unsigned long t = millis();
  if(t < _lastRead + _delay) return;
  _lastRead = t;
  analogInput * a = _analogInputs;
  while(a) {
    a->sum -= a->readings[a->reading];
    a->readings[a->reading] = _resolution - analogRead(a->pin);
    a->sum += a->readings[a->reading];
    a->reading++;
    a->reading >= analogInputsReadings && (a->reading = 0);
    int read = round((float) a->sum / (float) analogInputsReadings);
    if(abs(a->read - read) > 1) {
      read < 2 && (read = 0);
      read > (_resolution - 2) && (read = _resolution);
      a->read = read;
      if(!dontTriggerEvents) {
        if(a->onChange != NULL) a->onChange(a->pin, a->read);
        else if(_onChange != NULL) _onChange(a->pin, a->read);
      }
    }
    a = a->next;
  }
}

analogInput * AnalogInputs::get(byte pin) {
  analogInput * a = _analogInputs;
  while(a) {
    if(a->pin == pin) return a;
    a = a->next;
  }
}
