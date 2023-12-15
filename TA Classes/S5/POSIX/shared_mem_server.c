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


int main()
{
    int shm_fd;
    int* ptr;
    sem_t *sem;

    sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    printf("init sem\n");
    shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0)
    {
        perror("Failed to open shared mem");
        return EXIT_FAILURE;
    }
    ftruncate(shm_fd, SIZE);
    ptr = (int *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // sleep(5);
    printf("init map\n");

    for (size_t i = 0; i < IN_LEN; i++)
    {
        sem_wait(sem);
        ptr[i] = (i + 1) * 10;
        printf("Sent! : %ld\n", (i+1)*10);
        sem_post(sem);
        sleep(2);
    }
    munmap(ptr, SIZE);
    close(shm_fd);
    sem_close(sem);
    sem_unlink(SEM_NAME);
    return EXIT_SUCCESS;
}