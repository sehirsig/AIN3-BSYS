/*
 * linkedlist.c
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

int loops = 10;

typedef struct __node_t {
	int key;
	struct __node_t *next;
} node_t;

typedef struct __list_t {
	node_t *head;
	pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
	L->head = NULL;
	pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {
		node_t *new = malloc(sizeof(node_t));
		if (new == NULL) {
			perror("malloc");
			return;
		}
		new->key = key;
		
		pthread_mutex_lock(&L->lock);
		new->next = L->head;
		L->head = new;
		pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key) {
	int rv = -1;
	pthread_mutex_lock(&L->lock);
	node_t *curr = L->head;
	while (curr) {
		if (curr->key == key) {
			rv = 0;
			break;
		}
		curr = curr->next;
	}
	pthread_mutex_unlock(&L->lock);
	return rv;
}

void *func(void *args) {
	list_t *templist = (list_t *)args;
	List_Lookup(templist, 0);
	return NULL;
}

void List_PrintAll(list_t *L) { //Für den Debug Code
	int temp = 0;
	node_t *curr = L->head;
	while (temp < loops) {
		printf("Key: %d\n", curr->key);
		curr = curr->next;
		temp++;
	}
}

int main(int argc, char *argv[]) {
    if((argc < 3 && argc > 3)) {
        char** neveraccess = argv;
        neveraccess = neveraccess;
    }
    
   int numthreads = 2;
   int opt;
   int debug = 0;
   
   while ((opt = getopt(argc, argv, "n:i:h d")) != -1) {
    	switch(opt) {
    		case 'h':
    			printf("Usage: ./linkedlist -n { Number of Threads } -i { Number of Iterations } -d (/DebugMode/)\nDefault n = 2, Default i = 10\n");
        		return 0;
        	case 'n':
    			numthreads = atoi(optarg);
    			break;
    		case 'i':
    			loops = atoi(optarg);
    			break;
    		case 'd':
    			debug = 1;
    		break;
    	}
    }

   	pthread_t threads[numthreads];
   	
   	list_t *list = malloc(sizeof(list_t));
   	
   	List_Init(list);
   	
   	for(int i = 0; i < loops; ++i) {
   		List_Insert(list, i);
   	}
   	
    struct timespec start, stop;
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(int i = 0; i < numthreads; ++i) {
    	assert(pthread_create(&threads[i], NULL, func, list) == 0);
	}

	for(int i = 0; i < numthreads; ++i) {
        assert(pthread_join(threads[i], NULL) == 0);
    }
	clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
	
	long zeit = (stop.tv_sec - start.tv_sec) * 1000000000 + stop.tv_nsec - start.tv_nsec;
	
	if (debug) {
		List_PrintAll(list);
	}
	printf("Dauer: %lu ns\n", zeit);
	
	free(list);
	
	return 0;
}
