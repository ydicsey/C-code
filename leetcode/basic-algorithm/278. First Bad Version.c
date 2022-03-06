// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 1;
    int right = n;
    int pivot;
    while (left <= right)
    {
        pivot = left + (right-left)/2;
        if (isBadVersion(pivot))
        {
            if (!isBadVersion(pivot-1))
                return pivot;
            right = pivot - 1;
        }
        else
            left = pivot + 1;
    }
    return pivot;
}