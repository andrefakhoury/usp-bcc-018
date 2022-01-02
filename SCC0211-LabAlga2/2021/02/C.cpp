/** SPOJ - Lose it!
 * https://codeforces.com/contest/1176/problem/C
 * Tag: greedy, sequences
 * Ideia: primeiramente, vamos falar que S = {4, 8, 15, 16, 23, 42}. A ideia aqui vai ser
 *    pra cada S_i, considerar quantas subsequencias podem terminar nele. Por exemplo: S_0
 *    não depende de mais ninguém para formar as sequencias, então f(S_0) = frequencia(S_0).
 *    Porém, nem todos são assim: S_1 depende de S_0 para formar as sequencias. Assim, temos
 *    que, se andamos da esquerda pra direita, temos que considerar não apenas a resposta de
 *    f(S_1), mas também a resposta de f(S_0). O guloso é o seguinte: quando você está em um
 *    caractere 'i', da esquerda pra direita, você consegue encontrar a melhor resposta para
 *    ele. Isso já garante que a resposta dos caras depois dele também serão máximas, porque
 *    queremos simplesmente maximizar a quantidade de sequencias, utilizando todo mundo possí-
 *    vel. */

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr); // notion tem mais detalhes deste "fastcin"

	vector<int> mp(100); // em vez de ficar trabalhando com {4, 8, 16...}, é mais fácil {1, 2, ...}
	mp[4] = 1, mp[8] = 2, mp[15] = 3, mp[16] = 4, mp[23] = 5, mp[42] = 6;

	vector<int> ans(7);
	ans[0] = 1e9; // é possível montar "infinitas" sequencias com 0 caras (nesse caso)

	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		x = mp[x]; // mapeia o cara pra {1, 2, 3, 4, 5, 6}

		ans[x] = min(ans[x - 1], ans[x] + 1);
		// a resposta do cara atual é no máximo a delimitada pelo número anterior
	}

	// ans[6] armazena a quantidade de sequencias possíveis. O problema pede a quantidade de caracteres
	// que precisam ser eliminados - mas é fácil calcular:

	cout << n - 6 * ans[6] << '\n';
}
