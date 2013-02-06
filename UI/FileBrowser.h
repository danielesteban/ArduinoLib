/*
    FileBrowser.h - Library for FileBrowsing UI.
    Created by Daniel Esteban, February 6, 2013.
    Released into the public domain.
*/

#ifndef FileBrowser_h
#define FileBrowser_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <stdlib.h>
#include <WProgram.h>
#endif
#include <Menu.h>
#include <Directory.h>
#include "UI.h"
#include "Menu.h"

class FileBrowser : public UI {
    public:
        FileBrowser(String title, const char * path, StringCallback callback);
        ~FileBrowser();
        void render(UTFT tft);
    private:
        byte _page;
        String _title;
        String _filename;
        Menu * _menu;
        StringCallback _callback;
        Directory * _dir;
        static const byte _numFilenames = 6;
        String _filenames[6];
        void onDown(byte id);
        void onClick(byte id);
};
 
#endif
