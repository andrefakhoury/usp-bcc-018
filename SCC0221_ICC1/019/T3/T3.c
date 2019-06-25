#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXSTR 50
#define NUMVIZINHOS 4

/** Estrutura de uma imagem */
typedef struct {
	int** mat; // matriz da foto
	int m, n;	// nro de linhas e colunas
} Imagem;

int ordem[NUMVIZINHOS][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // ordem de visita

/** Aloca uma matriz na heap */ 
int** alocaMatriz(int n, int m) {
	int** mat = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		mat[i] = calloc(m, sizeof(int));
	}
	return mat;
}

/** Libera a memoria utilizada pela matriz na heap */
void liberaMatriz(int** mat, int n) {
	for (int i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);
}

/** Le a imagem em fp e retorna o vetor de int correspondente */
Imagem leImagem(FILE* fp) {
	fscanf(fp, "%*s"); // ignora o P2

	Imagem im;
	fscanf(fp, "%d%d", &im.n, &im.m);

	fscanf(fp, "%*d"); // ignora o valor inteiro

	// malloca a qtd necessaria de pixel
	im.mat = alocaMatriz(im.m, im.n);

	// le os pixels da imagem
	for (int i = 0; i < im.m; i++) {
		for (int j = 0; j < im.n; j++) {
			fscanf(fp, "%d", &im.mat[i][j]);
		}
	}

	return im;
}

/** Retorna se uma posicao (i, j) eh valida */
bool posicaoValida(int i, int j, Imagem im) {
	return i >= 0 && j >= 0 && i < im.m && j < im.n;
}

/** Faz o flood fill na matriz de imagem */
void dfs(int i, int j, int* curSum, int* curQtt, Imagem im, int C, int numVisita, int** vis) {
	if (!posicaoValida(i, j, im)) { 
		return; // out of bounds
	}

	if (vis[i][j] != 0) {
		return; // ja visitado
	}

	// soma pra media
	*curSum += im.mat[i][j];
	*curQtt += 1;

	// marca a hora de visitado
	vis[i][j] = numVisita;

	// visita todos os vizinhos, na ordem pre-estabelecida
	for (int ord = 0; ord < NUMVIZINHOS; ord++) {
		int I = i + ordem[ord][0];
		int J = j + ordem[ord][1];

		if (!posicaoValida(I, J, im)) {
			continue;
		} else if (fabs(im.mat[I][J] - (*curSum)/(float)(*curQtt)) <= C) {
			dfs(I, J, curSum, curQtt, im, C, numVisita, vis);
		}
	}
}

int main() {
	char nomeArquivo[MAXSTR];
	scanf(" %s", nomeArquivo);

	FILE* fp = fopen(nomeArquivo, "r");
	if (fp == NULL) { // arquivo invalido
		fprintf(stderr, "Erro na leitura do arquivo!\n");
		return 0;
	}

	// le a imagem do arquivo
	Imagem im = leImagem(fp);
	fclose(fp);

	// aloca o vetor de visitados
	int** vis = alocaMatriz(im.m, im.n);

	int k;
	scanf("%d", &k);

	// le os cliques do usuario e percorre a matriz
	for (int op = 1; op <= k; op++) {
		int x, y, c;
		scanf("%d %d %d", &x, &y, &c);
		int curSum = 0, curQtt = 0;
		dfs(x, y, &curSum, &curQtt, im, c, op, vis);
	}

	// checa todos os pontos, verificando se sao bordas
	for (int i = 0; i < im.m; i++) {
		for (int j = 0; j < im.n; j++) {
			bool ehBorda = false;

			for (int ord = 0; ord < NUMVIZINHOS; ord++) {
				int I = i + ordem[ord][0];
				int J = j + ordem[ord][1];

				if (!posicaoValida(I, J, im)) {
					continue;
				}

				ehBorda |= vis[I][J] != vis[i][j];
			}

			if (ehBorda) {
				printf("(%d, %d)\n", i, j);
			}
		}
	}

	// libera tudo da heap
	liberaMatriz(vis, im.m);
	liberaMatriz(im.mat, im.m);
}