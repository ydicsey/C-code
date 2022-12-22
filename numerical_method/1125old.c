#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define N 13
#define NumOfvariable 4

void multiplyMatrices(double firstMatrix[][N], double secondMatrix[][N], double multResult[][N], int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{	
    int i, j, k;

	// Initializing elements of matrix mult to 0.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			multResult[i][j] = 0;
		}
	}

	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			for(k=0; k < columnFirst; ++k)
			{
				multResult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}
}

void getTranspose(double A[][N], double T[][N], int row, int column)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j) 
        {
            T[j][i] = A[i][j];
        }
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
            // printf("\nin find main i: %d\n", i);
        }
    }
    // printf("\nin find main max: %d\n", maxRowindex);
    return maxRowindex;
}

int main()
{
    double A[N][NumOfvariable];
    double x[N] = {0.0 , 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5 , 2.75, 3.0 };
    // create A
    printf("\nA:\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < NumOfvariable; j++)
        {
            // printf("%d %d\n", i, j);
            switch(j)
            {
                case 0:
                {
                    A[i][j] = 1;
                    break;
                }
                case 1:
                {
                    A[i][j] = x[i];
                    break;
                }
                case 2:
                {
                    A[i][j] = x[i] * x[i];
                    break;
                }
                case 3:
                {
                    A[i][j] = x[i] * x[i] * x[i];
                    break;
                }
            }
            printf("  %f  ", A[i][j]);
        }
        printf("\n");
    }

    double AT[NumOfvariable][N];
    // get transpose
    printf("\nAT:\n");
    for(int i = 0; i < NumOfvariable; i++)
    {
        for(int j = 0; j < N; j++)
        {
            AT[i][j] = A[j][i];
            printf("  %f  ", AT[i][j]);
        }
        printf("\n");
    }

    // AT * A
    double ATA[NumOfvariable][NumOfvariable+1];
    // initial ATA
    printf("\nATA\n");
    for(int i = 0; i < NumOfvariable; i++)
    {
        for(int j = 0; j < NumOfvariable; j++)
        {
            ATA[i][j] = 0;
        }
    }
    for(int i = 0; i < NumOfvariable; i++)
    {
        for(int j = 0; j < NumOfvariable; j++)
        {
            for(int k = 0; k < N; k++)
            {
                ATA[i][j] += AT[i][k] * A[k][j];
            }
            printf(" %f ", ATA[i][j]);
        }
        printf("\n");
    }

    // AT * B
    double B[N] = {6.3806, 7.1338, 9.1662, 11.5545, 15.6414, 22.7371, 32.0696, 47.0756, 73.1596, 111.4684, 175.9895, 278.5550, 446.4441};
    double ATB[NumOfvariable];
    // initial ATB
    printf("\nATB\n");
    for(int i = 0; i < NumOfvariable; i++)
    {
        ATB[i] = 0.0;
    }
    for(int i = 0; i < NumOfvariable; i++)
    {
        for(int j = 0; j < N; j++)
        {
            ATB[i] += AT[i][j] * B[j];
            // printf("%d, %d, %f * %f = %f\n", i, j, AT[i][j], B[j], ATB[i]);
        }
        printf("  %f  ", ATB[i]);
        printf("\n");
    }

    float tmp;
    int i, j, k;
    int numOfVariable = NumOfvariable;

    double** permu_mat = (double **)malloc(numOfVariable * sizeof(double*));
    double** matrix = (double **)malloc(numOfVariable * sizeof(double*));
    double** lower = (double **)malloc(numOfVariable * sizeof(double*));

    for(i = 0; i < numOfVariable; i++)
    {
        permu_mat[i] = (double *)malloc(numOfVariable * sizeof(double));
        matrix[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));
        lower[i] = (double *)malloc((numOfVariable + 1) * sizeof(double));

        for(j = 0; j < numOfVariable; j++)
        {
            matrix[i][j] = ATA[i][j];
            if(i == j)
            {
                permu_mat[i][j] = 1;
            }
        }
        matrix[i][j] = ATB[i];
    }
    printf("\nmatrix ==> ATA(x) = ATB:");
    print2d(matrix, numOfVariable, numOfVariable+1);
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
        temp = permu_mat[k];
        permu_mat[k] = permu_mat[maxRowindex];
        permu_mat[maxRowindex] = temp;
        temp = lower[k];
        lower[k] = lower[maxRowindex];
        lower[maxRowindex] = temp;
        // printf("\nmatrix:");
        // print2d(matrix, numOfVariable, numOfVariable+1);
        // printf("k: %d, index: %d\n", k, maxRowindex);
        for(i = k+1; i < numOfVariable; i++)
        {
            // printf("\n ik: %f, kk: %f", matrix[i][k], matrix[k][k]);
            ratio = matrix[i][k] / matrix[k][k];
            lower[i][k] = ratio;
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
    // lower 對角線=1
    for(i = 0; i < numOfVariable; i++)
    {
        lower[i][i] = 1;
    }
    // printf("\nL:");
    // print2d(lower, numOfVariable, numOfVariable);
    // printf("\nU:");
    // print2d(matrix, numOfVariable, numOfVariable);
    // printf("\nP:");
    // print2d(permu_mat, numOfVariable, numOfVariable);
    // printf("\nmatrix:");
    // print2d(matrix, numOfVariable, numOfVariable+1);

    printf("\nans: ( ");
    for(i = 0; i < numOfVariable-1; i++)
    {
        printf("%f, ", ans[i]);
    }
    printf("%f )\n", ans[i]);
}