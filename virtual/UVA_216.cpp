#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

double operator-(const pair<int, int>& a, const pair<int, int>& b)
{
    int x = a.first - b.first;
    int y = a.second - b.second;
    x *= x;
    y *= y;
    return (16.0 + sqrt(x + y));
}

int main()
{
    int N = 0, Case = 0;
    while(cin >> N, N)
    {
        vector<int> idx;
        vector<pair<int, int>> computer;
        for(int i = 0; i < N; ++i)
        {
            int x, y;
            cin >> x >> y;
            computer.emplace_back(x, y);
            idx.emplace_back(i);
        }

        vector<int> ans = idx;
        double min = 1e9;
        
        do{
            double dist = 0.0;
            for(int i = 0; i < idx.size()-1; ++i)
            {
                dist += computer[idx[i]] - computer[idx[i+1]];
            }
            if(dist < min)
            {
                min = dist;
                ans = idx;
            }
        }while(next_permutation(idx.begin(), idx.end()));

        cout << "**********************************************************" << endl;
        cout << "Network #" << ++Case << endl;
        for(int i = 0; i < idx.size()-1; ++i)
        {
            double dist = computer[ans[i]] - computer[ans[i+1]];
            cout << "Cable requirement to connect (" << computer[ans[i]].first << "," << computer[ans[i]].second << ") to (";
            cout << fixed << setprecision(2) << computer[ans[i+1]].first << "," << computer[ans[i+1]].second << ") is " << dist << " feet." << endl;
            
        }
        cout << "Number of feet of cable required is " << min << "." << endl;
    }
}