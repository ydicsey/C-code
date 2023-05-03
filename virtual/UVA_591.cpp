#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
T cnt_move(const vector<T>& ref)
{
    T sum = 0;
    for(auto it : ref)
    {
        sum += it;
    }
    T height = sum / ref.size();
    T move = 0;
    for(auto it : ref)
    {
        move += abs(height - it);
    }
    return move / 2;
}

int main()
{
    int N = 0;
    int set = 0;
    while(cin >> N, N)
    {
        set++;
        vector<int> height;
        for(int i = 0; i < N; ++i)
        {
            int temp = 0;
            cin >> temp;
            height.emplace_back(temp);
        }
        cout << "Set #" << set << endl;
        cout << "The minimum number of moves is "<< cnt_move(height) << "." << endl << endl;
    }
}