# 希望我可以完成每日一題的紀錄

## leetcode 815

花超久時間, 感覺對BFS還不是很熟, 這邊複習一下BFS的結構

- 用queue實現

## leetcode 241

- 加括號到算式中, 輸出所有可能的答案
亦開始會覺得為DP, 但看完題解不是, 而是 divide and conquer, 把運算子左右兩邊切開, 並遞迴下去, 再進行運算

  - 參考：[題解](https://labuladong.online/algo/practice-in-action/divide-and-conquer/)
  - 補充DP的括號問題：[括號匹配](https://leetcode.com/problems/generate-parentheses/description/)、
  矩陣相乘...

## leetcode 2376

找出特殊數字, 數字範圍超大

- 數位DP

> 利用位運算(bitmask)把 int 當成set來用
>> {0, 2, 3} => bin (1, 1, 0, 1) = dex(13)
>>> mask 是為了判斷東西有沒有重複

$ leetcode 1012, 357 
