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
unsigned int hm_hash(void*);

void hm_init(HashMap *hm) {
    hm->map = malloc(sizeof(void*)*DEFAULT);
    hm->size = DEFAULT;
}

void hm_insert(HashMap *hm, void *key, void *item) {
    hm->map[hm_hash(key)%hm->size] = item;
}

void *hm_get(HashMap *hm, void *key) {
    return hm->map[hm_hash(key)%hm->size];
}

void hm_free(HashMap *hm) {
    free(hm->map);
}

unsigned int hm_hash(void *key) {
    // WARNING: This is a terrible hashing algorithm. Please don't ever do this.
    // UPDATE: uses the first character of a key (whose value is assumed to be a string)
    return *(char*)key;
}