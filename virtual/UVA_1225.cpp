#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main()
{
    int N = 0;
    cin >> N;
    while(N--)
    {
        int range = 0;
        string s;
        cin >> range;
        for(int i = 1; i <= range; ++i)
        {
            s += to_string(i);
        }
        for(int i = 0; i < 10; ++i)
        {
            if(i)
            {
                cout << " ";
            }
            cout << count(s.begin(), s.end(), i+48);
        }
        cout << endl;
    }
}