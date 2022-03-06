int searchInsert(int* nums, int numsSize, int target){
    if(target < nums[0]){
        return 0;
    }
    if(target > nums[numsSize-1]){
        return numsSize;
    }
    int left = 0;
    int right = numsSize - 1;
    int pivot;
    while (left <= right)
    {
        pivot = left + (right - left) / 2;
        if (nums[pivot] < target)
            left = pivot + 1;
        else if (nums[pivot] > target)
            right = pivot - 1;
    }
    return left;
}