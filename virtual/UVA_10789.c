#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool prime[2005];

void eratosthenes()
{
    int i, j;
    for (i = 0; i < 2005; i++)
        prime[i] = true;

    prime[0] = false;
    prime[1] = false;

    for (i = 2; i < 2005; i++)
        if (prime[i])
            for (j = i + i; j < 2005; j += i)
                prime[j] = false;
}

int main()
{
    int i, j, flag_empty;
    int n;

    /*建立質數表*/
    eratosthenes();

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        flag_empty = 1;
        int CNT[130] = {0};
        char s[2005] = {};

        scanf("%s", s);
        for (j = 0; j < strlen(s); j++)
        {
            /*
            if(((s[j] < 58) && (s[j] > 47)) || ((s[j] > 64) && (s[j] > 91)) || ((s[j] > 96) && (s[j] > 123)))
            */
            CNT[s[j]]++;
        }

        printf("Case %d: ", i+1);
        for(j = 0; j < 123; j++)
        {
            if(CNT[j] && prime[CNT[j]])
            {
                flag_empty = 0;
                printf("%c", j);
            }
        }
        if(flag_empty)
        {
            printf("empty");
        }
        printf("\n");
    }
}