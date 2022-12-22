#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// C program to multiply two rectangular matrices
// https://www.geeksforgeeks.org/c-program-multiply-two-matrices/
double** multiply(int m1, int m2, double** mat1, int n1, int n2, double** mat2)
{
    int x, i, j;
    double** res = (double **)malloc(m1 * sizeof(double*));
    for (i = 0; i < m1; i++) 
    {
        res[i] = (double *)malloc(n1 * sizeof(double));
        for (j = 0; j < n2; j++) 
        {
            res[i][j] = 0;
            for (x = 0; x < m2; x++) 
            {
                *(*(res + i) + j) += *(*(mat1 + i) + x) * *(*(mat2 + x) + j);
            }
        }
    }
    return res;
}

void print2d(double **A, int x, int y)
{
    printf("\n");
    int i, j;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            printf("%.5f \t", A[i][j]);
        }
        printf("\n");
    }
}

int findmain(double **matrix, int ROW, int num)
{
    int maxRowindex = ROW, i;
    float maxRowvalue; 
    maxRowvalue = fabs(matrix[ROW][ROW]);
    for(i = ROW; i < num; i++)
    {
        if(fabs(matrix[i][ROW]) > maxRowvalue)
        {
            maxRowvalue = fabs(matrix[i][ROW]);
            maxRowindex = i;
            printf("\nin find main i: %d\n", i);
        }
    }
    printf("\nin find main max: %d\n", maxRowindex);
    return maxRowindex;
}

int main()
{
    float tmp;
    int i, j, k;
    int numOfVariable = 4;

    double** permu_mat = (double **)malloc(numOfVariable * sizeof(double*));
    double** matrix = (double **)malloc(numOfVariable * sizeof(double*));
    double** lower = (double **)malloc(numOfVariable * sizeof(double*));

    for(i = 0; i < numOfVariable; i++)
    {
        permu_mat[i] = (double *)malloc(numOfVariable * sizeof(double));
        matrix[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));
        lower[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));

        printf("\n input the col[%d]: ", i+1);
        for(j = 0; j < numOfVariable + 1; j++)
        {
            scanf("%f", &tmp);
            matrix[i][j] = tmp;
            if(i == j)
            {
                permu_mat[i][j] = 1;
            }
        }
    }
    printf("\nA:");
    print2d(matrix, numOfVariable, numOfVariable);
    // 計算PA=LU
    // suppose A=M*n, L=(zero matrix)m*m, P=(identity matrix)m*m
    // start with i = j = 1;

    double ratio;
    double sum, ans[numOfVariable];
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
        temp = permu_mat[k];
        permu_mat[k] = permu_mat[maxRowindex];
        permu_mat[maxRowindex] = temp;
        temp = lower[k];
        lower[k] = lower[maxRowindex];
        lower[maxRowindex] = temp;
        printf("\nmatrix:");
        print2d(matrix, numOfVariable, numOfVariable);
        printf("k: %d, index: %d\n", k, maxRowindex);
        for(i = k+1; i < numOfVariable; i++)
        {
            printf("\n ik: %f, kk: %f", matrix[i][k], matrix[k][k]);
            ratio = matrix[i][k] / matrix[k][k];
            lower[i][k] = ratio;
            for(j = 0; j <= numOfVariable; j++)
            {
                matrix[i][j] = matrix[i][j] - ratio* matrix[k][j];
            }
            printf("\nL:");
            print2d(lower, numOfVariable, numOfVariable);
            printf("\nU:");
            print2d(matrix, numOfVariable, numOfVariable);
            printf("\nP:");
            print2d(permu_mat, numOfVariable, numOfVariable);
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
    // lower 對角線=1
    for(i = 0; i < numOfVariable; i++)
    {
        lower[i][i] = 1;
    }
    printf("\nL:");
    print2d(lower, numOfVariable, numOfVariable);
    printf("\nU:");
    print2d(matrix, numOfVariable, numOfVariable);
    printf("\nP:");
    print2d(permu_mat, numOfVariable, numOfVariable);
    printf("\nmatrix:");
    print2d(matrix, numOfVariable, numOfVariable+1);

    printf("\nans: ( ");
    for(i = 0; i < numOfVariable-1; i++)
    {
        printf("%f, ", ans[i]);
    }
    printf("%f )\n", ans[i]);
}