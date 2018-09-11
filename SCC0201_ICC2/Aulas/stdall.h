#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1
#define FAIL -404

int* geraVetor(int tam, int min, int max);
int imprimeVetor(int* v, int tam);
/*	Pior:	O(N) */
int buscaSequencial(int* v, int tam, int chave);
int buscaSequencialRec(int* v, int tam, int at, int chave);
/*	Pior:	O(logN) */
int buscaBinaria(int* v, int tam, int chave);
int buscaBinariaRec(int* v, int l, int r, int chave);
/*	Pior: 	O(N^2) */
void insertionSort(int* v, int n);
/*	Pior: O(N logN) */
void mergeSort(int* v, int l, int r);