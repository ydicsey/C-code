#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// 先找到平均值
template < typename T >
double avg(const vector<T>& arr)
{
    double sum = 0;
    for(const auto& it : arr)
    {
        sum += it;
    }
    return (sum / arr.size());
}

int main()
{
    int N = 0;
    cin >> N;
    while(N--)
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

        auto average = avg(v);
        // cout << "|avg: " << average << endl;
        double cnt = 0;
        for(auto it : v)
        {
            if(it > average)
            {
                cnt++;
            }
        }
        // cout << "|cnt: " << cnt << " " << v.size() << endl;
        double percentage = cnt / v.size();
        percentage = round(percentage * 100000)/1000;
        cout << std::fixed << std::setprecision(3) << percentage << "%" << endl;
    }
}