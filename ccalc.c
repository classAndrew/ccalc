#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<string.h>
#include "integration.h"
#include "parsing/parser.c"
#include<stdlib.h>

double f(double x);

// prgrmname n a b
int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (strcmp(argv[1],"integrate") == 0) {
            printf("%20.20f\n", integrateSim(&f, atoi(argv[2]), atoi(argv[3]), atoi(argv[4])));
        } 
        else if (strcmp(argv[1],"eval") == 0) {
            int ind = 0;
            Nodep n = parse("3+(4+9)", &ind);
            printf("%f\n", n->left->val);
            printf("%f\n", n->right->right->val);
            printf("%f\n", eval(n));
            //printf("%d\n", n->optype);
        } 
        else {
            fputs("Unknown Command! See ccalc help.\n", stderr);
            exit(-1);
        }
    } else {
        fputs("Invalid Arguments\n", stderr);
        exit(-1);
    }

}

double f(double x) {
    return pow(2.7182818284590452, x);
}
// LEFT SUM
