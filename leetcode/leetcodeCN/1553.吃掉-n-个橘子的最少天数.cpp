/*
 * @lc app=leetcode.cn id=1553 lang=cpp
 *
 * [1553] 吃掉 N 个橘子的最少天数
 */

// @lc code=start
class Solution {
    // 動態規劃
    unordered_map<int, int>DP;
public:
    int minDays(int n) {
        // cout << "n:" << n << endl;
        if(n <= 2)
        {
            return n;
        }
        // 連續吃掉k個使橘子為或3的倍數
        // recursive
        if(DP.count(n))
        {
            return DP[n];
        }
        DP[n] = 1 + min(n%3 + minDays(n/3), n%2 + minDays(n/2));
        return DP[n];
    }
};
// @lc code=end

