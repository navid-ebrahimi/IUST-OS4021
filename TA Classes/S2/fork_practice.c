#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int sum(int numbers[], int startindex)
{
    int result = 0;
    for (int i = startindex * 10; i < (startindex + 1) * 10; i++)
    {
        result += numbers[i];
    }
    return result;
}

int main()
{
    int numbers[40];
    for (int i = 0; i < 40; i++)
    {
        numbers[i] = i;
    }
    int res = 0;
    for (int i = 0; i < 4; i++)
    {
        int temp = vfork();
        if (temp == 0)
        {
            res += sum(numbers, i);
            exit(0);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        wait(NULL);
    }
    printf("%d\n", res);
    return 0;
}