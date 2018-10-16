#include <stdlib.h>
#include "stack.h"
#define stSize 300

struct stack {
	type vet[stSize];
	int top;
};

Stack* stackCreate() {
	Stack* P = malloc(sizeof(Stack));
	P->top = -1;
	return P;
}

int stackPush(Stack* P, type X) {
	if (P->top == stSize-1) return 1;
	P->vet[++P->top] = X;
	return 0;
}

int stackPop(Stack* P, type* X) {
	if (P->top == -1) return 1;
	*X = P->vet[P->top--];
	return 0;
}

type stackTop(Stack* P) {
	if (P->top == -1) return -1;
	return P->vet[P->top];
}

int stackIsEmpty(Stack* P) {
	return P->top == -1;
}

void stackEmpty(Stack* P) {
	P->top = -1;
}

int stackSize(Stack* P) {
	return P->top+1;
}

int stackCompare(Stack* P, Stack* Q) {
	if (P->top != Q->top) return 0;
	for (int i = 0; i <= P->top; i++) if (Q->vet[i] != P->vet[i]) return 0;
	return 1;
}