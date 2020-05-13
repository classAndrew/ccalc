#include <stdio.h>
#include <limits.h>
//#include<string.h>
#include <math.h>
#include "integration.h"
//#include "parsing/lexer.c"
#include "parsing/eval.c"

double f(double x);

// prgrmname n a b
int main(int argc, char *argv[]) {

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

        }
        else if (strcmp(argv[1], "test") == 0) {
            //Vector *toks = tokenize("abc(abc(1+20),3+4,7)+5");
            Vector *toks = tokenize("1+2");
            Node* t = expr(toks, 0);
            printf("%f\n", evaluate(t));
            vector_free(toks);
            free_tree(t);
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
