#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "shared_mem.h"
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

int processUnit(int *ptr)
{
}

int main()
{
    int shm_fd;
    int *ptr;
    sem_t *sem;

    sem = sem_open(SEM_NAME, O_RDONLY, 0666, 1);
    printf("init sem\n");
    
    shm_fd = shm_open(NAME, O_RDONLY, 0666);
    if (shm_fd < 0)
    {
        perror("Failed to open shared mem");
        return EXIT_FAILURE;
    }


    ptr = (int *)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    printf("init map\n");

    for (size_t i = 0; i < IN_LEN; i++)
    {
        sem_wait(sem);
        printf("Recieved: %d\n", ptr[i]);
        sem_post(sem);
        sleep(3);
    }

    munmap(ptr, SIZE);
    close(shm_fd);
    sem_close(sem);
}