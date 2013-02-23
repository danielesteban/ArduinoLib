/*
	LedMatrix.cpp - Library for interfacing with led matrices.
	Created by Daniel Esteban, February 21, 2013.
	Released into the public domain.
*/

#include "LedMatrix.h"

bool LedMatrix::zero[15] PROGMEM = {
	1, 1, 1,
	1, 0, 1,
	1, 0, 1,
	1, 0, 1,
	1, 1, 1
};

bool LedMatrix::one[15] PROGMEM = {
	0, 1, 0,
	1, 1, 0,
	0, 1, 0,
	0, 1, 0,
	1, 1, 1,
};

bool LedMatrix::two[15] PROGMEM = {
	1, 1, 1,
	0, 0, 1,
	1, 1, 1,
	1, 0, 0,
	1, 1, 1
};

bool LedMatrix::three[15] PROGMEM = {
	1, 1, 1,
	0, 0, 1,
	1, 1, 1,
	0, 0, 1,
	1, 1, 1
};

bool LedMatrix::four[15] PROGMEM = {
	1, 0, 1,
	1, 0, 1,
	1, 1, 1,
	0, 0, 1,
	0, 0, 1
};

bool LedMatrix::five[15] PROGMEM = {
	1, 1, 1,
	1, 0, 0,
	1, 1, 1,
	0, 0, 1,
	1, 1, 1
};

bool LedMatrix::six[15] PROGMEM = {
	1, 1, 1,
	1, 0, 0,
	1, 1, 1,
	1, 0, 1,
	1, 1, 1
};

bool LedMatrix::seven[15] PROGMEM = {
	1, 1, 1,
	0, 0, 1,
	0, 1, 0,
	0, 1, 0,
	1, 0, 0
};

bool LedMatrix::eight[15] PROGMEM = {
	1, 1, 1,
	1, 0, 1,
	1, 1, 1,
	1, 0, 1,
	1, 1, 1
};

bool LedMatrix::nine[15] PROGMEM = {
	1, 1, 1,
	1, 0, 1,
	1, 1, 1,
	0, 0, 1,
	0, 0, 1
};

const bool * LedMatrix::numbers[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

LedMatrix::LedMatrix(volatile unsigned char * DirectionRegister, volatile unsigned char * Port, byte LatchPin, byte ClockPin, byte DataPin) {
	_port = Port;
	_latchPin = LatchPin;
	_clockPin = ClockPin;
	_dataPin = DataPin;
	_pwmCount = _row = 0;
	clear();
	
	* DirectionRegister |= (1 << LatchPin);
	* DirectionRegister |= (1 << ClockPin);
	* DirectionRegister |= (1 << DataPin);
}

byte LedMatrix::getPixel(byte x, byte y) {
	return _pixels[(numRows * y) + x];
}

byte LedMatrix::getPixel(byte n) {
	return _pixels[n];
}

void LedMatrix::setPixel(byte x, byte y, byte brightness) {
	_pixels[(numRows * y) + x] = brightness;
}

void LedMatrix::setPixel(byte n, byte brightness) {
	_pixels[n] = brightness;
}

void LedMatrix::clear() {
	for(byte x=0; x<numColums * numRows; x++) _pixels[x] = 0;
}

void LedMatrix::update() {
	int x;

	* _port &= ~(1 << _latchPin);
	for(x=numRows - 1; x>=0; x--) {
        if(_row == x) * _port |= (1 << _dataPin);
        else * _port &= ~(1 << _dataPin);
        * _port |= (1 << _clockPin);
        * _port &= ~(1 << _clockPin);
    }
    for(x=numColums - 1; x>=0; x--) {
    	const byte brightness = _pixels[(numRows * _row) + x];
        if(brightness == 255 || (brightness > 0 && brightness > _pwmCount)) * _port &= ~(1 << _dataPin);
        else * _port |= (1 << _dataPin);
        * _port |= (1 << _clockPin);
        * _port &= ~(1 << _clockPin);
    }
    * _port |= (1 << _latchPin);

	_row++;
	if(_row == numRows) {
		_row = 0;
		_pwmCount += 42;
		_pwmCount == 252 && (_pwmCount = 0);
	}
}

void LedMatrix::printNumber(byte x, byte y, byte n) {
	n = constrain(n, 0, 9);
	for(byte py=0; py<5; py++) {
		for(byte px=0; px<3; px++) setPixel(px + x, py + y, pgm_read_byte_near(numbers[n] + ((py * 3) + px)) ? 255 : 0);
	}
}
