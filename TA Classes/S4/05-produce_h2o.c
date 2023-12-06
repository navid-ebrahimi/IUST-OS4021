#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define H2O_COUNT 10

sem_t sem;

void* produce_h(void* arg) {
    for (int i = 0; i < H2O_COUNT * 2; i++) {
        printf("H produced\n");
        sem_post(&sem);
        sleep(1);
    }
}

void* produce_o(void* arg) {
    for (int i = 0; i < H2O_COUNT; i++) {
        sem_wait(&sem);
        sem_wait(&sem);
        printf("H2O produced\n");
    }
}

int main() {
    sem_init(&sem, 0, 0);

    pthread_t th[2];
    pthread_create(&th[0], NULL, &produce_h, NULL);
    pthread_create(&th[1], NULL, &produce_o, NULL);

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);

    sem_destroy(&sem);
    return 0;
}