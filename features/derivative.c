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
    if (!n) {
        return te_eval(node);
    }
    else if (n == 1) {
        return dy_dx_xp(node, x);
    }
    double prev_y = dny_dxn_xp(node, n-1, x);
    *x += dx;
    double prev_dy = dny_dxn_xp(node, n-1, x);
    *x -= dx;
    return (prev_dy-prev_y)/dx;
}

// Points will be a 26 element array. Order will determine the order in which they are evaluated,
// So order = {y,x,z} will be df/dydxdz
// For computing df/dxdy, dx will be seen as another function with respect to dy
// so whatever df/dx at (a, b) and (a+dx, b) and then at (a, b+dx) (a+dx, b+dx) and then their difference
// Computing df/dxdydz involves computing df/dxdy first and then taking it's difference along z+dx
// ((a, b, z)-(a+dx, b, z)-(a, b+dx, z)-(a+dx, b+dx, z)) - ((a, b, z+dx)-(a+dx, b, z+dx)-(a, b+dx, z+dx)-(a+dx, b+dx, z+dx))
double partial_at(te_expr *expr, double **point, char *order) {
    // These will have the values mapped to each variable as they are held fixed
    if (*order == '\0') {
        return te_eval(expr);
    }
    *point[*order-'a'] += dx;
    double prev2 = partial_at(expr, point, order+1);
    *point[*order-'a'] -= dx;
    double prev1 = partial_at(expr, point, order+1);
    return (prev2-prev1)/dx;
}
    
double partial_wrapper(char **argv, int argc) {
    double var_addrs[26] = {1.0}; // just one-initialize everything for now. this is point (1, 1, 1...)
    double *addresses[argc-2];
    te_variable vars[argc-2];
    char order[argc-1];
    int i = 0;
    for (int i = 0; i < argc; i++) { // work on later
        vars[i].name = *p;
        addresses[i] = &var_addrs['z'-(**p)];
        vars[i].address = addresses[i];
        order[i] = **p;
    }
    order[i] = '\0';
    te_expr *expr = te_compile(argv[2], vars, argc-2, NULL);
    double val = partial_at(expr, addresses, order);
    te_free(expr);
    return val;
}