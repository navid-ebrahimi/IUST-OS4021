#include<stdio.h>
#include<unistd.h>

int main()
{
  int x = 10;
  pid_t pid = fork();
  x++;
  printf("%d\n", x);
}