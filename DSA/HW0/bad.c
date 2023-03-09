#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define MAXLEN 260

typedef struct
{
    int32_t *arr;
    int64_t len;
}BigInt;

BigInt *str2BigInt(const char* str)
{
    BigInt* ret = NULL;
    int64_t len = strlen(str);

    ret = (BigInt*) malloc(sizeof(BigInt));
    ret->len = len;
    ret->arr = (int32_t*)malloc(sizeof(int32_t) * len);

    for(int64_t i = len-1, idx = 0; i >= 0; i--, idx++)
    {
        ret->arr[i] = (int64_t)(str[idx] - '0');
    }

    return ret;
}

void BigInt_print(const BigInt* tmp)
{
    for(int i = tmp->len-1; i >= 0; i--)
    {
        printf("%d", tmp->arr[i]);
    }
    printf("\n");
}

int BigInt_iszero(const BigInt* tmp)
{
    int i;
    if(tmp->len <= 0)
    {
        return 1;
    }
    if(NULL == tmp->arr)
    {
        return 1;
    }
    for(i = tmp->len -1; i >= 0; i--)
    {
        if(tmp->arr[i] != 0)
        {
            break;
        }
    }
    if(i < 0)
    {
        return 1;
    }
    return 0;
}

int BigInt_iseven(const BigInt* tmp)
{
    return (1-(tmp->arr[0] % 2));
}

int32_t BigInt_len(const int32_t* tmp)
{
    int64_t i;
    for(i = MAXLEN-1; i >= 0; i--)
    {
        if(tmp[i] != 0)
        {
            break;
        }
    }

    if(i < 0)
    {
        i++;
    }

    return ++i;
}

BigInt *BigInt_mul_2(const BigInt* a)
{
    BigInt *ans = (BigInt*)malloc(sizeof(BigInt));

    int32_t *tmp = (int32_t*)malloc(sizeof(int32_t) * MAXLEN);

    int64_t i;
    for(i = 0; i < a->len; i++)
    {
        tmp[i] = a->arr[i] * 2;
    }
    for(i = 0; i < MAXLEN-1; i++)
	{
		tmp[i+1] += tmp[i] / 10;
		tmp[i] %= 10;
	}

    ans->len = BigInt_len(tmp);
    ans->arr = (int32_t*)malloc(sizeof(int32_t) * ans->len);
    for(i = 0; i < ans->len; i++)
    {
        ans->arr[i] = tmp[i];
    }
    free(tmp);
    return ans;
}

BigInt *BigInt_div_2(const BigInt* a)
{
    BigInt *ans = (BigInt*)malloc(sizeof(BigInt));
    int32_t *tmp = (int32_t*)malloc(sizeof(int32_t) * MAXLEN);

    int64_t i, r = 0;
    for(i = a->len -1; i >= 0; i--)
    {
        r = r*10 + a->arr[i];
        tmp[i] = r / 2;
        r %= 2;
    }

    ans->len = BigInt_len(tmp);
    ans->arr = (int32_t*)malloc(sizeof(int32_t) * ans->len);
    for(i = 0; i < ans->len; i++)
    {
        ans->arr[i] = tmp[i];
    }
    free(tmp);
    return ans;
}

// a must large then b
// return a-b
BigInt *BigInt_sub(const BigInt* a, const BigInt* b)
{
    BigInt *ans = (BigInt*)malloc(sizeof(BigInt));
    int32_t *tmp = (int32_t*)malloc(sizeof(int32_t) * MAXLEN);
    int64_t i;

    for(i = 0; i < a->len; i++)
    {
        tmp[i] = a->arr[i] - b->arr[i];
    }

    for(i = 0; i < MAXLEN; i++)
    {
        if(tmp[i] < 0)
        {
            tmp[i+1] --;
            tmp[i] += 10;
        }
    }

    ans->len = BigInt_len(tmp);
    ans->arr = (int32_t*)malloc(sizeof(int32_t) * ans->len);
    for(i = 0; i < ans->len; i++)
    {
        ans->arr[i] = tmp[i];
    }
    free(tmp);
    return ans;
}

// a < b
int less_then(const BigInt* a, const BigInt* b)
{
    if(a->len == b->len)
    {
        for(int i = a->len -1; i >= 0; i--)
        {
            if(a->arr[i] != b->arr[i])
            {
                return (a->arr[i] < b->arr[i]);
            }
        }
    }
    else
    {
        return (a->len < b->len);
    }
}

void BigInt_free(BigInt** tmp)
{
    if ((*tmp)->arr) 
    {
        free((*tmp)->arr);
	}
    (*tmp)->arr = NULL;
    (*tmp)->len = 0;
    free(*tmp);
}

// if a < b
// tmp = a;
// a = b;
// b = tmp;
void swap(BigInt* a, BigInt* b)
{
    BigInt* tmp = (BigInt*)malloc(sizeof(BigInt));
    tmp->len = a->len;
    tmp->arr = (int32_t*)malloc(sizeof(int32_t) * (tmp->len));
    for(int i = 0; i < tmp->len; i++)
    {
        tmp->arr[i] = a->arr[i];
    }
    a->len = b->len;
    a->arr = (int32_t*)malloc(sizeof(int32_t) * a->len);
    for(int i = 0; i < a->len; i++)
    {
        a->arr[i] = b->arr[i];
    }
    b->len = tmp->len;
    for(int i = 0; i < b->len; i++)
    {
        b->arr[i] = tmp->arr[i];
    }
    BigInt_free(&tmp);
}

int main()
{
    char input_1[MAXLEN] = {0};
    char input_2[MAXLEN] = {0};

    // fgets(input_1, MAXLEN-1, stdin);
    // input_1[strlen(input_1) -1] = '\0';
    // fgets(input_2, MAXLEN-1, stdin);
    // input_2[strlen(input_2) -1] = '\0';

    scanf("%s %s", input_1, input_2);

    BigInt* A = str2BigInt(input_1);
    BigInt* B = str2BigInt(input_2);
    BigInt* ans = str2BigInt("1");

    // BigInt_print(A);
    // BigInt_print(B);

    if(!less_then(A, B))
    {
        printf("a>b\n");
        swap(A, B);
    }

    BigInt_print(A);
    BigInt_print(B);

    // binary algo
    // A < B
    while(!BigInt_iszero(A) && !BigInt_iszero(B))
    {
        getchar();
        if(BigInt_iseven(A) && BigInt_iseven(B))
        {
            printf("1:");
            ans = BigInt_mul_2(ans);
            A = BigInt_div_2(A);
            B = BigInt_div_2(B);
        }
        else if(BigInt_iseven(A))
        {
            printf("2:");
            A = BigInt_div_2(A);
        }
        else if(BigInt_iseven(B))
        {
            printf("3:");
            B = BigInt_div_2(B);
        }
        if(!less_then(A, B))
        {
            swap(A, B);
        }
        BigInt_print(A);
        BigInt_print(B);
        BigInt_print(ans);
        printf("B-A\n");
        B = BigInt_sub(B, A);
        BigInt_print(A);
        BigInt_print(B);
        BigInt_print(ans);
        printf("\n");
    }
    // BigInt_print(A);
    // BigInt_print(B);
    // BigInt_print(ans);
}