/*
  Midi.h - Library for midi out.
  Created by Daniel Esteban, November 29, 2012.
  Released into the public domain.
*/

#include "Midi.h"

static const byte STATUS_EVENT_NOTE_OFF = 0x80,
	STATUS_EVENT_NOTE_ON = 0x90;

Midi::Midi(HardwareSerial &serial) : _serial(serial) {

}

void Midi::begin(unsigned long speed) {
	_serial.begin(speed);
}

void Midi::sendNoteOff(byte note, byte velocity, byte channel) {
	send(STATUS_EVENT_NOTE_OFF, channel, note, velocity);
}

void Midi::sendNoteOn(byte note, byte velocity, byte channel) {
	send(STATUS_EVENT_NOTE_ON, channel, note, velocity);
}

void Midi::send(byte status, byte channel, byte data1, byte data2) {
	_serial.write(status | ((channel-1) & 0x0F));
	_serial.write(data1 & 0x7f);
	_serial.write(data2 & 0x7f);
}
