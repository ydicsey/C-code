/*
 * @lc app=leetcode.cn id=1657 lang=c
 *
 * [1657] 确定两个字符串是否接近
 */

// @lc code=start
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

bool closeStrings(char * word1, char * word2){
    int len_str1 = strlen(word1);
    int len_str2 = strlen(word2);

    if(len_str1 == len_str2)
    {
        int CNT_str1[30] = {0};
        int CNT_str2[30] = {0};

        for(int i = 0; i < len_str1; i++)
        {
            CNT_str1[ word1[i] - 'a' ] ++;
            CNT_str2[ word2[i] - 'a' ] ++;
        }
        // 替換的話需要兩的字符都存在才有替換的可能
        // 若是有字符不存在是不可能可以替換的
        for(int i = 0; i < 26; i++)
        {
            if((CNT_str1[i] == 0 && CNT_str2[i] != 0) || (CNT_str1[i] != 0 && CNT_str2[i] == 0))
            {
                return 0;
            }
        }

        qsort(CNT_str1, 26, sizeof(int), cmpfunc);
        qsort(CNT_str2, 26, sizeof(int), cmpfunc);

        // 替換也需要量個字符的次數一致
        // 對比排序後的字串就知道了
        for(int i = 0; i < 26; i++)
        {
            if(CNT_str1[i] != CNT_str2[i])
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
// @lc code=end

