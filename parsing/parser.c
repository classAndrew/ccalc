#include "parser.h"
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