#include <stdio.h>
#include <string.h>
#define Min(x, y) ((x)>(y)?(y):(x))
#define Max(x, y) ((x)<(y)?(y):(x))

int main()
{
    char input[10];
    int guess;
    int lower = 0;
    int upper = 10;

    while(scanf("%d", &guess) !=  EOF)
    {
        if (guess == 0)
        {
            return 0;
        }

        fgets(input, 10, stdin);

        if( !strcmp(input ,"right on\n"))
        {
            if(guess <= upper && guess >= lower)
            {
                puts("Stan may be honest");
            }
            else
            {
                puts("Stan is dishonest");
            }
            lower = 0;
            upper = 10;
        }

        else
        {
            if( !strcmp(input ,"too high\n"))
            {
                upper = Min(upper, guess-1);
            }
            else if( !strcmp(input ,"too low\n"))
            {
                lower = Max(lower, guess+1);
            }
        }
    }
}
