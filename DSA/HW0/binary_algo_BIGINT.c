#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

// bigint 進位為10^9
// 所以要int64_t
typedef int64_t arrtype;
#define Base 1000000000
// arr 中每個元素最多有九位
#define Digit 9

typedef struct BIGINT
{
    /*
    arr = {67, 45, 23}
    base = 100
    => 23*100^2+45*100+67 = 234567
    */
    arrtype *arr;
    arrtype len;
}S_BigInt;

S_BigInt* str2_BigInt_dec(const char* str_int)
{
    S_BigInt* ret = NULL;
    arrtype i, len = 0;
    arrtype ret_len, offset, tmp;

    if(NULL != str_int)
    {
        // 計算string 的長度
        for(len = 0; str_int[len] != 0; len++);

        ret = (S_BigInt*)malloc(sizeof(S_BigInt));

        // 算出在base = 10^9 下會有幾位
        ret_len = (len + Digit -1) / Digit;

        if(NULL != ret)
        {
            ret->len = ret_len;
            ret->arr = (arrtype*)malloc(sizeof(arrtype) * ret_len);
            if(NULL != ret->arr)
            {
                // init the return BigInt's arr
                for(i = 0; i < ret_len; i++)
                {
                    ret->arr[i] = 0;
                }
                // star convert
                tmp = 1;
                for(i = 0; i< len; i++)
                {

                }
            }
        }
    }
}

void BigInt_print(const S_BigInt* BigInt)
{
    arrtype i, j;
    char *ret = NULL, tmp = NULL;
    ret = (char*)malloc(sizeof(char) * (BigInt->len * Digit + 1));
    tmp = (char*)malloc(sizeof(char) * (Digit * 2 + 1));

    if((NULL != ret) && (NULL != tmp))
    {
        ret[0] = '\0';
    }
}