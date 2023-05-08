#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

/*
n: total pages
s: input pages
0 < n(n+1)/2 -s <= n
    n(n+1) - 2s <= 2n

*/ 

int main()
{
    int N = 0, sum = 0;
    vector<int> table;
    for(int i = 0; sum <= 2 * 1e8; ++i)
    {
        sum += i;
        table.emplace_back(sum);
    }
    while(cin >> N, N)
    {
        vector<int>::iterator low ;
        low = lower_bound(table.begin(), table.end(), N);
        if(!(*low - N))
        {
            cout << low-table.begin() + 1 << " " << low-table.begin() + 1<< endl;
        }
        else
        {
            cout << *low-N << " " << low-table.begin() << endl;
        }
    }
}