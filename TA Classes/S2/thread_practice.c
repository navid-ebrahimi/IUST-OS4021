#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct
{
    int *numbers;
    int index;
    int range;

} ThreadData;
void *ThreadFunc(void *args)
{
    ThreadData *passed_data = (ThreadData *)args;
    int res = 0;
    for (int i = passed_data->index * passed_data->range; i < (passed_data->index + 1) * passed_data->range; i++)
    {
        res += passed_data->numbers[i];
    }
    printf("%d chunk ---> %d\n", passed_data->index + 1, res);
}

int main()
{
    int n, m;
    scanf("%d  %d", &n, &m);
    int *numbers = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        numbers[i] = i + 1;
    }
    pthread_t threads[m];

    ThreadData ds[m];

    for (int i = 0; i < m; i++)
    {
        ds[i].numbers = numbers;
        ds[i].index = i;
        ds[i].range = n / m;
        pthread_create(&threads[i], NULL, ThreadFunc, &ds[i]);
    }

    for (int i = 0; i < m; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}