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

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

typedef void (*Callback)(void);
typedef void (*StringCallback)(String str);

#include "UIButton.h"

class UI {
    public:
        UI();
        virtual ~UI();
        virtual void render(UTFT tft) = 0;
        virtual void update() {};
        void readTouch(UTFT tft, UTouch touch, byte orientation, ByteCallback menuOnClick = NULL, ByteCallback menuOnDown = NULL, int * cords = NULL);
        byte availableOrientations[2];
        bool rendered;
    protected:
        void addButton(int x = -1, int y = -1, int width = -1, int height = -1, ByteCallback onClick = NULL, ByteCallback onDown = NULL);
        virtual void onTouch(byte orientation, int x, int y) {};
        virtual void onTouchEnd() {};
        virtual void onClick(byte id) {};
        virtual void onDown(byte id) {};
        UIButton * _buttons;
    private:
        UIButton * _lastButton;

        byte _lastRead,
            _lastTouch;

        unsigned long _debounce;
};

#endif
