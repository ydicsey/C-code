#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int findnumber(int cnt, int* arr, int arrSize)
{
    int CNT = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == 1)
        {
            CNT++;
            if (CNT == cnt)
            {
                return i;
            }
        }
    }
}

int* main(){
    int arrSize = 10;
    int returnSize = 2;
    int *arr = (int *)malloc(sizeof(int) * arrSize);
    int *ans = (int *)malloc(sizeof(int) * 2);
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 0;
    arr[3] = 1;
    arr[4] = 1;
    arr[5] = 0;
    arr[6] = 1;
    arr[7] = 1;
    arr[8] = 0;
    arr[9] = 1;

    int CNT_one = 0;
    for (int i = 0; i < arrSize; i++)
    {
        CNT_one += arr[i];
    }
    if (CNT_one % 3)
    {
        ans[0] = -1;
        ans[1] = -1;
        printf("-1, -1");
        return 0;
    }
    if (CNT_one == 0)
    {
        ans[0] = 0;
        ans[1] = 2;
        printf("0, 2");
        return 0;
    }

    int CNT_first_part = 0, CNT_second_part = 0, CNT_third_part = 0;
    int CNT_one_inApart = CNT_one / 3;

    CNT_first_part = findnumber(1, arr, arrSize);
    CNT_second_part = findnumber(CNT_one_inApart + 1, arr, arrSize);
    CNT_third_part = findnumber(CNT_one_inApart*2 + 1, arr, arrSize);

    printf("%d, %d, %d\n", CNT_first_part, CNT_second_part, CNT_third_part);
    while (CNT_third_part < arrSize && (arr[CNT_first_part] == arr[CNT_second_part]) && (arr[CNT_second_part] == arr[CNT_third_part]))
    {
        CNT_first_part += 1;
        CNT_second_part += 1;
        CNT_third_part += 1;
    }

    printf("%d, %d, %d\n", CNT_first_part, CNT_second_part, CNT_third_part);

    if (CNT_third_part == arrSize)
    {
        ans[0] = CNT_first_part-1;
        ans[1] = CNT_second_part;
        printf("%d, %d",  CNT_first_part-1, CNT_second_part);
        return 0;
    }

    printf("-1, -1");
    return 0;
}