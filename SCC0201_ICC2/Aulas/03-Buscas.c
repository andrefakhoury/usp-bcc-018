#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1

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
	return -1;
}
int buscaSequencialRec(int* v, int tam, int at, int chave) {
	if (at >= tam) return -1;
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
		Fechada: Fn = c logN + c */
int buscaBinaria(int* v, int tam, int chave) {
	int l = 0, r = tam, mid;
	while(l < r) {
		mid = (l+r)/2;
		if (v[mid] == chave) return mid;
		else if (v[mid] < chave) l = mid+1;
		else if (v[mid] > chave) r = mid-1;
	}
	return -1;
}
int buscaBinariaRec(int* v, int l, int r, int chave) {
	int mid = (l+r)/2;

	if (l > r) return -1;
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

int main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("Uso do programa: \n");
		printf("%s <tamanho> <minimo> <maximo>\n", argv[0]);
		return 1;
	}

	int N = atoi(argv[1]);
	int min = atoi(argv[2]);
	int max = atoi(argv[3]);

	int* vet = geraVetor(N, min, max);
	if (DEBUG) imprimeVetor(vet, N);

	//insertionSort(vet, N);
	mergeSort(v, 0, N-1);
	if (DEBUG) imprimeVetor(vet, N);
	

	int chave = min;
	printf(">Digite o valor para ser encontrado dentro do intervalo\n [%d, %d] ou fora do intervalo para sair\n", min, max);
	while (scanf("%d", &chave), chave >= min && chave <= max) {
		//int pos = buscaSequencialRec(vet, N, 0, chave);
		//int pos = buscaSequencial(vet, N, chave);
		//int pos = buscaBinaria(vet, N, chave);
		int pos = buscaBinariaRec(vet, 0, N, chave);

		if (pos == -1) printf("Chave nao encontrada\n\n");
		else printf("Chave encontrada na pos %d\n\n", pos);
	}


	return 0;
}
