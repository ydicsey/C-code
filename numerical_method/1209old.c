#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define M 4
#define N 3
#define numOfVariable 3
#define maxstep 100
// 4 nonlinear equations, 3 unknowns

void printDr(double Dr[M][N])
{
    int i, j;
    for(int i = 0; i < numOfVariable ;i++)
    {
        for(j = 0; j < numOfVariable; j++)
        {
            // printf(" %f ", Dr[i][j]); 
        }
        // printf("\n");
    }
}

void print2d(double **A, int x, int y)
{
    // printf("\n");
    int i, j;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            // printf("%.2f \t", A[i][j]);
        }
        // printf("\n");
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

void getTranspose(double Dr[M][N], double DrT[N][M], int row, int column)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j) 
        {
            DrT[j][i] = Dr[i][j];
        }
    }
}

void Dr_mul(double Dr[M][N], double x, double y, double k)
{
    Dr[0][0] = (x + 1) / sqrt(pow((x + 1), 2) + pow(y, 2) ) - 1;
    Dr[0][1] = y / sqrt(pow((x + 1), 2) + pow(y, 2) ) - 1;
    Dr[0][2] = -1;
    Dr[1][0] = (x - 1) / sqrt(pow((x - 1), 2) + pow((y - 0.5), 2) ) - 1;
    Dr[1][1] = (y - 0.5) / sqrt(pow((x - 1), 2) + pow((y - 0.5), 2) ) - 1;
    Dr[1][2] = -1;
    Dr[2][0] = (x - 1)  / sqrt(pow((x - 1), 2) + pow((y + 0.5), 2) ) - 1;
    Dr[2][1] = (y + 0.5)  / sqrt(pow((x - 1), 2) + pow((y + 0.5), 2) ) - 1;
    Dr[2][2] = -1;
    Dr[3][0] = x  / sqrt(pow(x, 2) + pow((y - 1), 2) ) - 1;
    Dr[3][1] = (y - 1) / sqrt(pow(x, 2) + pow((y - 1), 2) ) - 1;
    Dr[3][2] = -1;
}

