#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char country[2000][80];
char others[80];

int compare(const void *p1, const void *p2)
{
    return strcmp((char *)p1, (char *)p2);
}

int main()
{
    int n;
    int count = 1;
    int i = 0;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s", country[i]);
        fgets(others, 75, stdin);
    }

    qsort(country, n, 80, compare);
    i = 0;        

    while(i < n)
    {
        int j = i;
        j++;
        while(j < n && !strcmp(country[i], country[j]))
        {
            j++;
        }

        printf("%s %d\n",country[i], j-i);

        i = j;
    }
}