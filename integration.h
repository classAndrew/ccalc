#ifndef INTEG_H__
#define INTEG_H__
#include "./parsing/parser.h"
double integrateLSum(double (*)(double), int, double, double);
double integrateSim(double (*)(double ), int, double, double);
double integrateSim_AST(Node *, int, double, double);
#include "integration.c"
#endif