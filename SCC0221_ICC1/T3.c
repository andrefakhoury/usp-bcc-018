/*
 *	Programa que calcula o balanceamento de distribuicao de recursos, utilizando matrizes e a tecnica de flood fill.
 *	Andre Fakhoury, USP-Sao Carlos
 *	Numero USP: 4482145
*/

#include <stdio.h>
#include <stdlib.h> //alloc
#include <math.h> //fabs

/*
 * Funcao que aloca uma matriz na heap.
 * Parametros:
 *		int N - quantidade de linhas da matriz
 *		int M - quantidade de colunas da matriz
 *	Retorno:
 *		int** m - endereco alocado na heap
*/
int** alocaMatriz(int N, int M) {

	int** m = NULL;
	
	m = (int**) calloc(N, sizeof(int *)); // aloca N linhas como vetores de int*
	for (int i = 0; i < N; i++) {
		m[i] = (int *) calloc(M, sizeof(int)); // para cada linha, M colunas de tipo int
	}
	return m;
}

/*
 * Funcao que desaloca uma matriz na heap.
 * Parametros:
 *		int N - quantidade de linhas da matriz
 *		int M - quantidade de colunas da matriz
 *		int** m - endereco do primeiro elemento da matriz, para ser limpado na heap
*/
void desalocaMatriz(int N, int M, int** m) {
	int i;
	for (i = 0; i < N; i++) { // cada vetor (coluna) dentro da matriz tem que ser liberado na heap
		free(m[i]);
	}
	free(m); // libera o vetor de linhas na heap
}

/*	
 *	Funcao que copia os valores de uma matriz em outra matriz.
 *	Parametros:
 *		int matBase[9][9] - matriz base de valores
 * 		int matAlt[9][9]  - matriz que sera alterada de acordo com a base
*/
void copiaMatriz(int matBase[9][9], int matAlt[9][9]) {
	int i, j; // variaveis para os indices de repeticao
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			matAlt[i][j] = matBase[i][j];
		}
	}
	return;
}

/*	
 *	Funcao recursiva que realiza o flood fill de uma matriz, a partir das posicoes iniciais e finais.
 *	Essa matriz tera seus valores alterados - se o flood fill for realizado em uma posicao, seu valor sera substituido por 2
 *	Parametros:
 *		int posIX - posicao atual, coordenada X
 *		int posIY - posição atual, coordenada Y
 *		int posFX - posicao final, coordenada X
 *		int posFY - posicao final, coordenada Y
 *		int map[9][9] - matriz do mapa de coordenadas
 *		int* flag - endereco de um inteiro que armazena a condicao de parada; se for alterada em uma
 *			chamada de flood fill, ele tera reflexo em todas as outras chamadas recursivas.
*/
void floodFill(int posIX, int posIY, int posFX, int posFY, int map[9][9], int* flag) {
	if (*flag) { //a funcao so sera realizada caso a flag (na funcao valorExp) tenha valor 1
		if (posIX < 0 || posIX > 8) return; // fora dos indices X da matriz
		if (posIY < 0 || posIY > 8) return; // fora dos indices Y da matriz
		
		if (posIX == posFX && posIY == posFY) { 
			*flag = 0; // se chegar na posicao final, a flag indicara valor 0
			return; 
		}
		if (map[posIX][posIY] != 0) return; // o flood fill so ocorrera caso a celula for transponivel
		
		// se a funcao chegou ate esse ponto, o flood fill ocorrera
		// troca a celula do mapa de 0 para 2, para referenciar que ocorreu flood fill no local
		map[posIX][posIY] = 2;
		floodFill(posIX+1, posIY, posFX, posFY, map, flag); // flood fill para o sul
		floodFill(posIX-1, posIY, posFX, posFY, map, flag); // flood fill para o norte
		floodFill(posIX, posIY-1, posFX, posFY, map, flag); // flood fill para o oeste
		floodFill(posIX, posIY+1, posFX, posFY, map, flag); // flood fill para o leste
	}
	
	return;
}

