#ifndef PARSE_H__
#define PARSE_H__
#include "lexer.h"
#include <stdlib.h>
enum {FUNCTREE, VALUE, OPTREE, VARIABLE};
typedef struct node_s {

    char type;
    union {
        struct {
            char* func;
            Vector* func_args;
        } functree;
        struct {
            struct node_s *right;
            struct node_s *left;
            char operator;
        } optree;
    } node_u;
    double val;
    char *var_name;
    int sign;
} Node;

Node *nud(Vector*, Token*);
int greaterBinding(Token*, int);
int getBinding(Token*);
Node *expr(Vector*, int);
Node *led(Node*, Token*, Vector*);
#endif
