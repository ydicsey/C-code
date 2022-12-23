#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

double D_f(double x)
{
    return 4* x*x*x + 9* x*x - 66*x + 36;
}

int main()
{
    // f(x) = x^4 + 3(x-2)^3 -15x^2 + 1
    // f'(x) = 4x^3 + 9x^2 -66x +36
    double learn_rate = 0.00005;
    double pre_x = -1, x;
    double df = D_f(pre_x);
    int steps = 0;
    do{
        x = pre_x - learn_rate * df;
        df = D_f(x);
        pre_x = x;
        steps++;
        printf("\nx:%f, x-1:%f, df:%f\n", x, pre_x, df);
    }while(fabs(df) > 0.000001);

    printf("step:%d, %f\n", steps, x);
}