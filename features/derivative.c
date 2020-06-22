#include "derivative.h"

double dy_dx_xp(te_expr *node, double *x) {
    double y = te_eval(node);
    *x += dx;
    double dy = te_eval(node);
    *x -= dx;
    //printf("%f %f\n", *x, dy-y);
    return (dy-y)/dx;
}