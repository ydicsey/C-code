#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    string key, ori;
    while(cin >> key >> ori)
    {
        int idx = 0, flag = 1;
        for(auto it : key)
        {
            auto res = find(ori.begin() + idx, ori.end(), it);
            if(res == ori.end())
            {
                flag = 0;
                break;
            }
            idx = res - ori.begin() +1;
        }
        if(flag)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}