#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int mypipe[2];
    pipe(mypipe);

    int pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            char expression[30];
            read(mypipe[0], &expression, 30);
            printf("reversed string --> ");
            for (int i = strlen(expression) - 1; i >= 0; i--)
            {
                printf("%c", (char)expression[i]);
            }
            printf("\n");
        }
    }

    if (pid > 0)
    {
        while (1)
        {
            char expression[30];
            scanf("%s", expression);
            write(mypipe[1], &expression, 30);
        }
    }
    wait(NULL);
    return 0;
}