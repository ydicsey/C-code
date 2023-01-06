#include <stdio.h> 
#include <unordered_map>
#include <algorithm>

/*  
直接聯想到把數據切成兩半的做法。
這題的類題不勝枚舉，把集合拆成兩半，每半部的集合都枚舉所有 2^N/2 種subset
枚舉其中一半部時 hash 每個總合的值出現多少次，而枚舉另外一半部時
就可以根據 hash 值得知他有多少種和前一半部的組合加總可以湊成 T    
*/

using namespace std;

unordered_map<long long, int> dp;
int n, i;
long long m, A[45], sum[1<<20];

int main() {
	scanf("%d %lld", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &A[i]);
    }

	long long ans = 0;
	int list1 = n/2, list2 = n - n/2;
	
	dp.clear();
	
	for (int i = 0; i < list1; i++)
	{
		sum[1<<i] = A[i];
	}
	for (int i = 0; i < (1<<list1); i++) 
	{
		sum[i] = sum[i - ((i-1)&i)] + sum[(i-1)&i];
		long long x = sum[i];
		dp[x]++;
	}
	for (int i = 0; i < list2; i++)
		sum[1<<i] = A[i + list1];
	for (int i = 0; i < (1<<list2); i++) {
		sum[i] = sum[i - ((i-1)&i)] + sum[(i-1)&i];
		long long x = sum[i];
		if (dp.count(m - x))
		{
			ans += dp[m - x];
		}
	}
	if (m == 0)		
    {
        ans--;
    }
	printf("%lld\n", ans);
	return 0;
}
