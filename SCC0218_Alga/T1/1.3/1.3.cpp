#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; // numero de trens
	scanf("%d", &n);

	set<int> times; // todos os tempos da entrada (em minutos)
	map<int, int> chegada, partida; // frequencia de chegada e partida de cada minuto

	// le todos os tempos de chegada
	for (int i = 0; i < n; i++) {
		int h, m; // hora e minuto
		scanf("%d:%d", &h, &m);

		int t = h * 60 + m; // converte para minutos

		times.insert(t); // inclui esse tempo no set de todos os tempos
		chegada[t]++; // aumenta a frequencia desse minuto
	}

	// le todos os tempos de partida
	for (int i = 0; i < n; i++) {
		int h, m; // hora e minuto
		scanf("%d:%d", &h, &m);

		int t = h * 60 + m; // converte para minutos

		times.insert(t); // inclui esse tempo no set de todos os tempos
		partida[t]++; // aumenta a frequencia desse minuto
	}

	int qtd = 0; // quantidade de trens ao mesmo tempo
	int ans = 0; // resposta do problema

	// percorre todos os tempos, simulando a entrada e saida dos trens
	for (int t : times) {
		qtd -= partida[t]; // decrementa a qtd de trens que sairam agora

		qtd += chegada[t]; // incrementa a qtd de trens que chegaram agora
		ans = max(ans, qtd);
	}

	// printa a resposta
	printf("%d\n", ans);

	return 0;
}