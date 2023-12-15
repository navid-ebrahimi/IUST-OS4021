#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "systemv.h"

int main()
{
    key_t key = ftok(KEY, PROJID);
    int shmid = shmget(key, SIZE, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    sleep(2);
    for (size_t i = 0; i < NO; i++)
    {
        sprintf(str, "Hello%ld", i);
        printf("Send: %s\n", str);
        sleep(2);
    }

    shmdt(str);
    return EXIT_SUCCESS;
}