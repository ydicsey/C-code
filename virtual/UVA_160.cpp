#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
using namespace std;

int main()
{
    // 建質數表
    bool prime[105];
    for(int i = 0; i < 105; ++i)
    {
        prime[i] = true;
    }
    prime[0] = false;
    prime[1] = false;
    for(int i = 2; i < 105; ++i)
    {
        if(prime[i])
        {
            for(int j = i+i; j < 105; j+=i)
            {
                prime[j] = false;
            }
        }
    }

    int n = 0;
    while(cin >> n, n)
    {
        int ans[105] = {0};
        for(int i = 2; i <= n; ++i)
        {
            if(prime[i])
            {
                int tmp = n;
                while(tmp / i)
                {
                    ans[i] += tmp / i;
                    tmp /= i;
                    // cout << tmp << " " << i << " ";
                }
                // cout << endl;
            }
        }
        printf("%3d! =", n);
        int dig = 0;
        for(int i = 0; i <= n; ++i)
        {
            if(prime[i] && ans[i])
            {
                // cout << ans[i] << " ";
                printf(" %2d", ans[i]);
                dig ++;
                if(dig == 15)
                {
                    printf("\n      ");
                    dig = 0;
                }
            }
        }
    }
}