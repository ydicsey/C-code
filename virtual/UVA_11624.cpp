#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// maze = m * n
int m = 0, n = 0;
char maze[1005][1005];
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

void show_maze()
{
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

int in_range(int next_m, int next_n)
{
    return(next_m < m && next_n < n && next_m >= 0 && next_n >= 0 && maze[next_m][next_n] != 'F');
}

// 先對火進行BFS得到火到了時間
int main()
{
    int N = 0;
    cin >> N;
    while(N--)
    {
        pair<int, int> Joe;
        queue<pair<int, int>> q;
        cin >> m >> n; cin.ignore();
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                cin >> maze[i][j];
                if(maze[i][j] == 'J')
                {
                    Joe = {i, j};
                    maze[i][j] = '.';
                }
                else if(maze[i][j] == 'F')
                {
                    q.push({i, j});
                }
            }
        }
        // BFS on fire
        int fire_step = 0;
        while( !q.empty() )
        {
            int CNT = q.size();
            while(CNT--)
            {
                pair<int, int> pos = q.front();
                q.pop();
                for(int i = 0; i < 4; ++i) 
                {
                    int next_m = pos.first + dir[i][0], next_n = pos.second + dir[i][1];
                    // not visited
                    if(in_range(next_m, next_n) && (maze[next_m][next_n] == '.' || maze[next_m][next_n] > fire_step))
                    {

                    }
                }
            }
        }
    }
}