/*
 * counter.c
 * Chapter 29
 *
 * 40 CPUS (VPN Linux)
 * 6 online
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


typedef struct __counter_t {
	int value;
	int loops;
	pthread_mutex_t lock;
} counter_t;

void init(counter_t* c, int loop) {
	c->value = 0;
	assert(pthread_mutex_init(&c->lock, NULL) == 0);
	c->loops = loop;
}

void* increment(void *c) {
	counter_t *args = (counter_t *)c;
	
	for(int i = 0; i < args->loops; ++i) {
		assert(pthread_mutex_lock(&args->lock) == 0);
		args->value++;
		assert(pthread_mutex_unlock(&args->lock) == 0);
	}
	return NULL;
}

int main(int argc, char *argv[]) {
    if((argc < 3 && argc > 3)) {
        char** neveraccess = argv;
        neveraccess = neveraccess;
    }
    int numthreads = 2;
    int looper = 10;
    int opt;
    
    while ((opt = getopt(argc, argv, "n:i:h")) != -1) {
    	switch(opt) {
    		case 'h':
    			printf("Usage: ./counter -n { Number of Threads } -i { Number of Iterations }\nDefault n = 2, Default i = 10\n");
        		return 0;
        	case 'n':
    			numthreads = atoi(optarg);
    			break;
    		case 'i':
    			looper = atoi(optarg);
    			break;
    	}
    }
   	pthread_t threads[numthreads];
   	counter_t *OurCounter = malloc(sizeof(counter_t));
   	init(OurCounter, looper);
   	
    struct timespec start, stop;
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int i = 0; i < numthreads; ++i) {
    	assert(pthread_create(&threads[i], NULL, increment, OurCounter) == 0);
	}
	for(int i = 0; i < OurCounter->loops; ++i) {
		assert(pthread_mutex_lock(&OurCounter->lock) == 0);
		OurCounter->value++;
		assert(pthread_mutex_unlock(&OurCounter->lock) == 0);
	}
	for(int i = 0; i < numthreads; ++i) {
        assert(pthread_join(threads[i], NULL) == 0);
    }
	clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
	
	long zeit = (stop.tv_sec - start.tv_sec) * 1000000000 + stop.tv_nsec - start.tv_nsec;
	printf("Zähler = %d\nDauer: %lu ns\n", OurCounter->value, zeit);
	
	pthread_mutex_destroy(&OurCounter->lock);
	free(OurCounter);
	
	return 0;
}
