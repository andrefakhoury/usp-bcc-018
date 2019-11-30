#include <bits/stdc++.h>
using namespace std;

// maximum possible value of n
const int MAXN = 1e3;

// memoization table
long long memo[MAXN];

/** recursive dp function */
long long solve(int n, vector<int>& steps) {
	// basic return states
	if (n <= 0) return 0;
	if (n == 1) return 1;

	// value already calculated
	if (memo[n] != -1) return memo[n];

	// test all steps
	long long ret = 0;
	for (int x : steps) {
		ret += solve(n-x, steps);
	}

	// memoize and return
	memo[n] = ret;
	return ret;
}

/** iterative version of the problem */
long long iterative(int n, vector<int>& steps) {
	// basic states
	memo[0] = 0, memo[1] = 1;

	// iterate each value
	for (int i = 2; i <= n; i++) {
		memo[i] = 0;

		// sum all steps
		for (int x : steps) {
			if (i - x >= 0) {
				memo[i] += memo[i-x];
			}
		}
	}

	// return nth dp value
	return memo[n];
}

/** This is the main function */
int main() {
	// set memo table to EMPTY states
	memset(memo, -1, sizeof memo);

	// read values
	int n, m; scanf("%d%d", &n, &m);
	vector<int> steps(m);

	for (int i = 0; i < m; i++) {
		scanf("%d", &steps[i]);
	}

	// print answer
	printf("%lld\n", solve(n, steps));
	// printf("%lld\n", iterative(n, steps));
}


/* test cases:
Test Case 1:
	input:
		13 2
		1 2
	output:
		233

Test Case 2:
	input: 
		13 5
		1 2 3 4 5
	output:
		1793

Test Case 3:
	input:
		2 1
		1
	output:
		1
*/