// #include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main()
{
    int x = 0;
    int f1 = fork();
    if (f1 == 0)
    {
        printf("im the child and my pid is %d\n" , getpid());
        x++;
        exit(0);
    }
    else
    {
        sleep(10);
        int status;
        wait(&status);
    }
    // printf("%d\n", x);
    return 0;
}