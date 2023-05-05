#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string input, Min;
    int N = 0;
    cin >> N;
    while(N--)
    {
        cin >> input;
        Min = input;
        for(int i = 0; i < input.size() -1; ++i)
        {
            rotate(input.begin(), input.begin() + 1, input.end());
            if(Min > input)
            {
                Min = input;
            }
        }
        cout << Min << endl;
    }
}