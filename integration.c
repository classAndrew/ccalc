#include "./parsing/eval.c"

extern Vars *progvars;
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

double integrateSim_AST(Node *node, int n, double a, double b) {
    double sum = 0;
    var_add(progvars, 'x', a);
    sum += evaluate(node);
    var_add(progvars, 'x', b);
    sum += evaluate(node);
    double deltax = (b-a)/n;
    int i = 0;
    while ((a += deltax) < b) {
        var_add(progvars, 'x', a);
        sum += evaluate(node)*((++i)&1 ? 2 : 1);
    }
    return sum*deltax*(2.0/3);
}