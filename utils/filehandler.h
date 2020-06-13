#ifndef FILHDN_H__
#define FILHDN_H__
#include <stdio.h>
#include "hashmap.h"
// read into hashmap. path, mapptr, 
void freadhm(char*, HashMap*);
void fwritehm(char*, HashMap*);
#endif