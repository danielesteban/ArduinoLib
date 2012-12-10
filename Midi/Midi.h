/*
  Midi.h - Library for midi out.
  Created by Daniel Esteban, November 29, 2012.
  Released into the public domain.
*/

#ifndef Midi_h
#define Midi_h

#include <Arduino.h>

class Midi {
  public:
    Midi(HardwareSerial &serial = Serial);
    void begin(unsigned long speed = 31250);
    void sendNoteOff(byte note, byte velocity, byte channel = 0);
    void sendNoteOn(byte note, byte velocity, byte channel = 0);
  private:
    void send(byte status, byte channel, byte data1, byte data2);
    HardwareSerial _serial;
};
 
#endif
