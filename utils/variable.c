#include "variable.h"

void var_init(Vars *v) {
    v->size = DEFAULTSIZE;
    v->table = (te_variable**) malloc(sizeof(te_variable*)*DEFAULTSIZE);
}

void var_set(Vars *v, char *key, double *val) {
    if (v->table[*key] == NULL) {
        te_variable *var = (te_variable*) malloc(sizeof(te_variable));
        var->address = val;
        var->name = key;
        v->table[*key] = var;
    } else {
        v->table[*key]->address = val;
    }
}