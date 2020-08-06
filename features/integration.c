#include "integration.h"

double integrateLSum(double (*f)(double x), int n, double a, double b) {
    double deltax = (b-a)/n;
     double sum = 0;
    for (; a < b; a+=deltax) {
        sum += f(a);
    }
    return sum*deltax;
}

double integrateSim(double (*f)(double x), int n, double a, double b) {
    // 1 4 2 4 2 4 1
    double sum = f(a)+f(b);
    double deltax = (b-a)/n;
    int i = 0;
    while ((a += deltax) < b) {
        sum += f(a)*((++i)&1 ? 2 : 1);
    }
    return sum*deltax*(2.0/3);
}

double integrateSim_AST(char *expr, int n, double a, double b) {
    double sum = 0, old = a;
    te_variable vars[] = {{"x", &a}};
    te_expr *node = te_compile(expr, vars, 1, NULL);
    sum += te_eval(node);
    a = b;
    sum += te_eval(node);
    a = old;
    double deltax = (b-a)/n;
    int i = 0;
    while ((a += deltax) < b) {
        // var_add(progvars, 'x', a);
        sum += te_eval(node)*((++i)&1 ? 2 : 1);
    }
    te_free(node);
    return sum*deltax*(2.0/3);
}

double mulvar_iint(char * expr, int varc, char *varnames, const char **bounds) {
    te_variable vars[varc];
    double at_d[varc]; 
    te_expr bounds[varc*2];

    for (int i = 0; i < varc; i++) {
        char name[] = {varnames[i], '\0'};
        te_variable v = {name,&at_d[i]};
        vars[i] = v; 
        // Each bound will have to be its own expression. The eval of each expr stored in at_d
        bounds[i*2] = te_compile(bounds[i*2], vars, varc, NULL);
        bounds[i*2+1] = te_compile(bounds[i*2+1], vars, varc, NULL);
    }
    for (int i = 0; i < varc; i++) {
        
    }
    return 0;
}

double mulvar_iint_h(te_expr* f );