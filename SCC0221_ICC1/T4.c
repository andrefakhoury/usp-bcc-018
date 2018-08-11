/*
	Programa que calcula, com escalonamento de matriz, a colisao entre dois objetos no R2.
	Trabalho inter-disciplinar entre ICC e GA da USP de Sao Carlos, 2018.
	
	Andre Fakhoury - 4482145
	USP Sao Carlos
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _Fracao {
	int num, den;
} Fracao;

/*
 * Funcao que aloca uma matriz na heap.
 * Parametros:
 *		Fracao*** m   - endereco de uma Fracao** da main, cujo valor sera alterado para um endereco na Heap.
 *		int qtLinhas  - quantidade de linhas da matriz
 *		int qtColunas - quantidade de colunas da matriz
*/
void alocarMatrizFracao(Fracao ***m, int qtLinhas, int qtColunas) {
	*m = (Fracao**)malloc(qtLinhas * sizeof(Fracao*));
	for (int i = 0; i < qtLinhas; i++)
		(*m)[i] = (Fracao*) malloc(qtColunas * sizeof(Fracao));
}

/*
 * Funcao que desaloca uma matriz na heap.
 * Parametros:
 *		Fracao** m   - endereco do primeiro elemento da matriz, para ser limpado na heap
 *		int qtLinhas - quantidade de linhas da matriz
*/
void desalocaMatrizFracao(Fracao** m, int qtLinhas) {
	for (int i = 0; i < qtLinhas; i++)
		free(m[i]);
	free(m);
}

/*
 * Funcao que permuta duas linhas em uma matriz, de modo que o primeiro valor da primeira linha nao pode ser nulo.
 * Parametros:
 *		Fracao** inter - matriz de Fracoes alocada na heap
 *		int ini 	   - valor da primeira posicao a ser considerada da matriz (de acordo com a nivel do escalonamento ja feito)
 *		int qtLinhas   - quantidade de linhas da matriz
 *		int qtColunas  - quantidade de colunas da matriz
*/
void swap(Fracao** inter, int ini, int qtLinhas, int qtColunas) {
	for (int i = ini; i < qtLinhas; i++) {
		if (inter[i][ini].num != 0) { //o valor do primeiro coeficiente da primeira linha nao podera ser nulo
			for (int j = ini; j < qtColunas; j++) {
				Fracao aux = inter[i][j];
				inter[i][j] = inter[ini][j];
				inter[ini][j] = aux;
			}
			break;
		}
	}
}

/*
 * Funcao que calcula o MMC (minimo multiplo comum) entre dois inteiros.
 * Parametros:
 *		int x, y - inteiros para o calculo
 * Retorno:
 *		inteiro, resultado do MMC entre x e y.
*/
int mmc(int x, int y) {
	int a = (x>y) ? y : x; //a recebe o minimo entre x e y
	int b = (x<y) ? y : x; //b recebe o maximo entre x e y

	for (int i = b; i <= a*b; i++)
		if (i%a == 0 && i%b == 0) return i; //retornara o minimo multiplo comum entre a e b
	return -1; //se nao foi retornado nenhum numero, entao ocorreu algum erro (retorna -1)
}

/*
 * Funcao que realiza a subtracao entre duas fracoes, e retorna este resultado.
 * Parametros:
 * 		Fracao f1, f2 - fracoes para serem subtraidas
 * Retorno:
 * 		Fracao, resultado da conta f1-f2.
*/
Fracao subtraiFracao(Fracao f1, Fracao f2) {	
	Fracao res;
	res.den = mmc(f1.den, f2.den);
	res.num = ((res.den/f1.den)*f1.num) - ((res.den/f2.den)*f2.num);
	return res;
}

/*
 * Funcao que realiza a multiplicacao entre duas fracoes, e retorna este resultado.
 * Parametros:
 * 		Fracao f1, f2 - fracoes para serem multiplicadas
 * Retorno:
 * 		Fracao, resultado da conta f1*f2.
*/
Fracao multFracao(Fracao f1, Fracao f2) {
	Fracao res;
	res.num = f1.num * f2.num;
	res.den = f1.den * f2.den;
	return res;
}

