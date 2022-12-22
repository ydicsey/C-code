#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// lagrange interpolation

typedef struct 
{
    double x;
    double y;
}S_XY;

double lagrange(S_XY A[], double xi, int n)
{
    double res = 0;
    for(int i = 0; i < n; i++)
    {
        double y = A[i].y;
        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                y *= ( (xi - A[j].x) / (A[i].x - A[j].x) );
            }
        }
        res += y;
    }
    return res;
}

int main()
{
    S_XY A[] = {{1.00, 0.1924}, {1.05, 0.2414}, {1.10, 0.2933}, {1.15, 0.3492}};
    printf("\nans: %f\n", lagrange(A, 1.09, 4));
}