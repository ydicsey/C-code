/*
 * @lc app=leetcode.cn id=241 lang=cpp
 * @lcpr version=30204
 *
 * [241] 为运算表达式设计优先级
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
    vector<int> diffWaysToCompute(string expression) {
        // 以運算符分開成左右兩邊計算
        vector<int> res;
        for(int i = 0; i < expression.size(); ++i)
        {
            char op = expression[i];
            if(op == '*' || op == '+' || op == '-')
            {
                vector<int> left = diffWaysToCompute(expression.substr(0, i));
                vector<int> right = diffWaysToCompute(expression.substr(i+1));
                for(const auto& i : left)
                {
                    for(const auto &j : right)
                    {
                        if(op == '+')
                        {
                            res.emplace_back(i+j);
                        }
                        else if(op == '-')
                        {
                            res.emplace_back(i-j);
                        }
                        else if(op == '*')
                        {
                            res.emplace_back(i*j);
                        }
                    }
                }
            }
        }
        if(res.empty())
        {
            res.emplace_back(stoi(expression));
        }
        return res;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "2-1-1"\n
// @lcpr case=end

// @lcpr case=start
// "2*3-4*5"\n
// @lcpr case=end

 */

