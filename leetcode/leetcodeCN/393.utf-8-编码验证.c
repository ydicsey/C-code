/*
 * @lc app=leetcode.cn id=393 lang=c
 *
 * [393] UTF-8 编码验证
 */

// @lc code=start

bool validUtf8(int* data, int dataSize){
    int CNT = 0;
    for(int i = 0; i < dataSize; i++)
    {
        if(CNT == 0)
        {
            if ((data[i] >> 7) == 0)
            {
                // one byte only
                continue;
            }
            else if ((data[i] >> 6) % 2 == 0)
            {
                return 0;
            }
            else if ((data[i] >> 5) % 2 == 0)
            {
                CNT = 1;
            }
            else if ((data[i] >> 4) % 2 == 0)
            {
                CNT = 2;
            }
            else if ((data[i] >> 3) % 2 == 0)
            {
                CNT = 3;
            }
            else 
            {
                return 0;
            }
        }
        else
        {
            if ((data[i] >> 7) == 0)
            {
                return 0;
            }   
            if((data[i] >> 6) %2 == 0)
            {
                // init with "10"
                CNT--;
            }
            else
            {
                return 0;
            }
        }
    }
    return CNT == 0;
}
// @lc code=end

