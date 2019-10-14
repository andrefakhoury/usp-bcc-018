#include <bits/stdc++.h>
using namespace std;

const int N = 100;

int main() {
	int n; // numero de tarefas
	scanf("%d", &n);

	// todos os profits do i-esimo deadline
	vector<int> custo[N];

	for (int i = 1; i <= n; i++) {
		int deadline, profit;
		scanf("%d %d", &deadline, &profit);

		// adiciona uma tarefa no prazo estabelecido
		custo[deadline].push_back(profit);
	}

	long long ans = 0;

	// priority queue com as melhores tarefas
	priority_queue<int> pq;

	// percorre o tempo de tras para frente, adicionando todas as tarefas possiveis
	// ao percorrer de tras pra frente, garante-se que todas as tarefas na priority queue podem ser realizadas
	for (int i = N-1; i >= 1; i--) {
		// adiciona todas as tarefas que tem prazo ate t=i
		for (int& cur : custo[i]) {
			pq.push(cur);
		}

		// nenhuma tarefa a fazer
		if (pq.empty()) {
			continue;
		}

		// realiza a tarefa com maior profit
		ans += pq.top();
		pq.pop();
	}

	// imprime a resposta
	printf("%lld\n", ans);

	return 0;
}