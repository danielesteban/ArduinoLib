/*
	Wave.h - Library for generating audio waves.
	Created by Daniel Esteban, December 5, 2012.
	Released into the public domain.
*/

#ifndef Wave_h
#define Wave_h

#include <Arduino.h>

#define WaveShapeSquare (0)
#define WaveShapeTriangle (1)
#define WaveShapeSaw (2)
#define WaveShapeSine (3)

const String WaveShapeNames[] = {"Square", "Triang", "Saw", "Sine"};

class Wave {
	public:
		Wave(byte shape, unsigned int _sampleRate, unsigned int frequency = 1);
		void setFrequency(unsigned int frequency);
		void setShape(byte shape);
		byte getShape();
		byte next();
	private:
		byte _shape,
			_byte,
			_inc;

		unsigned int _sampleRate,
	    	_frequency,
	    	_count,
	    	_byteInt,
			_period,
			_incInt;
};
 
#endif
