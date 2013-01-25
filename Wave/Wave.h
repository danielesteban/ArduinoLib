/*
	Wave.h - Library for generating audio waves.
	Created by Daniel Esteban, December 5, 2012.
	Released into the public domain.
*/

#ifndef Wave_h
#define Wave_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
const String WaveShapeNames[] = {"Square", "Triangle", "Saw", "Sine"};
#else
#include <WProgram.h>
#endif

#define WaveShapeSquare (0)
#define WaveShapeTriangle (1)
#define WaveShapeSaw (2)
#define WaveShapeSine (3)

class Wave {
	public:
		Wave(byte shape, unsigned int _sampleRate, unsigned int frequency = 1);
		void setFrequency(unsigned int frequency);
		void setShape(byte shape);
		byte getShape();
		byte next();
	private:
		byte _shape,
			_inc;

		unsigned int _sampleRate,
	    	_frequency,
	    	_count,
			_period,
			_intInc,
			_out;
};
 
#endif
