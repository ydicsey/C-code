#include<stdio.h>
#include<stdint.h>
#include<string.h>
#define inputMAX 4097
#define keyMAX 65

// =====strart on 2/26/2022
void red()
{
    printf("\033[1;32;31m");
}
void none()
{
    printf("\033[m");
}
void blue()
{
    printf("\033[0;33;34m");
}

int main()
{
    uint8_t input[inputMAX];
    uint8_t keyWord[keyMAX];
    uint8_t newWord[keyMAX];
    
    char* i;

    printf("\n===========STRAT===========");
    printf("\nPlease enter the string: \n");
    fgets(input, inputMAX - 1, stdin);
    printf("Please enter the key word: \n");
    fgets(keyWord, keyMAX - 1, stdin);
    printf("Please enter the new word: \n");
    fgets(newWord, keyMAX - 1, stdin);

    input[strlen(input) - 1] = '\0';
    keyWord[strlen(keyWord) - 1] = '\0';
    newWord[strlen(newWord) - 1] = '\0';

    printf("\nOriginal: \n");

    for(i = input; *i != 0; i++)
    {
        if(*i == keyWord[0])
        {
            if(0 == strncmp(i, keyWord, strlen(keyWord)))
            {
                red();
                printf("%s", keyWord);
                none();
                i += strlen(keyWord) - 1;
            }
            else
            {
                none();
                printf("%c", *i);
            }
        }
        else
        {
            none();
            printf("%c", *i);
        }
    }

    printf("\nNew: \n");

    for(i = input; *i != 0; i++)
    {
        if(*i == keyWord[0])
        {
            if(0 == strncmp(i, keyWord, strlen(keyWord)))
            {
                blue();
                printf("%s", newWord);
                none();
                i += strlen(keyWord) - 1;
            }
            else
            {
                none();
                printf("%c", *i);
            }
        }
        else
        {
            none();
            printf("%c", *i);
        }
    }
    printf("\n");
    return 0;
}
