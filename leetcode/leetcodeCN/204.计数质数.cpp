/*
 * @lc app=leetcode.cn id=204 lang=cpp
 *
 * [204] 计数质数
 */

// @lc code=start
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n, true);
        for(int i = 2; i * i < n; ++i)
        {
            if(isPrime[i])
            {
                for(int j = i * i; j < n; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }
        int CNT = 0;
        for(int i = 2; i < n; ++i)
        {
            if(isPrime[i])
            {
                CNT++;
            }
        }
        return CNT;
    }
};
// @lc code=end

