#include <stdio.h>
#include <string.h>
#include "list.h"

int menu() {
	int op;
	printf("\n1-Pesquisar por nome\n2-Pesquisar por cerimonia\n3-Listar todos\n0-Sair\n::");
	scanf("%d", &op);
	return op;
}

int main() {
	int n;
	scanf("%d", &n);

	list* l = list_create();
	Convidado c;

	for (int i = 0; i < n; i++) {
		printf("\nDigite nome: ");
		scanf(" %s", c.nome);
		int flag;

		printf("Convidado pra recepcao? 0 se nao, 1 se sim: ");
		scanf("%d", &flag);
		c.evento[RECEPCAO] = (bool)flag;

		printf("Convidado pra cerimonia? 0 se nao, 1 se sim: ");
		scanf("%d", &flag);
		c.evento[CERIMONIA] = (bool)flag;

		printf("Convidado pra banquete? 0 se nao, 1 se sim: ");
		scanf("%d", &flag);
		c.evento[BANQUETE] = (bool)flag;

		list_insert(l, c);
	}

	int op, op2;
	char nome[20];

	while(op = menu()) {
		if (op == 1) {
			printf("\nDigite o nome que quer pesquisar: ");
			scanf("%s", nome);
			list_print_byName(l, nome);
		} else if (op == 2) {
			printf("01: Recepcao\n02-Cerimonia\n03-Banquete\n::");
			scanf("%d", &op2);
			if (op < 1 || op > 3) {
				printf("Evento invalido\n");
				continue;
			}
			list_print_byOption(l, op2-1);
		} else if (op == 3) {
			list_print_names(l);
		}
	}

	list_destroy(l);
	return 0;
}