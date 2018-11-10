#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FREE -1
#define DEL -2

/*====================================================
|| Algoritmo	| Operacoes	| Estavel	| Memoria	||
------------------------------------------------------
|| MergeSort	| O(n lg N)	| SIM		| O(n)		||
------------------------------------------------------
|| QuickSort	| O(n log N)| NAO		| O(1)		||
------------------------------------------------------
|| HeapSort		| O(n lg N) | NAO		| O(1)		||
======================================================
|| Counting		| O(n)		| SIM		| O(k)		||
------------------------------------------------------
|| Bucket		| O(n) 		| SIM		| O(n+k)	||
------------------------------------------------------
|| Radix		| O(n) 		| SIM		| O(alpha)	||
====================================================*/

int hash_division(int key, int m, int k) {
	return (key+(k*k)) % m; //sondagem quadratica
}

int hash_multi(int key, double A, int m, int k) { 
	double val = (key+(k*k))*A; //sondagem quadratica
	val = val - ((int)val);
	return (int)(val*m);
}

int insert(int* t, int key, int m) {
	if (key < 0) return -1;

	double A = (sqrt(5)-1)/2.0;
	int pos, k = -1;

	do pos = hash_multi(key, A, m, ++k);
	while (t[pos] != FREE && t[pos] != DEL);

	t[pos] = key;
}

int search(int *t, int key, int m) {
	if (key < 0) return -1;

	double A = (sqrt(5)-1)/2.0;
	int pos, k = -1;

	do	pos = hash_multi(key, A, m, ++k);
	while (k < m && t[pos] != FREE && t[pos] != key);

	if (t[pos] == key) return pos;
	else return FREE;
}


int delete(int *t, int key, int m) {
	int pos = search(t, key, m);
	if (pos < 0) return pos;
	t[pos] = DEL;
}

int* create_hash_table(int m) {
	int* t = malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) t[i] = FREE;
	return t;
}