#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define SIZE 4096


int main(void) {
    const char *name="OS";
    int shmFd;
    void *ptr;

    shmFd=shm_open(name,O_RDONLY,0666);
    ptr=mmap(0,SIZE,PROT_READ,MAP_SHARED,shmFd,0);
    printf("%s",(char *)ptr);
    shm_unlink(name);
    return 0;
}