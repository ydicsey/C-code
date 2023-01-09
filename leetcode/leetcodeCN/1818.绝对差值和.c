/*
 * @lc app=leetcode.cn id=1818 lang=c
 *
 * [1818] 绝对差值和
 */

// @lc code=start

/* 
j替換i
最大( |num1[i]-num2[i]| - |num1[j]-num2[i]| )
=> 最小化 |num1[j]-num2[i]|
*/

int minAbsoluteSumDiff(int* nums1, int nums1Size, int* nums2, int nums2Size){
    const int mod = 1000000007;
    int sum = 0;
    // 最大的絕對值差
    // 最大( |num1[i]-num2[i]| - |num1[j]-num2[i]| )
    int max_diff = 0;

    for(int i = 0; i < nums1Size; i++)
    {
        int num1i = nums1[i];
        int num2i = nums2[i];
        int diff_orig = abs(num1i - num2i);
        sum += diff_orig;
        sum %= mod;
        
        // 減少循環的次數避免TLE
        if (diff_orig <= max_diff) 
        {
            continue;
        }
        for(int j = 0; j < nums1Size; j++)
        {
            int num1j = nums1[j];
            int diff = abs(num1j - num2i);
            int tmp = diff_orig - diff;
            max_diff = tmp > max_diff ? tmp : max_diff;
        }
    }

    sum -= max_diff;
    sum %= mod;
    sum += mod;
    sum %= mod;
    return sum;
}
// @lc code=end

