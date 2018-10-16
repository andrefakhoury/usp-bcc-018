#include <stdlib.h>
#include <string.h>
#include "agenda.h"

#define maxP 200

static int qtdeP = 0;

struct Pessoa {
	char nome[50], endereco[300];
};

struct Agenda {
	Pessoa pessoa[maxP];
};

int estaNaAgenda(Agenda a, char nome[50]) {
	for (int i = 0; i < maxP; i++)
		if (strcmp(a.pessoa[i].nome, nome) == 0) return i;
	return -1;
}

void insere(Agenda* a, char nome[50], char endereco[300]) {
	strcpy((*a).pessoa[qtdeP].nome, nome);
	strcpy((*a).pessoa[qtdeP].endereco, endereco);

	qtdeP++;
}

void tiraDaAgenda(Agenda* a, char nome[50]) {
	int pos = estaNaAgenda(*a, nome);
	if (pos == -1) return;

	Agenda b = *a;
	for (int i = pos; i < qtdeP-1; i++) {
		b.pessoa[i] = (*a).pessoa[i+1];
	}
	*a = b;
	qtdeP--;
}

char* buscaEndereco(Agenda a, char nome[50]) {
	char* ret = malloc(50 * sizeof(char));

	int pos = estaNaAgenda(a, nome);
	for (int i = 0; i < 50; i++) ret[i] = a.pessoa[pos].nome[i];

	return ret;
}