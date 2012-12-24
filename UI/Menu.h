/*
    Menu.h - Library for graphical menus.
    Created by Daniel Esteban, December 23, 2012.
    Released into the public domain.
*/

#ifndef Menu_h
#define Menu_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <stdlib.h>
#include <WProgram.h>
#endif
#include <UTFT.h>
#include "UI.h"

class Menu : public UI {
    public:
        Menu(byte numItems, char * items[], TouchEvent onClick = NULL, TouchEvent onDown = NULL);
        void render(UTFT tft);
        void touch(int x, int y);
        void click();
    private:
        byte _numItems,
            _page;
};
 
#endif
