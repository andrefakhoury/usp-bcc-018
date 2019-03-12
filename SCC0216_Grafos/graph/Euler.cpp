#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

bool vis[MAXN];
vector<int> edges[MAXN];
int n, m;

void dfs(int u) {
	vis[u] = true;
	for (int v : edges[u]) {
		if (!vis[v]) dfs(v);
	}
}

bool isConex() {
	memset(vis, 0, sizeof vis);
	dfs(1);

	for (int i = 1; i <= n; i++) if (!vis[i]) return false;
	return true;
}

bool degree() {
	for (int i = 1; i <= n; i++)
		if (edges[i].size() % 2) return false;
	return true;
}

map<pair<int, int>, bool> used;

bool solve(int u, int initial) {
	for (int v : edges[u]) {
		if (!used[make_pair(u, v)]) {
			used[make_pair(u, v)] = true;
			if (solve())
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v; scanf("%d%d", &u, &v);
		edges[u].push_back(v);
	}

	if (!isConex() or !degree()) return !printf("Nope\n");
	memset(vis, 0, sizeof vis);


}