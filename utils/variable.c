#include "variable.h"
#include <stdlib.h>
#include <ctype.h>
const char var_allowmap[charsize] = {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1};
// Variable count of an expression
int var_count(const char *expr, char **variables) {
    int count = var_allowmap[25-'z'+expr[0]] && !isalnum(expr[1]);
    // Due to order, all differentials will be placed alphabetically.
    char which[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    which[25-'z'+expr[0]] = count;
    char val;
    for (int i = 1;;i++) {
       
        if (expr[i+1] == '\0') {
            count += var_allowmap[25-'z'+expr[i]] && !isalnum(expr[i-1]);
            which[25-'z'+expr[i]] = 1;
            break;
        }
        else if (!isalnum(expr[i-1]) && !isalnum(expr[i+1])) {
            which[25-'z'+expr[i]] = 1;
            count++;
        }

    }
    *variables = (char *) malloc(sizeof(char)*count);
    for (int i = 0, j = 0; i < charsize; i++) {
        if (which[i]) {
            (*variables)[j++] = i-25+'z';
        }
    }
    return count;
}