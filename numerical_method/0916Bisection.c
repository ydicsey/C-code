#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// x - x^1/3 -2 = 0
// root:3-4

// e^(x-2) + x^3 - x
// root:(-1, -2)

int main()
{
    // printf("%f",3 - pow(3, 0.3333333) - 2);
    // printf("\n%f\n",4 - pow(4, 0.3333333) - 2);
    float left = 1, right = 2, mid;

    while(right - left > 0.0001)
    {        
        mid = (left + right)/2;
        // printf("\n%f %f %f\n", left, right, mid);
        if(pow(mid, 3) + 4*pow(mid, 2) - 10 > 0)
        {
            right = mid;
            // printf("\n%f %f %f\n", left, right, mid);
        }
        else
        {
            left = mid;
            // printf("\n%f %f %f\n", left, right, mid);
        }
    }
    printf("\n%f\n", mid);
}