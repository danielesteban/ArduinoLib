/*
    Nunchucks.h - Library for reading multiple nunchucks.
    Created by Daniel Esteban, February 15, 2013.
    Released into the public domain.
*/

#ifndef Nunchucks_h
#define Nunchucks_h

#include <Arduino.h>

#if defined(__AVR_ATtiny84__) | defined(__AVR_ATtiny85__)
#include <TinyWireM.h>
#define Wire (TinyWireM)
#else
#include <Wire.h>
#endif
#include <EEPROM.h>

typedef void (*nunchuckAnalogEvent)(/*byte pin, */byte axis, int read);
typedef void (*nunchuckButtonEvent)(/*byte pin, */byte button); 

const byte nunchucksReadings = 10;

typedef struct nunchuck { 
    //byte pin;
    byte cnt;
    uint8_t status[6];

    bool bZStatus;
    bool bZRead;
    unsigned long bZDebounce;

    bool bCStatus;
    bool bCRead;
    unsigned long bCDebounce;

    byte reading;

    int jXRead;
    int jXReadings[nunchucksReadings];
    int jXSum;
    byte JoyXZero;

    int jYRead;
    int jYReadings[nunchucksReadings];
    int jYSum;
    byte JoyYZero;

    int xRead;
    int xReadings[nunchucksReadings];
    int xSum;
    int xZero;

    /*int yRead;
    int yReadings[nunchucksReadings];
    int ySum;
    int yZero;

    int zRead;
    int zReadings[nunchucksReadings];
    int zSum;
    int zZero;*/
    
    //struct nunchuck * next;
} nunchuck;

class Nunchucks {
    public:
        Nunchucks(nunchuckAnalogEvent onJoyChange = NULL, nunchuckAnalogEvent onAccelChange = NULL, nunchuckButtonEvent onDown = NULL, nunchuckButtonEvent onUp = NULL);
        void setup(/*byte pin*/);
        void read(bool dontTriggerEvents = false);
        nunchuck * get(/*byte pin*/);
    private:
        //void activate(byte pin);
        nunchuck * _nunchucks;
        //unsigned long _lastRead;
        //byte _active;

        nunchuckAnalogEvent _onJoyChange;
        nunchuckAnalogEvent _onAccelChange;
        nunchuckButtonEvent _onDown;
        nunchuckButtonEvent _onUp;
};
 
#endif
