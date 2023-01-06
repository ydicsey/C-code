#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define Max(x, y) ((x)<(y)?(y):(x))
#define Min(x, y) ((x)>(y)?(y):(x))
#define MAXN 3005

uint32_t ans = 0;
uint32_t dp[MAXN];

typedef struct
{
    uint32_t x;
    uint32_t y;
}loc;

int cmpX(const void *a, const void *b)
{
    loc* A = (loc*)a;
    loc* B = (loc*)b;
    return (A->x - B->x);
}

int cmpY(const void *a, const void *b)
{
    loc* A = (loc*)a;
    loc* B = (loc*)b;
    if(A->x == B->x)
    {
        return (A->y - B->y);
    }
    return (A->x - B->x);
}

int main()
{
    uint32_t n;
    uint32_t i, j, k;

    scanf("%d", &n);

    if(n == 0)
    {
        return 0;
    }

    loc *input = (loc *)malloc((n+1) * sizeof(input));

    for(i = 0; i < n; i++)
    {
        scanf("%d %d", &input[i].x, &input[i].y);
    }

    // qsort(input, n, sizeof(loc), cmpX);
    qsort(input, n, sizeof(loc), cmpY);

    // LIS length
    uint32_t len = 1;
    uint32_t *temp = (uint32_t *)malloc((n+1) * sizeof(int));
    memset(temp, 0, (n+1) * sizeof(int));
    temp[1] = input[1].y;

    for(i = 2; i < n + 1; i++)
    {
        if(input[i].y > temp[len])
        {
            temp[++len] = input[i].y;
        }
        else
        {
            // binary search
            uint32_t left = 1, right = len;
            while (left <= right)
            {
                uint32_t mid = (left+right)/2;
                if (temp[mid] <= input[i].y) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            temp[left] = input[i].y;
        }
    }
    free(temp);
    printf("%d", len);
}