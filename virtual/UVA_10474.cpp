#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T, typename V>
size_t where(T begin, T end, const V& val)
{
    size_t idx = 1;
    while(begin != end)
    {
        if(*begin == val)
        {
            return idx;
        }
        ++idx;
        ++begin;
    }
    return 0;
}

int main()
{
    int N = 0, Q = 0, Case = 0;
    while(cin >> N >> Q, N||Q)
    {
        ++Case;
        vector<int> marbles;
        for(int i = 0; i < N; ++i)
        {
            int temp = 0;
            cin >> temp;
            marbles.emplace_back(temp);
        }
        sort(marbles.begin(), marbles.end());
        cout << "CASE# " << Case << ":" << endl;
        for(int i = 0; i < Q; ++i)
        {
            int temp = 0;
            cin >> temp;
            // size_t idx = where(marbles.begin(), marbles.end(), temp);
            auto it = lower_bound(marbles.begin(), marbles.end(), temp);
            if(marbles[it - marbles.begin()] == temp)
            {
                cout << temp << " found at " << it - marbles.begin() +1 << endl;
            }
            else
            {
                cout << temp << " not found" << endl;
            }
        }
    }
}