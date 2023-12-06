#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define COUNT_THREADS 1000

typedef struct {
	int wid;
} t_arg;


int tail;
int arr[COUNT_THREADS];

void *worker_func(void *_arg)
{
	sleep(1);
	t_arg *arg = (t_arg *)_arg;
	arr[tail] = arg->wid;
	printf("wid: %d\n", arg->wid);
	tail++;
	pthread_exit(NULL);
}

int main()
{
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


	return 0;
}
