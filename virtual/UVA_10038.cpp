#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    int N = 0;
    while(cin >> N)
    {
        vector<int> dis;
        vector<int> ori;
        int pre = 0, cur = 0;
        cin >> pre;
        for(int i = 1; i < N; i++)
        {
            ori.emplace_back(i);
            cin >> cur;
            dis.emplace_back(abs(pre - cur));
            pre = cur;
        }
        // sort it
        sort(dis.begin(), dis.end());
        int flag = 0;
        for(int i = 0; i < dis.size(); i++)
        {
            if(dis[i] != ori[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            cout << "Not jolly" << endl;
        }
        else
        {
            cout << "Jolly" << endl;
        }
    }
}