#include "../utils/vector.c"
#include<string.h>
#include<ctype.h>

// Operations Enum
enum {NONE, ADD, SUB, MUL, DIV};
// Token type enum
enum {NUM, OP, BRACKET, VAR, FUNC, COMMA};

typedef struct node {
    struct node* left;
    struct node* right;
    char optype;
    double val;
} Node;

typedef struct {
    char token_type;
    union {
        char symbol; // Brackets and variables
        double var_val; // Variable / Numerical value
        char *funcname;
        char operator; // Operator
    } token_val;
} Token;
int isOperator(char);
Vector* tokenize(char* expr) {
    int i = 0;
    Vector* vec = (Vector* )malloc(sizeof(Vector)); // Vector of tokens
    init_vec(vec);
    while (expr[i] != '\0') {
        if (isdigit(expr[i]) || expr[i] == '.') {
            Vector* buf = (Vector* )malloc(sizeof(Vector));
            init_vec(buf);
            while (expr[i] != '\0' && (isdigit(expr[i]) || expr[i] == '.')) {
                add_to_vec(buf, expr+i); // This may be an issue. if so, malloc separate char
                ++i;
            }
            --i;
            char nterm = '\0';
            add_to_vec(buf, &nterm);
            char* str = vec_to_str(buf);
            Token* t = (Token* ) malloc(sizeof(Token));
            t->token_type = NUM;
            t->token_val.var_val = strtod(str, 0);
            add_to_vec(vec, t);
            free(buf);
            free(str);
        }
        else if (isalpha(expr[i])) {
            Vector* buf = (Vector* )malloc(sizeof(Vector));
            init_vec(buf);
            while (expr[i] != '\0' && isalpha(expr[i])){
                add_to_vec(buf, &expr[i]);
                ++i;
            }
            --i;
            Token* t = (Token* ) malloc(sizeof(Token));
            t->token_type = FUNC;
            t->token_val.funcname = vec_to_str(buf);
            add_to_vec(vec, t);
            free(buf);
        }
        else if (isOperator(expr[i])) {
            Token* t = (Token* ) malloc(sizeof(Token));
            t->token_type = OP;
            t->token_val.operator = expr[i];
            add_to_vec(vec, t);
        }
        else if (expr[i] == ')' || expr[i] == '(' || expr[i] == ',') {
            Token* t = (Token* ) malloc(sizeof(Token));
            t->token_type = BRACKET;
            t->token_val.symbol = expr[i];
            add_to_vec(vec, t);
        }
        else {
            printf("Invalid Token\n");
            exit(-1);
        }
        ++i;
    }
    return vec;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}