#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

#define max(x, y) (x > y) ? x : y

struct set {
	bool* vet;
	int size;
};

Set* criarConjunto() {
	Set* s = malloc(sizeof(Set));
	s->vet = malloc(sizeof(bool));
	s->size = 1;
	return s;
}

void uniao(Set* A, Set* B, Set* C) {
	int qtd = max(A->size, B->size);
	
	C->vet = (bool*) realloc(C->vet, qtd * sizeof(bool));
	C->size = qtd;

	for (int i = 0; i < qtd; i++) {
		if (A->size > i) C->vet[i] |= A->vet[i];
		if (B->size > i) C->vet[i] |= B->vet[i];
	}
}

void interseccao(Set* A, Set* B, Set* C) {
	int qtd = max(A->size, B->size);
	
	C->vet = (bool*) realloc(C->vet, qtd * sizeof(bool));
	C->size = qtd;

	for (int i = 0; i < qtd; i++) {
		if (A->size > i && B->size > i) C->vet[i] = A->vet[i] && B->vet[i];
	}
}

void diferenca(Set* A, Set* B, Set* C) {
	int qtd = A->size;
	
	C->vet = (bool*) realloc(C->vet, qtd * sizeof(bool));
	C->size = qtd;

	for (int i = 0; i < qtd; i++) {
		if (B->size > i) C->vet[i] = B->vet[i] ? false : A->vet[i];
		else C->vet[i] = A->vet[i];
	}
}

bool membro(int X, Set* A) {
	if (X < A->size && A->vet[X])
		return true;
	return false;
}

void inserir(int X, Set* A) {
	A->size = max(A->size, X+1);
	A->vet = (bool*) realloc(A->vet, A->size * sizeof(bool));
	A->vet[X] = true;
}

void remover(int X, Set* A) {
	A->vet[X] = false;
}

void atribuir(Set* dest, Set* orig) {
	dest->size = orig->size;
	dest->vet = (bool*) realloc(dest->vet, orig->size * sizeof(bool));
	for (int i = 0; i < orig->size; i++)
		dest->vet[i] = orig->vet[i];
}

int Min(Set* A) {
	for (int i = 0; i < A->size; i++)
		if (A->vet[i]) return i;
	return 0x3f3f3f3f;
}

int Max(Set* A) {
	for (int i = A->size-1; i > -1; i--)
		if (A->vet[i]) return i;
	return -0x3f3f3f3f;
}

bool igual(Set* A, Set* B) {
	int qtd = max(A->size, B->size);
	for (int i = 0; i < qtd; i++) {
		if ((A->size <= i && B->vet[i]) || (B->size <= i && A->vet[i]) ||
			(A->vet[i] != B->vet[i]))
			return false;
	}

	return true;
}

void liberar(Set* A) {
	if (A->vet != NULL) free(A->vet);
	if (A != NULL) 		free(A);
}

void imprimir(Set* A) {
	for (int i = 0; i < A->size; i++)
		if (A->vet[i]) printf("%d ", i);
	printf("\n");
}