/*
 * aufgabe2.c
 * Chapter 6 Aufgabe 2
 *
 * Autor: @sehirsig
 * Erstellt am: 22.03.2021
 */
 
#define BILLION 1E9;
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h>


int main(int argc, char *argv[]) {
    if(argc != 2) {
    	printf("Usage: ./aufgabe2 { Anzahl Loops }\n");
    	exit(1);
    }
	char* buf = '\0';

	int fd = open("./test.txt", O_CREAT | O_WRONLY, S_IRWXU);

	cpu_set_t myset;
	struct timespec start, end, start2, end2;
	CPU_ZERO(&myset);
	CPU_SET(2, &myset);
	
	int pipeone[2], pipetwo[2];
	if(pipe(pipeone) == -1) {
		exit(1);
	}
		
	if(pipe(pipetwo) == -1) {
		exit(1);
	}
		
	int loops = atoi(argv[1]);
		
	printf("%d Loops have been set!\n\n", loops);
	
	clock_gettime(CLOCK_REALTIME, &start);
	for (int i = 0; i < loops; i++) {
	read(fd, buf, 0);
	//getpid();
	write(fd, buf, 0);
	}
	clock_gettime(CLOCK_REALTIME, &end);

	double result1 = ( end.tv_nsec - start.tv_nsec);//(end.tv_sec - start.tv_sec) + ( end.tv_nsec - start.tv_nsec) / BILLION;
	printf("%.20lf nanoseconds for No Context-Switch\n", result1 / loops);
	
	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child (new process)
		if (sched_setaffinity(getpid(), sizeof(myset), &myset) == -1) {
			exit(1);
		}
		
		close(pipeone[1]);
		close(pipetwo[0]);
		
		for(int i = 0; i < loops; i++) {
			read(pipeone[0], buf, 0);
			write(pipetwo[1], buf, 0);
			}
		
		//int rc_wait2 = wait(NULL);
	} else {
		// parent goes down this path (main)
		if (sched_setaffinity(getpid(), sizeof(myset), &myset) == -1) {
		exit(1);}
		//int rc_wait = wait(NULL);
		close(pipeone[1]);
		close(pipetwo[0]);
		clock_gettime(CLOCK_REALTIME, &start2);
		for(int i = 0; i < loops; i++) {
			write(pipeone[1], buf, 0);
			read(pipetwo[0], buf, 0);
		}
		clock_gettime(CLOCK_REALTIME, &end2);
	
		double result = ( end2.tv_nsec - start2.tv_nsec);//(end2.tv_sec - start2.tv_sec) + ( end2.tv_nsec - start2.tv_nsec) / BILLION;
		printf("%.20lf nanoseconds for Context-Switch\n", (result/loops));
		
		
		printf("Context-Switch takes %.20lf nanoseconds more time\n", ((result/loops) - (result1/loops)));
	}

	return 0;
}
