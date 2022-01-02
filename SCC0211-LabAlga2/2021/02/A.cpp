/** SPOJ - BUSYMAN
 * https://www.spoj.com/problems/BUSYMAN/ 
 * Tag: greedy, interval scheduling
 * Ideia: ordenar pelo TÉRMINO de cada evento
 *   'quanto antes você acabar um, mais cedo pode começar outro' */

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr); // notion tem mais detalhes deste "fastcin"

	int tc; cin >> tc;
	while(tc--) {
		int n; cin >> n;
		vector<pair<int, int>> a(n);
		for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
		sort(a.begin(), a.end(), [](pair<int, int> const& a, pair<int, int> const& b) {
			return a.second < b.second;
		});

		int ans = 0, last = 0;
		for (int i = 0; i < n; i++) if (a[i].first >= last) {
			last = a[i].second;
			ans++;
		}

		cout << ans << "\n";
	}
}