#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define Min_2(x, y) ((x)>(y)?(y):(x))
#define Max(x, y) ((x)<(y)?(y):(x))

// http://anoopsarkar.github.io/nlp-class/assets/slides/editdist.pdf
int main()
{
    uint32_t addCost, removeCost, rotateCost;
    int32_t i, j, k;
    uint8_t a[5005] = {0};
    uint8_t b[5005] = {0};

    scanf("%u %u %u", &addCost, &removeCost, &rotateCost);
    scanf("%s", a);
    scanf("%s", b);

    uint32_t lenA = strlen(a);
    uint32_t lenB = strlen(b); 

    int** dp = (int**)malloc((lenB + 1) * sizeof(int*));
    for (i = 0; i < lenB + 1; i++)
    {
        dp[i] = (int*)malloc((lenA + 1) * sizeof(int));
    }

    dp[0][0] = 0;

    for(i = 1; i < lenA + 1; i++)
    {
        dp[0][i] = dp[0][i - 1] + removeCost;
    }
    for(i = 1; i < lenB + 1; i++)
    {
        dp[i][0] = dp[i - 1][0] + addCost;
    }

    for (i = 1; i < lenB + 1; i++) 
    {
        for (j = 1; j < lenA + 1; j++) 
        {
            int left = dp[i - 1][j] + addCost;
            int down = dp[i][j - 1] + removeCost;
            int left_down_1 = dp[i - 1][j - 1];
            int left_down_2 = dp[i - 1][j - 1];
                left_down_1 += removeCost;
                left_down_1 += addCost;
                left_down_2 += Min_2(abs(b[i - 1] - a[j - 1]), abs(26 - abs(b[i - 1] - a[j - 1]))) * rotateCost;
                dp[i][j] = Min_2(Min_2(left, down), Min_2(left_down_1, left_down_2));
                // printf("(%d)", dp[i][j]);
        }
        // printf("\n");
    }
    printf("%d", dp[lenB][lenA]);
}