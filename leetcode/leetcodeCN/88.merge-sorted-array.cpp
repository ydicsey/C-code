/*
 * @lc app=leetcode.cn id=88 lang=cpp
 * @lcpr version=30204
 *
 * [88] 合并两个有序数组
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
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int idx_m = 0, idx_n = 0, idx = 0;
        vector<int> res(m+n, 0);
        while(m != idx_m && n != idx_n)
        {
            cout << nums1[idx_m] << nums2[idx_n] << idx_m << idx_n << idx << endl;
            if(nums1[idx_m] < nums2[idx_n])
            {
                res[idx++] = nums1[idx_m++];
            }
            else
            {
                res[idx++] = nums2[idx_n++];
            }
        }
        
        if(m != idx_m)
        {
            while (m != idx_m)
            {
                res[idx++] = nums1[idx_m++];
            }
        }
        else
        {
            while (n != idx_n)
            {
                res[idx++] = nums2[idx_n++];
            }
        }
        for(int i : res)
        {
            cout << i << endl;
        }
        nums1 = res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,0,0,0]\n3\n[2,5,6]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n[]\n0\n
// @lcpr case=end

// @lcpr case=start
// [0]\n0\n[1]\n1\n
// @lcpr case=end

 */

