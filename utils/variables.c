#include <stdlib.h>
#define DEFAULTSIZE 256

typedef struct {
    int size;
    double *table;
} Vars;

void var_add(Vars*, char, double);
double var_get(Vars*, char);
double var_init(Vars*);

double var_init(Vars *v) {
    v->size = DEFAULTSIZE;
    v->table = (double *)malloc(sizeof(double)*DEFAULTSIZE);
}

void var_add(Vars *v, char key, double val) {
    v->table[key] = val;
}

double var_get(Vars *v, char key) {
    return v->table[key];
}