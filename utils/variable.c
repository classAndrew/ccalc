#include "variable.h"
#include <ctype.h>
char var_allowmap[charsize] = {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1};
// Variable count of an expression
int var_count(const char *expr) {
    int count = var_allowmap[25-'z'+expr[0]] && !isalnum(expr[1]);
    char val;
    for (int i = 1;;i++) {
       
        if (expr[i+1] == '\0') {
            count += var_allowmap[25-'z'+expr[0]] && !isalnum(expr[i-1]);
            break;
        }
        else if (!isalnum(expr[i-1]) && !isalnum(expr[i+1])) {
            count++;
        }

    }
    return count;
}