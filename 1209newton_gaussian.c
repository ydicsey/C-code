#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mat.h"

// 4 nonlinear equations, 3 unknowns
#define M 4
#define N 3
#define maxstep 10

double r_fun(double x, double y, double r, double x1, double y1, double k)
{
    return(sqrt(pow((x - x1), 2) + pow((y - y1), 2) ) - (r+k));
}

void r_mul(double r[][M], double value[N])
{
    r[0][0] = r_fun(-1, 0, 1, value[0], value[1], value[2]);
    r[0][1] = r_fun(1, 0.5, 0.5, value[0], value[1], value[2]);
    r[0][2] = r_fun(1, -0.5, 0.5, value[0], value[1], value[2]);
    r[0][3] = r_fun(0, 1, 0.5, value[0], value[1], value[2]);
}
// Dr(M *N)
void Dr_mul(double Dr[M][N], double x, double y)
{
    Dr[0][0] = (x + 1) / sqrt((pow((x + 1), 2) + pow(y, 2)) );
    Dr[0][1] = y / sqrt(pow((x + 1), 2) + pow(y, 2) );
    Dr[0][2] = -1;
    Dr[1][0] = (x - 1) / sqrt((pow((x - 1), 2) + pow((y - 0.5), 2)) );
    Dr[1][1] = (y - 0.5) / sqrt((pow((x - 1), 2) + pow((y - 0.5), 2)) );
    Dr[1][2] = -1;
    Dr[2][0] = (x - 1) / sqrt((pow((x - 1), 2) + pow((y + 0.5), 2)) );
    Dr[2][1] = (y + 0.5) / sqrt((pow((x - 1), 2) + pow((y + 0.5), 2)) );
    Dr[2][2] = -1;
    Dr[3][0] = x / sqrt((pow(x, 2) + pow((y - 1), 2)) );
    Dr[3][1] = (y - 1) / sqrt((pow(x, 2) + pow((y - 1), 2)) );
    Dr[3][2] = -1;
}

int main()
{
    int step = 0;
    double a_Dr[M][N] = {0};
    double a_r[1][M] = {0};
    double x_k[N] = {0.1, 0.1, 0.1};

    int rightOrNot;
    double error = 0.0000000001;
    while(step < maxstep)
    {
        Dr_mul(a_Dr, x_k[0], x_k[1]);
        mat A = matrix_copy(N, a_Dr, M);
        r_mul(a_r, x_k);
        mat r = matrix_copy(M, a_r, 1);
        // puts("A");
        // matrix_show(A);
        // puts("r");
        // matrix_show(r);
        
        mat AT = matrix_getTranspose(A);
        // puts("AT");
        // matrix_show(AT);
        mat ATA = matrix_mul(AT, A);
        // puts("ATA");
        // matrix_show(ATA);
        r = matrix_getTranspose(r);
        // matrix_show(r);
        mat ATB = matrix_mul(AT, r);
        // puts("ATB");
        // matrix_show(ATB);
        for(int i = 0; i < ATB->m; i++)
        {
            ATB->v[0][i] *= -1;
        }
        // puts("ATB");
        // matrix_show(ATB);
        mat matrix_full = extension(ATA, ATB);
        // matrix_show(matrix_full);

        mat v_k = gaussian_pviot(matrix_full);
        // matrix_show(v_k);

        x_k[0] += v_k->v[0][0];
        x_k[1] += v_k->v[0][1];
        x_k[2] += v_k->v[0][2];
        for(int i = 0; i < v_k->n; i++)
        {
            rightOrNot = (fabs(v_k->v[0][i]) < error) ? 1:0;
        }
        if(rightOrNot)
        {
            printf("step: %d", step);
            printf("\nX: %.4f, %.4f, %.4f\n", x_k[0], x_k[1], x_k[2]);
            return 0;
        }
        rightOrNot = 0;

        step++;
    }
    printf(" %.4f, %.4f, %.4f\n\n", x_k[0], x_k[1], x_k[2]);
    return 0;
}
