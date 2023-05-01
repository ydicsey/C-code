#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template< typename T>
T find_max_element(T begin, const T end)
{
    if(begin == end)
    {
        return end;
    }
    T max = begin;
    begin++;
    for(; begin != end; begin++)
    {
        if(*max < *begin)
        {
            max = begin;
        }
    }
    return max;
}

int main()
{
    int N = 0;
    cin >> N;
    for(int i = 1; i <= N; ++i)
    {
        vector<int> v;
        int M = 0;
        cin >> M;
        while(M--)
        {
            int tmp = 0;
            cin >> tmp;
            v.emplace_back(tmp);
        }
        int max = *find_max_element(v.begin(), v.end());
        cout << "Case " << i << ": " <<max << endl;
    }
}