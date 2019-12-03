#include <pthread.h>
#include <stdio.h>
#define NUM_OF_THREADS 5


void *runner(void *param) {
    pthread_exit(0);
} 


int main(int argc, char *argv[]) {
    pthread_attr_t attribute;
    int policy,i;
    pthread_t threadid[NUM_OF_THREADS];

    // get the default attribute
    pthread_attr_init(&attribute);

    // get the current schduling
    if(pthread_attr_getschedpolicy(&attribute,&policy)!=0) {
        fprintf(stderr,"Unable to get policy.\n");
    }
    else {
        if(policy==SCHED_OTHER) printf("SCHED_OTHER\n");
        else if(policy==SCHED_RR) printf("SCHED_RR\n");
        else if(policy==SCHED_FIFO) printf("SCHED_FIFO\n");
    }

    // set the scheduling policy to SCHED_FIFO
    if(pthread_attr_setschedpolicy(&attribute,SCHED_FIFO)!=0) {
        fprintf(stderr,"Unable to set policy.\n");
    }

    // create the threads
    for(i=0;i<NUM_OF_THREADS;i++) {
        pthread_create(&threadid[i],&attribute,runner,NULL);
    }

    // join on each thread -> wait for the thread to complete
    for(i=0;i<NUM_OF_THREADS;i++) {
        pthread_join(threadid[i],NULL);
    }

    return 0;
}