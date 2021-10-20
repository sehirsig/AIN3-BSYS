/*
 * free100.c
 * Chapter 14 Aufgabe 6
 *
 * Autor: @sehirsig
 * Erstellt am: 08.04.2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if(argc < 1 || (strcmp(argv[0], "Dummy") == 0) ) {
        printf("Usage: ./{file name}");
        exit(1);
    }
    
    int* pointer = (int*) malloc(100 * sizeof(int));
    
    free(&pointer[69]);
    
    
    printf("%d\n", pointer[69]);

	return 0;
}
