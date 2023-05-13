#include<bits/stdc++.h>
using namespace std;

int main()
{
	long long int m, n;
	vector<int> arr;
	while(cin >> n >> m)
	{
		if(m <= 1 || n < m)
		{
			cout << "Boring!" << endl;
			continue;
		}
        while(n%m == 0)
        {
            arr.emplace_back(n);
            n /= m;
        }
        arr.emplace_back(n);
        if(arr.back() != 1)
	}
}