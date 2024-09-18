/*
 * @lc app=leetcode.cn id=179 lang=cpp
 * @lcpr version=30204
 *
 * [179] 最大数
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
// @lcpr-template-end
// @lc code=start
bool cmp(const string& a, const string& b)
{
    return a+b < b+a;
}
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> tmp;
        string ans;
        for(const auto& i: nums)
        {
            tmp.push_back(to_string(i));
        }
        sort(tmp.rbegin(), tmp.rend(), cmp);
        for(const auto& i: tmp)
        {
            ans += i;
        }
        return ans[0] == '0'? "0" : ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,2]\n
// @lcpr case=end

// @lcpr case=start
// [3,30,34,5,9]\n
// @lcpr case=end

 */

