#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  int rows;
  int cols;
  printf("Enter number of rows of original array\n");
  scanf("%d", &rows);
  printf("Enter number of columns of original array\n");
  scanf("%d", &cols);
  int **mat = (int **)malloc(rows * sizeof(int*));
  for(int i = 0; i < rows; i++) mat[i] = (int *)malloc(cols * sizeof(int));
  printf("Enter the matrix elements\n");
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      scanf("%d", &mat[i][j]);
    }
  }

  int w_rows;
  int w_cols;
  printf("Enter number of rows of window array\n");
  scanf("%d", &w_rows);
  printf("Enter number of columns of window array\n");
  scanf("%d", &w_cols);
  int **window = (int **)malloc(w_rows * sizeof(int*));
  for(int i = 0; i < w_rows; i++) 
    window[i] = (int *)malloc(w_cols * sizeof(int));
  printf("Enter the window matrix elements\n");
  for (int i = 0; i < w_rows; i++)
  {
    for (int j = 0; j < w_cols; j++)
    {
      scanf("%d", &window[i][j]);
    }
  }
  clock_t start_t, end_t;
  double total_t;
  start_t = clock();
  int **result = (int **)malloc((rows - w_rows + 1) * sizeof(int*));
  for(int i = 0; i < (rows - w_rows + 1); i++) result[i] = (int *)malloc((cols - w_cols + 1) * sizeof(int));
  for (int i = 0; i < (rows - w_rows + 1); i++)
  {
    for (int j = 0; j < (cols - w_cols + 1); j++)
    {
      int sum = 0;
      for (int k = 0; k < w_rows; k++)
      {
        for (int l = 0; l < w_cols; l++)
        {
          sum += mat[i+k][j+l] * window[k][l];
        }
      }
      result[i][j] = sum;
    }
  }
  end_t = clock();
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Total time taken: %f\n", total_t);

  for (int i = 0; i < rows; i++)
    free(mat[i]);
  for (int i = 0; i < w_rows; i++)
    free(window[i]);
  for (int i = 0; i < (rows - w_rows + 1); i++)
    free(result[i]);
  free(mat);
  free(window);
  free(result);
}
