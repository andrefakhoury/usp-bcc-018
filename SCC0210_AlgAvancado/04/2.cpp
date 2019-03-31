#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

#define mp make_pair

string final = "12345678x";

int h(string& s) {
	int ans = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		ans += final[i] != s[i];
	}
	return ans;
}

int find(string& s) {
	for (int i = 0; i < (int)s.size(); i++) if (s[i] == 'x') return i;
	return 0;
}

string up(string& s, int id) {
	string r = s;
	if (id < 4) return r;
	swap(r[id], r[id-3]);
	return r;
}

00010203
04050607

string down(string& s, int id) {
	string r = s;
	if (id > 15) return r;
	swap(r[id], r[id+3]);
	return r;
}

string left(string& s, int id) {
	string r = s;
	if (id == 0 or id == 3 or id == 6) return r;
	swap(r[id], r[id-1]);
	return r;
}

string right(string& s, int id) {
	string r = s;
	if (id == 2 or id == 5 or id == 8) return r;
	swap(r[id], r[id+1]);
	return r;
}

string bfs(string& s) {
	unordered_map<string, string> dist;
	priority_queue<pair<int, string> > pq;
	pq.push(make_pair(0, s));
	dist[s] = "";

	while(pq.size()) {
		string u = pq.top().second;
		if (u == final) return dist[u];
		pq.pop();
		int id = find(u);

		string v;
		v = up(u, id);
		if (v != u) {
			if (dist.find(v) == dist.end() or dist[u].size()+1 < dist[v].size()) {
				dist[v] = dist[u] + 'U';
				int w = dist[v].size() + h(v) + 1;
				pq.push(make_pair(-w, v));
			}
		}

		v = down(u, id);
		if (v != u) {
			if (dist.find(v) == dist.end() or dist[u].size()+1 < dist[v].size()) {
				dist[v] = dist[u] + 'D';
				int w = dist[v].size() + h(v) + 1;
				pq.push(make_pair(-w, v));
			}
		}

		v = left(u, id);
		if (v != u) {
			if (dist.find(v) == dist.end() or dist[u].size()+1 < dist[v].size()) {
				dist[v] = dist[u] + 'L';
				int w = dist[v].size() + h(v) + 1;
				pq.push(make_pair(-w, v));
			}
		}

		v = right(u, id);
		if (v != u) {
			if (dist.find(v) == dist.end() or dist[u].size()+1 < dist[v].size()) {
				dist[v] = dist[u] + 'R';
				int w = dist[v].size() + h(v) + 1;
				pq.push(make_pair(-w, v));
			}
		}
	}

	return "This puzzle is not solvable.";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

	int t; cin >> t;
	int count = 0;
	while(t--) {
		if (count != 0) cout << "\n";
		string s;
		for (int i = 0; i < 9; i++) {
			char c; cin >> c;
			s += c;
		}

		cout << bfs(s) << "\n";
		count++;
	}
}