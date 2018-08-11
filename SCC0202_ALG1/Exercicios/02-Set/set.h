#include <stdbool.h>
typedef struct set Set;
Set* criarConjunto();
void uniao(Set* A, Set* B, Set* C);
void interseccao(Set* A, Set* B, Set* C);
void diferenca(Set* A, Set* B, Set* C);
bool membro(int X, Set* A);
void inserir(int X, Set* A);
void remover(int X, Set* A);
void atribuir(Set* dest, Set* orig);
int Min(Set* A);
int Max(Set* A);
bool igual(Set* A, Set* B);
void liberar(Set* A);
void imprimir(Set* A);