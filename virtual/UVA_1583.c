#include <stdio.h>

/* 
N is small; prepare an array of size 100044; that is the largest possible digit sum for this problem 
*/

int main()
{
    int array[100045] = {0};
    int i, j, sum, tmp;
    for(i = 0; i < 100001; i++)
    {
        /* 
        sumdigit
        */
        sum = i;
        tmp = i;
        while(tmp)
        {
            sum += tmp % 10;
            tmp /= 10;
        }
        if(!array[sum])
        {
            array[sum] = i;
        }
    }

    int n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &i);
        printf("%d\n", array[i]);
    }
}