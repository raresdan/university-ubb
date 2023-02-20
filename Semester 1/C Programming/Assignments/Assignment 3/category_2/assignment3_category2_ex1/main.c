/*Multiply 2 matrices of integers*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num_rows1, num_cols1, num_rows2, num_cols2;
    int **matrix1, **matrix2, **result;

    printf("Enter the number of rows of matrix 1: ");
    scanf("%d", &num_rows1);
    printf("Enter the number of columns of matrix 1: ");
    scanf("%d", &num_cols1);

    printf("Enter the number of rows of matrix 2: ");
    scanf("%d", &num_rows2);
    printf("Enter the number of columns of matrix 2: ");
    scanf("%d", &num_cols2);

    if (num_cols1 != num_rows2) {
        printf("Error: The matrices cannot be multiplied.\n");
        return 1;
    }

    matrix1 = malloc(num_rows1 * sizeof(int*));
    if (matrix1 == NULL) {
        printf("Error allocating memory for matrix 1.\n");
        return 1;
    }
    matrix2 = malloc(num_rows2 * sizeof(int*));
    if (matrix2 == NULL) {
        printf("Error allocating memory for matrix 2.\n");
        return 1;
    }
    result = malloc(num_rows1 * sizeof(int*));
    if (result == NULL) {
        printf("Error allocating memory for result matrix.\n");
        return 1;
    }

    for (int i = 0; i < num_rows1; i++) {
        matrix1[i] = malloc(num_cols1 * sizeof(int));
        if (matrix1[i] == NULL) {
            printf("Error allocating memory for matrix 1.\n");
            return 1;
        }
    }
    for (int i = 0; i < num_rows2; i++) {
        matrix2[i] = malloc(num_cols2 * sizeof(int));
        if (matrix2[i] == NULL) {
            printf("Error allocating memory for matrix 2.\n");
            return 1;
        }
    }
    for (int i = 0; i < num_rows1; i++) {
        result[i] = malloc(num_cols2 * sizeof(int));
        if (result[i] == NULL) {
            printf("Error allocating memory for result matrix.\n");
            return 1;
        }
    }

    printf("Enter the elements of matrix 1: \n");
    for (int i = 0; i < num_rows1; i++) {
        for (int j = 0; j < num_cols1; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }
    printf("Enter the elements of matrix 2: \n");
    for (int i = 0; i < num_rows2; i++) {
        for (int j = 0; j < num_cols2; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    for (int i = 0; i < num_rows1; i++) {
        for (int j = 0; j < num_cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < num_cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    printf("Result: \n");
    for (int i = 0; i < num_rows1; i++) {
        for (int j = 0; j < num_cols2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < num_rows1; i++) {
        free(matrix1[i]);
        free(result[i]);
    }
    for (int i = 0; i < num_rows2; i++) {
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
    }


