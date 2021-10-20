/*
 * vector.c
 * Chapter 14 Aufgabe 8
 *
 * Autor: @sehirsig
 * Erstellt am: 08.04.2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct vector_struct {
	int* data;
	int capacity;
	int size;
} vector;

void vector_create(vector* v, int capacity);
void vector_insert(vector* v, int number);
void vector_remove(vector* v);
void vector_destroy(vector* v);

int main(int argc, char *argv[]) {
	if(argc < 1 || (strcmp(argv[0], "Dummy") == 0) ) {
        printf("Usage: ./{file name}");
        exit(1);
    }
    
    vector vec;
    vector *vecp = &vec;
    vector_create(vecp, 2);
    
    vector_insert(vecp, 2);
    vector_insert(vecp, 67);
    vector_insert(vecp, 3);
    
    vector_insert(vecp, 5);
    
    vector_destroy(vecp);
	return 0;
}

void vector_create(vector* v, int capacity) {
	v -> data = (int*) malloc(capacity * sizeof(int));
	v -> capacity = capacity;
	v -> size = 0;
}

void vector_insert(vector* v, int number) {
	if (v -> size >= v -> capacity) {
		v -> capacity = 2 * v -> capacity;
		v -> data = realloc(v -> data, v -> capacity);
	}
	v -> data[v -> size++] = number;
}

void vector_remove(vector* v) {
	v -> data[v-> size--] = 0;
}

void vector_destroy(vector* v) {
	free(v->data);
	v->size=0;
	v->capacity=0;
}
