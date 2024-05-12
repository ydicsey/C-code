/*
 * @lc app=leetcode.cn id=264 lang=cpp
 *
 * [264] 丑数 II
 */

// @lc code=start
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> ugly_(n, 1);
        int twoidx = 0, threeidx = 0, fiveidx = 0, idx = 0;
        int twoNum = 1, threeNum = 1, fiveNum = 1;
        for(int i = 0; i < n; ++i)
        {
            int tmp = min({twoNum, threeNum, fiveNum});
            ugly_[idx++] = tmp;
            if(tmp == twoNum)
            {
                twoNum = 2 * ugly_[twoidx++];
            }
            if(tmp == threeNum)
            {
                threeNum = 3 * ugly_[threeidx++];
            }
            if(tmp == fiveNum)
            {
                fiveNum = 5 * ugly_[fiveidx++];
            }
        }
        // cout << ugly_[n-1];
        return ugly_[n-1];
    }
};
// @lc code=end

