#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

int main() {
	int n; scanf("%d", &n);

	char nome[20], status[20];
	int itens;

	Pessoa p;
	queue* q = queue_create();

	for (int i = 0; i < n; i++) {
		scanf(" %s %d%s", nome, &itens, status);
		strcpy(p.nome, nome);
		p.itens = itens;
		if (!strcmp(status, "idoso") || !strcmp(status, "gestante") || !strcmp(status, "cadeirante"))
			p.preferencial = true;
		else p.preferencial = false;
		queue_insert(q, p);
	}

	int caixa;
	while(!queue_isEmpty(q)) {
		queue_remove(q, &p);

		if (p.preferencial) caixa = 1;
		else if (p.itens <= 5) caixa = 4;
		else if (p.itens <= 10) caixa = 3;
		else caixa = 2;

		printf("%s, %d itens, %s: caixa %d\n", p.nome, p.itens, p.preferencial ? "preferencial" : "normal", caixa);
	}

	return 0;
}