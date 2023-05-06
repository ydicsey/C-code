#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
char maze[1005][1005];
int step_fire[1005][1005];
int step_joe[1005][1005];
int m = 0, n = 0;
queue<pair<int, int>> q;
pair<int, int> Joe;

void BFS_fire()
{
    while( !q.empty() )
    {
        pair<int, int> tmp = q.front();
        q.pop();
        for(int i = 0; i < 4; ++i)
        {
            int mm = tmp.first + dir[i][0];
            int nn = tmp.second + dir[i][1];
            if(mm >= m || nn >= n || mm < 0 || nn < 0)
            {
                continue;
            } 
            if(maze[mm][nn] == '#')
            {
                continue;
            }
            if(step_fire[mm][nn] == 0)
            {
                step_fire[mm][nn] = step_fire[tmp.first][tmp.second]+1;
                q.push({mm, nn});
            }
        }
        // for(int i = 0; i < m; ++i)
        // {
        //     for(int j = 0; j < n; ++j)
        //     {
        //         cout << step_fire[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
}

int BFS_joe()
{
    queue<pair<int, int>> qq;
    qq.push(Joe);
    while( !qq.empty() && step_joe[Joe.first][Joe.second] )
    {
        pair<int, int> tmp = qq.front();
        qq.pop();
        
        if(tmp.first == m-1 || tmp.first == 0 || tmp.second == n-1 || tmp.second == 0)
        {
            if(step_fire[tmp.first][tmp.second] && step_fire[tmp.first][tmp.second] > step_joe[tmp.first][tmp.second])
            {
                return step_joe[tmp.first][tmp.second];
            }
            if( !step_fire[tmp.first][tmp.second] )
            {
                return step_joe[tmp.first][tmp.second];
            }
        }
        if(step_fire[tmp.first][tmp.second] && step_fire[tmp.first][tmp.second] <= step_joe[tmp.first][tmp.second])
        {
            continue;
        }
        for(int i = 0; i < 4; ++i)
        {
            int mm = tmp.first + dir[i][0];
            int nn = tmp.second + dir[i][1];
            if(mm >= m || nn >= n || mm < 0 || nn < 0)
            {
                continue;
            } 
            if(maze[mm][nn] == '#')
            {
                continue;
            }
            if(step_joe[mm][nn] == 0)
            {
                step_joe[mm][nn] = step_joe[tmp.first][tmp.second]+1;
                qq.push({mm, nn});
            }
        }
    }
    return -1;
}

int main()
{
    int N = 0;
    cin >> N;
    while(N--)
    {
        cin >> m >> n; cin.ignore();
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                cin >> maze[i][j];
                // 初始化步數
                step_fire[i][j] = 0;
                step_joe[i][j] = 0;

                if(maze[i][j] == 'F')
                {
                    q.push({i, j});
                    step_fire[i][j] = 1;
                }
                if(maze[i][j] == 'J')
                {
                    Joe = {i, j};
                    maze[i][j] = '.';
                    step_joe[i][j] = 1;
                }
            }
        }
        BFS_fire();
        int ans = BFS_joe();
        if(ans == -1)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            cout << ans << endl;
        }
        // for(int i = 0; i < m; ++i)
        // {
        //     for(int j = 0; j < n; ++j)
        //     {
        //         cout << step_joe[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        // for(int i = 0; i < m; ++i)
        // {
        //     for(int j = 0; j < n; ++j)
        //     {
        //         cout << step_fire[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
}