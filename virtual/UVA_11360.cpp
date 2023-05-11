#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N = 0, Case = 1;
    cin >> N;
    while(N--)
    {
        int row;
        cin >> row;
        vector<string> mat(row);
        for(int i = 0; i < row; ++i)
        {
            cin >> mat[i];
        }
        int q = 0;
        cin >> q;
        while(q--)
        {
            vector<string>trans(row);
            string move;
            cin >> move;
            if(move[0] == 'r')
            {
                int a, b;
                cin >> a >> b;
                swap(mat[a-1], mat[b-1]);
            }
            else if(move[0] == 'c')
            {
                int a, b;
                cin >> a >> b;
                for(int i = 0; i < row; ++i)
                {
                    swap(mat[i][a-1], mat[i][b-1]);
                }
            }
            else if(move[0] == 'i')
            {
                for(int i = 0; i < row; ++i)
                {
                    for(int j = 0; j < row; ++j)
                    {
                        int tmp = mat[i][j] - '0';
                        tmp += 1;
                        tmp %= 10;
                        mat[i][j] = tmp + '0';
                    }
                }
            }
            else if(move[0] == 'd')
            {
                for(int i = 0; i < row; ++i)
                {
                    for(int j = 0; j < row; ++j)
                    {
                        int tmp = mat[i][j] - '0';
                        tmp -= 1;
                        tmp %= 10;
                        tmp += 10;
                        tmp %= 10;
                        mat[i][j] = tmp + '0';
                    }
                }
            }
            else if(move[0] == 't')
            {
                for(int i = 0; i < row; ++i)
                {
                    for(int j = 0; j < row; ++j)
                    {
                        trans[j] += mat[i][j];
                    }
                }
                mat = trans;
            }
        }
        cout << "Case #" << Case++ << endl;
        for(int i = 0; i < row; ++i)
        {
            cout << mat[i] << endl;
        }
        cout << endl;
    }
}