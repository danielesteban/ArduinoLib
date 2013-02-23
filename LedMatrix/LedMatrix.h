/*
	LedMatrix.h - Library for interfacing with led matrices.
	Created by Daniel Esteban, February 21, 2013.
	Released into the public domain.
*/

#ifndef LedMatrix_h
#define LedMatrix_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class LedMatrix {
	public:
		LedMatrix(volatile unsigned char * DirectionRegister, volatile unsigned char * Port, byte LatchPin, byte ClockPin, byte DataPin);
		byte getPixel(byte x, byte y);
		byte getPixel(byte n);
		void setPixel(byte x, byte y, byte brightness);
		void setPixel(byte n, byte brightness);
		void clear();
		void update();
		void printNumber(byte x, byte y, byte n);
		
		static const byte numColums = 8,
			numRows = 8;
	private:
		volatile unsigned char * _port;

		byte _latchPin,
			_clockPin,
			_dataPin,
			_pwmCount,
			_row,
			_pixels[numColums * numRows];

		static bool zero[15] PROGMEM;
		static bool one[15] PROGMEM;
		static bool two[15] PROGMEM;
		static bool three[15] PROGMEM;
		static bool four[15] PROGMEM;
		static bool five[15] PROGMEM;
		static bool six[15] PROGMEM;
		static bool seven[15] PROGMEM;
		static bool eight[15] PROGMEM;
		static bool nine[15] PROGMEM;

		static const bool * numbers[10];
};
 
#endif
