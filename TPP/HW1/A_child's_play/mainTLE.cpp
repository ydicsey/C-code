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
pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b )
{
    return make_pair(a.first + b.first, a.second + b.second);
}


int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    long long n;
    cin >> n; cin.ignore();
    // n = 20;

    // init dirction is UP
    int dir = 0;
    const pair<int,int> moves[4] {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    // store init postion: (x, y)
    pair<int, int> pos(-1, -1);
    // use vector store obstacle
    vector<pair<int, int>> obstacles;

    for (int i = 0; i < h; i++) {
        string line;
        getline(cin, line);
        for(int j = 0; j < w; j++)
        {
            if(line[j] == '#')
            {
                obstacles.push_back(make_pair(j ,i));
            }
            else if(line[j] == 'O' && pos.first == -1)
            {
                pos = make_pair(j ,i);
            }
        }
    }

    cerr << "init_pos: " << pos.second << pos.first << " " <<dir << endl;

    // memoized position instead of simulating the robot's movements again.
    map<tuple<int, int, int>, int> memo;
    // store next postion: (x, y)
    pair<int, int> next_pos(-1, -1);
    int repeat = 0;

    for(int step = 0; step < n; step++)
    {
        tuple<int, int, int> tmp = {pos.first, pos.second, dir};
        if(memo.end() != memo.find(tmp) || repeat)
        {
            // this x,y and dir are matched
            repeat = 1;
            long long cycle_len = step - memo[tmp];
            long long mut = (n - step -1) / cycle_len;
            step += mut > 0? cycle_len * mut : 0LL;
        }
        else
        {
            memo[tmp] = step;
        }

        // 會遇到四周都是#進而無限迴圈
        // 好像不會遇到這種狀況
        for(next_pos = pos + moves[dir]; find(obstacles.begin(), obstacles.end(), next_pos) != obstacles.end(); dir = (dir+1) % 4, next_pos = pos + moves[dir]);

        pos = next_pos;
        // cout << pos.second << pos.first << endl;
    }

    cout << pos.first << " " << pos.second << endl;
    // cout << "answer" << endl;
}