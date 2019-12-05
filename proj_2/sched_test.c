#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>


pthread_barrier_t barrier;


// runner function for the threads
void *runner(void *parameter) {
    int threadid,i,j;
    int ret=0;
    cpu_set_t mask;
    struct sched_param param;
    double cnt;

    threadid=*(int *)parameter;

    if(*((int *)parameter+1)) {
        // set CPU affinity
        CPU_ZERO(&mask);
        CPU_SET(0,&mask);
        ret=sched_setaffinity(1,sizeof(mask),&mask);

        // set thread priority 
        printf("Thread %d sched_scheduler()\n",threadid);
        param.sched_priority=sched_get_priority_max(SCHED_FIFO);
        ret=sched_setscheduler(0,SCHED_FIFO,&param);
        printf("Thread %d sched after %s\n",threadid,strerror(errno));
    }

    // Thread running -> busy waiting for 1 second
    pthread_barrier_wait(&barrier);
    printf("ERROR %s\n",strerror(errno));
    for(i=0;i<8;i++) {
        printf("Thread %d is running\n",threadid);
        cnt=0;
        for(j=0;j<10000000;j++) {
            cnt+=0.1f;
        }
    }
    return (void *)0;
}

void *createArg(int x, int schedular) {
    int *p=(int *)malloc(sizeof(int)*2);
    *p=x;
    *(p+1)=schedular;
    return (void *)p;
}


int main(int argc, char *argv[]) {
    int numOfThread,i,err,policy,schedular;
    pthread_attr_t attr;

    // get the number of thread from the input    
    numOfThread=atoi(argv[1]);
    pthread_t threadid[numOfThread];

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

    // define new policy
    if(argc==3){
        if(strncmp(argv[2],"SCHED_FIFO",strlen("SCHED_FIFO"))==0) schedular=SCHED_FIFO;
        else if(strncmp(argv[2],"SCHED_RR",strlen("SCHED_RR"))==0) schedular=SCHED_RR;
    }
    else schedular=policy;

    // create threads
    pthread_barrier_init(&barrier,NULL,numOfThread);
    for(i=0;i<numOfThread;i++) {
        printf("Thread %d was created.\n",i+1);
        err=pthread_create(&threadid[i],NULL,runner,createArg(i+1,schedular));
        assert(err==0);
    }

    // wait for the thread to complete
    for(i=0;i<numOfThread;i++) {
        pthread_join(threadid[i],NULL);
    } 

}