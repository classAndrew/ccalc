#ifndef DERIV_H__
#define DERIV_H__
#include "../parsing/parser.h"
#include "../parsing/eval.h"
#include "../parsing/tinyexpr.h"
#include "../utils/variable.h"
#define dx 0.0001
extern Vars *progvars;
double dy_dx_xp(te_expr*, double*);
#endif