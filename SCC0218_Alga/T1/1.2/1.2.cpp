#include <bits/stdc++.h>
using namespace std;

const int N = 100;

string getString(vector<string>& vec) {
	string s;

	for (string& t : vec) {
		if (s.find(t) != string::npos) {
			continue;
		}

		int n = s.size();
		int m = t.size();
		int i;

		for (i = 0; i < n; i++) {
			bool can = true;

			int last = 0;
			for (int j = 0; i + j < n && j < m; j++) {
				can &= s[i + j] == t[j];
				last = i + j;
			}

			if (last == n - 1 && can) break;
		}

		for (int j = 0; j < m; j++, i++) {
			if (i < n) s[i] = t[j];
			else s.push_back(t[j]);
		}
	}

	return s;
}

int main() {
	int n;
	scanf("%d", &n);

	char aux[N];

	vector<string> vec;

	for (int i = 0; i < n; i++) {
		scanf(" %s", aux);
		vec.push_back(string(aux));
	}

	sort(vec.begin(), vec.end());

	string ans = getString(vec);

	while(next_permutation(vec.begin(), vec.end())) {
		string cur = getString(vec);
		if ((ans.size() == cur.size() && cur < ans) || ans.size() > cur.size()) {
			ans = cur;
		}
	}

	printf("%s\n", ans.c_str());
}