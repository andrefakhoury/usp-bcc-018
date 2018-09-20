#include "stdall.h"

int* geraVetor(int tam, int min, int max) {
	if (tam < 1 || min >= max) return NULL;

	int* vet = (int*)malloc(tam * sizeof(int));
	if (vet == NULL) return NULL;

	for (int i = 0; i < tam; i++)
		vet[i] = rand()%(max-min+1)+min;
	return vet;
}

int imprimeVetor(int* v, int tam) {
	for (int i = 0; i < tam; i++)
		printf("%d ", v[i]);
	printf("\n");
}

/*	Melhor:	M(1)
	Pior:	O(N) - Tempo Linear
	Recorrencia:
		Equacao: Fn = c + F(n-1)
		Fechada: Fn = cN */
int buscaSequencial(int* v, int tam, int chave) {
	for (int i = 0; i < tam; i++)
		if (v[i] == chave) return i;
	return FAIL;
}
int buscaSequencialRec(int* v, int tam, int at, int chave) {
	if (at >= tam) return FAIL;
	if (v[at] == chave) return at;
	return buscaSequencialRec(v, tam, at+1, chave);
}

/*	Melhor: M(1)
	Pior:	O(logN)
	Recorrencia:
		Equacao: Fn = c + F(n/2)
					Fn = k*c + c
					n/(2^k) = 1
					k = logN
		Fechada: Fn = c*logN + c */
int buscaBinaria(int* v, int tam, int chave) {
	int l = 0, r = tam, mid;
	while(l < r) {
		mid = (l+r)/2;
		if (v[mid] == chave) return mid;
		else if (v[mid] < chave) l = mid+1;
		else if (v[mid] > chave) r = mid-1;
	}
	return FAIL;
}
int buscaBinariaRec(int* v, int l, int r, int chave) {
	int mid = (l+r)/2;

	if (l > r) return FAIL;
	if (v[mid] == chave) return mid;
	if (v[mid] < chave)  return buscaBinariaRec(v, mid+1, r, chave);
	if (v[mid] > chave)  return buscaBinariaRec(v, l, mid-1, chave);
}


/*	Comparacoes e movimentacoes/trocas
	Melhor: O(N)
	Pior: 	O(N^2) */
void insertionSort(int* v, int n) {
	int i = 1;
	while(i < n) {
		int chave = v[i];

		int j = i-1;
		while(j >= 0 && chave < v[j]) {
			v[j+1] = v[j];
			j--;
		}

		v[j+1] = chave;
		i++;	
	}
	//algoritmo in place: Nao usa memoria externa
	//algoritmo estavel: sei la o q significa, acho q nao troca a ordem de tipo tem 2 numeros iguais e tals
}

//selectionSort: procura o maior e troca com o ultimo; procura o 2o maior e joga em penultimo; etc

/*	Pior: O(N logN)
	*Dividir e conquistar
	*Intercalacao
	Equacao:
		Fn = N + F(n/2)
		Fn = N + N/2 + F(N/4)
		F1 = 1

		Fk = N/(2^k)
*/
void mergeSort(int* v, int l, int r) {
	if (r <= l) return;
	int mid = (l+r)/2;

	mergeSort(v, l, mid);
	mergeSort(v, mid+1, r);

	int i = l, j = mid+1, k = 0;
	int* aux = malloc((r-l+1)*sizeof(int));

	while (i <= mid && j <= r) {
		if (v[i] < v[j]) aux[k++] = v[i++];
		else aux[k++] = v[j++];
	}

	while (i <= mid) aux[k++] = v[i++];
	while (j <= r) aux[k++] = v[j++];

	for (int i = l; i <= r; i++) v[i] = aux[i-l];

	free(aux);
}

/*
	Melhor: N logN
	Pior: N**2

	Pior quando ja ta ordenado e pega o pivo inicial
	Ou quando as mesmas chaves se repetem varias vezes
	Nao eh estavel
*/
void quickSort(int* v, int l, int r, int (*eep)(int, int)) {
	if (l >= r) return;

	int p = eep(l, r);

	int tmp = v[p];
	v[p] = v[l];
	v[l] = tmp;
	p = l;

	int i = l+1; //percorre lista 1 - procura <=
	int j = r; //percorre lista 2 - procura >

	while (i < j) {	
		while (i < r && v[i] <= v[p]) i++;
		while (v[j] > v[p]) j--;

		if (j > i) {
			tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
		}
	}

	p = j;
	tmp = v[p];
	v[p] = v[l];
	v[l] = tmp;

	//3: chamadas recursivas
	quickSort(v, l, p-1, eep);
	quickSort(v, p+1, r, eep);
}