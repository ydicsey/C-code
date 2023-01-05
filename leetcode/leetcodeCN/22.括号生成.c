/*
 * @lc app=leetcode.cn id=22 lang=c
 *
 * [22] 括号生成
 */

// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 卡塔蘭數 1430
#define MAX_SIZE 1430 

void dfs(int length, int left_cnt, int right_cnt, int *returnSize, char **result, char *str, int n)
{
    if(left_cnt == 0 && right_cnt == 0)
    {
        // puts(str);
        result[(*returnSize)] = (char*)calloc((2 * n + 1), sizeof(char));
        strncpy(result[(*returnSize)++], str, 2*n);
        return;
    }
    if(left_cnt > right_cnt)
    {
        return;
    }
    if(left_cnt > 0)
    {
        str[length] = '(';
        dfs(length+1, left_cnt-1, right_cnt, returnSize, result, str, n);
    }
    if(right_cnt > left_cnt)
    {
        str[length] = ')';
        dfs(length+1, left_cnt, right_cnt-1, returnSize, result, str, n);
    }
}

char ** generateParenthesis(int n, int* returnSize){
    char *str = (char*)calloc((2 * n + 1), sizeof(char));
    char **result = calloc((2 * n + 1) * MAX_SIZE, sizeof(char));

    *returnSize = 0;
    dfs(0, n, n, returnSize, result, str, n);
    return result;
}
// @lc code=end

