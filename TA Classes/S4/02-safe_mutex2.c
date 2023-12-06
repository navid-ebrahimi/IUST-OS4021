// a program to add worker id at the end of an array

#include <stdio.h>
#include <pthread.h>

#define COUNT_THREADS 20

typedef struct {
	int wid;
} t_arg;

pthread_mutex_t lock;
int tail;
int arr[COUNT_THREADS];

void *worker_func(void *_arg)
{
	t_arg *arg = (t_arg *)_arg;
	pthread_mutex_lock(&lock);
	arr[tail] = arg->wid;
	printf("wid: %d\n", arg->wid);
	tail++;
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main()
{
	pthread_mutex_init(&lock, NULL);
	pthread_t threads[COUNT_THREADS];
 	t_arg args[COUNT_THREADS];
	int i;

	tail = 0;
	for (i = 0; i < COUNT_THREADS; i++) {
		arr[i] = 0;
	}

	for (i = 0; i < COUNT_THREADS; i++) {
		args[i].wid = i;
		pthread_create(&threads[i], NULL,
				worker_func, (void *)&args[i]);
	}

	for (i = 0; i < COUNT_THREADS; i++)
		pthread_join(threads[i], NULL);

	// print result
	for (i = 0; i < COUNT_THREADS; i++)
		printf("%d: wid: %d\n", i, arr[i]);

	pthread_mutex_destroy(&lock);
	return 0;
}
