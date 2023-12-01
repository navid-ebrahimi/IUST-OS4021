#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_COUNT 1000

pthread_t tid[THREAD_COUNT];
int counter;
pthread_mutex_t lock;
  

void* increment(void* arg) {
    sleep(1);
	pthread_mutex_lock(&lock);
    counter++;
	pthread_mutex_unlock(&lock);
}

void* decrement(void* arg) {
    sleep(1);
	pthread_mutex_lock(&lock);
    counter--;
	pthread_mutex_unlock(&lock);
}
  
int main(void)
{
    int i = 0;
    int error;

	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		return 1;
	}
  
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
	pthread_mutex_destroy(&lock);

    return 0;
}