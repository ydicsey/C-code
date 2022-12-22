#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define numOfVariable 10
#define maxstep 1000

// 看是不是對角線占優矩陣，是的話才能使用 jacobi
bool isApplicable(double** matrix)
{
    int i, j;
    for(i = 0; i < numOfVariable; i++)
    {
        double sum = 0;
        for(j = 0; j < numOfVariable; j++)
        {
            sum += (i != j ? matrix[i][j] : 0);
        }
        if(fabs(matrix[i][i]) < sum)
        {
            break;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void print2d(double A[][numOfVariable], int x, int y)
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

int main()
{
    int i, j ,k, rightOrNot;
    int step;
    double sum, error = 0.0000000001;
    // double matrix[numOfVariable][numOfVariable] = 
    // {
	// 	-4,2,0,0,0,0,0,0,0,0,
	// 	2,-4,2,0,0,0,0,0,0,0,
	// 	0,2,-4,2,0,0,0,0,0,0,
	// 	0,0,2,-4,2,0,0,0,0,0,
	// 	0,0,0,2,-4,2,0,0,0,0,
	// 	0,0,0,0,2,-4,2,0,0,0,
	// 	0,0,0,0,0,2,-4,2,0,0,
	// 	0,0,0,0,0,0,2,-4,2,0,
	// 	0,0,0,0,0,0,0,2,-4,2,
	// 	0,0,0,0,0,0,0,0,2,-4
    // };
    // double b[numOfVariable] = 
    // {
	// 	2,3,4,5,6,7,8,9,10,11
	// };

    double matrix[numOfVariable][numOfVariable] = 
    {
		3,-1,0,0,0,0,0,0,0,0,
		-1,3,-1,0,0,0,0,0,0,0,
		0,-1,3,-1,0,0,0,0,0,0,
		0,0,-1,3,-1,0,0,0,0,0,
		0,0,0,-1,3,-1,0,0,0,0,
		0,0,0,0,-1,3,-1,0,0,0,
        0,0,0,0,0,-1,3,-1,0,0,
        0,0,0,0,0,0,-1,3,-1,0,
        0,0,0,0,0,0,0,-1,3,-1,
        0,0,0,0,0,0,0,0,-1,3
    };
    double b[numOfVariable] = 
    {
		2,1,1,1,1,1,1,1,1,2
	};

    // initial guess every unknows as 0
    double value[maxstep][numOfVariable] = {0};

    for(step = 1; step < maxstep; step++)
    {
        for(i = 0; i < numOfVariable; i++)
        {
            sum = 0;
            for(j = 0; j < numOfVariable; j++)
            {
                sum += (i!=j ? matrix[i][j] * value[step -1][j] : 0);
            }
            value[step][i] = (b[i] - sum) / matrix[i][i];
        }

        for(k = 0; k < numOfVariable; k++)
        {
            // printf("%f | ", value[step][k]);
            if(fabs(value[step][k] - value[step - 1][k]) < error)
            {
                rightOrNot = 1;
            }
            else
            {
                rightOrNot = 0;
            }
        }   
        // printf("\n");
        if(rightOrNot)
        {
            printf("step: %d\n", step);
            for(i = 0; i < numOfVariable; i++)
            {
                printf("%f | ", value[step-1][i]);
            }
            printf("\n");
            return 0;
        }
        rightOrNot = 0;
    }

    printf("step: %d\n", step);
    for(i = 0; i < numOfVariable; i++)
    {
        printf("%f | ", value[step-1][i]);
    }
    printf("\n");
    print2d(matrix, numOfVariable, numOfVariable);
    return 0;
}