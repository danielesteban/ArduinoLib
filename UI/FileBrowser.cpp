/*
    FileBrowser.cpp - Library for FileBrowsing UI.
    Created by Daniel Esteban, February 6, 2013.
    Released into the public domain.
*/

#include "FileBrowser.h"

FileBrowser::FileBrowser(String title, const char * path, StringCallback callback) : UI() {
	_title = title;
	_filename = path;
	_filename += '/';
	_dir = new Directory(path);
	_callback = callback;
	_page = 0;
	_menu = NULL;
}

FileBrowser::~FileBrowser() {
	delete _menu;
	delete _dir;
}

void FileBrowser::render(UTFT tft) {
	_tft = tft;
	_renderedPage = 255;
}

void FileBrowser::update() {
	if(_page == _renderedPage) return;
	_renderedPage = _page;
	while(_buttons != NULL) {
		UIButton * next = _buttons->next;
		delete _buttons;
		_buttons = next;
	}

	if(_menu != NULL) delete _menu;

	byte count = 0,
		x;

	file * f = _dir->getFiles();
	while(f != NULL && count < (_page + 1) * _numFilenames) { //this is really lame, but i'm kinda tired ;P
	    count++;
	    f = f->next;
	}

	f = _dir->getFiles();
	for(byte x=0; x<_page * (_numFilenames - 1); x++) {
		f = f->next;
		count--;
	}
	count > _numFilenames && (count = _numFilenames);
	for(byte x=0; x<count; x++) {
		_filenames[x] = x == 5 && f->next != NULL ? "More -->>" : f->name;
		f = f->next;
	}

	_menu = new Menu(_title, count, _filenames);	

	_menu->render(_tft);

	UIButton * b = _menu->getButtons();
	while(b != NULL) {
		addButton(b->x, b->y, b->width, b->height);
		b = b->next;
	}
}

void FileBrowser::onDown(byte id) {
	if(_menu != NULL) _menu->onDown(id);
}

void FileBrowser::onClick(byte id) {
	if(_menu != NULL) _menu->onClick(id);
	if(id == 5) {
		_page++;
		return;
	}
	_filename += _filenames[id];
	_callback(_filename);
}
