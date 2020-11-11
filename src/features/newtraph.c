#include "newtraph.h"
int find_zeroes(double* zeros, char *expression) { 
    double x_0 = 1;
    te_variable vars[] = {{"x", &x_0}};
    te_expr *t = te_compile(expression, vars, 1, NULL);
    double fox, fpx;
    int ind = 0;
    for (int j = -10; j < 10; j++) {
        x_0 = j;
        for (int i = 0; i < 100; i++) {
            fox = te_eval(t);
            fpx = dy_dx_xp(t, &x_0);
            if (fpx < 0.001 && fpx > -0.001) {
                goto skip;
            } 
            x_0 = x_0 - fox/fpx;
        }
        if ((zeros[ind-1] - x_0 > 0.001 || zeros[ind-1] - x_0 < -0.001) && (fox < 0.001 && fox > -0.001)) {
            zeros[ind++] = x_0;
        }
        skip:
            continue;   
    }
    return ind;
}