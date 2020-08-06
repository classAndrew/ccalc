#ifndef INTEG_H__
#define INTEG_H__
#include "../parsing/parser.h"
#include "../parsing/eval.h"
#include "../parsing/tinyexpr.h"
#define MUL_VAR_N 100;

double integrateLSum(double (*)(double), int, double, double);
double integrateSim(double (*)(double ), int, double, double);
double integrateSim_AST(char *, int, double, double);
// Multivariable Iterated Integral
double mulvar_iint(char *, int, char*, char **);
double mulvar_iint_h(te_expr* f, double *vf[], te_expr *bounds[], int i, int varc);

#endif