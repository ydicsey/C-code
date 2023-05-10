#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a, b;
    while(getline(cin, a))
    {
        getline(cin, b);
        int cnta[130] = {0}, cntb[130] = {0};
        for(int i = 0; i < a.size(); ++i)
        {
            cnta[a[i]]++;
        }
        for(int i = 0; i < b.size(); ++i)
        {
            cntb[b[i]]++;
        }
        for(int i = 'a'; i <= 'z'; ++i)
        {
            if(cnta[i] && cntb[i])
            {
                for(int j = 0; j < cnta[i] && j < cntb[i]; ++j)
                    cout << (char)i;    
            }
        }
        cout << endl;
    }
}