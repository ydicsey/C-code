#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int N = 0; 
    cin >> N;
    cout << "Lumberjacks:" << endl;
    while (N--)
    {
        vector<int> input;
        for(int i = 0; i < 10; ++i)
        {
            int temp = 0;
            cin >> temp;
            input.emplace_back(temp);
        }
        bool ascend = is_sorted(input.begin(), input.end());
        bool descend = is_sorted(input.rbegin(), input.rend());
        if(ascend || descend)
        {
            cout << "Ordered" << endl;
        }
        else
        {
            cout << "Unordered" << endl;
        }
    }
}