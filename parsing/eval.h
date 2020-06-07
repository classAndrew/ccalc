#ifndef EVAL_H__
#define EVAL_H__
#include <stdio.h>
#include <math.h>
#include "../utils/variables.c"
#include "lexer.h"
#include "parser.h"
#include <string.h>
extern Vars *progvars;
double evaluate(Node*);
void free_tree(Node*);
#include "eval.c"
#endif