/*
 * aufgabe1.c
 * Chapter 6 Aufgabe 1
 *
 * Autor: @sehirsig
 * Erstellt am: 22.03.2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define BILLION 1E9;

int main(int argc, char *argv[]) {
    if(argc > 1 || (strcmp(argv[0], "Dummy") == 0) ) {
        printf("Usage: ./{file name}");
        exit(1);
    }

	struct timespec start, end;
	
	clock_gettime(CLOCK_REALTIME, &start);
	write(0, NULL, 0);
	clock_gettime(CLOCK_REALTIME, &end);
	double result = (end.tv_sec - start.tv_sec) + ( end.tv_nsec - start.tv_nsec) / BILLION;
	printf("It took %.20lf seconds\n", result);

	return 0;
}
