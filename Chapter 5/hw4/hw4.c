/*
 * hw1.c
 * Chapter 5 Aufgabe 4
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


    	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child (new process)
		char *myargs[2];
		myargs[0] = strdup("/bin/ls");
		myargs[1] = strdup("");
		myargs[2] = NULL;
		//execv(myargs[0], myargs);
		execl(myargs[0], myargs[0], NULL);
		//char *list[] = {""};
		//execle(myargs[0], "ls", "-l", (char *)0, list);
		
		
	} else {
		// parent goe down this path (main)
	}

	return 0;
}
