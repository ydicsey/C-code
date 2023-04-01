#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();
    long long n;
    cin >> n; cin.ignore();
    // cerr << n << endl;
    
    vector<pair<int,int>> dir = {
        { 0, -1},
        { 1, 0},
        { 0, 1},
        {-1, 0}
    };
    
    vector<string> map(h);
    int x, y, d = 0, t = 1;
    for (int i = 0; i < h; i++) {
        getline(cin, map[i]);
        if(map[i].find('O') != string::npos) {
            y = i;
            x = map[i].find('O');
        }
        // cerr << map[i] << endl;
    }
    
    vector<vector<vector<int>>> history(4);
    for(int i = 0; i < 4; ++i) {
        history[i].resize(h);
        for(int j = 0; j < h; ++j) {
            history[i][j].resize(w, -1);
        }
    }
    
    for(long long z=0; z < n; ++z) {
        if(history[d][y][x] != -1 && (n - t + 1) % (t - history[d][y][x]) == 0) {
            cerr << "break\n";
            break;
        }
        history[d][y][x] = t++;
        for(;;) {
            int x1 = x + dir[d].first;
            int y1 = y + dir[d].second;
            if(map[y1][x1] == '#') {
                d = (d + 1) % 4;
                continue;
            }
            x = x1;
            y = y1;
            break;
        }
    }

    cout << x << " " << y << endl;
}