#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
pair<int,int> operator+(const std::pair<int, int>& x, const std::pair<int, int>& y) 
{
    return make_pair(x.first+y.first, x.second+y.second);
}

int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    long long n;
    cin >> n; cin.ignore();

    // 紀錄機器人初始位置
    pair<int, int> loc(-1, -1);
    // 紀錄方位
    pair<int, int> dir[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int d = 0;

    // 創建二維vector儲存地圖
    // 邊邊是牆(obstacle)
    vector<vector<char>> grid(h+2);

    for (int i = 0; i < h+2; i++) {
        grid[i] = vector<char>(w+2);
        // 第一行跟最後一行為(obstacle)
        if (i == 0 || i == (h+1))
        {
            for(int j = 0; j < w+2; j++)
            {
                grid[i][j] = '#';
            }
            continue;
        }
        string line;
        getline(cin, line);
        // 處理grid與機器人的位置
        size_t found = line.find('O');
        if (found != string::npos)
        {
            line[found] = '.';
            loc = make_pair(i, found+1);
        }
        line.insert(0, 1, '#');
        line.push_back('#');

        vector<char> tmp(line.begin(), line.end());
        grid[i] = tmp;
    }

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    for (int i = 0; i < grid.size(); i++) 
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            cerr << grid[i][j] << " ";
        }    
        cerr << endl;
    }

    // cout << loc.first << loc.second << endl;

    // next step data
    pair<int, int> next;

    // chache to record history
    // tuple(x, y, dir), stepID
    map<tuple<int, int, int>, int> chache;
    for(long long stepID = 0; stepID < n; stepID ++)
    {
        tuple<int, int, int> tmp = {loc.first, loc.second, d};
        
        if(chache.find(tmp) != chache.end())
        {
            // 在紀錄裡面 => 重複走過並且方位一樣
            // 種類只有800種 => 200格 * 4種方位
            int cycle = stepID - chache[tmp];
            n = (n - stepID) % cycle;
            // long long int z = max(0LL,(n - stepID-1)/cycle);
            // stepID+=cycle*z;
        }
        else
        {
            chache[tmp] = stepID;
        }

        pair<int, int> next;
        for(int i = 0; i < 4; i++)
        {
            next = loc + dir[d];
            cerr << next.first << next.second << endl;
            if(grid[next.first][next.second] == '#')
            {
                d = (d+1) % 4;
            }
            else
            {
                loc = next;
                // cerr << i << d;
                break;
            }
        }
    }
    
    cout << loc.first << " " << loc.second << endl;
}