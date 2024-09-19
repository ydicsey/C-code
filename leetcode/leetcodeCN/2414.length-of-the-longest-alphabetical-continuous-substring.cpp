/*
 * @lc app=leetcode.cn id=2414 lang=cpp
 * @lcpr version=30204
 *
 * [2414] 最长的字母序连续子字符串的长度
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
class Solution {
public:
    int longestContinuousSubstring(string s) {
        int left = 0, right = 1, ans = 1;
        while(right < s.size())
        {
            if((s[right] - s[right -1]) != 1)
            {
                ans = max(ans, right - left);
                left = right;
            }
            ++right;
        }
        ans = max(ans, right - left);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "abacaba"\n
// @lcpr case=end

// @lcpr case=start
// "abcde"\n
// @lcpr case=end

 */

