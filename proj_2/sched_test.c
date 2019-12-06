#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <syscall.h>


// runner function for the threads
void *runner(void *parameter) {
    int i,j;
    int a=0;
    pthread_t tid;
    tid=pthread_self();
    printf("Thread: %li\n",(unsigned long int) tid);

    for(i=0;i<1000000;i++) {
        for(j=0;j<1000;j++) {
           a+=a; 
        }
    }
    return (void *)0;
}


int main(int argc, char *argv[]) {
    int numOfThread,i,err,policy,scheduler,ret;
    pthread_attr_t attr;
    cpu_set_t mask;
    struct sched_param param;

    // get the number of thread from the input    
    numOfThread=atoi(argv[1]);
    pthread_t threadid[numOfThread];

    // set CPU affinity
    CPU_ZERO(&mask);
    CPU_SET(0,&mask);
    ret=sched_setaffinity(0,sizeof(mask),&mask);

    // get default policy
    pthread_attr_init(&attr);
    if(pthread_attr_getschedpolicy(&attr,&policy)!=0) {
        fprintf(stderr,"Unable to get policy.\n");
    
    }
    else {
        printf("Default policy is ");
        if(policy==SCHED_OTHER) printf("SCHED_OTHER\n");
        else if(policy==SCHED_FIFO) printf("SCHED_FIFO\n");
        else if(policy==SCHED_RR) printf("SCHED_RR\n");
    }

    // set new policy
    if(argc==3){
        if(strncmp(argv[2],"SCHED_FIFO",strlen("SCHED_FIFO"))==0) {
            scheduler=SCHED_FIFO;
            printf("Set pthread SCHED_FIFO policy success\n");
        }
        else if(strncmp(argv[2],"SCHED_RR",strlen("SCHED_RR"))==0){
            scheduler=SCHED_RR;
            printf("Set pthread SCHED_RR policy success\n");
        }
    }
    else scheduler=policy;
    param.sched_priority=sched_get_priority_max(scheduler);
    ret=sched_setscheduler(0,scheduler,&param);


    // Create threads
    for(i=0;i<numOfThread;i++) {
        // printf("Thread %d was created.\n",i+1);
        err=pthread_create(&threadid[i],NULL,runner,NULL);
        assert(err==0);
    }

    // wait for the thread to complete
    for(i=0;i<numOfThread;i++) {
        pthread_join(threadid[i],NULL);
    }
    printf("Thread ends\n"); 
    return 0;
}