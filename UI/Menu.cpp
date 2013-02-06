/*
    Menu.cpp - Library for graphical menus.
    Created by Daniel Esteban, December 23, 2012.
    Released into the public domain.
*/

#include "Menu.h"

Menu::Menu(String title, byte numItems, String items[], ByteCallback onClick, ByteCallback onDown) : UI() {
	_title = title;
	_numItems = numItems;
	_items = items;
	_onClick = onClick;
	_onDown = onDown;
	_lastPress = 255;
	for(byte x=0; x<itemsPerPage; x++) addButton();
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
	for(byte x=0; x<itemsPerPage; x++) {
		b->width = itemWidth;
		b->height = itemHeight;
		if(x + offset >= to) b->x = b->y = -1;
		else {
			b->x = menuPadding;
			b->y = menuPadding + titleHeight + (x * (itemHeight + itemMargin));
			renderItem(x);
		}
		b = b->next;
	}
}

void Menu::setLabel(byte id, String label, bool render) {
	_items[id] = label;
	if(render) renderItem(id - (_page * itemsPerPage));
}

void Menu::onClick(byte id) {
	_lastPress = 255;
	renderItem(id);
	if(_onClick != NULL) _onClick((_page * itemsPerPage) + id);
}

void Menu::onDown(byte id) {
	if(_lastPress != 255) renderItem(_lastPress);
	_lastPress = id;
	if(id != 255) renderItem(id, true);
	if(_onDown != NULL) _onDown((_page * itemsPerPage) + id);
}

void Menu::renderItem(byte id, bool pressed) {
	byte c = 0;
	UIButton * b = _buttons;
	while(b != NULL && c < id) {
		c++;
		b = b->next;
	}
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
	_tft.print(_items[(_page * itemsPerPage) + id], b->x + _itemPadding, b->y + _itemPadding);
}

UIButton * Menu::getButtons() {
	return _buttons;
}
