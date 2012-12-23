/*
  MapleDAC.h - Library for output to a MapleDAC with the leaflabs Maple.
  Created by Daniel Esteban, December 17, 2012.
  Released into the public domain.
*/

#ifndef MapleDAC_h
#define MapleDAC_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const byte DAC_BITS = 8;

class MapleDAC {
  public:
    MapleDAC(const byte pins[DAC_BITS]);
  	void output(byte output);
  private:
    byte _pins[DAC_BITS],
    	_current;
};
 
#endif
