#include "bank.h"

Bank create_bank() {
	Bank b;
	for (int i=0; i < tamMax-1; i++)
	b.vet[i].next = i+1;

	b.vet[tamMax-1].next = -1;
	b.empty = 0;
	return b;    
}

void set_info(Bank *b, int pos, elem* x) {
	strcpy(b->vet[pos].info, x);
}

void set_next(Bank *b, int pos, int next) {
	b->vet[pos].next = next;
}

elem* get_info(Bank *b, int pos) {
	return b->vet[pos].info;
}

int get_next(Bank *b, int pos) {
	return b->vet[pos].next;
}

int get_node(Bank *b) {
	int p;
	if (b->empty == -1) return -1;
	p = b->empty; 
	b->empty = b->vet[b->empty].next;
	return p;
}

int isFull_bank(Bank *b) {
	return b->empty == -1;
}

void free_bank(Bank *b, int pos) {
	b->vet[pos].next = b->empty; 
	b->empty = pos;
}
