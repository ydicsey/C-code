#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "math.h"

#define N 3
#define NumOfvariable 1

/* 
    4*k     = 3
    7*k     = 5
    11*k    = 8
*/

// ATA * x = ATb
int main()
{
    // double a_A[N][NumOfvariable];
    double a_A[N][NumOfvariable] = {{4}, {7}, {11}};

    printf("\nA:\n");
    mat A = matrix_copy(NumOfvariable, a_A, N);
    matrix_show(A);
    mat AT = matrix_getTranspose(A);
    printf("\nAT:\n");
    matrix_show(AT);
    mat ATA = matrix_mul(AT, A);
    printf("\nATA:\n");
    matrix_show(ATA);
    // AT * B
    double a_B[1][N] = {3, 5, 8};

    mat B = matrix_copy(N, a_B, 1);
    B = matrix_getTranspose(B);
    printf("\nB:\n");
    matrix_show(B);

    mat ATB = matrix_mul(AT, B);
    printf("\nATB:\n");
    matrix_show(ATB);
    
    mat matrix_full = extension(ATA, ATB);
    mat x_k = gaussian_pviot(matrix_full);
    matrix_show(x_k);
}