/*
    Menu.cpp - Library for graphical menus.
    Created by Daniel Esteban, December 23, 2012.
    Released into the public domain.
*/

#include "Menu.h"

const byte itemsPerPage = 6,
	menuPadding = 20,
	itemMargin = 10;

Menu::Menu(byte numItems, char * items[], TouchEvent onClick, TouchEvent onDown) : UI(onClick, onDown) {
	_numItems = numItems;
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
		itemHeight = (tft.getDisplayYSize() - (menuPadding * 2) - (itemMargin * (itemsPerPage - 1))) / itemsPerPage;
	
	const byte itemPadding = (itemHeight - 10) / 2;
	page = _page;

	tft.clrScr();
	tft.setBackColor(255, 255, 255);
	UIButton * b = _buttons;
	while(b != NULL) {
		b->width = itemWidth;
		b->height = itemHeight;
		if(x < offset || x >= to) b->x = b->y = -1;
		else {
			tft.setColor(255, 255, 255);
			int y = menuPadding + ((x - offset) * (itemHeight + itemMargin));
			tft.fillRoundRect(menuPadding, y, menuPadding + itemWidth, y + itemHeight);
			tft.setColor(0, 0, 0);
			tft.print(b->label, menuPadding + itemPadding, y + itemPadding);
			b->x = menuPadding;
			b->y = y;
		}
		b = b->next;
		x++;
	}
}
