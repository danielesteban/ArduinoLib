/*
  AnalogInputs.h - Library for analog inputs.
  Created by Daniel Esteban, October 7, 2012.
  Released into the public domain.
*/

#ifndef AnalogInputs_h
#define AnalogInputs_h

#include <Arduino.h>

typedef void (*analogInputEvent)(byte pin, int read); 

const byte analogInputsReadings = 10;

typedef struct analogInput { 
  byte pin;
  int read;
  int readings[analogInputsReadings];
  byte reading;
  int sum;
  analogInputEvent onChange;
  struct analogInput * next;
} analogInput;

class AnalogInputs {
  public:
    AnalogInputs(analogInputEvent onChange = NULL);
    void setup(byte pin, analogInputEvent onChange = NULL);
    void read();
    analogInput * get(byte pin);
  private:
    analogInput * _analogInputs;
    unsigned long _lastRead;
    analogInputEvent _onChange;
};
 
#endif
