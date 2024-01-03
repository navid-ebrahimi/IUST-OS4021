#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    srand(time(NULL));
    int mypipe[2];
    pipe(mypipe);

    int pid = fork();
    if (pid == 0)
    {
        for (size_t i = 0; i < 100; i++)
        {
            int randnum = rand();
            write(mypipe[1], &randnum, sizeof(int));
        }
    }

    if (pid > 0)
    {
        int odds = 0;
        int evens = 0;
        for (size_t i = 0; i < 100; i++)
        {
            int randnum = 0;
            read(mypipe[0], &randnum, sizeof(int));
            if (randnum % 2 == 0)
            {
                evens++;
            }
            else
            {
                odds++;
            }
        }
        printf("Number of odd numbers : %d\nNumber of even numbers : %d\n", odds, evens);
    }
    wait(NULL);
    return 0;
}