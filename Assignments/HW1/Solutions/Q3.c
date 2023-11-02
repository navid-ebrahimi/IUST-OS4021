#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to rotate the image by 90 degrees anticlockwise
void rotateImageAntiClockwise(int **image, int imageSize) {
    int **temp = (int **)malloc(imageSize * sizeof(int *));
    for (int i = 0; i < imageSize; i++) {
        temp[i] = (int *)malloc(imageSize * sizeof(int));
        for (int j = 0; j < imageSize; j++) {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            image[i][j] = temp[j][imageSize - i - 1];
        }
    }

    // Free the temporary array
    for (int i = 0; i < imageSize; i++) {
        free(temp[i]);
    }
    free(temp);
}


// Function to print the image
void printImage(int **image, int imageSize) {
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int imageSize;
    int numRotations;

    // Input the image size and num of rotations from the user
    scanf("%d", &imageSize);

    int **image = (int **)malloc(imageSize * sizeof(int *));
    for (int i = 0; i < imageSize; i++) {
        image[i] = (int *)malloc(imageSize * sizeof(int));
    }

    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            scanf("%d", &image[i][j]);
        }
    }

    if (image[0][imageSize - 1] == 0)
    {
        numRotations = 1; 
    }
    else if (image[imageSize - 1][imageSize - 1] == 0)
    {
        numRotations = 2;
    }
    else if (image[imageSize - 1][0] == 0)
    {
        numRotations = 3;
    }
    else
    {
        printImage(image, imageSize);
        return 0;
    }

    for (int j = 0; j < numRotations; j++) {
        rotateImageAntiClockwise(image, imageSize);
    }

    // Print the modified image
    printImage(image, imageSize);

    // Free the memory allocated for the image
    for (int i = 0; i < imageSize; i++) {
        free(image[i]);
    }
    free(image);

    return 0;
}
