#ifndef VARI_H__
#define VARI_H__
#include <stdlib.h>
#define DEFAULTSIZE 256

typedef struct {
    int size;
    double *table;
} Vars;

void var_add(Vars*, char, double);
double var_get(Vars*, char);
double var_init(Vars*);
#endif