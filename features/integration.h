#ifndef INTEG_H__
#define INTEG_H__
#include "../parsing/parser.h"
#include "../parsing/eval.h"
#include "../parsing/tinyexpr.h"

double integrateLSum(double (*)(double), int, double, double);
double integrateSim(double (*)(double ), int, double, double);
double integrateSim_AST(char *, int, double, double);
// Multivariable Iterated Integral
double mulvar_iint(char *, int, char*, const char **);

#endif