#include <stdio.h>
#include "utils/vector.h"
#include <limits.h>
//#include<string.h>
#include "./parsing/eval.h"
#include "./features/integration.h"
#include "./utils/filehandler.h"
#include "./utils/hashmap.h"

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
            Vector *toks = tokenize(argv[2]);
            Node* t = expr(toks, 0);
            printf("%f\n", evaluate(t));
        }
        else if (!strcmp(argv[1], "int_function")) {
            Vector *toks = tokenize(argv[2]);
            Node* t = expr(toks, 0);
            // n, a, b
            double result = integrateSim_AST(t, atoi(argv[3]), strtod(argv[4],0), strtod(argv[5],0));
            printf("%f\n", result);
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