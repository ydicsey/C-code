#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/ 
pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b )
{
    return make_pair(a.first + b.first, a.second + b.second);
}


int main()
{
    int width;
    int height;
    cin >> width >> height; cin.ignore();
    long long MAX_steps;
    cin >> MAX_steps; cin.ignore();
    // n = 20;

    const pair<int,int> moves[4] {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    // store init postion: (x, y)
    pair<int, int> pos(-1, -1);

    vector<string> map(height);
    for (int i = 0; i < height; i++) 
    {
        // string line;
        getline(cin, map[i]);
        for(int j = 0; j < width; j++)
        {
            if(map[i][j] == 'O' && pos.first == -1)
            {
                map[i][j] = '.';
                pos = make_pair(j ,i);
            }
        }
    }

    cerr << "init_pos: " << pos.second << pos.first << endl;

    // memoized position instead of simulating the robot's movements again.
    // init with -1, means not visied by this dir
    // like memo[h][w][4]
    vector<vector<vector<int>>> memo(height, vector<vector<int>>(width, vector<int>(4, -1)));
    // store next postion: (x, y)
    pair<int, int> next_pos(-1, -1);
    // init dirction is UP
    int dir = 0, t = 1;
    long long cycle_len = 0, step = 1;

    while(step <= MAX_steps)
    {
        cycle_len = step - memo[pos.second][pos.first][dir];
        if(memo[pos.second][pos.first][dir] != -1 && ((MAX_steps - step +1) % cycle_len) == 0)
        {
            cerr << cycle_len << "\n" << endl;
            break;
        }
        memo[pos.second][pos.first][dir] = step++;
        while(1)
        {
            next_pos = pos + moves[dir];
            if(map[next_pos.second][next_pos.first] == '#')
            {
                dir = (dir+1) % 4;
                continue;
            }
            pos = next_pos;
            break;
        }
        cout << pos.first << " " << pos.second << endl;
    }

    // cout << pos.first << " " << pos.second << endl;
    // cout << "answer" << endl;
}