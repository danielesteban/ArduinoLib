/*
    Directory.cpp - Library for listing directories and handle files with the SD library.
    Created by Daniel Esteban, December 23, 2012.
    Released into the public domain.
*/

#include "Directory.h"

Directory::Directory(const char * path, const bool filesOnly, const bool inverted) {
	File dir = SD.open(path),
	    entry;

	_files = NULL;
	file * lastFile;

	while(entry = dir.openNextFile()) {
	    if(filesOnly && entry.isDirectory()) continue;
	    file * f = (file *) malloc(sizeof(file));
	    strcpy(f->name, entry.name());
	    f->isDirectory = entry.isDirectory();
	    !f->isDirectory && (f->size = entry.size());
	    if(inverted) {
	    	f->next = _files;
 			_files = f;
	    } else {
		    f->next = NULL;
		    if(_files == NULL) _files = lastFile = f;
		    else {
		        lastFile->next = f;
		        lastFile = f;
		    }
		}
	    entry.close();
	}
	dir.close();
}

Directory::~Directory() {
    while(_files != NULL) {
        file * next = _files->next;
        free(_files);
        _files = next;
    }
}

file * Directory::getFiles() {
    return _files;
}
