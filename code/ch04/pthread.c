#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum;

void *runner(void *parameter) {
    sum=0;
    int i;
    for(i=0;i<=atoi(parameter);i++) sum+=i;
    pthread_exit(0);
}

int main(int argc, char **argv) {
    pthread_t threadID;
    pthread_attr_t attribute;

    if(argc!=2) {
        fprintf(stderr,"usage pthread <integer value>\n");
        return -1;
    }

    if(atoi(argv[1])<0) {
        fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
        return -1;
    }

    pthread_attr_init(&attribute);
    pthread_create(&threadID,&attribute,runner,argv[1]);
    pthread_join(threadID,NULL);
    printf("%d\n",sum);
    return 0;
}