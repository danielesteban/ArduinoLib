/*
    Directory.h - Library for listing directories and handle files with the SD library.
    Created by Daniel Esteban, December 23, 2012.
    Released into the public domain.
*/

#ifndef Directory_h
#define Directory_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <stdlib.h>
#include <WProgram.h>
#endif

typedef struct file {
    char name[12];
    bool isDirectory;
    long size;
    struct file * next;
} file;

file * getDirectory(const char * path, const bool filesOnly = true) {
    File dir = SD.open(path),
        entry;

    file * files = NULL,
        * lastFile;
    
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
    }
    dir.close();
    return files;
}

void freeDirectory(file * directory) {
    while(directory != NULL) {
        file * next = directory->next;
        free(directory);
        directory = next;
    }
}
 
#endif
