/*
 * @lc app=leetcode.cn id=3066 lang=cpp
 * @lcpr version=30204
 *
 * [3066] 超过阈值的最少操作数 II
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
    int minOperations(vector<int>& nums, int k) {
        priority_queue <long long int ,vector<long long int>, greater<>> pq;
        if(nums.size() >= 2)
        {
            for (long long int i : nums)
            {
                pq.push(i);
            }
            long long int cnt = 0, a = 0, b = 0 ;
            while((a = pq.top()) && a < k)
            {
                pq.pop();
                b = pq.top();
                pq.pop();
                cout << a << " " << b << " " << min(a, b) + 2 * max(a, b)<< endl;
                pq.push((min(a, b) << 1) + max(a, b));
                
                ++cnt;
            }
            return cnt;
        }
        return 0;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,11,10,1,3]\n10\n
// @lcpr case=end

// @lcpr case=start
// [1,1,2,4,9]\n20\n
// @lcpr case=end

 */

