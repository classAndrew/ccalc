#include <stdio.h>
#include "utils/vector.h"
#include <limits.h>
//#include<string.h>
#include "features/integration.h"
#include "utils/filehandler.h"
#include "parsing/tinyexpr.h"
#include "utils/hashmap.h"
#include "features/derivative.h"
#include "features/series.h"
#include "features/newtraph.h"
#include "features/series.h"
#include "utils/variable.h"

int main(int argc, char *argv[]) {

    if (argc >= 2) {
        if (!strcmp(argv[1], "eval")) {
            te_expr *expr = te_compile(argv[2], NULL, 0, NULL);
            printf("%f\n", te_eval(expr));
            te_free(expr);
        }
        else if (!strcmp(argv[1], "int_function")) {
            // Single Variable Integration
            double result = integrateSim_AST(argv[2], atoi(argv[3]), strtod(argv[4],0), strtod(argv[5],0));
            printf("%f\n", result);
        }
        else if (!strcmp(argv[1], "newt")) {
            // Newton's Method
            double *zeros = (double*) calloc(100, sizeof(double));
            int ind = find_zeroes(zeros, argv[2]);
            for (int i = 0; i < ind; i++) {
                printf("%f\n", zeros[i]);
            }
        }
        else if (!strcmp(argv[1], "n_diff")) {
            double starting = strtod(argv[4], NULL);
            te_variable vars[] = {{"x", &starting}};
            te_expr *expr = te_compile(argv[2], vars, 1, NULL);
            printf("%f\n", dny_dxn_xp(expr, atoi(argv[3]), &starting));
            te_free(expr);
        }
        else if (!strcmp(argv[1], "run_file")) {
            freadhm(argv[2], NULL);
        }
        else if (!strcmp(argv[1], "taylor")) {
            double a = 0;
            int terms = atoi(argv[3]);
            te_variable vars[] = {{"x", &a}};
            te_expr *expr = te_compile(argv[2], vars, terms, NULL);
            double *coe = gen_taylor_coe(expr, terms, &a);
            printf("This is currently a buggy feature.\n");
            for (int i = 0; i < terms; i++) {
                printf("%0.3f*x^%d%c", coe[i], i, (i != terms-1) ? '+' : 0);
            }
            printf("\n");
            te_free(expr);
        }
        else if (!strcmp(argv[1], "test")) {
            double d = 10;
            const te_variable v = {{"x", &d}};
            printf("%f\n", te_eval(te_compile("300", &v, 1, NULL)));
        }
        else {
            fputs("Unknown Command! See ccalc help.\n", stderr);
            exit(-1);
        }
    }
    else {
        fputs("Invalid Arguments\n", stderr);
        exit(-1);
    }
}