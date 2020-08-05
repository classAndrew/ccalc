#ifndef EVAL_H__
#define EVAL_H__
#include <stdio.h>
#include <math.h>
#include "lexer.h"
#include "parser.h"
#include <string.h>

double evaluate(Node*);
void free_tree(Node*);
#endif