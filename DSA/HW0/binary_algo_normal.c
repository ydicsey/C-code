#include <stdio.h>

// https://rosettacode.org/wiki/Greatest_common_divisor#Iterative_binary_algorithm
int gcd_bin(int u, int v)
{
    int t, k;
    /* abs(u) */
    u = u < 0 ? -u : u; 
    v = v < 0 ? -v : v;

    if (u < v)
    {
        t = u;
        u = v;
        v = t;
    }
    if (v == 0)
        return u;

    k = 1;
    while ((u & 1) == 0 && (v & 1) == 0)
    { /* u, v - even */
        u >>= 1;
        v >>= 1;
        k <<= 1;
    }

    t = (u & 1) ? -v : u;
    while (t)
    {
        while ((t & 1) == 0)
            t >>= 1;

        if (t > 0)
            u = t;
        else
            v = -t;

        t = u - v;
    }
    return u * k;
}

int main()
{
    printf("gcd(20230228, 82203202): %d\n" ,gcd_bin(20230228, 82203202));
    printf("gcd(20210208, 80201202): %d\n" ,gcd_bin(20210208, 80201202));

}