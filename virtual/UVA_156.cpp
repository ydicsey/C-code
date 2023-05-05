#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    unordered_map<string , pair<string, int>> dic;
    string s;
    while (cin >> s, s != "#")
    {
        string ori = s;
        for(int i = 0; i < s.size(); ++i)
        {
            s[i] = tolower(s[i]);
        }
        sort(s.begin(), s.end());
        if( !dic[s].second )
        {
            dic[s].first = ori;
            dic[s].second = 1;
        }
        else
        {
            ++dic[s].second;
        }
    }
    vector<string> ans;
    for(auto it : dic)
    {
        if(it.second.second == 1)
        {
            ans.emplace_back(it.second.first);
        }
    }
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << endl;
    }
}