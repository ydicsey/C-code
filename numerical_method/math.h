#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int m, n;
    double ** v;
} mat_t, *mat;

// initial matrix
mat matrix_new(int m, int n)
{
	mat x = malloc(sizeof(mat_t));
	// x->v = (double**)calloc(sizeof(double), m * n);
	x->v = malloc(sizeof(double*) * m);
	x->v[0] = calloc(sizeof(double), m * n);
	for (int i = 0; i < m; i++)
	{
		x->v[i] = x->v[0] + n * i;
	}
	x->m = m;
	x->n = n;
	return x;
}

// free matrix
void matrix_delete(mat m)
{
	free(m->v[0]);
	free(m->v);
	free(m);
}

// return transpose of a matrix
mat matrix_getTranspose(mat m)
{
	mat T = matrix_new(m->n, m->m);
	for (int i = 0; i < m->n; i++) 
	{
		for (int j = 0; j < m->m; j++) 
		{
			T->v[i][j] = m->v[j][i];
		}
	}
	return T;
}

// put array into matrix
mat matrix_copy(int n, double a[][n], int m)
{
	mat x = matrix_new(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			x->v[i][j] = a[i][j];
	return x;
}

// return x*y in matrix
mat matrix_mul(mat x, mat y)
{
	if (x->n != y->m) 
	{
		return 0;
	}

	mat r = matrix_new(x->m, y->n);
	for (int i = 0; i < x->m; i++)
	{
		for (int j = 0; j < y->n; j++)
		{
			for (int k = 0; k < x->n; k++)
			{
				r->v[i][j] += x->v[i][k] * y->v[k][j];
			}
		}
	}
	return r;
}

// print matrix
void matrix_show(mat m)
{
	for(int i = 0; i < m->m; i++) 
	{
		for (int j = 0; j < m->n; j++) 
		{
			printf(" %f\t", m->v[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// pvoitGu need
int findmain(mat matrix, int ROW)
{
    int maxRowindex = ROW, i;
    float maxRowvalue; 
    maxRowvalue = fabs(matrix->v[ROW][ROW]);
    for(int i = ROW; i < matrix->m; i++)
    {
        if(fabs(matrix->v[i][ROW]) > maxRowvalue)
        {
            maxRowvalue = fabs(matrix->v[i][ROW]);
            maxRowindex = i;
            // printf("\nin find main i: %d\n", i);
        }
    }
    // printf("\nin find main max: %d\n", maxRowindex);
    return maxRowindex;
}

// exchange matrix(row1,  row2)
void matrix_exchange(mat m, int row1, int row2)
{
	for (int j = 0; j < m->n; j++) 
	{
		double t = m->v[row1][j];
		m->v[row1][j] = m->v[row2][j];
		m->v[row2][j] = t;
	}
}

// create extension matrix
// matrix(m * m), x(1*m)
mat extension(mat matrix, mat x)
{
	mat extension_mat = matrix_new(matrix->m, matrix->m +1);
	if((matrix->m - matrix->n) == 0)
	{
		for(int i = 0; i < matrix->m; i++)
		{
			int j;
			for(j = 0; j < matrix->n; j++)
			{
				extension_mat->v[i][j] = matrix->v[i][j];
			}
			extension_mat->v[i][j] = x->v[0][i];
		}
	}
	else
	{
		printf("error in gaussion matrix m != n\n");
	}
	return extension_mat;
}

// gaussian for extension matrix(m * n), n = m+1
// return ans in matrix(1*m)
mat gaussian_pviot(mat matrix)
{
	// find main pvoit row
	// number of variable = matrix->m
    for(int k = 0; k < matrix->m; k++)
    {
        int maxRowindex = findmain(matrix, k);
        // exchange row k<->maxindex
		matrix_exchange(matrix, k, maxRowindex);

        for(int i = k+1; i < matrix->m; i++)
        {
            double ratio = matrix->v[i][k] / matrix->v[k][k];
            for(int j = 0; j <= matrix->m + 1; j++)
            {
                matrix->v[i][j] = matrix->v[i][j] - ratio* matrix->v[k][j];
            }
        }
    }

	// backward sub
	mat ans = matrix_new(1, matrix->m);
	ans->v[0][matrix->m -1] = matrix->v[matrix->m-1][matrix->m] / matrix->v[matrix->m-1][matrix->m-1];
	for(int i = matrix->m - 1; i > 0; i--)
	{
		double sum = 0;
		int j;
		for(j = i; j < matrix->m; j++)
		{
			sum += matrix->v[i-1][j] * ans->v[0][j];
			// printf("%.1f\n", sum);
		}
		sum *= -1;
		sum += matrix->v[i-1][j];
		ans->v[0][i-1] = sum / matrix->v[i-1][i-1];
	}
	return ans;
}