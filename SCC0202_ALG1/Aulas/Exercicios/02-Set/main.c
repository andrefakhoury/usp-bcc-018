#include "set.h"
#include <stdio.h>

int main() {
	Set *A, *B, *C;
	
	A = criarConjunto();
	B = criarConjunto();
	C = criarConjunto();

	inserir(10, A); inserir(20, A); inserir(20, A); inserir(30, A); remover(10, A);
	inserir(5, B); inserir(25, B); inserir(20, B); inserir(35, B); remover(3, B);

	diferenca(A, B, C);

	printf("%d %d %d\n", membro(20, B), Min(B), Max(B));

	printf("%d\n", igual(A, B));
	atribuir(A, B);
	printf("%d\n", igual(A, B));

	imprimir(A);
	imprimir(B);
	imprimir(C);

	liberar(A);
	liberar(B);
	liberar(C);

	return 0;
}