/** AtCoder - Build Stairs
 * https://atcoder.jp/contests/abc136/tasks/abc136_c
 * Tag: Greedy
 * Ideia: ir do final pro começo, SEMPRE tentar diminuir quando for maior. */

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];

	bool ans = true;
	for (int i = n - 2; ans && i >= 0; i--) {
		if (a[i] - 1 == a[i + 1]) a[i]--; // dá pra diminuir
		else if (a[i] > a[i + 1]) ans = false; // não dá
	}

	cout << (ans ? "Yes" : "No") << "\n";
}