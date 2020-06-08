#include "eval.h"

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
