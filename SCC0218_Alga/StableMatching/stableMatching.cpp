#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);

		map<char, vector<char> > man;
		map<char, map<char, int> > wmn;

		map<char, char> wife, hsbn;
		map<char, int> cnt;
		set<char> singles;

		for (int i = 0; i < n; i++) {
			char c; scanf(" %c", &c);
			man[c] = vector<char>();
			wife[c] = 0;
			singles.insert(c);
		}

		for (int i = 0; i < n; i++) {
			char c; scanf(" %c", &c);
			wmn[c] = map<char, int>();
			hsbn[c] = 0;
			cnt[c] = 0;
		}

		for (int i = 0; i < n; i++) {
			char c, aux[30]; scanf(" %c:%s", &c, aux);
			for (int k = 0; k < n; k++) man[c].push_back(aux[k]);
		}

		for (int i = 0; i < n; i++) {
			char c, aux[30]; scanf(" %c:%s", &c, aux);
			for (int k = 0; k < n; k++) wmn[c][aux[k]] = k;
		}

		while(singles.size()) {
			char m = *singles.begin();
			singles.erase(m);

			if (cnt[m] == n) continue;

			char w = man[m][cnt[m]];
			cnt[m]++;

			if (hsbn[w] == 0) {
				wife[m] = w;
				hsbn[w] = m;
			} else {
				if (wmn[w][m] < wmn[w][hsbn[w]]) {
					singles.insert(hsbn[w]);

					wife[hsbn[w]] = 0;
					hsbn[w] = m;
					wife[m] = w;

				} else singles.insert(m);
			}
		}

		for (auto p : wife) printf("%c %c\n", p.first, p.second);
		if (t) printf("\n");
	}
}