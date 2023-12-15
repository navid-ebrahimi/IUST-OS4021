#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int mypipe[3][2];

int main(){
    srand(time(NULL));

    pipe(mypipe[0]);
    pipe(mypipe[1]);
    pipe(mypipe[2]);

    int pid1 = fork();
    if(pid1 == 0){
        int nums1 = 0;
        while (1){
            read(mypipe[0][0], &nums1, sizeof(int));
            nums1 = nums1 * nums1;
            write(mypipe[1][1], &nums1, sizeof(int));
        }

        exit(0);
    }


    int pid2 = fork();
    if(pid2 == 0){
        int nums2 = 0;
        while (1){
            read(mypipe[1][0], &nums2, sizeof(int));
            nums2 = nums2 * 2;
            write(mypipe[2][1], &nums2, sizeof(int));
        }
        
        exit(0);
    }

    int pid3 = fork();
    if(pid3 == 0){
        int nums3 = 0;
        while (1){
            read(mypipe[2][0], &nums3, sizeof(int));
            printf("output -> %d\n", nums3 + 2);
        }
        
        exit(0);
    }

    int randnum = 0;
    while (1){
        randnum = rand() % 10;
        printf("input -> %d\n", randnum);
        write(mypipe[0][1], &randnum, sizeof(int));
        sleep(2);
    }

    return 0;
}