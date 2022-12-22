#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define N 5

typedef struct 
{
    double x;
    double y;
}S_XY;

void print2d(double A[][N], int x, int y)
{
    printf("\n");
    int i, j;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            printf("%f \t", A[i][j]);
        }
        printf("\n");
    }
}

double newton_interp(S_XY A[], double xi)
{
    double table[N][N] = {0};

    for(int i = 0; i < N; i++)
    {
        table[i][0] = A[i].y;
    }
    
    double ans = table[0][0];  
    double mul = xi-A[0].x;
    for(int offset = 1; offset < N; offset++)
    {
        for(int j = offset; j < N; j++)
        {
            int i = j - offset;
            // printf("i: %d, j: %d\n", i, j);
            if(offset == 1)
            {
                table[i][j] = (table[j][0] - table[j-1][0]) / (A[j].x - A[j-1].x);
            }
            else
            {
                table[i][j] = (table[j-offset+1][j] - table[i][i+offset-1]) / (A[j].x - A[i].x);
            }
        }
        ans += table[0][offset] * mul;
        mul *= (xi - A[offset].x);
    }  

    // 寫到for裡面去
    // double ans = table[0][0];
    // double mul = xi-A[0].x;
    // for(int i = 1; i < N; i++)
    // {
    //     ans += table[0][i] * mul;
    //     mul *= (xi - A[i].x);
    // }

    print2d(table, N, N);
    return ans;
}

void newton_interp2(S_XY A[], double xi)
{
    double table[N][N] = {0};
    for(int i = 0; i < N; i++)
    {
        table[i][0] = A[i].y;
    }

    for (int i = 1; i < N; i++) 
    {
        for (int j = 0; j < N - i; j++) 
        {
            table[j][i] = (table[j][i - 1] - table[j + 1][i - 1]) / (A[j].x - A[i + j].x);
        }
    }
    print2d(table, N, N);
}

int main()
{
    S_XY A[] = {{0.6, 1.433329}, {0.7, 1.632316}, {0.8, 1.896481}, {0.9, 2.247908}, {1.0, 2.718282}};

    printf("interpolation(0.82)\n%f\n", newton_interp(A, 0.82));
    printf("\ninterpolation(0.98)\n%f\n", newton_interp(A, 0.98));
    // print2d(table, N, N);
    newton_interp2(A, 0.82);
}