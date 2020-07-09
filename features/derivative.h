#ifndef DERIV_H__
#define DERIV_H__
#include "../parsing/parser.h"
#include "../parsing/eval.h"
#include "../parsing/tinyexpr.h"
#include "../utils/variable.h"
#define dx 9.765625E-4
extern Vars *progvars;
double dy_dx_xp(te_expr*, double*);
double dny_dxn_xp(te_expr*, int n, double*);
#endif