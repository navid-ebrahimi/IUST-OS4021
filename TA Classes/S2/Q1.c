#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int f1 = fork();
    if (f1 == 0)
    {
        printf("im the child and my parent pid is %d\n" , getppid());
        sleep(5);
        printf("im the child and my parent pid is %d\n" , getppid());
    }
    else
    {
        sleep(1);
    }
    return 0;
}