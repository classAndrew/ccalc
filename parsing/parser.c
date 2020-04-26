#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "../utils/vector.c"
#include<math.h>
#include<stdlib.h>

#define nodealloc() (Nodep) malloc(sizeof(struct node))
#define token_alloc() (Token* ) malloc(sizeof(struct Token))
#define MAXEXPRSIZE 1000

// Operations Enum
enum {NONE, ADD, SUB, MUL, DIV};
// Token type enum
enum {NONE, NUM, OP, BRACKET, VAR, FUNC};

struct node {
    struct node* left;
    struct node* right;
    char optype;
    double val;
};
typedef struct {
    char token_type;
    union {
        char symbol; // Brackets and variables
        double var_val; // Variable / Numerical value
        char operator; // Operator
    } token_val;
} Token;

typedef struct node* Nodep;

Nodep parse_str(char*);
Nodep parse(Token*, int*);

// Tokenize a string.
Token* tokenize(char* str) {
    int size = strlen(str);
    int i = 0, j = 0;
    Token* tokens = (Token*) calloc(MAXEXPRSIZE, sizeof(Token));
    for(; i < size; i++) {
        if (str[i] == '(' || str[i] == ')') {
            tokens[j].token_type = BRACKET;
            tokens[j].token_val.symbol = str[i];
            j++;
        }
        else if (isdigit(str[i]) || str[i] == '.') {
            //char c = 0;
            Vector* v = (Vector* )malloc(sizeof(Vector));
            init_vec(v); // Instantiate a vector
            while ((isdigit(str[i]) || str[i] == '.') && i < size) {
                char *c = (char*)malloc(sizeof (char));
                *c = str[i];
                add_to_vec(v, c);
                i++;
            }
            i--;
            char buff[v->len+1];
            for (int m = 0; m < v->len; m++) buff[m] = *(char* )get_at_vec(v, m); // Turn char vec to array
            buff[v->len] = '\0';
            double num = strtod(buff, '\0'); // String to doubles
            tokens[j].token_type = NUM;
            tokens[j].token_val.var_val = num;
            j++;
            free(v->data); // Free memory
        }
        else if (str[i] == '+') {
            tokens[j].token_type = OP;
            tokens[j].token_val.operator = '+';
            j++;
        }
    }
    return tokens;
}

// For Debugging / Testing purposes
void print_tokens(Token* tokens, int size) {
    //printf("%f\n", tokens[0].var_val);
    for (int i = 0; i < size; i++) {
        //printf("%d\n", tokens[i].token_type);
        if (tokens[i].token_type == NUM) printf("%f\n", tokens[i].token_val.var_val);
        else if (tokens[i].token_type == OP) printf("%c\n", tokens[i].token_val.operator);
        else if (tokens[i].token_type == BRACKET) printf("%c\n", tokens[i].token_val.symbol);
    }
}

Nodep parse_str(char* str) {
    int t = 0;
    return parse(tokenize(str), &t);
}



// Parses tokenarray to node AST
Nodep parse(Token *str, int *ip) {
    Nodep root = nodealloc();
    while (str[*ip].token_type != NONE) {
        if (str[*ip].token_val.symbol == '(') {
            (*ip)++;
            if (root->left == NULL)
                root->left = parse(str, ip);
            else {
                root->right = parse(str, ip);
            }
        } else if (str[*ip].token_val.symbol == ')') {
            return root;
        } else if (str[*ip].token_type == NUM) {
            if (root->left == NULL) {
                root->left = nodealloc();
                root->left->val = str[*ip].token_val.var_val;
            } else {
                root->right = nodealloc();
                root->right->val = str[*ip].token_val.var_val;
            }
        } else if (str[*ip].token_val.symbol == '+') {
            root->optype = ADD;
        }
        (*ip)++;
    }
    free(str);
    return root;
}
// Tree evaluation
double eval(Nodep root) {
    double a, b = 0;
    if (root->left != NULL) {
        a = eval(root->left);
    } 
    if (root->right != NULL) {
        b = eval(root->right);
    }
    if (root->right == NULL && root->left==NULL) return root->val;
    switch(root->optype) {
        case ADD:
        return a + b;
    }
}