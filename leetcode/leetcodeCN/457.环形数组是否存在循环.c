/*
 * @lc app=leetcode.cn id=457 lang=c
 *
 * [457] 环形数组是否存在循环
 */

// @lc code=start
#define signsame(num1, num2) ((num1>0 && num2>0) || (num1<0 && num2<0))

int next(int cur, int* nums, int numsSize)
{
    cur += nums[cur];
    cur %= numsSize;
    cur += numsSize;
    cur %= numsSize;

    return cur;
}

bool circularArrayLoop(int* nums, int numsSize){
    for(int i = 0; i < numsSize; i++)
    {
        // all nums =/= 0
        // if nums is 0 means it is visited
        if(nums[i] == 0)
        {
            continue;
        }

        // fast goes 2 steps
        // slow goes 1 step
        int slow = i;
        int fast = next(i, nums, numsSize);

        while(signsame(nums[fast], nums[slow]) && signsame(nums[fast], nums[next(fast, nums, numsSize)]))
        {
            if (slow == fast)
            {
                // cycle length = 1
                if (slow == next(slow, nums, numsSize))
                {
                    break;
                }
                else
                {
                    return 1;
                }
            }
        
            // fast goes 2 steps
            // slow goes 1 step
            slow = next(slow, nums, numsSize);
            fast = next(next(fast, nums, numsSize), nums, numsSize);
        }

        // set visited 0
        int index = i;
        while(nums[index] != 0)
        {
            nums[index] = 0;
            index = next(index, nums, numsSize);
        }
    }
    return 0;
}
// @lc code=end

