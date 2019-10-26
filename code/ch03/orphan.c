#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid=fork();
    if(pid>0) {
        printf("This is parent process\n");
        printf("PID= %d\n\n",getpid());
    }
    else if(pid==0) {
        printf("This is child process\n");
        printf("PID= %d\n",getpid());
        printf("And parent PID= %d\n\n",getppid());
        sleep(10);
        // Parent terminated
        printf("This is still child process\n");
        printf("PID= %d\n",getpid());
        printf("Parent PID= %d\n\n",getppid());
    }
    else printf("Failed to create child process\n");
    return 0;
}