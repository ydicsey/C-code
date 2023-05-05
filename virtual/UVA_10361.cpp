#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int N = 0;
    cin >> N; cin.ignore();
    while(N--)
    {
        int idx = 0;
        string arr[5], temp;
        getline(cin, temp);
        for(int i = 0; i < temp.size(); ++i)
        {
            if(temp[i] == '<')
            {
                idx++;
                continue;
            }
            else if(temp[i] == '>')
            {
                idx++;
                continue;
            }
            arr[idx] += temp[i];
            cout << temp[i];
        }
        cout << endl;
        temp.clear();
        getline(cin, temp);
        for(int i = 0; i < temp.size()-2; ++i)
        {
            if(temp[i] == '.' && temp[i+1] == '.' && temp[i+2] == '.')
            {
                cout << arr[3] << arr[2] << arr[1] << arr[4];
            }
            else
            {
                cout << temp[i];
            }
        }
        cout << endl;
    }
}