#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    int N = 0;
    string str = "";
    while(cin >> N, N)
    {
        cin >> str;
        // getline(cin, str, '\n');
        int numOfGroupMember = str.length() / N;
        for(int i = 0; i < str.length(); i += numOfGroupMember)
        {
            reverse(&str[i], &str[i] + numOfGroupMember);

            cout << i << " " << i + numOfGroupMember << endl;
        }
        cout << str << endl;
    }
}

// ATE0AFGHANISTAN0IRAQ0NOW0IRAN0