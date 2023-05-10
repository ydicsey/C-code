#include <bits/stdc++.h>
using namespace std;

int islegal(int c)
{
    return(isalnum(c) || c == '\n' || c == ' ');
}

int main()
{
    int idx = 0, max = 0;
    string a, b, ans[105];
    while(getline(cin, ans[idx]))
    {
        if(int len = ans[idx].size(); len > max)
        {
            max = len;
        }
        idx++;
    }

    for(int i = 0; i < max; ++i)
    {
        for(int j = idx-1; j >= 0; --j)
        {
            if(ans[j].size() > i)
            {
                cout << ans[j][i];
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}