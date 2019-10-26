#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    pid_t childPid;
    childPid=fork();
    if(childPid==0) {
        exit(0);
    }
    else {
        sleep(30);
        system("ps -eo pid,ppid,stat,cmd");
    }
    return 0;
}