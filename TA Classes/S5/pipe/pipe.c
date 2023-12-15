#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int mypipe[2];

int main(){
    // srand(time(NULL));
    pipe(mypipe);

    int pid = fork();
    if (pid == 0){
        int i = 0;
        while(1){
            // randnumw = rand();
            write(mypipe[1], &i, sizeof(int));
            // sleep(1);
            i++;
            printf("input -> %d\n", i);
        }
    }

    if (pid > 0){
        int randnum = 0;
        while(1){
            read(mypipe[0], &randnum, sizeof(int));
            printf("rand num is: %d\n", randnum);
            sleep(2);
        }
    }
    return 0;
}