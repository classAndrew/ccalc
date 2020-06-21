#include <stdio.h>
#include "utils/vector.h"
#include <limits.h>
//#include<string.h>
// #include "./features/integration.h"
#include "./utils/filehandler.h"
#include "./parsing/tinyexpr.h"
#include "./utils/hashmap.h"
#include "./features/derivative.h"

Vars *progvars;
HashMap *hm;
// prgrmname n a b
int main(int argc, char *argv[]) {
    progvars = (Vars *) malloc(sizeof(Vars));
    hm = (HashMap *) malloc(sizeof(HashMap));
    hm_init(hm);
    var_init(progvars);
    if (argc >= 2) {
        if (!strcmp(argv[1], "eval")) {
            // Vector *toks = tokenize(argv[2]);
            // // for (int i = 0; i < toks->count; i++) print_tok(vector_get(toks, i));
            // Node* t = expr(toks, 0);
            // // fail case (1-3)*(1-1)*(1-4)
            // //printf("%f\n", t->node_u.optree.right->node_u.optree.right->val);
            // printf("%f\n", evaluate(t));
        }
        else if (!strcmp(argv[1], "int_function")) {
            // Vector *toks = tokenize(argv[2]);
            // Node* t = expr(toks, 0);
            // // n, a, b
            // double result = integrateSim_AST(t, atoi(argv[3]), strtod(argv[4],0), strtod(argv[5],0));
            // printf("%f\n", result);
        }
        else if (!strcmp(argv[1], "newt")) {
            // Newton's Method
            double x_0;
            te_variable vars[] = {{"x", &x_0}};
            te_expr *t = te_compile(argv[2], vars, progvars->size, NULL);
            double *zeros = (double*) calloc(100, sizeof(double));
            int ind = 0;
            for (int j = -4; j < 5; j++) {
                x_0 = j;
                double fox, fpx;
                for (int i = 0; i < 100; i++) {
                    fox = te_eval(t);
                    fpx = dy_dx_xp(t, &x_0);
                    if (fpx < 0.1 || fpx > -0.1) {
                        printf("SKIPPED\n");
                        goto skip;
                    } 
                    x_0 = x_0 - fox/fpx;
                }
                printf("%f\n", x_0);
                if (zeros[ind-1] - x_0 > 0.01 || zeros[ind-1] - x_0 < -0.01) {
                    zeros[ind++] = x_0;
                }
                skip:
                    continue;   
            }
            printf("%d\n", ind);
            for (int i = 0; i < ind; i++) {
                printf("%f\n", zeros[i]);
            }
        }
        else if (!strcmp(argv[1], "run_file")) {
            freadhm(argv[2], NULL);
        }
        else if (!strcmp(argv[1], "test")) {
            //hm_insert()
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