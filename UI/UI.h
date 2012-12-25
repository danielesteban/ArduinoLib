/*
    UI.h - Library for arduino TFT UIs.
    Created by Daniel Esteban, December 24, 2012.
    Released into the public domain.
*/

#ifndef UI_h
#define UI_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <stdlib.h>
#include <WProgram.h>
#endif
#include <UTFT.h>
#include <UTouch.h>
#include "UIButton.h"

class UI {
    public:
        UI(TouchEvent onClick = NULL, TouchEvent onDown = NULL);
        virtual void render(UTFT tft) = 0;
        void readTouch(UTFT tft, UTouch touch, byte orientation, TouchEvent menuOnClick = NULL, TouchEvent menuOnDown = NULL, int * cords = NULL);
        byte availableOrientations[2];
    protected:
        void addButton(char * label, int width = -1, int height = -1, int x = -1, int y = -1, TouchEvent onClick = NULL, TouchEvent onDown = NULL);
        UIButton * _buttons;
        TouchEvent _onClick;
        TouchEvent _onDown;
    private:
        UIButton * _lastButton;

        byte _lastRead,
            _lastTouch;

        unsigned long _debounce;
};

#endif
