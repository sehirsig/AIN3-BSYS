#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//T3 works

#include "common_threads.h"

// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

// You likely need two semaphores to do this correctly, and some
// other integers to track things.

typedef struct __barrier_t {
    // add semaphores and other information here
	sem_t s1;
	sem_t preventcheckfailure;
	int wakecalls;
	int current;
} barrier_t;


// the single barrier we are using for this program
barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {
    // initialization code goes here
	sem_init(&b->s1, 0, 0);
	sem_init(&b->preventcheckfailure, 0, 1);
	b->wakecalls = num_threads;
	b->current = 1; //threadnummer
}

void barrier(barrier_t *b) {
    // barrier code goes here
	//thesis 1 - the number of threads in negative(+1) so everyone goes to sleep instead of the last one who runs on and wakes the last one up again - who wakes the next and so on - hätte damit die umgekehrte semaphor benötigt die bei erreichtem negativen wert invertiert und ab da an posted bis 0.
	sem_wait(&b->preventcheckfailure);
	if (b->current < b->wakecalls) {
		sleep(1); // hat Probleme gemacht weil alle denken sie sind noch nicht der letzte. denn sie sind alle schon durch die if durch während manche noch schlafen vor dem zählen
		b->current++;
		sem_post(&b->preventcheckfailure);
		sem_wait(&b->s1); //garantiert schlafen
	} else {
		sem_post(&b->preventcheckfailure);
		for (int i = 1; i<b->wakecalls; i++) { //der letzte weckt alle
			sem_post(&b->s1);
		}
		
	}
}

//
// XXX: don't change below here (just run it!) ----ok so no sleeps below here
//
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("child %d: before\n", t->thread_id);
    barrier(&b);
    printf("child %d: after\n", t->thread_id);
    return NULL;
}


// run with a single argument indicating the number of 
// threads you wish to create (1 or more)
int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);
    
    int i;
    for (i = 0; i < num_threads; i++) {
	t[i].thread_id = i;
	Pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++) 
	Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}

