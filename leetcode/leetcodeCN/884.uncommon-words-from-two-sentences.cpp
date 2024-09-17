/*
 * @lc app=leetcode.cn id=884 lang=cpp
 * @lcpr version=30204
 *
 * [884] 两句话中的不常见单词
 */


// @lcpr-template-start
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <sstream>
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) 
    {
        vector<string> tmp;
        stringSplitbySpace(s1);
        stringSplitbySpace(s2);
        for(const auto& pair : existWordFreq)
        {
            if(pair.second == 1)
            {
                tmp.push_back(pair.first);
            }
        }
        return tmp;
    }
    void stringSplitbySpace(const string& input)
    {
        vector<string> res;
        string tmp;
        stringstream ss(input);
        while(getline(ss, tmp, ' '))
        {
            ++existWordFreq[tmp];
        }
    }
private:
    unordered_map<string, int>existWordFreq;
};
// @lc code=end



/*
// @lcpr case=start
// "this apple is sweet"\n"this apple is sour"\n
// @lcpr case=end

// @lcpr case=start
// "apple apple"\n"banana"\n
// @lcpr case=end

 */

