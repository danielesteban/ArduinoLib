/*
    Directory.cpp - Library for listing directories and handle files with the SD library.
    Created by Daniel Esteban, December 23, 2012.
    Released into the public domain.
*/

#include "Directory.h"

Directory::Directory(const char * path, const bool filesOnly) {
	File dir = SD.open(path),
	    entry;

	files = NULL;
	file * lastFile;

	while(entry = dir.openNextFile()) {
	    if(filesOnly && entry.isDirectory()) continue;
	    file * f = (file *) malloc(sizeof(file));
	    strcpy(f->name, entry.name());
	    f->isDirectory = entry.isDirectory();
	    !f->isDirectory && (f->size = entry.size());
	    f->next = NULL;
	    if(files == NULL) files = lastFile = f;
	    else {
	        lastFile->next = f;
	        lastFile = f;
	    }
	    entry.close();
	}
	dir.close();
}

Directory::~Directory() {
    while(files != NULL) {
        file * next = files->next;
        free(files);
        files = next;
    }
}

file * Directory::getFiles() {
    return files;
}
