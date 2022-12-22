#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

double horner_method(int poly[], int32_t n, float x)
{
    int32_t i;
    float res = poly[0];

    for(i = 1; i < n; i++)
    {
        res = res * x + poly[i];
    }
    return res;
}

int main()
{
    int32_t i;
    float res;
    for(i = 0; i < 51; i++)
    {
        res = res * 1.0001 + 1;
    }
    printf("\n%.4f\n", res);

    // x = 1.0001
    // 1 = x^2 + x^3 +...+ x^50

    int *poly = malloc(55 * sizeof(int));

    // scanf poly
    for(i = 0; i < 51; i++)
    {
        poly[i] = 1;
    }

    printf("\n%f", horner_method(poly, 51, 1.0001));
}