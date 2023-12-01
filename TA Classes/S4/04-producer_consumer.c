#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 2

int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in the buffer
int in = 0;     // Index to insert items
int out = 0;    // Index to remove items

pthread_mutex_t lock;

void *producer(void *arg);
void *consumer(void *arg);

int main() {
    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}

void *producer(void *arg) {
    for (int i = 0; i < 10; ++i) {
        int item = rand() % 100;

        pthread_mutex_lock(&lock);
        // Wait if the buffer is full
        while (count == BUFFER_SIZE) {
            printf("Buffer is full. Producer is waiting...\n");
            pthread_mutex_unlock(&lock);
            usleep(100);
            pthread_mutex_lock(&lock);
        }

        buffer[in] = item;
        printf("Produced item: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;
        pthread_mutex_unlock(&lock);

        sleep(1);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; ++i) {

        pthread_mutex_lock(&lock);
        // Wait if the buffer is empty
        while (count == 0) {
            printf("Buffer is empty. Consumer is waiting...\n");
            pthread_mutex_unlock(&lock);
            usleep(100);
            pthread_mutex_lock(&lock);
        }

        // Consume an item from the buffer
        int item = buffer[out];
        printf("Consumed item: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;
        pthread_mutex_unlock(&lock);

        sleep(2);
    }

    pthread_exit(NULL);
}
