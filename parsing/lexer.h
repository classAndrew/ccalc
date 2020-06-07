#ifndef LEX_H__
#define LEX_H__
#include <ctype.h>
// Operations Enum
enum {NONE, ADD, SUB, MUL, DIV};
// Token type enum
enum {NUM, OP, BRACKET, VAR, FUNC, COMMA};

static char nterm = '\0';

typedef struct {
    char token_type;
    union {
        char symbol; // Brackets and variables
        double var_val; // Variable / Numerical value
        char *var_name;
        char *funcname;
        char operator;
    } token_val;
} Token;

int isOperator(char);
void print_tok(Token*);
Vector *tokenize(char*);
#include "lexer.c"
#endif