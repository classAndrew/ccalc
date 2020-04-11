#include<stdlib.h>
#include<string.h>
#include<ctype.h>
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

union token {
    char token_type;
    char symbol; // Brackets and variables
    double var_val; // Variable / Numerical value
    char operator; // Operator
};

typedef union token token_p;
typedef struct node* Nodep;

// Tokenize a string
token_p* tokenize(char* str) {
    int size = strlen(str)-1;
    int i = 0;
    token_p* tokens = (token_p*) calloc(size+1, sizeof(union token));
    for(; i < size; i++) {
        switch(str[i]) {
            case '(':
        }
    }
    return tokens;
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