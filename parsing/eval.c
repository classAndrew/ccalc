#include<stdio.h>
#include <math.h>
#include "lexer.c"
#include "../utils/variables.c"

enum {FUNCTREE, VALUE, OPTREE, VARIABLE};
extern Vars *progvars;
typedef struct node_s {

    char type;
    union {
        struct {
            char* func;
            Vector* func_args;
        } functree;
        struct {
            struct node_s *right;
            struct node_s *left;
            char operator;
        } optree;
    } node_u;
    double val;
    char *var_name;
    int sign;
} Node;

Node *nud(Vector*, Token*);
int greaterBinding(Token*, int);
int getBinding(Token*);
Node *expr(Vector*, int);

Node *nud(Vector *tokens, Token *token) {
    Node *e;
    if (token->token_type == OP && token->token_val.operator == '-') {
        e = (Node *) malloc(sizeof(Node));
        Token *next = ((Token *) vector_pop(tokens, 0));
        if (next->token_type == VAR) {
            e->type = VAR;
            e->sign = -1;
            e->var_name = next->token_val.var_name;
            return e;
        }
        e->type = VALUE;
        e->val = -(next->token_val.var_val);
        return e;
    }
    else if (token->token_type == BRACKET && token->token_val.symbol == '(') {
        e = expr(tokens, 0);
        if (((Token *)vector_get(tokens, 0))->token_val.symbol != ')') {
            printf("NO CLOSING PARANTHESIS");
            return NULL;
        }
        return e;
    }
    else if (token->token_type == FUNC) { //&& strcmp(token->token_val.funcname, "abc") == 0) {
        Vector *funcargs = (Vector *) malloc(sizeof(Vector));
        vector_init(funcargs);
        if (((Token *) vector_pop(tokens, 0))->token_val.symbol != '(') {
            printf("NO PARANTHESIS CLOSING");
            return NULL;
        }
        while (1) {
            Vector *mini_expr = (Vector *) malloc(sizeof(Vector));
            vector_init(mini_expr);
            int i = 0;
            while (vector_count(tokens) > 0) {
                Token *mini_token = (Token *) vector_get(tokens, 0);
                if (mini_token->token_val.symbol == ',' && i == 0) {
                    break;
                } else if (mini_token->token_val.symbol == '(') {
                    ++i;
                } else if(mini_token->token_val.symbol == ')') {
                    if (i == 0) {
                        break;
                    }
                    --i;
                }
                Token *t = (Token*) vector_pop(tokens, 0);
                vector_add(mini_expr, t);
            }
            Node *otherexpr = expr(mini_expr, 0);
            vector_add(funcargs, otherexpr);
            Token *next_token = (Token *) vector_pop(tokens, 0);
            if (next_token->token_val.symbol == ')') {
                break;
            } else if(next_token->token_val.symbol == ',') {
                continue;
            } else {
                printf("INVALID ARGUMENT");
                return NULL;
            }
        }
        e = (Node *) malloc(sizeof(Node));
        e->type = FUNCTREE;
        e->node_u.functree.func = token->token_val.funcname;
        e->node_u.functree.func_args = funcargs;
        return e;
    } else if (token->token_type == VAR) {
        e = (Node *) malloc(sizeof(Node));
        e->type = VARIABLE;
        e->sign = 1;
        e->var_name = token->token_val.var_name;
        return e;
    }
    e = (Node *) malloc(sizeof(Node));
    e->type = VALUE;
    e->val = token->token_val.var_val;
    return e;
}
Node *led(Node*, Token*, Vector*);

Node *led(Node *left, Token *t, Vector *tokens) {
    Node *tree = (Node *) malloc(sizeof(Node));
    tree->type = OPTREE;
    tree->node_u.optree.operator = (char) t->token_val.operator;
    tree->node_u.optree.left = left;
    tree->node_u.optree.right = expr(tokens, getBinding(t)-1);
    return tree;
}

Node *expr(Vector* tokens, int rbp) {
    //print_tok((Token*)vector_get(tokens, 0));
    Node *left = nud(tokens, (Token *) vector_pop(tokens, 0));
    while (vector_count(tokens) > 0 && greaterBinding((Token *)vector_get(tokens, 0), rbp)) {
        Node *temp = led(left, (Token *) vector_pop(tokens, 0), tokens);
        //printf("%f\n", temp->optree.right->val);
        left = temp;
    }
    return left;
}

double evaluate(Node *n) {
    if (n->type == FUNCTREE) {
        if (strcmp(n->node_u.functree.func, "abc")==0) {
            int sum = 0;
            for (int i = 0; i < vector_count(n->node_u.functree.func_args); i++) {
                sum += evaluate(vector_get(n->node_u.functree.func_args, i));
            }
            return sum;
        } else if (strcmp(n->node_u.functree.func, "sqrt")==0) {
            int argc = vector_count(n->node_u.functree.func_args);
            if (argc != 1) {
                printf("[CCALC] Invalid Arg Count (EVAL STAGE)");
                return -1;
            }
            return sqrt(evaluate(vector_get(n->node_u.functree.func_args, 0)));
        }
    } else if (n->type == OPTREE) {
        switch(n->node_u.optree.operator) {
            // TODO USE MACROS
            case '+':
            return evaluate(n->node_u.optree.left)+evaluate(n->node_u.optree.right);
            case '-':
            return evaluate(n->node_u.optree.left)-evaluate(n->node_u.optree.right);
            case '/':
            return evaluate(n->node_u.optree.left)/evaluate(n->node_u.optree.right);
            case '*':
            return evaluate(n->node_u.optree.left)*evaluate(n->node_u.optree.right);
            case '^':
            return pow(evaluate(n->node_u.optree.left),evaluate(n->node_u.optree.right));
            default:
            printf("[CCALC] UNKNOWN OPERATOR (EVAL STAGE)");
            return -1;
        }
    } else if (n->type == VALUE) {
        return n->val;
    } else if (n->type == VARIABLE) {
        return var_get(progvars, n->var_name[0])*n->sign;
    }
}
void free_tree(Node*);
void free_tree(Node *tree) {
    if (tree->type == FUNCTREE) {

        for (int i = 0; i < vector_count(tree->node_u.functree.func_args); i++) {
            free_tree(vector_get(tree->node_u.functree.func_args, i));
            //vector_free(tree->node_u.functree.func_args);
        }

    } else if (tree->type == VARIABLE) {
        //free(tree->var_name);
        free(tree);
    } else if (tree->type == OPTREE) {
        free_tree(tree->node_u.optree.left);
        free_tree(tree->node_u.optree.right);
        free(tree);
    } else if (tree->type == VALUE) {
        free(tree);
    }
}

double f_eval(Node *n, double val) {

}

int getBinding(Token* t) {
    switch(t->token_val.operator) {
        case '+':
        return 100;
        case ')':
        return 0;
        case '-':
        return 150;
        case '/':
        return 250;
        case '*':
        return 200;
        case '^':
        return 300;
        default:
        printf("NOT FOUND BINDING\n");
        return -1;
    }
}

int greaterBinding(Token* t, int rbp) {
    return getBinding(t) > rbp;
}