double r_fun(double x, double y, double r, double x1, double y1, double k)
{
    return(sqrt(pow((x - x1), 2) + pow((y - y1), 2)) - (r+k));
}
void get_vk(double Dr[M][N], double v[N], double value[N])
{
    double DrT[N][M] = {0};
    double DrTDr[N][N] = {0};
    getTranspose(Dr, DrT, M, N);
    // DrT * Dr
    // printf("DrTDr\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            DrTDr[i][j] = 0;
        }
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < M; k++)
            {
                DrTDr[i][j] += DrT[i][k] * Dr[k][j];
            }
            // printf(" %f ",  DrTDr[i][j]);
        }
        // printf("\n");
    }

    double r[M] = {0};
    r[0] = r_fun(-1, 0, 1, value[0], value[1], value[2]);
    r[1] = r_fun(1, 0.5, 0.5, value[0], value[1], value[2]);
    r[2] = r_fun(1, -0.5, 0.5, value[0], value[1], value[2]);
    r[3] = r_fun(0, 1, 0.5, value[0], value[1], value[2]);

    // DrT * r
    double DrTr[N] = {0};
    // printf("\nDrTr\n");
    for(int i = 0; i < N; i++)
    {
        DrTr[i] = 0.0;
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            DrTr[i] += DrT[i][j] * r[j];
            // printf("%d, %d, %f * %f = %f\n", i, j, AT[i][j], B[j], ATB[i]);
        }
        // printf("  %f  ", DrTr[i]);
        // printf("\n");
    }

    // sol: DrTDr = DrTr
    double tmp;
    int i, j, k;

    double** matrix = (double **)malloc(numOfVariable * sizeof(double*));

    for(i = 0; i < numOfVariable; i++)
    {
        matrix[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));

        for(j = 0; j < numOfVariable; j++)
        {
            matrix[i][j] = DrTDr[i][j];
        }
        matrix[i][j] = -DrTr[i];
    }
    // 計算PA=LU
    // suppose A=M*n, L=(zero matrix)m*m, P=(identity matrix)m*m
    // start with i = j = 1;

    double ratio;
    double sum, ans[numOfVariable];
    double *temp = (double*)malloc(numOfVariable * sizeof(double));
    int maxRowindex;

    // 開始找最大的 row index
    for(k = 0; k < numOfVariable; k++)
    {
        maxRowindex = findmain(matrix, k, numOfVariable);
        // 交換row k<->maxindex
        temp = matrix[k];
        matrix[k] = matrix[maxRowindex];
        matrix[maxRowindex] = temp;
        // printf("\nmatrix:");
        // print2d(matrix, numOfVariable, numOfVariable+1);
        // printf("k: %d, index: %d\n", k, maxRowindex);
        for(i = k+1; i < numOfVariable; i++)
        {
            // printf("\n ik: %f, kk: %f", matrix[i][k], matrix[k][k]);
            ratio = matrix[i][k] / matrix[k][k];
            for(j = 0; j <= numOfVariable; j++)
            {
                matrix[i][j] = matrix[i][j] - ratio* matrix[k][j];
            }
            // printf("\nL:");
            // print2d(lower, numOfVariable, numOfVariable);
            // printf("\nU:");
            // print2d(matrix, numOfVariable, numOfVariable);
            // printf("\nP:");
            // print2d(permu_mat, numOfVariable, numOfVariable);
        }

        ans[numOfVariable - 1] = matrix[numOfVariable-1][numOfVariable] / matrix[numOfVariable-1][numOfVariable-1];
        // matrix[numOfVariable-1][numOfVariable] = matrix[numOfVariable-1][numOfVariable] / matrix[numOfVariable-1][numOfVariable-1];
        for(i = numOfVariable - 1; i > 0; i--)
        {
            // print2d(matrix, numOfVariable, numOfVariable + 1);
            sum = 0;
            for(j = i; j < numOfVariable; j++)
            {
                sum += matrix[i-1][j] * ans[j];
                // sum += matrix[i-1][j] * matrix[i][numOfVariable];
                // printf("%.1f\n", sum);
            }
            sum *= -1;
            sum += matrix[i-1][j];
            ans[i-1] = sum/matrix[i-1][i-1];
            // matrix[i-1][numOfVariable] = sum/matrix[i-1][i-1];
        }
    }
    for(i = 0; i < numOfVariable; i++)
    {
        v[i] = ans[i];
    }
}

int main()
{
    int i, j, k, rightOrNot;
    int step = 0;
    double error = 0.0000000001;
    // initial guess every unknows as 0
    double value[numOfVariable] = {0.1, 0.1, 0.1};
    // printf("\nX: %f, %f, %f\n", X_value[0], X_value[1], X_value[2]);
    double Dr[M][N] = {0};
    // s
    double v[numOfVariable] = {0};

    while(step < maxstep)
    {
        Dr_mul(Dr, value[0], value[1], value[2]);
        step ++;
        
        get_vk(Dr, v, value);
        // printf("\ns: %f, %f, %f\n", S[0], S[1], S[2]);
        // printf("\nF: %f, %f, %f\n", F[0], F[1], F[2]);
        value[0] += v[0];
        value[1] += v[1];
        value[2] += v[2];
        // printf("v0: %f, v1: %f, v2: %f\n", v[0], v[1], v[2]);
        for(i = 0; i < numOfVariable; i++)
        {
            rightOrNot = (fabs(v[i]) < error) ? 1:0;
        }
        if(rightOrNot)
        {
            printf("\nstep: %d", step);
            printf("\nX: %f, %f, %f\n", value[0], value[1], value[2]);
            return 0;
        }
        rightOrNot = 0;
    }
    printf("\nX: %f, %f, %f\n", value[0], value[1], value[2]);
}