/*
 * Funcao que procura absurdo num sistema. Este calculo e realizado da seguinte forma:
 *		Se todos os coeficientes iniciais de uma linha forem nulos, o ultimo coeficiente tambem deve ser nulo.
 *		Caso isso nao aconteca, existe um absurdo no sistema.
 * Parametros:
 * 		Fracao** inter - matriz de funcoes na heap
 *		int ini 	   - valor da primeira posicao a ser considerada da matriz (de acordo com a nivel do escalonamento ja feito)
 *		int qtLinhas   - quantidade de linhas da matriz
 *		int qtColunas  - quantidade de colunas da matriz
 * Retorno:
 * 		0, se nao existir absurdo;
 *		1, se existir absurdo.
*/
int procuraAbsurdo(Fracao** inter, int ini, int qtLinhas, int qtColunas) {
	for (int i = ini; i < qtLinhas; i++) {
		for (int j = ini; j < qtColunas; j++) {
			if (j != qtColunas-1 && inter[i][j].num != 0) break;
			if (j == qtColunas-1 && inter[i][j].num != 0) return 1; //esse trecho so sera executado caso todos os primeiros
																	//coeficientes sejam iguais a zero; entao, e feita a condicao de aburdo.
		}
	}
	return 0;
}

/*
 * Funcao recursiva que realiza o escalonamento de um sistema, alem de realizar a condicional de existencia de absurdo neste sistema.
 * Parametros:
 * 		Fracao** inter - matriz de funcoes na heap
 *		int ini 	   - valor da primeira posicao a ser considerada da matriz (de acordo com a nivel do escalonamento ja feito)
 *		int* colide    - endereco de uma variavel na stack (main), que indicara se existe colisao no sistema.
 *		int qtLinhas   - quantidade de linhas da matriz
 *		int qtColunas  - quantidade de colunas da matriz
*/
void escalona(Fracao** inter, int ini, int* colide, int qtLinhas, int qtColunas) {
	if (ini == qtLinhas-1) return; //a condicao de parada ocorre se o sistema for representado pela matriz linha.
	
	swap(inter, ini, qtLinhas, qtColunas); //realiza a troca entre linhas para que o pivo nao seja nulo.

	Fracao pivo = inter[ini][ini];
	
	for (int i = ini+1; i < qtLinhas; i++) {
		Fracao aux; //representa o quociente entre o primeiro coeficiente da linha e o pivo da matriz considerada.
		aux.num = inter[i][ini].num * pivo.den;
		aux.den = inter[i][ini].den * pivo.num;
		
		for (int j = ini; j < qtColunas; j++) {
			inter[i][j] = subtraiFracao(inter[i][j], multFracao(inter[ini][j], aux));
		}
	}

	if (procuraAbsurdo(inter, ini, qtLinhas, qtColunas)) *colide = 0; //caso ocorra absurdo no sistema, nao existe colisao.

	escalona(inter, ini+1, colide, qtLinhas, qtColunas); //chamada recursiva da funcao, dessa vez considerando uma matriz menor
}

int main() {
	Fracao** inter; //matriz que armazena (s1 inter s2)
	int colide = 1; //inteiro que armazena 1 ou 0 (colide ou nao colide)
	int qtLinhas, qtColunas, indice = 0;
	char obj; //r ou p

	scanf("%d %d", &qtLinhas, &qtColunas);

	alocarMatrizFracao(&inter, qtLinhas, qtColunas);
	
	//leitura da matriz de entrada
	for (int i = 0; i < 2; i++) {
		scanf(" %c", &obj);
		if (obj == 'r') {
			for (int j = 0; j < 4; j++)
				scanf("%d %d", &inter[indice][j].num, &inter[indice][j].den);
			indice++;
			for (int j = 0; j < 4; j++)
				scanf("%d %d", &inter[indice][j].num, &inter[indice][j].den);
			indice++;
		} else if (obj == 'p') {
			for (int j = 0; j < 4; j++)
				scanf("%d %d", &inter[indice][j].num, &inter[indice][j].den);
			indice++;
		}
	}

	escalona(inter, 0, &colide, qtLinhas, qtColunas);
	
	printf("%s\n", (colide) ? "sim" : "nao"); //se colide for 1, houve colisao; caso contrario, nao.
	
	//imprime a matriz resultante do escalonamento.
	for (int i = 0; i < qtLinhas; i++) {
		for (int j = 0; j < qtColunas; j++) {
			if (inter[i][j].num == 0) inter[i][j].den = 1;
			else {
				if (inter[i][j].num % inter[i][j].den == 0) {
					inter[i][j].num/=inter[i][j].den;
					inter[i][j].den = 1;
				}
			}

			if (inter[i][j].den == 1)
				printf("%d\t", inter[i][j].num);
			else
				printf("%d/%d\t", inter[i][j].num, inter[i][j].den);
		}
		printf("\n");
	}
			
	desalocaMatrizFracao(inter, qtLinhas);
	return 0;
}