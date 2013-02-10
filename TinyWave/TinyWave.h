/*
	TinyWave.h - Library for generating square audio waves on the Attiny.
	Created by Daniel Esteban, February 10, 2013.
	Released into the public domain.
*/

#ifndef TinyWave_h
#define TinyWave_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class TinyWave {
	public:
		TinyWave(unsigned int sampleRate, unsigned int frequency = 1);
		void setFrequency(unsigned int frequency);
		int next();
	private:
		unsigned int _sampleRate,
	    	_frequency,
	    	_count,
			_period;
};
 
#endif
