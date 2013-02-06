/*
    Menu.cpp - Library for graphical menus.
    Created by Daniel Esteban, December 23, 2012.
    Released into the public domain.
*/

#include "Menu.h"

Menu::Menu(String title, byte numItems, String items[], TouchEvent onClick, TouchEvent onDown) : UI() {
	_title = title;
	_numItems = numItems;
	_onClick = onClick;
	_onDown = onDown;
	_lastPress = 255;
	for(byte x=0; x<numItems; x++) addButton(items[x]);
}

void Menu::render(UTFT tft) {
	byte page = 0, 
		offset = page * itemsPerPage,
		x = 0;

	offset >= _numItems && (_page = offset = 0);
	byte to = offset + itemsPerPage;
	to > _numItems && (to = _numItems);

	int itemWidth = tft.getDisplayXSize() - (menuPadding * 2),
		itemHeight = (tft.getDisplayYSize() - (menuPadding * 2) - titleHeight - (itemMargin * ((_numItems > itemsPerPage ? itemsPerPage : _numItems) - 1))) / (_numItems > itemsPerPage ? itemsPerPage : _numItems);

	_itemPadding = (itemHeight - 10) / 2;
	_page = page;

	tft.clrScr();
	tft.setColor(255, 255, 255);
	tft.fillRect(0, 0, tft.getDisplayXSize() - 1, titleHeight - 1);
	tft.setBackColor(255, 255, 255);
	tft.setColor(0, 0, 0);
	tft.setFont(SmallFont);
	tft.print(_title, 10, 0);

	_tft = tft;
	UIButton * b = _buttons;
	while(b != NULL) {
		b->width = itemWidth;
		b->height = itemHeight;
		if(x < offset || x >= to) b->x = b->y = -1;
		else {
			_items[x - offset] = b;
			b->x = menuPadding;
			b->y = menuPadding + titleHeight + ((x - offset) * (itemHeight + itemMargin));
			renderItem(b);
		}
		b = b->next;
		x++;
	}
}

void Menu::setLabel(byte id, String label, bool render) {
	UIButton * b = _buttons;
	byte x = 0;
	while(b != NULL && x < id) {
		b = b->next;
		x++;
	}
	if(b == NULL) return;
	b->label = label;
	if(render) renderItem(b);
}

void Menu::onClick(byte id) {
	_lastPress = 255;
	renderItem(_items[id]);
	if(_onClick != NULL) _onClick((_page * itemsPerPage) + id);
}

void Menu::onDown(byte id) {
	if(_lastPress != 255) renderItem(_items[_lastPress]);
	_lastPress = id;
	if(id != 255) renderItem(_items[id], true);
	if(_onDown != NULL) _onDown((_page * itemsPerPage) + id);
}

void Menu::renderItem(UIButton * b, bool pressed) {
	if(pressed) _tft.setColor(0, 172, 237);
	else _tft.setColor(255, 255, 255);
	_tft.fillRoundRect(b->x, b->y, b->x + b->width, b->y + b->height);
	if(pressed) {
		_tft.setBackColor(0, 172, 237);
		_tft.setColor(255, 255, 255);
	} else {
		_tft.setBackColor(255, 255, 255);
		_tft.setColor(0, 0, 0);
	}
	_tft.print(b->label, b->x + _itemPadding, b->y + _itemPadding);
}
