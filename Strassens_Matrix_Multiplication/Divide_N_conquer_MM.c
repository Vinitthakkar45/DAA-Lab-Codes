#include <stdio.h>
#include <stdlib.h>

#define ROW_1 8
#define COL_1 8   // 🙃 here I am just defining rows and colums of 
#define ROW_2 8   // two matrix that are multiplied
#define COL_2 8

void printMat(int a[][COL_2], int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void add_matrix(int row,int col, int A[row][col], int B[row][col], int C[row][col]) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiply_matrix(int row, int col, int A[row][col], int B[row][col], int C[row][col] ) {
    if (row == 1 && col == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    } else {
        int newSize = row / 2;
        int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
        int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
        int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
        int temp1[newSize][newSize], temp2[newSize][newSize];


        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        multiply_matrix( newSize, newSize, A11, B11, temp1);
        multiply_matrix(newSize,newSize,A12, B21, temp2);
        add_matrix(newSize,newSize,temp1, temp2, C11);

        multiply_matrix(newSize,newSize,A11, B12, temp1);
        multiply_matrix(newSize,newSize,A12, B22, temp2);
        add_matrix(newSize,newSize,temp1, temp2, C12);

        multiply_matrix(newSize,newSize,A21, B11, temp1);
        multiply_matrix(newSize,newSize,A22, B21, temp2);
        add_matrix(newSize,newSize,temp1, temp2, C21);

        multiply_matrix(newSize,newSize,A21, B12, temp1);
        multiply_matrix(newSize,newSize,A22, B22, temp2);
        add_matrix(newSize,newSize,temp1, temp2, C22);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }
}

int main() {
    int matrix_A[ROW_1][COL_1] = {{1, 1, 1, 1,1,1,1,1},
                                   {2, 2, 2, 2,2,2,2,2},
                                   {3, 3, 3, 3,3,3,3,3},
                                   {2, 2, 2, 2,2,2,2,2},
                                   {1, 1, 1, 1,1,1,1,1},
                                   {2, 2, 2, 2,2,2,2,2},
                                   {3, 3, 3, 3,3,3,3,3},
                                   {2, 2, 2, 2,2,2,2,2}};

    printf("Array A =>\n");
    printMat(matrix_A, ROW_1, COL_1);

    int matrix_B[ROW_2][COL_2] = {{1, 1, 1, 1,1,1,1,1},
                                   {2, 2, 2, 2,2,2,2,2},
                                   {3, 3, 3, 3,3,3,3,3},
                                   {2, 2, 2, 2,2,2,2,2},
                                   {1, 1, 1, 1,1,1,1,1},
                                   {2, 2, 2, 2,2,2,2,2},
                                   {3, 3, 3, 3,3,3,3,3},
                                   {2, 2, 2, 2,2,2,2,2}};
    printf("Array B =>\n");
    printMat(matrix_B, ROW_2, COL_2);

    int result_matrix[ROW_1][COL_2];
    multiply_matrix( ROW_1, COL_2 , matrix_A, matrix_B, result_matrix);

    printf("Result Array =>\n");
    printMat(result_matrix, ROW_1, COL_2);

    return 0;
}