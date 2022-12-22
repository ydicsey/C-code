#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <string.h>
// 高斯消去法 original augmented matrix >> A row echelon matrix >> The reduced row echelon matrix
void print2d(double **A, int n)
{
    printf("\n");
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j <= n; j++)
        {
            printf("%.2f \t", A[i][j]);
        }
        printf("\n");
    }
}

void printMatrix(double **A, int n)
{
    printf("\n");
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%.1f \t", A[i][j]);
        }
        printf("\n");
    }
}

void printAns(double **a, int n)
{
    printf("\nans: (");
    int i, j;
    for(i = 0; i < n - 1; i++)
    {
        // printf("%f %f %.2f\n", a[i][n], a[i][i], (a[i][n] / a[i][i]));
        printf("%.2f, ", a[i][n]);
    }
    printf("%.2f)\n", a[i][n]);
}

int main()
{
    int i, j ,k;
    float tmp;
    // 有多少個變數(未知數)
    int numOfVariable = 4;
    // 創建 original augmented matrix
    // double matrix[3][4] = {1, 2, -1, 3,
    //                        2, 1, -2, 3,
    //                        -3, 1, 1, -6};
    double **matrix = (double **)malloc(numOfVariable * sizeof(double*));
    double **lower = (double **)malloc(numOfVariable * sizeof(double*));
    // memset(lower, 0, sizeof(lower));

    for(i = 0; i < numOfVariable; i++)
    {
        matrix[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));
        lower[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));
        printf("\n input the col[%d]: ", i+1);
        for(j = 0; j <= numOfVariable; j++)
        {
            scanf("%f", &tmp);
            matrix[i][j] = tmp;
            if(i == j)
            {
                lower[i][j] = 1;
            }
        }
    }

    double ratio, ratio2;

    
    // step1: original augmented matrix >> A row echelon matrix
    // 計算Upper matrix
    for(k = 0; k < numOfVariable; k++)
    {
        for(i = 0; i < numOfVariable; i++)
        {
            if(i > k)
            {
                ratio = matrix[i][k] / matrix[k][k];
                lower[i][k] = ratio;
                for(j = 0; j <= numOfVariable; j++)
                {
                    matrix[i][j] = matrix[i][j] - ratio* matrix[k][j];
                }
            }
        }
    }

    printf("\nL:");
    printMatrix(lower, numOfVariable);
    printf("\nU:");
    printMatrix(matrix, numOfVariable);
    

    // step2: A row echelon matrix >> The reduced row echelon matrix
    double sum, ans[numOfVariable];
    ans[numOfVariable - 1] = matrix[numOfVariable-1][numOfVariable] / matrix[numOfVariable-1][numOfVariable-1];
    matrix[numOfVariable-1][numOfVariable] = matrix[numOfVariable-1][numOfVariable] / matrix[numOfVariable-1][numOfVariable-1];
    for(i = numOfVariable - 1; i > 0; i--)
    {
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
    // print2d(matrix, numOfVariable);
    printAns(matrix, numOfVariable);

    printf("\nans: ( ");
    for(i = 0; i < numOfVariable-1; i++)
    {
        printf("%.1f, ", ans[i]);
    }
    printf("%.1f )\n", ans[i]);
}