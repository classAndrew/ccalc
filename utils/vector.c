#include<stdlib.h>

// A standard vector implementation

static const int DEFAULTCAP = 10;

struct vector {
    void **data;
    int max_size;
    int len;
};

typedef struct vector Vector;

void add_to_vec(Vector*, void*);
void* get_at_vec(Vector*, int);

void init_vec(Vector* vec) {
    vec->data = malloc(sizeof(void*) * DEFAULTCAP);
    vec->len = 0;
    vec->max_size = DEFAULTCAP; //use calloc?
}

void add_to_vec(Vector* vec, void* element) {
    if (vec->len == vec->max_size) {
        vec->data = (void** )realloc(vec->data, sizeof(void*)*(vec->max_size*2));
        vec->max_size = vec->max_size*2;
    }
    (vec->data)[vec->len] = element;
    vec->len += 1;
}

void* get_at_vec(Vector* vec, int ind) {
    if (ind > vec->max_size || ind < 0) {
        printf("[CCALC] OUT OF BOUNDS VECTOR!\n");
        exit(-1);
    }
    return vec->data[ind];
}