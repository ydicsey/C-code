/*
 * @lc app=leetcode.cn id=327 lang=c
 *
 * [327] 区间和的个数
 */

// @lc code=start

// 計算subset sum在 lower and upper之間的個數
/*
j >= i
lower <= ( presum[j] - presum[i] ) <= upper
*/ 

int count;

void merge(long long *presum, int left, int mid, int right, long long *temp, int lower, int upper)
{
    for(int i = left; i <= right; i++)
    {
        temp[i] = presum[i];
    }

    int startidx = mid+1, endidx = mid+1;
    for(int i = left; i <= mid; i++)
    {
        while(startidx <= right && (presum[startidx] - presum[i]) < lower)
        {
            startidx++;
        }
        while(endidx <= right && (presum[endidx] - presum[i]) <= upper)
        {
            endidx++;
        }
        // printf("%d, %d, %d\n", startidx, endidx, count);
        count += (endidx - startidx);
    }

    

    int cnt = left;
    int i = left, j = mid + 1;
    while (i <= mid || j <= right) 
    {
        if (i > mid) 
            presum[cnt++] = temp[j++];
        else if (j > right) 
            presum[cnt++] = temp[i++];
        else if (temp[i] >= temp[j]) 
            presum[cnt++] = temp[j++];
        else 
            presum[cnt++] = temp[i++];
    }
}

void sort(long long *presum, int left, int right, long long *temp, int lower, int upper)
{
    if(left == right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    sort(presum, left, mid, temp, lower, upper);
    sort(presum, mid+1, right, temp, lower, upper);

    merge(presum, left, mid, right, temp, lower, upper);
}


int countRangeSum(int* nums, int numsSize, int lower, int upper){
    // helper for merge sort
    long long *temp = malloc((numsSize+1) * sizeof(long long));
    // 為了算i~j的和
    long long *presum = malloc((numsSize+1) * sizeof(long long));
    presum[0] = 0;
    for(int i = 0; i < numsSize; i++)
    {
        presum[i+1] = (long long)(nums[i] + presum[i]);
    }
    count = 0;
    sort(presum, 0, numsSize, temp, lower, upper);
    return count;
}
// @lc code=end