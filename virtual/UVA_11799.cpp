#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

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
        int max = *max_element(v.begin(), v.end());
        cout << "Case " << i << ": " <<max << endl;
    }
}