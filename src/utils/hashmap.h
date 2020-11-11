#ifndef HMAP_H__
#define HMAP_H__
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define DEFAULT 1000

typedef struct {
    void **map;
    int size;
} HashMap;

void hm_init(HashMap*);
void hm_insert(HashMap*, void*, void*);
void *hm_get(HashMap*, void*);
void hm_free(HashMap*);
void hm_print(HashMap*);
unsigned int hm_hash(void*);
#endif