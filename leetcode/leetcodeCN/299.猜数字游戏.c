/*
 * @lc app=leetcode.cn id=299 lang=c
 *
 * [299] 猜数字游戏
 */

// @lc code=start
#define Min(x, y) ((x)>(y)?(y):(x))

char * getHint(char * secret, char * guess){
    int len = strlen(secret);
    int A = 0;
    int B = 0;
    int sec_cnt[10] = {0};
    int gue_cnt[10] = {0};

    for(int i = 0; i < len; i++)
    {
        if(secret[i] == guess[i])
        {
            A++;
        }
        else
        {
            sec_cnt[(int)(secret[i] - '0')] ++;
            gue_cnt[(int)(guess[i] - '0')] ++;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        B += Min(sec_cnt[i], gue_cnt[i]);
    }

    char *ans = malloc(sizeof(char)*10);
    sprintf(ans, "%dA%dB", A, B);
    return ans;
}
// @lc code=end

