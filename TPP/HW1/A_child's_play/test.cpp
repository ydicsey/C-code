#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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
    vector<string> board(h);
    for (int i = 0; i < h; i++) {
        string line;
        getline(cin, board[i]);
    }
    int x=-1,y;
    for(int c=0;x==-1&&c<board.size();c++) {
        for(int c2=0;x==-1&&c2<board[c].size();c2++) {
            if(board[c][c2]=='O'){
                x = c;
                y = c2;
                break;
            }
        }
    }
    
    
    
    int d = 0;
    int dx[4]={-1,0,1,0};
    int dy[4]={0,1,0,-1};

    map<tuple<int,int,int>,int> m;
    

    
    for(long long int c=0;c<n;c++) {
        tuple<int,int,int> t = make_tuple(x,y,d);
        
        //cout<<c<<" "<<x<<" "<<y<<" "<<d<<endl;
        if(m.find(t)!=m.end()) {
            long long int lengthCycle = c-m[t];
            long long int z = max(0LL,(n - c-1)/lengthCycle);
            c+=lengthCycle*z;
        } else {
            m[t]=c;
        }
        //cout<<c<<" "<<x<<" "<<y<<" "<<d<<endl;
            
        while(1){
            int x2 = x + dx[d];
            int y2 = y + dy[d];
            if(board[x2][y2]=='#') {
                d++;
                d%=4;
            } else {
                
                x=x2;
                y=y2;
                break;
            }
        }
    }
    cout<<y<<" "<<x;
}