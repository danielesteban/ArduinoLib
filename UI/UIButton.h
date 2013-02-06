/*
    UIButton.h - Library for UI buttons.
    Created by Daniel Esteban, December 24, 2012.
    Released into the public domain.
*/

#ifndef UIButton_h
#define UIButton_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <stdlib.h>
#include <WProgram.h>
#endif

typedef void (*ByteCallback)(byte id);

class UIButton {
    public:
        UIButton(int gx = -1, int gy = -1, int w = -1, int h = -1, ByteCallback oc = NULL, ByteCallback od = NULL);
        int width;
        int height;
        int x;
        int y;
        ByteCallback onClick;
        ByteCallback onDown;
        UIButton * next;
    private:
};
 
#endif