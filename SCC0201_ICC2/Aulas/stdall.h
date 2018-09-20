#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1
#define FAIL -404

int* geraVetor(int, int, int);
int imprimeVetor(int*, int);
/*	Pior:	O(N) */
int buscaSequencial(int*, int, int);
int buscaSequencialRec(int*, int, int, int);
/*	Pior:	O(logN) */
int buscaBinaria(int*, int, int);
int buscaBinariaRec(int*, int, int, int);
/*	Pior: 	O(N^2) */
void insertionSort(int*, int);
/*	Pior:	O(N logN) */
void mergeSort(int*, int, int);
/*	Pior:	O() */
void quickSort(int*, int, int, int (*)(int, int));