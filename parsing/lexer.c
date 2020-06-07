#include "../utils/vector.h"

Vector* tokenize(char* expr) {
    int i = 0;
    Vector* vec = (Vector* )malloc(sizeof(Vector)); // Vector of tokens
    vector_init(vec);
    while (expr[i] != '\0') {
        if (isdigit(expr[i]) || expr[i] == '.') {
            Vector* buf = (Vector* )malloc(sizeof(Vector));
            vector_init(buf);
            while (expr[i] != '\0' && (isdigit(expr[i]) || expr[i] == '.')) {
                vector_add(buf, expr+i); // This may be an issue. if so, malloc separate char
                ++i;
            }
            --i;
            char* str = vector_tostr(buf);
            Token* t = (Token* ) malloc(sizeof(Token));
            t->token_type = NUM;
            t->token_val.var_val = strtod(str, 0);
            vector_add(vec, t);
            //free(buf);
            //free(str);
        }
        else if (isalpha(expr[i])) {
            Vector* buf = (Vector* )malloc(sizeof(Vector));
            vector_init(buf);
            while (expr[i] != '\0' && isalpha(expr[i])){
                vector_add(buf, &expr[i]);
                ++i;
            }
            Token* t = (Token* ) malloc(sizeof(Token));
            if (expr[i] != '(') {
                t->token_type = VAR;
                t->token_val.var_name = vector_tostr(buf);
            } else {
                t->token_type = FUNC;
                t->token_val.funcname = vector_tostr(buf);
            }
            vector_add(vec, t);
            --i;
            //free(buf);
        }
        else if (isOperator(expr[i])) {
            Token* t = (Token* ) malloc(sizeof(Token));
            t->token_type = OP;
            t->token_val.operator = expr[i];
            vector_add(vec, t);
        }
        else if (expr[i] == ')' || expr[i] == '(' || expr[i] == ',') {
            Token* t = (Token* ) malloc(sizeof(Token));
            t->token_type = BRACKET;
            t->token_val.symbol = expr[i];
            vector_add(vec, t);
        }
        else {
            printf("Invalid Token\n");
            exit(-1);
        }
        ++i;
    }
    return vec;
}


void print_tokens(Vector* tokens) {
    for (int i = 0; i < vector_count(tokens); i++) {
        print_tok((Token* )vector_get(tokens, i));
    }
}

void print_tok(Token* t) {
    int type = (t)->token_type;
    if (type == NUM)
        printf("%f\n", (t)->token_val.var_val);
    if (type == OP)
        printf("%c\n", (t)->token_val.operator);
    if (type == FUNC)
        printf("%s\n", (t)->token_val.funcname);
    if (type == BRACKET)
        printf("%c\n", (t)->token_val.symbol);
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}