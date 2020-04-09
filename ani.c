#include<stdio.h>
#include<math.h>
#include<limits.h>
#include "integration.h"
#include<stdlib.h>

double f(double x);

// prgrmname n a b
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fputs("Insufficient Arguments!\n", stderr);
        exit(-1);
    }
    printf("%20.20f\n", integrateSim(&f, atoi(argv[1]), atoi(argv[2]), atoi(argv[3])));

}

double f(double x) {
    return pow(2.7182818284590452, x);
}
// LEFT SUM
