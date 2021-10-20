 /*
 * sloppycounter.c
 * Chapter 29
 *
 * Team: Gruppe1
 *** @sehirsig, @cr-jkb
 * Erstellt am: 31.05.2021
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

int NUMTHREADS = 2;
int loops = 10;
int threshold = 50;

typedef struct __counter_t {
	int global;							// global count
	pthread_mutex_t glock;				// global lock
	int local[50];						// per-CPU count
	pthread_mutex_t llock[50];			// ... and locks
	int threshold;						// update frequency
} counter_t;

void init(counter_t *c, int threshold) {
	c->threshold = threshold;
	c->global = 0;
	pthread_mutex_init(&c->glock, NULL);
	int i;
	for (i = 0; i < NUMTHREADS; i++) {
		c->local[i] = 0;
		pthread_mutex_init(&c->llock[i], NULL);
	}
}

void update(counter_t *c, int threadID) {
	pthread_mutex_lock(&c->llock[threadID]);
	c->local[threadID]++;
	
	if (c->local[threadID] >= c->threshold) {
		pthread_mutex_lock(&c->glock);
		c->global += c->local[threadID];
		pthread_mutex_unlock(&c->glock);
		c->local[threadID] = 0;
	}
	pthread_mutex_unlock(&c->llock[threadID]);
}

int get(counter_t *c) {
	pthread_mutex_lock(&c->glock);
	int val = c->global;
	pthread_mutex_unlock(&c->glock);
	return val; // only approximate!
}

typedef struct __args_t {
	counter_t *counter;
	int tid;
} args_t;

void *func(void *arges) {
	args_t *args = (args_t *)arges;
	int i;
	for (i = 0; i < loops; ++i) {
		update(args->counter, args->tid);
	}
	return NULL;
}



int main(int argc, char *argv[]) {
    if((argc < 3 && argc > 3)) {
        char** neveraccess = argv;
        neveraccess = neveraccess;
    }
    
    int opt;
    
    while ((opt = getopt(argc, argv, "n:i:t:h")) != -1) {
    	switch(opt) {
    		case 'h':
    			printf("Usage: ./sloppycounter -n { Number of Threads (MAX 50) } -i { Number of Iterations } -t { Number of Treshold }\nDefault n = 2, Default i = 10, Default t = 50\n");
        		return 0;
        	case 'n':
        	    if (atoi(optarg) <= 50) {
    				NUMTHREADS = atoi(optarg);
    			} else {
    				printf("-n 50 is MAXIMUM, -n set to Default\n");
    			}
    			break;
    		case 'i':
    			loops = atoi(optarg);
    			break;
    		case 't':
    			threshold = atoi(optarg);
    			break;
    	}
    }
    
   	pthread_t threads[NUMTHREADS];
   	args_t argumente[NUMTHREADS];
   	
   	counter_t *OurCounter = malloc(sizeof(counter_t));//
   	
   	init(OurCounter, threshold);
    struct timespec start, stop;
    
    
    for(int i = 0; i < NUMTHREADS; ++i) {
    	argumente[i].tid = i;
    	argumente[i].counter = OurCounter;
    }
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int i = 0; i < NUMTHREADS; ++i) {
    	assert(pthread_create(&threads[i], NULL, func, &argumente[i]) == 0);
	}
	

	for(int i = 0; i < NUMTHREADS; ++i) {
        assert(pthread_join(threads[i], NULL) == 0);
    }
	clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
	
	long zeit = (stop.tv_sec - start.tv_sec) * 1000000000 + stop.tv_nsec - start.tv_nsec;
	printf("Zähler = %d\nDauer: %lu ns\n", OurCounter->global, zeit);
	
	free(OurCounter);
	
	return 0;
}
