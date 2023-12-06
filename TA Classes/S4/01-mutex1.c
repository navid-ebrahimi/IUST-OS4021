#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_COUNT 1000

pthread_t tid[THREAD_COUNT];
int counter;
  
void* increment(void* arg) {
    sleep(1);
    counter++;
}

void* decrement(void* arg) {
    sleep(1);
    counter--;
}
  
int main(void)
{
    int i = 0;
    int error;
  
    while (i < THREAD_COUNT) {
        if (i%2) {
            error = pthread_create(&(tid[i]), NULL, &increment, NULL);
        } else {
            error = pthread_create(&(tid[i]), NULL, &decrement, NULL);
        }
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        i++;
    }

    for (int j = 0; j < THREAD_COUNT; j++) {
        pthread_join(tid[j], NULL);
    }
  
    printf("counter: %d\n", counter);

    return 0;
}