#include <stdlib.h>
#include "stack.h"
#define stSize 300

struct stack {
	stackType vet[stSize];
	int top;
};

Stack* stackCreate() {
	Stack* P = malloc(sizeof(Stack));
	P->top = -1;
	return P;
}

int stackPush(Stack* P, stackType X) {
	if (P->top == stSize-1) return 1;
	P->vet[++P->top] = X;
	return 0;
}

int stackPop(Stack* P, stackType* X) {
	if (P->top == -1) return 1;
	*X = P->vet[P->top--];
	return 0;
}

stackType stackTop(Stack* P) {
	Queue fail;
	if (P->top == -1) return fail;
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