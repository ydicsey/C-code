/*
 * @lc app=leetcode.cn id=1845 lang=cpp
 * @lcpr version=30204
 *
 * [1845] 座位预约管理系统
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
class SeatManager {
public:
    SeatManager(int n) : CNT(n) 
    {
        for(int i = 0; i < CNT; ++i)
        {
            seatReserve.push(i+1);
        }
    }

    int reserve() 
    {
        auto leftMost = seatReserve.top();
        seatReserve.pop();
        return leftMost;
    }

    void unreserve(int seatNumber) {
        seatReserve.push(seatNumber);
    }
private:
    int CNT;
    priority_queue<int, vector<int>, greater<int>> seatReserve;
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
// @lc code=end



/*
// @lcpr case=start
// ["SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"][[5], [], [], [2], [], [], [], [], [5]]\n
// @lcpr case=end

 */

