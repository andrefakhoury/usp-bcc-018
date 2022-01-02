/** CF - Restore the Permutation by Merger
 * https://codeforces.com/problemset/problem/1385/B
 * Tag: STL, greedy
 * Ideia: pegar apenas os caras que não apareceram antes */

#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; cin >> T;
	while(T--) { // mesma coisa que while(T-- > 0), repete o código T vezes
		int n; cin >> n;

		vector<bool> vis(n + 1); // vetor de visitados, pode ser um map/set também
		for (int i = 0; i < n + n; i++) {
			int x; cin >> x;
			if (!vis[x]) cout << x << " ";
			vis[x] = 1;
		}
		cout << "\n";
	}
}