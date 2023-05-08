#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int N = 0;
    cin >> N;
    while(N--)
    {
        int n = 0, pre = 0, cur = 0, ans = 1;
        cin >> n;
        cin >> pre;
        n--;
        while(n--)
        {
            cin >> cur;
            if(ans & 1)
            {
                if(cur < pre)
                {
                    ans++;
                }
            }
            else
            {
                if(pre < cur)
                {
                    ans++;
                }
            }
            pre = cur;
        }
        cout << ans << endl;
    }
}