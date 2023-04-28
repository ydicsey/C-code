#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    while(n--)
    {
        int m;
        int cnt = 0;
        cin >> m;
        int * arr = (int*)malloc(sizeof(int) * m);
        for(int i = 0; i < m; ++i)
        {
            cin >> arr[i];
        }
        while(m--)
        {
            for(int i = 0; i < m; ++i)
            {
                if(arr[i+1] < arr[i])
                {
                    int tmp = arr[i+1];
                    arr[i+1] = arr[i];
                    arr[i] = tmp;
                    cnt++;
                }
            }
        }
        cout << "Optimal train swapping takes "<< cnt << " swaps."<<  endl;
    }
    return 0;
}