#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vector_init(Vector *v)
{
	v->data = NULL;
	v->size = 0;
	v->count = 0;
}

int vector_count(Vector *v)
{
	return v->count;
}

void vector_add(Vector *v, void *e)
{
	if (v->size == 0) {
		v->size = 10;
		v->data = malloc(sizeof(void*) * v->size);
		memset(v->data, '\0', sizeof(void) * v->size);
	}

	// condition to increase v->data:
	// last slot exhausted
	if (v->size == v->count) {
		v->size *= 2;
		v->data = realloc(v->data, sizeof(void*) * v->size);
	}

	v->data[v->count] = e;
	v->count++;
}

void vector_set(Vector *v, int index, void *e)
{
	if (index >= v->count) {
		return;
	}

	v->data[index] = e;
}

void *vector_get(Vector *v, int index)
{
	if (index >= v->count) {
        printf("INVALID ACCESS TO VECTOR\n");
		return NULL;
	}

	return v->data[index];
}

void vector_delete(Vector *v, int index)
{
	if (index >= v->count) {
		return;
	}

	v->data[index] = NULL;

	int i, j;
	void **newarr = (void**)malloc(sizeof(void*) * v->count * 2);
	for (i = 0, j = 0; i < v->count; i++) {
		if (v->data[i] != NULL) {
			newarr[j] = v->data[i];
			j++;
		}		
	}

	//free(v->data);

	v->data = newarr;
	v->count--;
}

void vector_free(Vector *v)
{
	free(v->data);
}

char* vector_tostr(Vector *v) {
    int i;
    char* str = (char *) malloc(sizeof(char)*vector_count(v)+1);
    for (i = 0; i < vector_count(v); i++) {
        char newchar = *(char *)vector_get(v, i);;
        str[i] = newchar;
    }
    str[i] = '\0';
    return str; 
}

void *vector_pop(Vector* v, int i) {
    void* item = vector_get(v, i);
    vector_delete(v, i);
    return item;
}

