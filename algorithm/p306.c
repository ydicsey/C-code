#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t n;
    int32_t i, ans, pre, cur;
    scanf("%d", &n);

    ans = 0;
    pre = ans;

    for(i = 0; i < n; i++)
    {
        scanf("%d", &cur);
        ans += (cur > pre? cur - pre : 0);
        pre = cur;
    }
    printf("%d", ans);
}