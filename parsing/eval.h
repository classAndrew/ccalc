#ifndef EVAL_H__
#define EVAL_H__
#include <stdio.h>
#include <math.h>
#include "../utils/variable.h"
#include "lexer.h"
#include "parser.h"
#include <string.h>
extern Vars *progvars;
double evaluate(Node*);
void free_tree(Node*);
#endif