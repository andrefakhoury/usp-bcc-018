#include <stdio.h>
#include "pilha.h"
#define tamMax 300

int main() {
	//notacao polonesa posfixa
	char exp[tamMax];
	Pilha* P = criaPilha();
	elem X, Y;

	printf("Digite uma expressao: ");
	scanf("%s", exp);

	int i;
	for (char c = exp[0], i = 0; exp[i] != 0; i++, c = exp[i]) {
		if (c != '/' && c != '*' && c != '+' && c != '-') push(P, c-'0');

		else {
			pop(P, &Y); pop(P, &X);
			if (c == '/') push(P, X/Y);
			else if (c == '*') push(P, X*Y);
			else if (c == '+') push(P, X+Y);
			else if (c == '-') push(P, X-Y);
		}
	}

	printf("Resultado: %d\n", top(P));

	return 0;
}