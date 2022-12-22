#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "math.h"

#define N 10
#define NumOfvariable 2

// fit function: a + bx + cx^2 + dx^3

// model: y = c1 * t^c2
// fit function: ln(y) = ln(c1) + c2ln(t)
//                     =    k   + c2ln(t)
// fit function: 16.3 * t^2.42

// ATA * x = ATb
int main()
{
    double a_A[N][NumOfvariable];
    // double x[N] = {0.0 , 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5 , 2.75, 3.0 };
    double x[N] = {0.912, 0.986, 1.06, 1.13, 1.19, 1.26, 1.32, 1.38, 1.41, 1.49};
    // create A
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < NumOfvariable; j++)
        {
            // printf("%d %d\n", i, j);
            switch(j)
            {
                case 0:
                {
                    // fit function: a + bx + cx^2 + dx^3
                    // a_A[i][j] = 1;
                    a_A[i][j] = 1;
                    break;
                }
                case 1:
                {
                    // a_A[i][j] = x[i];
                    a_A[i][j] = log(x[i]);
                    break;
                }
                case 2:
                {
                    a_A[i][j] = x[i] * x[i];
                    break;
                }
                case 3:
                {
                    a_A[i][j] = x[i] * x[i] * x[i];
                    break;
                }
            }
            // printf("  %f  ", a_A[i][j]);
        }
        // printf("\n");
    }

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
    // double a_B[1][N] = {6.3806, 7.1338, 9.1662, 11.5545, 15.6414, 22.7371, 32.0696, 47.0756, 73.1596, 111.4684, 175.9895, 278.5550, 446.4441};
    double a_B[1][N] = {13.7, 15.9, 18.5, 21.3, 23.5, 27.2, 32.7, 36, 38.6, 43.7};
    for(int i = 0; i < N; i++)
    {
        a_B[0][i] = log(a_B[0][i]);
    }
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
    printf(" %f \n", exp(x_k->v[0][0]));
}