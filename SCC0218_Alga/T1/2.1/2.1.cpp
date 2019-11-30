#include <bits/stdc++.h>
using namespace std;

/** Função principal */
int main() {
    // numero de pessoas, numero de transacoes
    int n, m; scanf("%d%d", &n, &m);
    vector<double> saldo(n); // saldo de cada pessoa (negativo = pagou muito, positivo = esta devendo)

    // le todas as transacoes, atualizando o saldo por pessoa
    for (int i = 0; i < m; i++) {
        int a, b;
        double x;
        
        scanf("%d%d%lf", &a, &b, &x);
        saldo[a] -= x;
        saldo[b] += x;
    }

    vector<pair<double, int>> todoNeg; // transacoes que precisam ser feitas
    priority_queue<pair<double, int>> pq; // pessoas que podem pagar

    // percorre todos as pessoas, atualizando quem pode pagar ou quem deve
    for (int i = 0; i < n; i++) {
        if (saldo[i] == 0) continue;
        if (saldo[i]  < 0) todoNeg.emplace_back(-saldo[i], i);
        if (saldo[i]  > 0) pq.emplace(saldo[i], i);
    }

    // algoritmo guloso: ordena em ordem decrescente
    // quem pode pagar mais paga quem tem o maior saldo absoluto
    // (entre as pessoas que devem)

    sort(todoNeg.rbegin(), todoNeg.rend());
    vector<pair<pair<int, int>, double>> ans;

    // percorre todos os negativados
    for (int i = 0; i < (int)todoNeg.size(); i++) {
        auto p = todoNeg[i];
        if (pq.size() && pq.top().first >= p.first) {
            ans.push_back(make_pair(make_pair(pq.top().second, todoNeg[i].second), p.first));
            pair<double, int> topo = pq.top();
            topo.first -= p.first;

            pq.pop();
            if (topo.first + 1e-9 > 0) pq.emplace(topo);
        } else if (pq.size()) {
            ans.push_back(make_pair(make_pair(pq.top().second, todoNeg[i].second), pq.top().first));
            todoNeg[i].first -= pq.top().first; // diminui o tanto que pagou agora

            pq.pop();
            i--; // continua no cara atual       
        } else {
            printf("Não há como equalizar...\n");
            return 0;
        }
    }

    // caso tenham transações
    if (ans.size()) {
        for (auto& p : ans) {
            printf("%d %d %.1lf\n", p.first.first, p.first.second, p.second);
        }
    } else {
        printf("Nao ha transações a serem feitas\n");
    }

    
}