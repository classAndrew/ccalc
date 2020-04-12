#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "../utils/vector.c"
#include<math.h>
#include<stdlib.h>

#define nodealloc() (Nodep) malloc(sizeof(struct node))
#define token_alloc() (token_p) malloc(sizeof(struct token))

// Operations Enum
enum {ADD, SUB, MUL, DIV};
// Token type enum
enum {NUM, OP, BRACKET, VAR, FUNC};

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

// Tokenize a string.
Token* tokenize(char* str) {
    int size = strlen(str);
    int i = 0, j = 0;
    Token* tokens = (Token*) calloc(100, sizeof(Token));
    for(; i < size; i++) {
        if (str[i] == '(' || str[i] == ')') {
            tokens[j].token_type = BRACKET;
            tokens[j].token_val.symbol = str[i];
            j++;
        }
        else if (isdigit(str[i]) || str[i] == '.') {
            //char c = 0;
            Vector* v = (Vector* )malloc(sizeof(Vector));
            init_vec(v);
            while ((isdigit(str[i]) || str[i] == '.') && i < size) {
                char *c = (char*)malloc(sizeof (char));
                *c = str[i];
                add_to_vec(v, c);
                i++;
            }
            i--;
            char buff[v->len+1];
            for (int m = 0; m < v->len; m++) buff[m] = *(char* )get_at_vec(v, m);
            buff[v->len] = '\0';
            double num = strtod(buff, '\0');
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
    }
}

// This currently only works for single digits and addition
// Parses tokenarray to node AST
Nodep parse(char* str, int *ip) {
    Nodep root = nodealloc();
    while (str[*ip] != '\0') {
        if (str[*ip] == '(') {
            (*ip)++;
            if (root->left == NULL)
                root->left = parse(str, ip);
            else {
                root->right = parse(str, ip);
            }
        } else if (str[*ip] == ')') {
            return root;
        } else if (isdigit(str[*ip])) {
            if (root->left == NULL) {
                root->left = nodealloc();
                root->left->val = str[*ip]-'0';
            } else {
                root->right = nodealloc();
                root->right->val = str[*ip]-'0';
            }
        } else if (str[*ip] == '+') {
            root->optype = ADD;
        }
        (*ip)++;
    }
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