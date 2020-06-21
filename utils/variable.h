#ifndef VARI_H__
#define VARI_H__
#include <stdlib.h>
#include "../parsing/tinyexpr.h"
#define DEFAULTSIZE 256

typedef struct {
    int size;
    te_variable **table;
} Vars;

void var_init(Vars*);
void var_set(Vars*, char*, double*);
#endif