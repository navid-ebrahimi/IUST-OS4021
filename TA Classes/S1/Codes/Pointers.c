// #include <stdio.h>
// int main()
// {
//     int a=10; //variable declaration
//     int *p; //pointer variable declaration
//     p=&a; //store address of variable a in pointer p
//     printf("Address stored in a variable p is:%x\n",p); 
//     printf("Value stored in a variable p is:%d\n",*p); 

//     int myNumbers[4] = {25, 50, 75, 100};
//     printf("%d\n", *(myNumbers + 1));
//     printf("%d", *(myNumbers + 2));
//     return 0;
// }



// extra point


int main()
{
    int arr1[5][5] = { { 0, 1, 2, 3, 4 },
                       { 2, 3, 4, 5, 6 },
                       { 4, 5, 6, 7, 8 },
                       { 5, 4, 3, 2, 6 },
                       { 2, 5, 4, 3, 1 } };
    // int* arr2[5][5];
    // for (int i = 0; i < 5; i++) {
    //     for (int j = 0; j < 5; j++) {
    //         arr2[i][j] = &arr1[i][j];
    //     }
    // }
    // printf("???????\n");
    // for (int i = 0; i < 5; i++) {
    //     for (int j = 0; j < 5; j++) {
    //         printf("%d ", *arr2[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d ",*(*(arr1+1)+1));
    return 0;
}