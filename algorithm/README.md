# HW2
## p303. Treasure
## p304. Combination Lock
## p305. Another Treasure
## p306. Auction
- reference
    - [评论区的一个奇妙的解法｜不用DP](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/solution/by-gopherhiro-hl5x/)
# HW3
## p338. Bento
## p339. Leva
- Description
    - One day, Jason has nightmare that he wakes up and finds part of bedroom has been burned out with lava. Fortunately, due to the slow flow of lava, Jason has some time to escape from bed to door.
- method
    - BFS to get the erriest time that leva arrive, and then use binary search to apply time to check if can arrive door using BSF
    - 2 * BFS + binary search
- reference
    - [course.2020.ntnu.algorithms/HW5/pB](https://github.com/c5h11oh/course.2020.ntnu.algorithms/blob/master/HW5/pB/main.cpp)
    - [LeetCode 2258. Escape the Spreading Fire](https://leetcode.cn/problems/escape-the-spreading-fire/)
    - [youtube. LeetCode 2258. Escape the Spreading Fire](https://www.youtube.com/watch?v=xUijWmULpzA&ab_channel=HuifengGuan)
<!-- - tips from teaching assistant
    - 我可以先把所有岩漿的位置記錄起來，從這些位置開始往外延伸，一秒就延伸一格，所以 T 秒之後每個岩漿會往外延伸 T 格，這樣就可以生出 T 秒之後房間的樣子了，方便我們快速知道每一格最早在幾秒後會有岩漿，經過剛剛的步驟生出房間的樣子，根據這個房間從床 B 出發去判斷是否可以走到門 D，可以的話代表時間還很充裕，不行的話代表太遲了，以上步驟可以用 BFS 實現。 -->

## p340. Target Sum
- Description
    - Given a target value T and a set of numbers S, try to find out how many different non-empty subsets of S sum up to T. Your task is to help him determine the number of solutions.
- method
    - DP
    - meet in the middle
    - recursion
- reference
    - [Count of subsets with sum equal to X using Recursion](https://www.geeksforgeeks.org/count-of-subsets-with-sum-equal-to-x-using-recursion/?ref=lbp)
    - [Count of subsets with sum equal to X](https://www.geeksforgeeks.org/count-of-subsets-with-sum-equal-to-x/)
    - [UVA 12911](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4776)
    - GitHub
        - [metaphysis/Code](https://github.com/metaphysis/Code/tree/master/UVa%20Online%20Judge/volume129/12911%20Subset%20Sum)
        - [sourav-saha/bitwise_problems](https://github.com/sourav-saha/bitwise_problems/blob/a26e8803abb99ef2ed562a501fbc33580bbd9cd3/array_subset_sum.py)
        - [morris821028/UVa](https://github.com/morris821028/UVa/blob/master/temp/UVaDate/12911%20-%20Subset%20sum.cpp)
        - [dibery/UVa](https://github.com/dibery/UVa/blob/master/vol129/12911.cpp)
    - [subset sum with negative values in c or c++](https://stackoverflow.com/questions/43078142/subset-sum-with-negative-values-in-c-or-c)
    <!-- that the target sum needs to be **offset** by **n*offset**-->
    - [Count Number of subsets with given Sum](https://www.codingninjas.com/codestudio/library/count-number-of-subsets-with-given-sum)
    - [Lecture 19
Dynamic Programming](https://courses.cs.washington.edu/courses/cse421/15au/lectures/Lecture19/Lecture19_ho.pdf)
     - [vjudge-12911](https://vjudge.net/status/#un=&OJId=UVA&probNum=12911&res=0&orderBy=run_id&language=)
- tips from teaching assistant
    - Subtask 1 & 2
        - N 的數字不大，考慮搜尋所有子集合的時間複雜度為O(N * 2N)。那怎麼有效率的把每個組合都遍歷過呢?集合中的每個數字都可以選擇取或不取，有兩種適合的方法。1. 透過Backtracking(類似 DFS) 的遞迴方式進行枚舉。2. 我們可以觀察 0 ~ 2N - 1 的二進位制編碼:假如N = 3, 結果如下:000, 001, 010, 011, 100, 101, 110, 111; 1代表取，0代表不取，同樣可以使用迴圈進行枚舉，以遍歷所有組合。
    - Subtask 3
        - N = 40 的情況，240 會超出一秒的時限，20 * 220 = 20 * 1048576，不會超過一秒的限制，可以想想看與題目 N 的限制有何關聯。
## p341. Anti-Sea-Bear Circle
- Description
- reference
    - [youtube-DFS](https://www.youtube.com/watch?v=FotFj2PeFd8&ab_channel=TuringMachines)

## 351.	Metro
## 352. Budget Cut
<!-- - tips from teaching assistant
    - 這題簡單來說就是要從圖中選出一個網路（子圖），選擇的方法有三個漸進的規則：

    1. 網路的 cabel 數量愈少愈好，同學已經點出來了，這個規則限制找的子圖一定會是樹，圖中的所有 spanning tree 都符合條件，所以可能不只一個方案，繼續看規則 2.

    2. 網路中瓶頸（最小的 bandwidth）要愈大愈好，以第三筆範例來說，所有 spanning tree 裡面，可以找到瓶頸最大的為瓶頸為 8 的時候，同樣地，圖中可能有多個可以選的子圖符合這個條件，所以繼續套用規則 3.

    3. 選擇 bandwidths 總和最小的那個

    - 至此最後我們會得出一個 bandwidths 總和最小值，即是這題所要的答案
    ![image](https://github.com/ydicsey/C-code/blob/master/algorithm/image/p352.png?raw=true)


    在題敘中有提到一個 Hint，在手寫題第一題中有提到如何找規則 2. 中的瓶頸，所以同學剩下規則 3. 需要思考，怎麼從符合規則 2. 的網路中找到 bandwidths 總和最小的那個
## 353. Traveling Salesman Problem
- Description
- method
    - use Dijkstra pseudocode
    - reference
        - [Fibonacci Heap](https://www.programiz.com/dsa/fibonacci-heap) -->
## 354.	Rent
<!-- - Description
- tips from teaching assistant

可以先把每個Uier和他朋友們分別住在A和B公寓的情況畫出來，如第一張圖。

每一條邊代表Unhappiness，可以看到我虛擬了兩個點S(Source，源點)、T(Sink，匯點)。

S -> A 代表住A公寓的Unhappiness，B -> T 代表住B公寓的Unhappiness。

兩個好朋友分開住的情形，舉例來說: 1和2是好朋友分開住會造成6的Unhappiness。1住A且2住B，中間就會有Unhappiness為6的邊;反之，1住B且2住A的情形也會有。

我們可以在把第一張圖簡化成第二張圖，因為A_i和B_i是同一個人。

    Hint: 1. 如圖: 紅色的X是正解的選法，可以觀察看看，最後選完公寓住的時候，是不是一定會造成S -> T不連通的狀況?  
2. 有什麼方法可以找出所有符合情況中的最小值? -->