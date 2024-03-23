#include <stdio.h>
#include <stdlib.h>

void add_matrices(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract_matrices(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen_multiply(int n, int A[][n], int B[][n], int C[][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int A11[newSize][newSize], A12[newSize][newSize], A21[newSize][newSize], A22[newSize][newSize];
    int B11[newSize][newSize], B12[newSize][newSize], B21[newSize][newSize], B22[newSize][newSize];
    int C11[newSize][newSize], C12[newSize][newSize], C21[newSize][newSize], C22[newSize][newSize];
    int P[newSize][newSize], Q[newSize][newSize], R[newSize][newSize], S[newSize][newSize], T[newSize][newSize], U[newSize][newSize], V[newSize][newSize];
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

    subtract_matrices(newSize, B12, B22, temp1);
    strassen_multiply(newSize, A11, temp1, P); // P = A11 * (B12 - B22)

    add_matrices(newSize, A11, A12, temp1);
    strassen_multiply(newSize, temp1, B22, Q); // Q = (A11 + A12) * B22

    add_matrices(newSize, A21, A22, temp1);
    strassen_multiply(newSize, temp1, B11, R); // R = (A21 + A22) * B11

    subtract_matrices(newSize, B21, B11, temp1);
    strassen_multiply(newSize, A22, temp1, S); // S = A22 * (B21 - B11)

    add_matrices(newSize, A11, A22, temp1);
    add_matrices(newSize, B11, B22, temp2);
    strassen_multiply(newSize, temp1, temp2, T); // T = (A11 + A22) * (B11 + B22)

    subtract_matrices(newSize, A12, A22, temp1);
    add_matrices(newSize, B21, B22, temp2);
    strassen_multiply(newSize, temp1, temp2, U); // U = (A12 - A22) * (B21 + B22)

    subtract_matrices(newSize, A21, A11, temp1);
    add_matrices(newSize, B11, B12, temp2);
    strassen_multiply(newSize, temp1, temp2, V); // V = (A21 - A11) * (B11 + B12)

    // Calculate C matrices
    add_matrices(newSize, T, S, temp1);
    subtract_matrices(newSize, temp1, Q, temp2);
    add_matrices(newSize, temp2, U, C11); // C11 = T + S - Q + U

    add_matrices(newSize, P, Q, C12); // C12 = P + Q

    add_matrices(newSize, R, S, C21); // C21 = R + S

    add_matrices(newSize, T, P, temp1);
    subtract_matrices(newSize, temp1, R, temp2);
    subtract_matrices(newSize, temp2, V, C22); // C22 = T + P - R - V

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

void print_matrix(int n, int matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int size;
    printf("Enter the size of the matrices (Of power 2): ");
    scanf("%d", &size);

    int A[size][size], B[size][size], C[size][size];

    printf("Enter the elements of the first matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter the elements of the second matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    strassen_multiply(size, A, B, C);

    printf("Resultant Matrix:\n");
    print_matrix(size, C);

    return 0;
}