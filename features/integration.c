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
    return sum*deltax*(2.0/3);
}