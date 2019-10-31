#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define SIZE 4096


int main(void) {
    const char *name="OS";
    char *msg0="This is the first message\n";
    char *msg1="This is the second message\n";
    int shmFd;
    void *ptr;

    // create shared memory
    shmFd=shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shmFd,4096);
    ptr=mmap(0, SIZE, PROT_WRITE, MAP_SHARED,shmFd, 0);
    // add message into the shared memory
    sprintf(ptr,"%s",msg0);
    ptr+=strlen(msg0);
    sprintf(ptr,"%s",msg1);
    ptr+=strlen(msg1);
    return 0;
}