/*
 * memory-user.c
 * Chapter 13 Aufgabe 3
 *
 * Autor: @sehirsig
 * Erstellt am: 06.04.2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define MILLION 1000000;


int main(int argc, char *argv[]) {
    if(argc > 3) {
        printf("Usage: ./memory-user { Number of Usage in Megabytes }, {Number of Seconds (Optional) }");
        exit(1);
    }
    
    printf("memory-user.c Process-ID: %ld\n", (long)getpid());
    
    struct timespec start, end;
    
    int argument1 = atoi(argv[1]);
    long inmegabytes = argument1 * MILLION;
    
    int argument2 = 1;
    if (argv[2] != NULL) {
    	argument2 = atoi(argv[2]);
    }
    
    
    char *a1 = calloc(inmegabytes, sizeof(char));
    if (a1 == NULL) {
    	return -1;
    }
    
    int i = 0;
    
    clock_gettime(CLOCK_REALTIME, &start);
    while (end.tv_sec - start.tv_sec <= argument2) {
    	a1[i++] = 'c';
    	if (i == inmegabytes) {
    		i = 0;
    	}
    	clock_gettime(CLOCK_REALTIME, &end);
    }
	
	
	free(a1);
	

	return 0;
}
