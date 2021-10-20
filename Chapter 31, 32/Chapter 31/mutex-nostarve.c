#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//



typedef struct __ns_mutex_t {
	sem_t mutex;
	sem_t lock1;
	int value;
	int turn;
} ns_mutex_t;


ns_mutex_t mut;
int currentChild = 1;

void ns_mutex_init(ns_mutex_t *m) {
	sem_init(&m->mutex,0,1);
	sem_init(&m->lock1,0,1);
	m->value = 0;
	m->turn = 0;
}

void ns_mutex_acquire(ns_mutex_t *m) {
	sem_wait(&m->lock1);
	int mynum = m->value++;
	sem_post(&m->lock1);
	while (mynum != m->turn) {
	}
	sem_wait(&m->mutex);
	currentChild = m->turn;
}

void ns_mutex_release(ns_mutex_t *m) {
	sem_wait(&m->lock1);
	m->turn++;
	sem_post(&m->mutex);
	sem_post(&m->lock1);
}


void *worker(void *arg) {
	ns_mutex_acquire(&mut);
	sleep(1);
	int thisnum = currentChild;
	printf("child: %d\n", thisnum);
	ns_mutex_release(&mut);
	ns_mutex_acquire(&mut);
	sleep(1);
	printf("child: %d\n", thisnum);
	ns_mutex_release(&mut);
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    int nums = atoi(argv[1]);
    pthread_t threads[nums];
    ns_mutex_init(&mut);
    printf("parent: begin\n");
    int i;
    for (i = 0; i < nums; i++) {
		Pthread_create(&threads[i], NULL, worker, NULL);
    }
    
    for (i = 0; i < nums; i++) {
		Pthread_join(threads[i], NULL);
	}
    printf("parent: end\n");
    return 0;
}

