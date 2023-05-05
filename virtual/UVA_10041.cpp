    #include <iostream>
    #include <algorithm>
    #include <vector>
    #include <cmath>
    using namespace std;

    int main()
    {
        int N = 0;
        cin >> N;
        while(N--)
        {
            int M = 0;
            cin >> M;

            vector<int> arr;
            while(M--)
            {
                int tmp = 0;
                cin >> tmp;
                arr.emplace_back(tmp);
            }
            // sort(arr.begin(), arr.end());
            auto mid = (arr.size() >> 1);
            auto m = arr.begin() + mid;
            nth_element(arr.begin(), m, arr.end());
            int sum = 0;
            for(int i = 0; i < arr.size(); ++i)
            {
                sum += abs(arr[i]- arr[mid]);
            }
            cout << sum <<endl;
        }
    }