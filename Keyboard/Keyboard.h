/*
    Keyboard.h - Library for on screen keyboard.
    Created by Daniel Esteban, February 5, 2012.
    Released into the public domain.
*/

#ifndef Keyboard_h
#define Keyboard_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <stdlib.h>
#include <WProgram.h>
#endif
#include "UI.h"

typedef void (*KeyboardEvent)(String str);

class Keyboard : public UI {
    public:
        Keyboard(KeyboardEvent callback, byte maxLength = 255);
        void render(UTFT tft);
    private:
        static const byte numKeys = 27;
        static const char keys[numKeys];

        UTFT _tft;
        String _str;
        KeyboardEvent _callback;
        byte _lastPress;
        byte _maxLength;
        void onTouch(byte orientation, int x, int y);
        void onTouchEnd();
        void printStr();
};
 
#endif
