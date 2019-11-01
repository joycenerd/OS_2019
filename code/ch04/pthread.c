#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum;

// the thread
void *runner(void *parameter) {
    sum=0;
    int i;
    for(i=0;i<=atoi(parameter);i++) sum+=i;
    pthread_exit(0);
}

int main(int argc, char **argv) {
    pthread_t threadID; // thread id
    pthread_attr_t attribute;   // thread attributes for the thread

    if(argc!=2) {
        fprintf(stderr,"usage pthread <integer value>\n");
        return -1;
    }

    if(atoi(argv[1])<0) {
        fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
        return -1;
    }

    pthread_attr_init(&attribute);  // get the default attribute
    pthread_create(&threadID,&attribute,runner,argv[1]);    // create the thread
    pthread_join(threadID,NULL);    // wait for the thread (child) to exit
    printf("%d\n",sum);
    return 0;
}