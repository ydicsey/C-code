/*
 * @lc app=leetcode.cn id=1815 lang=c
 *
 * [1815] 得到新鲜甜甜圈的最多组数
 */

// @lc code=start
#define max(x, y) ((x) < (y) ? (y) : (x))
#define Min(x, y) ((x) > (y) ? (y) : (x))

int maxHappyGroups(int batchSize, int *groups, int groupsSize)
{
    // 計算groupsize % size 是 0 數量
    int ans = 0;
    int freq[9];
    memset(freq, 0, sizeof(freq));

    for (int i = 0; i < groupsSize; i++)
    {
        int n = groups[i] % batchSize;
        if (n)
        {
            freq[n]++;
        }
        else
        {
            // 剛好整除的group
            ans++;
            freq[n] = 0;
        }
    }

    // 先處理兩組加起來的可以整除的
    for (int i = 1; i <= (batchSize - 1) / 2; i++)
    {
        int matchNum = batchSize - i;
        int matchCNT = 0;
        matchCNT = Min(freq[i], freq[matchNum]);
        ans += matchCNT;
        freq[i] -= matchCNT;
        freq[matchNum] -= matchCNT;
    }
    if (!batchSize % 2)
    {
        ans += freq[batchSize / 2] / 2;
        freq[batchSize / 2] -= ((freq[batchSize / 2] / 2) * 2);
    }

    // https://leetcode.cn/problems/maximum-number-of-groups-getting-fresh-donuts/solution/cpp-8zhong-xun-huan-dp-by-john_shelvin-kjog/
    int dp[freq[1] + 1][freq[2] + 1][freq[3] + 1][freq[4] + 1][freq[5] + 1][freq[6] + 1][freq[7] + 1][freq[8] + 1];
    for (int a = 0; a <= freq[1]; a++)
    {
        for (int b = 0; b <= freq[2]; b++)
        {
            for (int c = 0; c <= freq[3]; c++)
            {
                for (int d = 0; d <= freq[4]; d++)
                {
                    for (int e = 0; e <= freq[5]; e++)
                    {
                        for (int f = 0; f <= freq[6]; f++)
                        {
                            for (int g = 0; g <= freq[7]; g++)
                            {
                                for (int h = 0; h <= freq[8]; h++)
                                {
                                    dp[a][b][c][d][e][f][g][h] = 0;
                                    int tempsum = a * 1 + b * 2 + c * 3 + d * 4 + e * 5 + f * 6 + g * 7 + h * 8;
                                    if (a > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a - 1][b][c][d][e][f][g][h] + ((tempsum - 1) % batchSize == 0));
                                    }
                                    if (b > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a][b - 1][c][d][e][f][g][h] + ((tempsum - 2) % batchSize == 0));
                                    }
                                    if (c > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a][b][c - 1][d][e][f][g][h] + ((tempsum - 3) % batchSize == 0));
                                    }
                                    if (d > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a][b][c][d - 1][e][f][g][h] + ((tempsum - 4) % batchSize == 0));
                                    }
                                    if (e > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a][b][c][d][e - 1][f][g][h] + ((tempsum - 5) % batchSize == 0));
                                    }
                                    if (f > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a][b][c][d][e][f - 1][g][h] + ((tempsum - 6) % batchSize == 0));
                                    }
                                    if (g > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a][b][c][d][e][f][g - 1][h] + ((tempsum - 7) % batchSize == 0));
                                    }
                                    if (h > 0)
                                    {
                                        dp[a][b][c][d][e][f][g][h] = max(dp[a][b][c][d][e][f][g][h], dp[a][b][c][d][e][f][g][h - 1] + ((tempsum - 8) % batchSize == 0));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return ans + dp[freq[1]][freq[2]][freq[3]][freq[4]][freq[5]][freq[6]][freq[7]][freq[8]];
}
// @lc code=end
