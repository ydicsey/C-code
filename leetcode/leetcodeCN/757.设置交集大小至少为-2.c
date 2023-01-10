/*
 * @lc app=leetcode.cn id=757 lang=c
 *
 * [757] 设置交集大小至少为2
 */

// @lc code=start

int compare ( const void *pa, const void *pb ) {
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;
    if(a[1] == b[1])
        return (b[0] - a[0]);
    else
        return (a[1] - b[1]);
}

int intersectionSizeTwo(int** intervals, int intervalsSize, int* intervalsColSize){
    // 排序，interval[1] 升序, [0] 降序
    qsort(intervals, intervalsSize, sizeof(intervals[0]), compare);
    // for(int i = 0; i < intervalsSize; i++){
    //     printf("%d %d\n", intervals[i][0], intervals[i][1]);
    // }

    int right = -1, left = -1, ans = 0;
    for(int i = 0; i < intervalsSize; i++)
    {
        printf("\n%d, %d", left, right);
        // 完全不重疊
        if(right < intervals[i][0])
        {
            ans +=2;
            // greedy
            // 總是選擇interval中最後兩個數字
            left = intervals[i][1] - 1;
            right = intervals[i][1];
        }
        // 重疊一個完素
        else if(left < intervals[i][0])
        {
            ans += 1;
            // greedy
            // 因為 right > interval[0] 
            // 所以總是選擇 加入 interval[1]
            left = right;
            right = intervals[i][1];
        }
    }
    return ans;
}
// @lc code=end