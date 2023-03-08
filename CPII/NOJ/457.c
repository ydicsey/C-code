#include <stdio.h>
#include <string.h>

int main()
{
    char new[105] = {0};
    char key[105] = {0};
    char orig[10005] = {0};
    char temp[105] = {0};

    // scanf("%s", key);
    fgets(key, 100, stdin);
    // scanf("%s", new);
    fgets(new, 100, stdin);
    key[strlen(key) - 1] = '\0';
    new[strlen(new) - 1] = '\0';

    char *fast;

    while(fgets(orig, 10000, stdin) && orig)
    {
        for(fast = orig; *fast != 0; fast++)
        {
            if(*fast == key[0])
            {
                if( !(strncmp(fast, key, strlen(key))))
                {
                    printf("%s", new);
                    fast += strlen(key) -1;
                }
                else
                {
                    printf("%c", *fast);
                }
            }
            else
            {
                printf("%c", *fast);
            }
        }
    }
}