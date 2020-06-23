#include <stdio.h>
#include "utils/vector.h"
#include <limits.h>
//#include<string.h>
#include "./features/integration.h"
#include "./utils/filehandler.h"
#include "./parsing/tinyexpr.h"
#include "./utils/hashmap.h"
#include "./features/derivative.h"
#include "./features/newtraph.h"

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