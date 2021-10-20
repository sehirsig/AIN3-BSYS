/*
 * hw1.c
 * Chapter 5 Aufgabe 6
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


	int status;
	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child (new process)
		printf("hello\n");
		//int rc_wait2 = wait(NULL);
	} else {
		// parent goe down this path (main)
		int rc_wait = waitpid(rc,  &status, WCONTINUED);
		printf("%d\n", rc_wait);
		printf("%d\n", (int)getpid());
	}

	return 0;
}
