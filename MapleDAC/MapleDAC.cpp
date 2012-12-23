/*
  MapleDAC.cpp - Library for output to a MapleDAC with the leaflabs Maple.
  Created by Daniel Esteban, December 17, 2012.
  Released into the public domain.
*/

#include "MapleDAC.h"

MapleDAC::MapleDAC(const byte pins[DAC_BITS]) {
	_current = 0;
	for(byte i=0; i<DAC_BITS; i++) {
		pinMode(pins[i], OUTPUT);
		digitalWrite(pins[i], LOW);
		_pins[i] = pins[i];
	}
}

void MapleDAC::output(byte output) {
	if(_current == output) return;
	_current = output;
	for(byte i=0; i<DAC_BITS; i++) {
		digitalWrite(_pins[i], output & (1 << i) ? HIGH : LOW);
		/*if(SerialUSB.isConnected() && (SerialUSB.getDTR() || SerialUSB.getRTS())) {
			SerialUSB.print(_pins[i], DEC);
			SerialUSB.print(" ");
			SerialUSB.println(output & (1 << i) ? HIGH : LOW, DEC);
		}*/
	}
}
