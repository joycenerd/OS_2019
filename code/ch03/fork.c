#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("fork failed\n");
        exit(-1);
    }
    else if(pid==0){
        printf("This is child\n");
        execlp("/bin/ls","ls","/home/dmplus",NULL);
    }
    else{
        printf("This is parent and the child process PID= %d\n",pid);
        wait(NULL);
        printf("child complete\n");
        exit(0);
    }
    return 0;
}