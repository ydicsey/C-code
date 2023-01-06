// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;
// https://www.geeksforgeeks.org/count-of-subsets-with-sum-equal-to-x/

#define maxN 20
#define maxSum 50
#define minSum 50
#define base 50

// To store the states of DP
int dp[maxN][maxSum + minSum];
bool v[maxN][maxSum + minSum];

// Function to return the required count
int findCnt(int* arr, int i, int required_sum, int n)
{
	// Base case
	if (i == n) {
		if (required_sum == 0)
			return 1;
		else
			return 0;
	}

	// If the state has been solved before
	// return the value of the state
	if (v[i][required_sum + base])
		return dp[i][required_sum + base];

	// Setting the state as solved
	v[i][required_sum + base] = 1;

	// Recurrence relation
	dp[i][required_sum + base]
		= findCnt(arr, i + 1, required_sum, n)
		+ findCnt(arr, i + 1, required_sum - arr[i], n);
	return dp[i][required_sum + base];
}

// Driver code
int main()
{
	int arr[] = {-7494, -25474, 3688, -24702, 12960, 29556, -11219, 30162, -18870, -20459, 30950, -25456, 1992, -8622, -23842, -18825, -31862, -2364, 29730, -32718, -4409, -23123, 29983, 2280, 26854, -18284, -2668, 302064, 9840};
	int n = sizeof(arr) / sizeof(int);
	int x = 14139;

	cout << findCnt(arr, 0, x, n);

	return 0;
}