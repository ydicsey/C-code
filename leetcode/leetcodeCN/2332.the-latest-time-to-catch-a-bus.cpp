/*
 * @lc app=leetcode.cn id=2332 lang=cpp
 * @lcpr version=30204
 *
 * [2332] 坐上公交的最晚时间
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
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());

        int busIdx = 0, passIdx = 0, res = 0;
        for(const auto& busTime: buses)
        {
            int busCap = capacity;
            while(passIdx < passengers.size() && busCap > 0 && passengers[passIdx] <= busTime)
            {
                cout << "bus: " << busTime << res << endl;
                if(passIdx == 0 || (passIdx) > 0 && (passengers[passIdx]-1 != passengers[passIdx-1]))
                {
                    cout << "pass" << passIdx << " on bus" << busTime << endl;
                    res = passengers[passIdx]-1;
                }
                --busCap;
                ++passIdx;
            }
            if(busCap)
            {
                if(passIdx == 0 || (passIdx) > 0 && (busTime != passengers[passIdx-1]))
                    res = busTime;
            }
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,20]\n[2,17,18,19]\n2\n
// @lcpr case=end

// @lcpr case=start
// [20,30,10]\n[19,13,26,4,25,11,21]\n2\n
// @lcpr case=end

 */

