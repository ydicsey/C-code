/*
 * @lc app=leetcode.cn id=1578 lang=c
 *
 * [1578] 使绳子变成彩色的最短时间
 */

// @lc code=start

// greedy!
#define max(x, y) ((x) < (y) ? (y) : (x))

// 104 ms/ 14.3 MB
int minCost(char * colors, int* neededTime, int neededTimeSize){
    int len = neededTimeSize;
    int ans = 0, costSum = 0, maxCost = 0;
    for(int i = 1; i < len; i++)
    {
        char ch = colors[i-1];
        if(ch == colors[i])
        {
            costSum = neededTime[i-1];
            maxCost = neededTime[i-1];
            while(i < len && ch == colors[i])
            {
                costSum += neededTime[i];
                maxCost = max(neededTime[i], maxCost);
                i++;
            }
            ans += costSum - maxCost;
        }
    }
    return ans;
}
// @lc code=end

