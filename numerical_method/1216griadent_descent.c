#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

double D_f(double x)
{
    return 4* x*x*x - 6 * x*x;
}

int main()
{
    // f(x) = x^4 - 2*x^3 + 2
    // f'(x) = 4*x^3 - 6*x^2 
    double learn_rate = 0.05;
    double pre_x = 1, x;
    double df = D_f(pre_x);
    int steps = 0;
    do{
        x = pre_x - learn_rate * df;
        df = D_f(x);
        pre_x = x;
        steps++;
        // printf("%f, %f, %f\n", x, pre_x, df);
    }while(fabs(df) > 0.000001);

    printf("step:%d, %f\n", steps, x);
}