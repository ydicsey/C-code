/*
 * @lc app=leetcode.cn id=815 lang=cpp
 * @lcpr version=30204
 *
 * [815] 公交路线
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
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        int numofBusLine = routes.size();
        // 儲存這個 bus station 有哪些 bus line 經過
        unordered_map<int, vector<int>> linePassStation;
        for(int i = 0; i < numofBusLine; ++i)
        {
            for(auto &j: routes[i])
            {
                linePassStation[j].push_back(i);
            }
        }
        // 如果start or target沒有bus line pass through 
        if(!linePassStation.count(source) || !linePassStation.count(target))
        {
            return source == target ? 0 : -1;
        }

        // BFS structure
        queue<int>BFS;
        vector<bool>visited(numofBusLine, false);
        int dis = 0;
        BFS.push(source);
        while(!BFS.empty())
        {
            int size = BFS.size();
            ++dis;
            while(size--)
            {
                int station = BFS.front();
                BFS.pop();
                for(auto &i : linePassStation[station])
                {
                    if(false == visited[i])
                    {
                        visited[i] = true;
                        for(auto &j : routes[i])
                        {
                            if(j == target)
                            {
                                return source == target ? 0 : dis;
                            }
                            BFS.push(j);
                        }
                    }
                }                
            }
        }
        return -1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,7],[3,6,7]]\n1\n6\n
// @lcpr case=end

// @lcpr case=start
// [[7,12],[4,5,15],[6],[15,19],[9,12,13]]\n15\n12\n
// @lcpr case=end

 */

