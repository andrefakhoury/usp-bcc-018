/**
 *	Dado M pacotes de software (cada um com seu custo, mês inicial e duração), 
 *  imprime a melhor solução de escolha, de modo que consiga sofwares necessários
 *  por N meses. Assume que não se podem repetir os pacotes utilizados.
 */

#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 100, MAXM = 1 << 13;
const double INF = 1e10;

/** Estrutura de um pacote de software */
struct Pacote {
	int inicio, duracao;
	double custo;

	/** Construtores */
	Pacote() {}
	Pacote(int inicio, int duracao, double custo) {
		this->inicio = inicio;
		this->duracao = duracao;
		this->custo = custo;
	}

	/** Comparador de menor utilizado na ordenação */
	bool operator<(Pacote const& p) const {
		return tie(inicio, duracao, custo) <
			   tie(p.inicio, p.duracao, p.custo);
	}
};

/** Array de memoização */
double memo[MAXN][MAXM];

/** Função recursiva que resolve o problema */
double solve(int i, int meses, vector<Pacote>& pacotes, int& n, int& m) {
	if (i >= m) { // acabaram os pacotes disponíveis
		int final = (1 << n) - 1;
		if ((meses & final) == final) return 0;
		else return INF;
	}

	// verifica estado visitado
	double& ret = memo[i][meses];
	if (ret >= 0) return ret;

	// não pega o pacote atual
	ret = solve(i+1, meses, pacotes, n, m);

	// pega o pacote atual
	for (int j = pacotes[i].inicio, cnt = 0; cnt < pacotes[i].duracao; cnt++, j++)
		meses |= 1 << j;

	// vai para o próximo pacote disponível
	int next = lower_bound(pacotes.begin(), pacotes.end(), Pacote(pacotes[i].inicio + pacotes[i].duracao, 0, 0.0)) - pacotes.begin();
	ret = min(ret, pacotes[i].custo + solve(next, meses, pacotes, n, m));

	// retorna a melhor solução
	return ret;
}

/** Função principal */
int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	// lê as variáveis de entrada
	int n, m; cin >> n >> m;
	vector<Pacote> pacotes(m);

	for (Pacote& pacote : pacotes) {
		cin >> pacote.inicio;
		cin >> pacote.duracao;
		cin >> pacote.custo;
	}

	// seta os estados da PD para -1
	memset(memo, -1, sizeof memo);

	// ordena os pacotes
	sort(pacotes.begin(), pacotes.end());

	// imprime a solução final
	cout << setprecision(1) << fixed << solve(0, 0, pacotes, n, m) << endl;	

	return 0;
}