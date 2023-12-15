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

    for (size_t i = 0; i < 5; i++)
    {
        printf("Recieved: %s\n", str);
        sleep(2);
    }

    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return EXIT_SUCCESS;
}