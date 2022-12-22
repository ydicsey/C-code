#include <stdio.h>
#include <math.h>

// newton method or secant method
// x^5 + x = 1
// lnx + x^2 = 3
// sinx = 6x + 5

#define f(x) pow(x, 5) + x - 1
// #define g(x) x*x + log(x) - 3
#define h(x) x*x*x + x*x - 1
// #define h(x) sin(x) - 6*x - 5
// #define h(x) cos(x)*cos(x) +6 - x
// #define h(x) exp(x) + x - 7
#define g(x) ((1-x)*(3+x))/(x*(1+x)) - 3.06

void froot()
{
    float x0 = 0, x1 = 5, xi;
    float e = 10;
    float f0, f1, fi;

    while(e > 0.00001)
    {
        f0 = f(x0);
        f1 = f(x1);
        // secant!
        xi = x1 - ((x1 - x0) * f1)/(f1-f0);
        fi = f(xi);
        e = fabs(fi);
        f0 = f1;
        f1 = fi;
        x0 = x1;
        x1 = xi;
    }
    printf("%f\n", xi);
}

void groot()
{
    float x0 = -10, x1 = -5, xi;
    float e = 10;
    float f0, f1, fi;

    while(e > 0.00001)
    {   
        f0 = g(x0);
        f1 = g(x1);
        // printf("x0 %f, x1 %f, f0 %f, f1 %f, xi %f, fi %f\n", x0, x1, f0, f1, xi, fi);
        // secant!
        xi = x1 - f1 * (x1 - x0)/(f1-f0);
        fi = g(xi);
        f0 = f1;
        f1 = fi;
        x0 = x1;
        x1 = xi;
        e = fabs(fi);
        printf("x0 %f, x1 %f, f0 %f, f1 %f, xi %f, fi %f\n", x0, x1, f0, f1, xi, fi);
    }
    printf("%f\n", xi);
}

void hroot()
{
    float x0 = 0, x1 = 5, xi;
    float e = 10;
    float f0, f1, fi;

    while(e > 0.00001)
    {
        f0 = h(x0);
        f1 = h(x1);
        // secant!
        xi = x1 - ((x1 - x0) * f1)/(f1-f0);
        fi = h(xi);
        e = fabs(fi);
        f0 = f1;
        f1 = fi;
        x0 = x1;
        x1 = xi;
    }
    printf("%f\n", xi);
}

int main()
{
    froot();
    groot();
    hroot();
}