#include "hashmap.h"

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
    char *k = (char *)key;
    int s = *k;
    while (*(++k) != '\0') s += *k;
    return s;
}