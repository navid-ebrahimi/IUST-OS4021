#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

int max;
int counter = 0; // shared global variable

void *mythread(void *arg) {
    sleep(1);
    char *letter = arg;
    int i;
    printf("%s: begin [addr of i: %p]\n", letter, &i);
    for (i = 0; i < max; i++) {
        pthread_mutex_lock(&lock);
	    counter = counter + 1;
        printf("%s   %d  ",letter, counter);
        pthread_mutex_unlock(&lock);
    }
    printf("%s: done\n", letter);
    return NULL;
}

int main(int argc, char *argv[]) { 

    if (argc != 2) {
        fprintf(stderr, "usage: main-first <loopcount>\n");
        exit(1);
    }

    pthread_mutex_init(&lock, NULL);

    max = atoi(argv[1]);     // converts a string into an integer numerical representation. atoi stands for ASCII to integer. 
    pthread_t p1, p2;

    printf("main: begin [counter = %d] [%x]\n", counter, 
	   (unsigned int) &counter);

    pthread_create(&p1, NULL, mythread, "A"); 
    pthread_create(&p2, NULL, mythread, "B");

    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 

    printf("main: done\n [counter: %d]\n [should: %d]\n", 
	   counter, max*2);

    pthread_mutex_destroy(&lock);

    return 0;
}

