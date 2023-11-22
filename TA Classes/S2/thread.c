#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct
{
    char *firstname;
    char *lastname;
    int Age;
} Person;
// passing string
void *ThreadFunc1(void *args)
{
    char *passed_arg = (char *)args;
    printf("passed argumnet is : %s \n", passed_arg);
}
// passing int*
void *ThreadFunc2(void *args)
{
    int *passed_number = (int *)args;
    printf("%d\n", *passed_number);
}
// passing array (calloc malloc)
void *ThreadFunc3(void *args)
{
    int *numbers = (int *)args;
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", numbers[i]);
    }
}
// passing struct
void *ThreadFunc4(void *args)
{
    Person *p = (Person *)args;
    printf("%s\n", p->firstname);
    printf("%s\n", p->lastname);
    printf("%d\n", p->Age);
}
int main()
{
    pthread_t ps[4];
    pthread_create(&ps[0], NULL, ThreadFunc1, "first thread");
    int a = 1000000;
    pthread_create(&ps[1], NULL, ThreadFunc2, &a);
    int *numbers = malloc(4 * sizeof(int));
    for (int i = 0; i < 4; i++)
    {
        numbers[i] = i + 10;
    }
    pthread_create(&ps[2], NULL, ThreadFunc3, numbers);

    Person p = {"sobhan", "kazemi", 22};
    pthread_create(&ps[3], NULL, ThreadFunc4, &p);
    for (int i = 0; i < 4; i++)
    {
        pthread_join(ps[i], NULL);
    }
    free(numbers);
}
