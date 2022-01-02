/** CF - Registration system
 * https://codeforces.com/problemset/problem/4/C
 * Tag: STL
 * Ideia: utilização de um map de frequências */

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	map<string, int> f;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (f.count(s)) cout << s << f[s] << "\n";
		else cout << "OK\n";
		f[s]++;
	}
}