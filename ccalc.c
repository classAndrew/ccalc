#include <stdio.h>
#include "utils/vector.h"
#include <limits.h>
//#include<string.h>
#include "./parsing/eval.h"
#include "integration.h"

double f(double x);
Vars *progvars;
// prgrmname n a b
int main(int argc, char *argv[]) {
    progvars = (Vars *) malloc(sizeof(Vars));
    var_init(progvars);
    if (argc >= 2) {
        if (strcmp(argv[1], "integrate") == 0) {
            printf("%20.20f\n", integrateSim(&f, atoi(argv[2]), atoi(argv[3]), atoi(argv[4])));
        }
        else if (strcmp(argv[1], "eval") == 0) {
            Vector *toks = tokenize(argv[2]);
            Node* t = expr(toks, 0);
            printf("%f\n", evaluate(t));
        }
        else if (strcmp(argv[1], "function") == 0) {
            Vector *toks = tokenize(argv[2]);
            Node* t = expr(toks, 0);
            // n, a, b
            double result = integrateSim_AST(t, atoi(argv[3]), strtod(argv[4],0), strtod(argv[5],0));
            printf("%f\n", result);
        }
        else if (strcmp(argv[1], "test") == 0) {
            double val = 1.5;
            var_add(progvars, 't', 1);
            Vector *toks = tokenize("t+t");
            Node* t = expr(toks, 0);
            printf("%f\n", evaluate(t));
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

double f(double x) {
    return pow(2.7182818284590452, x);
}
