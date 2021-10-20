/*
 * hw2.c
 * Chapter 5 Aufgabe 2
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


    int file = open("test.txt", O_RDWR | O_CREAT, 0777);
	printf("Main Process: %d\n", file);
	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child (new process)
		write(file, "Test\n", sizeof("Test"));
		printf("Child Process: %d\n", file);
	} else {
		// parent goe down this path (main)
		write(file, "Toast\n", sizeof("Toast"));
		printf("Parent Process: %d\n", file);
	}

	return 0;
}
