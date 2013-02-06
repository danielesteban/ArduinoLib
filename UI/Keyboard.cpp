/*
    Keyboard.cpp - Library for on screen keyboard.
    Created by Daniel Esteban, February 5, 2013.
    Released into the public domain.
*/

#include "Keyboard.h"

const char Keyboard::keys[Keyboard::numKeys] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '.'};

Keyboard::Keyboard(StringCallback callback, byte maxLength) : UI() {
	availableOrientations[PORTRAIT] = 0;
	_callback = callback;
	_maxLength = maxLength;
	_lastPress = 255;
	_str = "";
}

void Keyboard::render(UTFT tft) {
	tft.clrScr();
	tft.setFont(BigFont);	
	
	tft.setBackColor(255, 255, 255);
	tft.setColor(255, 255, 255);
	tft.drawRoundRect(30, 30, tft.getDisplayXSize() - 111, 70);
	tft.fillRect(tft.getDisplayXSize() - 106, 30, tft.getDisplayXSize() - 66, 70);
	tft.setColor(0, 0, 0);
	tft.print("<-", tft.getDisplayXSize() - 102, 43);
	tft.setColor(255, 255, 255);
	tft.fillRect(tft.getDisplayXSize() - 61, 30, tft.getDisplayXSize() - 21, 70);
	tft.setColor(0, 0, 0);
	tft.print("OK", tft.getDisplayXSize() - 57, 43);

	byte br = 9,
		nl = 0,
		offset = 1;

	int x = offset,
		y = 120;

	for(byte j=0;j<numKeys; j++) {
		tft.setColor(255, 255, 255);
		tft.fillRect(x, y, x + 30, y + 30);
		tft.setColor(0, 0, 0);
		String str = "";
		str += keys[j]; //lame!
		tft.print(str, x + 7, y + 8);
		x += 32;
		nl++;
		if(nl > br) {
			offset += 15;
			x = offset;
			nl = 0;
			y += 32;
			br -= 1;
		}
	}

	_tft = tft;
}

void Keyboard::onTouch(byte orientation, int x, int y) {
	if(y > 120 && y < 214) { //keys
		if(_maxLength != 255 && _str.length() == _maxLength) return;
		y -= 120;
		y = y / 32;
		x -= y * 15;
		if(x <= 0 || x >= 32 * (y == 0 ? 10 : y == 1 ? 9 : 8)) {
			_lastPress = 255;
			return;
		}
		x = x / 32;
		y > 0 && (x += y == 1 ? 10 : 19);
		if(_lastPress != x) {
			_lastPress = x;
			_str += keys[x];
			printStr();
		}
	} else if(x > _tft.getDisplayXSize() - 106 && y > 30 && x < _tft.getDisplayXSize() - 21 && y < 70) { //DEL & OK
		x -= _tft.getDisplayXSize() - 106;
		x = x / 40;
		switch(x) {
			case 0: //DEL
				if(_str.length() == 0 || _lastPress == 253) return;
				_lastPress = 253;
				_str = _str.substring(0, _str.length() - 1);
				printStr();
			break;
			case 1: //OK
				if(_str.length() == 0 || _lastPress == 254) return;
				_lastPress = 254;
				_callback(_str);
		}
	} else _lastPress = 255;
}

void Keyboard::onTouchEnd() {
	_lastPress = 255;
}

void Keyboard::printStr() {
	_tft.setBackColor(0, 0, 0);
	_tft.setColor(0, 0, 0);
	_tft.fillRect(35, 35, _tft.getDisplayXSize() - 116, 65);
	_tft.setColor(255, 255, 255);
	_tft.print(_str.length() > 10 ? _str.substring(_str.length() - 10) : _str, 40, 43);
}
