/*
 * @lc app=leetcode.cn id=539 lang=cpp
 * @lcpr version=30204
 *
 * [539] 最小时间差
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
    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int pre = time2minute(timePoints.back());
        int cur = time2minute(timePoints.front());
        int res = 24*60 - pre + cur;   
        for(auto &i : timePoints)
        {
            cur = time2minute(i);
            res = min(res, abs(pre - cur));
            pre = cur;
        }     
        return res;
    }
    int time2minute(const string& time)
    {
        int hour = stoi(time);
        int minute = stoi(time.substr(3, 2));
        return hour * 60 + minute;
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["23:59","00:00"]\n
// @lcpr case=end

// @lcpr case=start
// ["00:00","23:59","00:00"]\n
// @lcpr case=end

 */

