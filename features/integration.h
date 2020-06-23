#ifndef INTEG_H__
#define INTEG_H__
#include "../parsing/parser.h"
#include "../parsing/eval.h"
#include "../utils/variable.h"
#include "../parsing/tinyexpr.h"
extern Vars *progvars;
double integrateLSum(double (*)(double), int, double, double);
double integrateSim(double (*)(double ), int, double, double);
double integrateSim_AST(char *, int, double, double);

#endif