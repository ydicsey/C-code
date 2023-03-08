#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    char new[105] = {0};
    char key[105] = {0};
    char temp[105] = {0};
    char tmp;

    scanf("%s", key);
    scanf("%s", new);

    while(scanf("%c", &tmp) != EOF)
    {
        if(key[0] == tmp)
        {
            fgets(temp, strlen(key), stdin);

            if(!(strncmp(temp, &key[1], strlen(key))))
            {
                printf("%s", new);
            }
            else
            {
                printf("%c", tmp);
                printf("%s", temp);
            }
        }
        else
        {
            printf("%c", tmp);
        }
    }
}