/*
 * @lc app=leetcode.cn id=1641 lang=c
 *
 * [1641] 统计字典序元音字符串的数目
 */

// @lc code=start

/*
arr[0]: 長度加一之後，首字母為"a"的個數
arr[1]: 長度加一之後，首字母為"e"的個數
arr[2]: 長度加一之後，首字母為"i"的個數
arr[3]: 長度加一之後，首字母為"o"的個數
arr[4]: 長度加一之後，首字母為"u"的個數

==> 
arr "U" = arr "U"
arr "O" = arr "O" + arr "U"
arr "I" = arr "I" + arr "O" + arr "U"
arr "E" = arr "E" + arr "I" + arr "O" + arr "U"
arr "A" = arr "A" + arr "E" + arr "I" + arr "O" + arr "U"

1 1 1 1 1       = 5
5 4 3 2 1       = 15
15 10 6 3 1     = 35
35 20 10 4 1    = 70
70 35 15 5 1    = 126
*/

int countVowelStrings(int n){
    int arr[5] = {1, 1, 1, 1, 1};
    for (int i = 0; i < n; i++) {
        arr[3] += arr[4];
        arr[2] += arr[3];
        arr[1] += arr[2];
        arr[0] += arr[1];
    }
    return arr[0];
}
// @lc code=end