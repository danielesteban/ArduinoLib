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
#include <SD.h>    

typedef struct file {
    char name[12];
    bool isDirectory;
    long size;
    struct file * next;
} file;

class Directory {
    public:
        Directory(const char * path, const bool filesOnly = true);
        ~Directory();
        file * getFiles();
    private:
        file * files;
};
 
#endif
