/*
 * tlb.c
 * Chapter 19
 *
 * Autor: @sehirsig, @cr-jkb
 * Gruppe: 01
 * Erstellt am: 22.04.2021
 */
 
#define _GNU_SOURCE
#define BILLION 1000000000
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sched.h>
#include <getopt.h>


int main(int argc, char *argv[]) {
    /*if(argc < 3 || argc > 3) {
        printf("Usage: ./tlb { Number of Pages }, { Number of Iterations }");
        exit(1);
    } else {*/
    int opt;
    long NUMPAGES = 2048;
    long iterationen = 50;
    
    while ((opt = getopt(argc, argv, "n:i:h")) != -1) {
    	switch(opt) {
    		case 'h':
    			printf("Usage: ./tlb -n { Number of Pages } -i { Number of Iterations }\n Default n = 2048, Default i = 50\n");
        		return 0;
        	case 'n':
    			NUMPAGES = atoi(optarg);
    			break;
    		case 'i':
    			iterationen = atoi(optarg);
    			break;
    	}
    }
    
    long PAGESIZE = getpagesize();
    long jump = PAGESIZE / (long)sizeof(int);
 	unsigned long total_time = 0;
 
 	cpu_set_t cpuset;
 	CPU_ZERO(&cpuset);
 	CPU_SET(4, &cpuset);
 	if(sched_setaffinity(0, sizeof(cpuset), &cpuset)){//
         perror("Sched_setaffinity Error");
         exit(EXIT_FAILURE);
    }
    
    struct timespec start, end;
    struct timespec clock_overhead_stop;
    

    int* a = (int*) calloc(NUMPAGES * jump, sizeof(int));
    if (a == NULL) {
    	fprintf(stderr, "Allocation Error!");
    	return -1;
    }
    
    for (int k = 0; k < iterationen; k++) {
    	long page_time = 0;
    	for (int i = 0; i < NUMPAGES * jump; i += jump) {
    		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    		clock_gettime(CLOCK_MONOTONIC_RAW, &clock_overhead_stop);
    		a[i] += 1;
    		clock_gettime(CLOCK_MONOTONIC_RAW, &end);

			long pages_access_time_start_nano = ((start.tv_sec * BILLION) + start.tv_nsec);
			long pages_access_time_end_nano = ((end.tv_sec * BILLION) + end.tv_nsec);
			long clock_overhead_stop_nano = ((clock_overhead_stop.tv_sec * BILLION) + clock_overhead_stop.tv_nsec);

    		page_time += (pages_access_time_end_nano - pages_access_time_start_nano) - (clock_overhead_stop_nano - pages_access_time_start_nano);
    	}
    	
    	
    	total_time += page_time / NUMPAGES;
    }
   
	unsigned long final_total_time = total_time / iterationen;
	
	printf("%lu Pages access takes %lu ns!\n", NUMPAGES, final_total_time);
	
	FILE* filepointer;
	
	filepointer = fopen("tabelle.csv", "a+");
	if (filepointer == NULL) {
		fprintf(stderr, "Error with File");
		return -1;
	}
	
	fprintf(filepointer, "%ld, %ld\n", NUMPAGES, final_total_time);
	
	free(a);
	fflush(filepointer);
	fclose(filepointer);
	
	return 0;
}
