#include "series.h"
#include "derivative.h"
#include <stdlib.h>

// Generate n number of coefficients
double *gen_taylor_coe(te_expr *expr, int n, double *a) {
    double *coe = calloc(n, sizeof(double)); 
    for (int i = 0; i < n; i++) {
        coe[i] = dny_dxn_xp(expr, i, a)/n_fac(i);
    }
    return coe;
}

// Compute the nth factorial
double n_fac(int n) {
    static double lastprod = 1;
    static int lastn = 1;
    if (!n) return 1; // n = 0 so 0! = 1
    if (n < lastn) {
        for (; lastn > n; lastprod /= (lastn--));
    } else {
        for (; lastn < n; lastprod *= (++lastn));
    }
    return lastprod;
}