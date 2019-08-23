#include <bits/stdc++.h>
using namespace std;

string TSP(int cur, int mask, vector<string>& vec, int n) {
	mask |= 1 << cur;

	if (mask == 1 << n) {
		return vec[cur];
	}
}

int main() {
	int n; cin >> n;
	vector<string> vec(n);

	for (string& s : vec) cin >> s;

	vector<vector<pair<int, int> > > matching(n);

	for (int i = 0; i < n; i++) {

		string& s = vec[i];

		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			string& t = vec[j];

			int curMatch = 0;

			for (int ii = max(0, int(s.size() - t.size())); !curMatch && ii < s.size(); ii++) {
				bool ok = true;

				for (int jj = 0; ok && ii + jj < s.size() && jj < t.size(); jj++) {
					ok &= s[ii + jj] == t[jj];
				}

				if (ok) curMatch = s.size() - ii;
			}

			matching[i].push_back(make_pair(curMatch, j));
		}

		sort(matching[i].begin(), matching[i].end());
	}

	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (auto x : matching[i]) {
			cout << "(" << x.first << ", " << x.second << ") ";
		}
		cout << endl;
	}


}