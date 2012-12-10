/*
  AnalogInputs.cpp - Library for analog inputs.
  Created by Daniel Esteban, October 7, 2012.
  Released into the public domain.
*/

#include "AnalogInputs.h"

AnalogInputs::AnalogInputs(analogInputEvent onChange) {
  _onChange = onChange;
  _analogInputs = NULL;
  _lastRead = 0;
}

void AnalogInputs::setup(byte pin, analogInputEvent onChange) {
  analogInput * a = (analogInput *) malloc(sizeof(analogInput));
  a->pin = pin;
  a->read = 0;
  a->sum = 0;
  for(byte i=0; i<analogInputsReadings; i++) {
    a->readings[i] = 1023 - analogRead(a->pin);
    a->sum += a->readings[i];
  }
  a->reading = 0;
  a->onChange = onChange;
  a->next = _analogInputs;
  _analogInputs = a;
}

void AnalogInputs::read(bool dontTriggerEvents) {
  unsigned long t = millis();
  if(t < _lastRead + 1) return;
  _lastRead = t;
  analogInput * a = _analogInputs;
  while(a) {
    a->sum -= a->readings[a->reading];
    a->readings[a->reading] = 1023 - analogRead(a->pin);
    a->sum += a->readings[a->reading];
    a->reading++;
    a->reading >= analogInputsReadings && (a->reading = 0);
    int read = round((float) a->sum / (float) analogInputsReadings);
    if(abs(a->read - read) > 1) {
      read < 2 && (read = 0);
      read > 1021 && (read = 1023);
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
