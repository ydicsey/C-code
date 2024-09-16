/*
 * @lc app=leetcode.cn id=1184 lang=cpp
 * @lcpr version=30204
 *
 * [1184] 公交站间的距离
 */


// @lcpr-template-start
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        int size = distance.size();
        int clockWise = 0, counterClockWise = 0;
        int range = abs(start - destination);
        if(start > destination)
        {
            swap(start, destination);
        }
        while(range--)
        {
            cout << distance[((start+size) % size)] << " ";
            clockWise += distance[((start+size) % size)];
            start++;
            cout << clockWise << endl;
        }
        for(auto &i: distance)
        {
            counterClockWise += i;
        }
        counterClockWise = abs(counterClockWise - clockWise);
        cout << clockWise << " " << counterClockWise << endl;
        return min(counterClockWise, clockWise);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4]\n0\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4]\n0\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4]\n0\n3\n
// @lcpr case=end

 */

