#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 3005
#define Min(x, y) ((x)>(y)?(y):(x))
#define Max(x, y) ((x)<(y)?(y):(x))


uint64_t N, U;
uint64_t dp[MAXN];

void zerooneKnapsack(uint64_t value, uint64_t weight)
{
    uint64_t i;
    for(i = U; i >= weight; i--)
    {
        dp[i] = Max(dp[i], dp[i-weight] + value);
    }
    return;
}

int main()
{
    uint64_t i;
    uint64_t weight, value, amount;

    scanf("%lu %lu", &N, &U);
    memset(dp, 0 , sizeof(dp));

    for(i = 0; i < N; i++)
    {
        scanf("%lu %lu %lu", &weight, &value, &amount);
        int64_t k = 1;
        while(k < amount)
        {
            zerooneKnapsack(value*k, weight * k);
            amount -= k;
            k = k << 1;
        }
        zerooneKnapsack(value * amount, weight * amount);
    }

    printf("%lu", dp[U]);
}