/*
 *	Funcao que realiza a contagem de blocos que foram visitados em um flood fill, e retorna seu comprimento.
 *	Parametros:
 *		int map[9][9] - matriz de coordenadas. Tera os valores 0, 1 ou 2, de acordo com o bloco
 *			(0: transponivel, 1: intransponivel, 2: passou pelo flood fill)
 *	Retorno:
 *		int comp - comprimento de blocos com valor 2 (blocos que passaram pelo flood fill)
*/
int compBlocos(int map[9][9]) {
	int i, j, comp = 1;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (map[i][j] == 2) comp++; // 2 indica que ocorreu flood fill na celula indicada
		}
	}
	return comp;
}

/*
 *	Funcao que calcula o valor de exploracao de cada jogador.
 *	Parametros:
 *		int N - numero de recursos do mapa + 1
 *		int P - numero de celulas transponiveis no mapa (com valor 0)
 *		int posJ[2] - posicao (x, y) do jogador 1 ou 2
 *		int** posR - endereco das posicoes dos recursos (que estao na heap)
 *		int mat[9][9] - matriz 9x9 do mapa
 *	Retorno:
 *		double com o valor de exploracao do jogador enviado por parametro.
*/
double valorExp(int N, int P, int posJ[2], int** posR, int mat[9][9]) {
	double somatorio = 0; 
	int j;
	int mapB[9][9]; // matriz que identificara o mapa para a realizacao do flood fill
	
	for (j = 0; j < N-1; j++) {
		copiaMatriz(mat, mapB); // chama a funcao para copiar o valor de mat para matB
		
		int flag = 1; // variavel utilizavel no flood fill que identificara se a posicao final foi encontrada
		
		floodFill(posJ[0], posJ[1], posR[j][0], posR[j][1], mapB, &flag); // realiza o flood fill, da posicao do jogador ate
																		  // a posicao do recurso, no mapB
		
		somatorio += ((compBlocos(mapB))/(double)P); // formula de somatorio	
	}
	
	// retorna o valor de exploracao encontrado
	return (1.0/(N-1)) * somatorio;
}

int main() {	
	int map[9][9]; // matriz do mapa do jogo
	int posJogador1[2]; // posicao (x, y) do jogador 1
	int posJogador2[2]; // posicao (x, y) do jogador 2
	int nRec; // numero de recursos do mapa
	int nTrans = 0; // quantidade de celulas transponiveis
	int i, j; //indices utilizados em for
	
	// input das celulas do mapa
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 0) nTrans++; // a celula sera transponivel se seu valor == 0
		}
	}
	
	// input das posicoes dos jogadores
	scanf("%d%d", &posJogador1[0], &posJogador1[1]);
	scanf("%d%d", &posJogador2[0], &posJogador2[1]);
	
	// input do numero de recursos
	scanf("%d", &nRec);
	
	int** recursos; // int**, endereco da matriz de recursos que sera alocada na heap
	recursos = alocaMatriz(nRec, 2); //aloca a matriz (tamanho nRec x 2) na heap, endereco guardado em recursos
	
	// input da posicao dos recursos
	for (i = 0; i < nRec; i++) {
		scanf("%d%d", &recursos[i][0], &recursos[i][1]);
	}
	
	// calcula o valor de exploracao de cada jogador com a funcao valorExp
	double expJog1 = valorExp(nRec+1, nTrans, posJogador1, recursos, map);
	double expJog2 = valorExp(nRec+1, nTrans, posJogador2, recursos, map);
	
	// output dos valores de exploracao
	printf("%.6lf\n", expJog1);
	printf("%.6lf\n", expJog2);
	
	// output de quem possui vantagem ou se o mapa eh balanceado,
	// de acordo com o valor de exploracao de cada jogador.
	// Essa diferenca so sera considerada caso seja maior que 0.001
	if (fabs(expJog1-expJog2) >= 0.001) {
		if (expJog1 < expJog2)
			printf("O jogador 1 possui vantagem\n");
		else
			printf("O jogador 2 possui vantagem\n");
	} else {
		printf("O mapa eh balanceado\n");
	}
	
	// desaloca a matriz de recursos na heap
	desalocaMatriz(nRec, 2, recursos);
	
	return(0);
}
