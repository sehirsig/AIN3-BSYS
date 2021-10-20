/*
 * null.c
 * Chapter 14 Aufgabe 1
 *
 * Autor: @sehirsig
 * Erstellt am: 06.04.2021
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
    
    int *pointer = NULL;
    int x;
    //dereference
    x = *pointer;
    
    printf("%d\n", x);

	return 0;
}
