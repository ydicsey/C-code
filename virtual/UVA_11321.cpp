#include <iostream>
#include <algorithm>
using namespace std;

class Compare
{
public:
    void SetDivisor(int d) { divisor_ = d; }
    // TODO: operator ()
    bool operator()(int lhs, int rhs) const;
private:
    int divisor_ = 1;
};
// ------------------------------------------------------------------
bool Compare::operator()(int lhs, int rhs) const
{
    // TODO
    int l = (lhs % divisor_);
    int r = (rhs % divisor_);
    // 若餘數相同
    if(l == r)
    {
        int ll = (((lhs % 2)+2)%2), rr = (((rhs % 2)+2)%2);
        if(ll || rr)
        {
            if(ll)
            {
                // lhs => 奇數
                if(rr)
                {
                    // lhs => 奇數, rhs => 奇數
                    // 都是奇數 => 大奇數 < 小奇數
                    return (rhs < lhs);
                }
                else 
                {
                    // lhs => 奇數, rhs => 偶數
                    // 奇數 < 偶數
                    return true;
                }
            }
            else
            {
                // lhs => 偶數
                if(rr)
                {
                    // lhs => 偶數, rhs => 奇數
                    // 偶數 < 奇數
                    return false;
                }
            }
        }
        else
        {
            // 都是偶數
            return (lhs < rhs);
        }
    }
    return (l < r);
}
// ------------------------------------------------------------------
int main()
{
    constexpr size_t MaxDataSize = 10000;
    int M=0, N=0, data[MaxDataSize]={};
    while (cin >> N >> M)
    {
        cout << N << ' ' << M << endl;
        if (N==0 && M==0) break;

        Compare comp;
        comp.SetDivisor(M);

        for (int i=0; i<N; i+=1)
        {
            cin >> data[i];
        }
        sort(data, data+N, comp);
        for (int i=0; i<N; i+=1)
        {
            cout << data[i] << endl;
        }
    }

}

/*
15 3
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
0 0
*/
