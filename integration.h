#include "integration.c"
double integrateLSum(double (*)(double), int, double, double);
double integrateSim(double (*)(double ), int, double, double);
double integrateSim_AST(Node *, int, double, double);