/*
 * hw1.c
 * Chapter 5 Aufgabe 8
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


    int pipefds[2];
    char buffer[5];
	
	if(pipe(pipefds) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child (new process)
		// close(STDOUT_FILENO);
		close(pipefds[0]);
		char strin[] = "Super";
		// dup2(pipefds[1], STDOUT_FILENO);
		write(pipefds[1], strin, strlen(strin) + 1);
		// open(pipefds[0]);
		//printf("Child Process: Test\n");
	} else {
		// parent goes down this path (main)
		int rc2 = fork();
			if (rc2 < 0) {
				// fork failed
				fprintf(stderr, "fork failed\n");
				exit(1);
			} else if (rc2 == 0) {
				// child (new process)
				close(pipefds[1]);
				read(pipefds[0], &buffer, sizeof(buffer) + 1);
				
				write(STDOUT_FILENO, &pipefds[0], 5);
				printf("Super = %s\n", buffer);
			} else {
				// parent goe down this path (main)
				//printf("Parent 2 Process: Test\n");
				return 0;
			}
	
		//printf("Parent Process: Test\n");
	}

	return 0;
}
