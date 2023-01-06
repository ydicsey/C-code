#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1005

int main()
{
    int32_t i, pre = 0, shrimp = 0;
    uint8_t a[MAXN], b[MAXN];

    scanf("%s", a);
    scanf("%s", b);

    uint32_t len = strlen(a);
    // uint32_t dp[MAXN][4];
    // // 0 -> two empty, 1 -> up empty, 2-> down empty, 3 -> none empty

    for(i = 0; i < len; i++)
    {
        uint32_t tmp = (a[i] == '0') + (b[i] == '0');
        pre += tmp;
        if(pre >= 3)
        {
            shrimp++;
            pre -= 3;
        }
        else
        {
            pre = tmp;
        }
    }
    printf("%d\n", shrimp);
}