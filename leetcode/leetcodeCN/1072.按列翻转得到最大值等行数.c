/*
 * @lc app=leetcode.cn id=1072 lang=c
 *
 * [1072] 按列翻转得到最大值等行数
 */

// @lc code=start
#define max(x, y) ((x) < (y) ? (y) : (x))

typedef struct
{
    unsigned int array[10];
}List;

typedef struct
{
    List key;                   /*  key: 紀錄一行的特徵                         */
    int CNT;                    /*  Count of occurrences: 出現的次數            */
    UT_hash_handle hh;          /*  makes this structure hashable 
                                    uthash 已經被 include 於目前的 LeetCode     */
}map;

map* hash_table = NULL;          /* a NULL struct for hash map initialization   */

// return Count of occurrences: 出現的次數
int hash_Add(List key)
{
    map *tmp;
    /* is it already in the hash ?
       tmp: output pointer      */
    HASH_FIND(hh, hash_table, &key, sizeof(key), tmp);
    if(NULL == tmp)
    {
        tmp = (map*)malloc(sizeof(map));
        tmp->key = key;
        // memcpy(&tmp->key, &key, sizeof(key));
        tmp->CNT = 1;
        HASH_ADD(hh, hash_table, key, sizeof(key), tmp);
    }
    else
    {
        tmp->CNT++;
    }
    return tmp->CNT;
}

int maxEqualRowsAfterFlips(int** matrix, int matrixSize, int* matrixColSize){
    int xSize = matrixSize;
    int ySize = matrixColSize[0];
    int ans = 0;
    unsigned int x = 0, y = 0;
    List key;

    for(int x = 0; x < xSize; x++)
    {
        for(int y = 0 ; y < ySize; y++)
        {
            // 若
            if(matrix[x][0] ^ matrix[x][y])
            {
                key.array[y >> 5] &= ~(1u << (y & 31));
            }
            else
            {
                key.array[y >> 5] |= (1u << (y & 31));
            }
        }
        int CNT_tmp = hash_Add(key);
        ans = max(CNT_tmp, ans);
    }
    return ans;
}
// @lc code=end

