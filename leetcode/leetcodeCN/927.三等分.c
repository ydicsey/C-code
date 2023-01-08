/*
 * @lc app=leetcode.cn id=927 lang=c
 *
 * [927] 三等分
 */

// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// return where is the number cnt's 1 in arr
// int findnumber(int cnt, int* arr, int arrSize)
// {
//     int CNT = 0;
//     for (int i = 0; i < arrSize; i++)
//     {
//         if (arr[i] == 1)
//         {
//             CNT++;
//             if (CNT == cnt)
//             {
//                 return i;
//             }
//         }
//     }
// }

int* threeEqualParts(int* arr, int arrSize, int* returnSize){
    *returnSize = 2;
    int *ans = (int *)malloc(sizeof(int) * 2);

    int CNT_one = 0;
    for (int i = 0; i < arrSize; i++)
    {
        CNT_one += arr[i];
    }
    if (CNT_one % 3)
    {
        ans[0] = -1;
        ans[1] = -1;
        return ans;
    }
    if (CNT_one == 0)
    {
        ans[0] = 0;
        ans[1] = 2;
        return ans;
    }

    int CNT_first_part = 0, CNT_second_part = 0, CNT_third_part = 0;
    int CNT_one_inApart = CNT_one / 3, tmp = 0;

    for(int i = 0; i < arrSize; i++)
    {
        if(arr[i] == 1)
        {
            if(tmp == 0)
            {
                CNT_first_part = i;
            }
            else if(tmp == CNT_one_inApart)
            {
                CNT_second_part = i;
            }
            else if(tmp == CNT_one_inApart *2)
            {
                CNT_third_part = i;
            }
            tmp++;
        }
    }

    while (CNT_third_part < arrSize && (arr[CNT_first_part] == arr[CNT_second_part]) && (arr[CNT_second_part] == arr[CNT_third_part]))
    {
        CNT_first_part += 1;
        CNT_second_part += 1;
        CNT_third_part += 1;
    }

    if (CNT_third_part == arrSize)
    {
        ans[0] = CNT_first_part-1;
        ans[1] = CNT_second_part;
        return ans;
    }

    ans[0] = -1;
    ans[1] = -1;
    return ans;
}
// @lc code=end

