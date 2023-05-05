#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    string s;
    while(getline(cin ,s))
    {
        istringstream iss(s);
        string word;
        int flag = 0;
        while(iss >> word)
        {
            if(flag++)
            {
                cout << " ";
            }
            reverse(word.begin(), word.end());
            cout << word;
        }
        cout << endl;
    }
}