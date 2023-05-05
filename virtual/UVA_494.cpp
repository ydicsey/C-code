#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

int main()
{
    string ss;
    while(getline(cin, ss))
    {
        int ans = 0;
        for(int i = 1; i < ss.size(); ++i)
        {
            if(isalpha(ss[i-1]) && !isalpha(ss[i]))
            {
                ++ans;
            }
        }
        cout << ans << endl;
    }
}