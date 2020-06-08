#ifndef VECTOR_H__
#define VECTOR_H__
typedef struct vector_ {
    void** data;
    int size;
    int count;
} Vector;

void vector_init(Vector*);
int vector_count(Vector*);
void vector_add(Vector*, void*);
void vector_set(Vector*, int, void*);
void *vector_get(Vector*, int);
void vector_delete(Vector*, int);
void vector_free(Vector*);
char *vector_tostr(Vector*);
void *vector_pop(Vector*, int);
#endif