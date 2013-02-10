/*
	TinyWave.cpp - Library for generating square audio waves on the Attiny.
	Created by Daniel Esteban, February 10, 2013.
	Released into the public domain.
*/

#include "TinyWave.h"

TinyWave::TinyWave(unsigned int sampleRate, unsigned int frequency) {
	_sampleRate = sampleRate;
	_count = 0;
	setFrequency(frequency);
}

void TinyWave::setFrequency(unsigned int frequency) {
	_frequency = frequency;
	_period = _sampleRate / frequency;
	_period == 0 && (_period = 1);
}

int TinyWave::next() {
	_count ++;
	_count >= _period && (_count = 0);
	return ((_period - _count) > _count ? 32 : -32);
}
