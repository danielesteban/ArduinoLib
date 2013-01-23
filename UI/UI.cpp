/*
    UI.h - Library for arduino TFT UIs.
    Created by Daniel Esteban, December 24, 2012.
    Released into the public domain.
*/

#include "UI.h"

UI::UI() {
	_buttons = _lastButton = NULL;
	_lastRead = _lastTouch = 255;
	_debounce = 0;
	availableOrientations[PORTRAIT] = availableOrientations[LANDSCAPE] = 1;
	rendered = false;
}

void UI::readTouch(UTFT tft, UTouch touch, byte orientation, TouchEvent menuOnClick, TouchEvent menuOnDown, int * cords) {
	int x, y;
	bool hit = false;
	UIButton * b = NULL;
	byte bt = 255,
		i;
	
	if(touch.dataAvailable()) {
		touch.read();
		x = touch.getX();
		y = touch.getY();

		if(cords != NULL) {
			cords[0] = x;
			cords[1] = y;
		}

		//Serial.print(x);
		//Serial.print(" ");
		//Serial.println(y);

		if((orientation == LANDSCAPE && x <= 20) || (orientation == PORTRAIT && y >= tft.getDisplayYSize())) { //menu buttons
			bt = 250 + (orientation == LANDSCAPE ? y * 5 / (tft.getDisplayYSize() - 1) : x * 5 / (tft.getDisplayXSize() - 1));
		} else {
			orientation == LANDSCAPE && (x -= 20);
			b = _buttons;
			i = 0;
			while(b != NULL) {
				if(b->x != -1 && b->y != -1 && x >= b->x && y >= b->y && x <= b->x + b->width && y <= b->y + b->height) {
					bt = i;
					break;	
				}
				b = b->next;
				i++;
			}

			onTouch(orientation, x, y);
		}

		unsigned long t = millis();
		_lastRead != bt && (_debounce = t);
	   	_lastRead = bt;
	    if(_lastTouch != _lastRead && (t - _debounce) > 10) {
			_lastTouch = _lastRead;
			if(bt != 255) {
				if(bt >= 250) { //menu buttons
					if(menuOnDown != NULL) menuOnDown(bt - 250);
				} else {
					if(b->onDown != NULL) b->onDown(i);
					else onDown(i);
				}
			} else onDown(255);
	    }
	}

	if(!touch.dataAvailable()) {
		if(_lastTouch != 255) {
			if(_lastTouch >= 250) { //menu buttons
				if(menuOnClick != NULL) menuOnClick(_lastTouch - 250);
			} else {
				b = _buttons;
				for(i=0; i<_lastTouch; i++) b = b->next;
				if(b->onClick != NULL) b->onClick(_lastTouch);
				else onClick(_lastTouch);
			}
			_lastRead = _lastTouch = 255;
			_debounce = 0;
		} else onTouchEnd();
	}
}

void UI::addButton(String label, int x, int y, int width, int height, TouchEvent onClick, TouchEvent onDown) {
	UIButton * b = new UIButton(label, x, y, width, height, onClick, onDown);
    if(_buttons == NULL) _buttons = _lastButton = b;
    else {
        _lastButton->next = b;
        _lastButton = b;
    }
}
