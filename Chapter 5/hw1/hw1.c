/*
 * hw1.c
 * Chapter 5 Aufgabe 1
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

int main(int argc, char *argv[]) {
    if(argc > 1 || (strcmp(argv[0], "Dummy") == 0) ) {
        printf("Usage: ./{file name}");
        exit(1);
    }


	int x = 100;

	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child (new process)
		x++;
		printf("Child Process: %d\n", x);
	} else {
		// parent goe down this path (main)
		x--;
		printf("Parent Process: %d\n", x);
	}

	return 0;
}
