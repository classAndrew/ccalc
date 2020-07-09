#include "derivative.h"

double dy_dx_xp(te_expr *node, double *x) {
    double y = te_eval(node);
    *x += dx;
    double dy = te_eval(node);
    *x -= dx;
    //printf("%f %f\n", *x, dy-y);
    return (dy-y)/dx;
}

// This is to compute the nth derivative at x
// Really, the 2nd derivative is just the limit difference quotient of the first.
// The third derivative is the limit difference quotient of the second, and so on...
double dny_dxn_xp(te_expr *node, int n, double *x) {
    // First derivative
    if (n == 1) {
        return dy_dx_xp(node, x);
    }
    double prev_y = dny_dxn_xp(node, n-1, x);
    *x += dx;
    double prev_dy = dny_dxn_xp(node, n-1, x);
    *x -= dx;
    return (prev_dy-prev_y)/dx;
}