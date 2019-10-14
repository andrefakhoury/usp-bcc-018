#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 100, MAXM = 1 << 13;
const double INF = 1e10;

struct Pacote {
	int inicio, duracao;
	double custo;

	Pacote() {}
	Pacote(int inicio, int duracao, double custo) {
		this->inicio = inicio;
		this->duracao = duracao;
		this->custo = custo;
	}

	bool operator<(Pacote& p) const {
		return tie(inicio, duracao, custo) <
			   tie(p.inicio, p.duracao, p.custo);
	}
};

double memo[MAXN][MAXM];

double solve(int i, int meses, vector<Pacote>& pacotes, int& n, int& m) {
	if (i >= m) {
		int final = (1 << n) - 1;
		if ((meses & final) == final) return 0;
		else return INF;
	}

	double& ret = memo[i][meses];
	if (ret >= 0) return ret;

	// Nao pega
	ret = solve(i+1, meses, pacotes, n, m);

	// Pega
	for (int j = pacotes[i].inicio, cnt = 0; cnt < pacotes[i].duracao; cnt++, j++)
		meses |= 1 << j;

	int next = lower_bound(pacotes.begin(), pacotes.end(), Pacote(pacotes[i].inicio + pacotes[i].duracao, 0, 0.0)) - pacotes.begin();
	ret = min(ret, pacotes[i].custo + solve(next, meses, pacotes, n, m));

	return ret;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int n, m; cin >> n >> m;
	vector<Pacote> pacotes(m);

	for (Pacote& pacote : pacotes) {
		cin >> pacote.inicio;
		cin >> pacote.duracao;
		cin >> pacote.custo;
	}

	for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXM; j++)
		memo[i][j] = -1;

	sort(pacotes.begin(), pacotes.end());

	cout << solve(0, 0, pacotes, n, m) << endl;	

	return 0;
}