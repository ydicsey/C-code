#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define numOfVariable 3
#define maxstep 100

void printDf(double Df[][3])
{
    int i, j;
    for(int i = 0; i < numOfVariable ;i++)
    {
        for(j = 0; j < numOfVariable; j++)
        {
            printf(" %f ", Df[i][j]); 
        }
        printf("\n");
    }
}

void print2d(double **A, int x, int y)
{
    printf("\n");
    int i, j;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            printf("%.2f \t", A[i][j]);
        }
        printf("\n");
    }
}

int findmain(double **matrix, int ROW, int num)
{
    int maxRowindex = ROW, i;
    float maxRowvalue; 
    maxRowvalue = fabs(matrix[ROW][ROW]);
    for(i = ROW; i < num-1; i++)
    {
        if(fabs(matrix[i+1][i]) > maxRowvalue)
        {
            maxRowvalue = fabs(matrix[i+1][i]);
            maxRowindex = i+1;
        }
    }
    return maxRowindex;
}

void pviotGu(double Df[][numOfVariable], double F[numOfVariable], double S[numOfVariable])
{
    int i, j, k;
    double **matrix = (double **)malloc(numOfVariable * sizeof(double*));
    double sum;
    // 創建一個增廣矩陣
    for(i = 0; i < numOfVariable; i++)
    {
        matrix[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));
        for(j = 0; j < numOfVariable ; j++)
        {
            matrix[i][j] = Df[i][j];
        }
        matrix[i][3] = -F[i];
    }

    double ratio;
    double * temp = (double*)malloc(numOfVariable * sizeof(double));
    int maxRowindex;

    // 開始找最大的 row index
    for(k = 0; k < numOfVariable; k++)
    {
        maxRowindex = findmain(matrix, k, numOfVariable);
        // 交換row k<->maxindex
        temp = matrix[k];
        matrix[k] = matrix[maxRowindex];
        matrix[maxRowindex] = temp;
        // print2d(matrix, numOfVariable, numOfVariable + 1);
        // printf("k: %d, index: %d\n", k, maxRowindex);
        for(i = k+1; i < numOfVariable; i++)
        {
            // printf("ik: %f, kk: %f", matrix[i][k], matrix[k][k]);
            ratio = matrix[i][k] / matrix[k][k];
            for(j = 0; j <= numOfVariable + 1; j++)
            {
                matrix[i][j] = matrix[i][j] - ratio* matrix[k][j];
            }
        }
    }

    matrix[numOfVariable-1][numOfVariable] = matrix[numOfVariable-1][numOfVariable] / matrix[numOfVariable-1][numOfVariable-1];
    for(i = numOfVariable - 1; i > 0; i--)
    {
        // print2d(matrix, numOfVariable, numOfVariable + 1);
        sum = 0;
        for(j = i; j < numOfVariable; j++)
        {
            // sum += matrix[i-1][j] * ans[j];
            sum += matrix[i-1][j] * matrix[i][numOfVariable];
            // printf("%.1f\n", sum);
        }
        sum *= -1;
        sum += matrix[i-1][j];
        // ans[i-1] = sum/matrix[i-1][i-1];
        matrix[i-1][numOfVariable] = sum/matrix[i-1][i-1];
    }

    for(i = 0; i < numOfVariable; i++)
    {
        S[i] = matrix[i][numOfVariable];
    }
}

void Df_mul_x(double Df[][3], double h, double k, double r)
{
    Df[0][0] = 16 + 2*h;
    Df[0][1] = 8 + 2*k;
    Df[0][2] = -2 * r;
    Df[1][0] = -12 + 2*h;
    Df[1][1] = -18 + 2*k;
    Df[1][2] = -2 * r;
    Df[2][0] = -8 + 2*h;
    Df[2][1] = 18 + 2*k;
    Df[2][2] = -2 * r;
}

void F_mul_x(double F[3], double h, double k, double r)
{
    F[0] = (8+h) * (8+h) + (4+k) * (4+k) - r*r;
    F[1] = (6-h) * (6-h) + (9-k) * (9-k) - r*r;
    F[2] = (4-h) * (4-h) + (9+k) * (9+k) - r*r;
}

void Df_mul_x2(double Df[][3], double h, double k, double r)
{
    Df[0][0] = cos(h);
    Df[0][1] = 2*k;
    Df[0][2] = pow(r, -1);
    Df[1][0] = 3;
    Df[1][1] = 2;
    Df[1][2] = -3*pow(r,2);
    Df[2][0] = 1;
    Df[2][1] = 1;
    Df[2][2] = 1;
}

void F_mul_x2(double F[3], double h, double k, double r)
{
    F[0] = sin(h) + k*k + log(r) - 7;
    F[1] = 3*h + 2*k - pow(r, 3) + 1;
    F[2] = h + k + r - 5;
}

int main()
{
    int i, j, k, rightOrNot;
    int step = 0;
    double error = 0.0000000001;
    // initial guess every unknows as 0
    double F[numOfVariable] = {0};
    double X_value[numOfVariable] = {2, 1, 3};
    // printf("\nX: %f, %f, %f\n", X_value[0], X_value[1], X_value[2]);
    // jacobi matrix
    double Df[numOfVariable][numOfVariable] = {0};
    // s
    double S[numOfVariable] = {0};

    while(step < maxstep)
    {
        Df_mul_x(Df, X_value[0], X_value[1], X_value[2]);
        F_mul_x(F, X_value[0], X_value[1], X_value[2]);
        step ++;

        // Dfx * s = -Fx
        // 用高斯消去法解
        pviotGu(Df, F, S);
        // printf("\ns: %f, %f, %f\n", S[0], S[1], S[2]);
        // printf("\nF: %f, %f, %f\n", F[0], F[1], F[2]);
        X_value[0] += S[0];
        X_value[1] += S[1];
        X_value[2] += S[2];
        for(i = 0; i < numOfVariable; i++)
        {
            rightOrNot = (fabs(S[i]) < error) ? 1:0;
        }
        if(rightOrNot)
        {
            printf("\t test1\nstep: %d", step);
            printf("\nX: %f, %f, %f\n", X_value[0], X_value[1], X_value[2]);
            break;
        }
        rightOrNot = 0;
    }
    step = 0;
    X_value[0] = 3;
    X_value[1] = 2;
    X_value[2] = 2;
    while(step < maxstep)
    {
        Df_mul_x2(Df, X_value[0], X_value[1], X_value[2]);
        F_mul_x2(F, X_value[0], X_value[1], X_value[2]);
        step ++;

        // Dfx * s = -Fx
        // 用高斯消去法解
        pviotGu(Df, F, S);
        // printf("\ns: %f, %f, %f\n", S[0], S[1], S[2]);
        // printf("\nF: %f, %f, %f\n", F[0], F[1], F[2]);
        X_value[0] += S[0];
        X_value[1] += S[1];
        X_value[2] += S[2];
        for(i = 0; i < numOfVariable; i++)
        {
            rightOrNot = fabs(S[i]) < error ? 1:0;
        }
        if(rightOrNot)
        {
            printf("\t test2\nstep: %d", step);
            printf("\nX: %f, %f, %f\n", X_value[0], X_value[1], X_value[2]);
            return 0;
        }
        rightOrNot = 0;
    }
}