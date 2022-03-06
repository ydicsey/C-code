int search(int* nums, int numsSize, int target){
    int left = 0;
    int right = numsSize-1;
    int pivot;
    while (left <= right)
    {
        pivot = (left + right) / 2;
        if (nums[pivot] == target)
            return pivot;
        if (nums[pivot] < target)
            left = pivot + 1;
        else if (nums[pivot] > target)
            right = pivot - 1;
    }
    return -1;
} 
