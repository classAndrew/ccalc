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

double mulvar_iint(char * expr, int varc, char *varnames, char **bounds) {
    te_variable vars[varc];
    double vec[varc];
    double *at_d[varc]; 
    char name_ps[2][varc];
    te_expr *bounds_ex[varc*2];
    for (int i = 0; i < varc; i++) {
        name_ps[i][0] = varnames[i];
        name_ps[i][1] = '\0';
        at_d[i] = &vec[i];
        
        te_variable v = {name_ps[i],at_d[i]};

        vars[i] = v; 
        // Each bound will have to be its own expression. The eval of each expr stored in at_d
        bounds_ex[i*2] = te_compile(bounds[i*2], vars, varc, NULL);
        bounds_ex[i*2+1] = te_compile(bounds[i*2+1], vars, varc, NULL);
    }
    
    te_expr *f = te_compile(expr, vars, varc, NULL);
    double value = mulvar_iint_h(f, at_d, bounds_ex, 0, varc);
    // free memory
    for (int i = 0; i < varc; i++) {
        te_free(bounds_ex[i*2]);
        te_free(bounds_ex[i*2+1]);
    }
    te_free(f);
    return value;
}
// Caller will set x, y, z vector in vf. f must be compiled with that vec too.
double mulvar_iint_h(te_expr* f, double *vf[], te_expr *bounds[], int i, int varc) {
    double sum = 0;
    *vf[i] = te_eval(bounds[i*2]);
    double b = te_eval(bounds[i*2+1]);
    double deltx = (b-*vf[i])/MUL_VAR_N;
    if (i == varc-1) {
        for (; fabs(*vf[i]-b) >= 1.0/MUL_VAR_N; *vf[i]+=deltx) { // abs is needed to add "backwards" for integrating 3->c for c < 3
            sum += te_eval(f);
        }
        return sum*deltx;
    } 
    for (; fabs(*vf[i]-b) >= 1.0/MUL_VAR_N; *vf[i]+=deltx) {
        sum += mulvar_iint_h(f, vf, bounds, i+1, varc);
    }
    return sum*deltx;
}