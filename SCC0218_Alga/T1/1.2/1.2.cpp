#include <bits/stdc++.h>
using namespace std;

const int N = 100;

/** Retorna a string mais curta que contenha todas as substrings, geradas na ordem do vetor */
string getString(vector<string>& vec) {
	string s; // string gerada

	// percorre todas as strings, e vai concatenando na string principal
	for (string& t : vec) {
		string x = t + "#" + s;
		int n = x.size();

		// gera prefix function
		vector<int> pi(n);
		for (int i = 1; i < n; i++) {
			pi[i] = pi[i-1];
			while(pi[i] > 0 && x[pi[i]] != x[i])
				pi[i] = pi[pi[i]-1];
			if (x[i] == x[pi[i]]) pi[i]++;
		}

		// t é substring de s
		if (*max_element(pi.begin(), pi.end()) == (int)t.size())
			continue;

		// merge da quantidade necessária
		int merge = pi.back(); // quantidade do merge é o último valor da prefix function
		s += t.substr(merge, t.size());
	}

	return s;
}

/** Função principal */
int main() {
	int n; // numero de strings
	scanf("%d", &n);

	char aux[N];

	// vetor de strings
	vector<string> vec;

	for (int i = 0; i < n; i++) {
		scanf(" %s", aux);
		vec.push_back(string(aux));
	}

	sort(vec.begin(), vec.end());

	// gera uma possível resposta
	string ans = getString(vec);

	// testa todas as permutações, pegando a menor string
	while(next_permutation(vec.begin(), vec.end())) {
		string cur = getString(vec);
		if ((ans.size() == cur.size() && cur < ans) || ans.size() > cur.size()) {
			ans = cur;
		}
	}

	// imprime a resposta
	printf("%s\n", ans.c_str());
}