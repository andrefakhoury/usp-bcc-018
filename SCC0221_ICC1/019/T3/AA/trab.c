//incluindo bibliotecas importantes//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//definindo termos para maior legibilidade//
#define and &&
#define or ||
#define atual col*x+y
#define cima col*(x-1)+y
#define baixo col*(x+1)+y
#define direita col*x+(y+1)
#define esquerda col*x+(y-1)
#define media (*soma)/(double)(*quantidade)

typedef struct {
	int* pixel;
	int* referencia;
} matrizes;

//funcao que realiza a conquista de pixels para a segmentacao de imagens de acordo com as condicoes fornecidas
//a funcao tenta conquistar novas casas na ordem (cima, direita, baixo, esquerda)
void conquista (matrizes imagem, int lin, int col, int x, int y, int crit, long long* soma, long long* quantidade) {
	if (imagem.referencia[atual] == 1) return;  //retorna se atual ja foi conquistada
	*quantidade +=1;               		    //aumenta a quantidade de casas conquistadas
	*soma += imagem.pixel[atual];       	    //aumenta a soma dos valores das casas conquistadas
	imagem.referencia[atual] = 1;		    //sinaliza como casa conquistada
	
	for (int i=1;i<=lin*col;i++) {
		printf("%d ", imagem.referencia[i-1]);
		if (i%col == 0) printf("\n");
	}	
	printf("\n");

	//condicao dos ifs: 1- analisa se a casa que esta sendo testada existe na matriz
	//		    2- analisa se a casa que esta sendo testada ainda nao foi conquistada
	//		    3- analisa se a operacao do algoritmo de conquista e' menor que o criterio estabelecido

	//vai para cima
	if (x != 0 and imagem.referencia[cima] == 0 and fabs(imagem.pixel[cima]-media) <= crit) {
		printf("Fui pra cima (%d ; %d)\n", x-1, y);
		conquista(imagem, lin, col, x-1, y, crit, soma, quantidade);
	}

	//vai para direita
	if (y != col-1 and imagem.referencia[direita] == 0 and fabs(imagem.pixel[direita]-media) <= crit) {
		printf("Fui pra direita (%d ; %d)\n", x, y+1);
		conquista(imagem, lin, col, x, y+1, crit, soma, quantidade);
	}

	//vai para baixo
	if (x != lin-1 and imagem.referencia[baixo] == 0 and fabs(imagem.pixel[baixo]-media) <= crit) {
		printf("Fui pra baixo (%d ; %d)\n", x+1, y);
		conquista(imagem, lin, col, x+1, y, crit, soma, quantidade);
	}

	//vai para esquerda
	if (y != 0 and imagem.referencia[esquerda] == 0 and fabs(imagem.pixel[esquerda]-media) <= crit) {
		printf("Fui pra esquerda (%d ; %d)\n", x, y-1);
		conquista(imagem, lin, col, x, y-1, crit, soma, quantidade);
	}
}


//funcao para analisar recursivamente o valor da posicao do vetor e comparar com casas adjacentes para concluir se pertence a borda ou nao
//tag 0 ou 9 na matriz de referencia - nao pertence a borda
//tag 1 ou 2 na matriz de referencia - pertence a borda
void bordas(int* ref, int lin, int col, int pos) {
	//definindo posicao x e y, interpretando o vetor como uma matriz
	int x = (int)(pos/col);
	int y = pos%col;
	
	int i = 0;	//variavel para contagem das possiveis comparacoes dependendo da posicao de "ref[atual]" em relacao aos adjacentes
	int flag = 0;	//flag para verificar se "ref[atual]" pertence a bordas, dependendo do numero de comparacoes possiveis


	if (ref[atual] == 1) {
		if(x != 0) {
			if (ref[cima] == 1 or ref[cima] == 9) flag++;
			else if (ref[cima] == 0) ref[cima] = 2;
			i++;
		}
		if(y != col-1) {
			if (ref[direita] == 1 or ref[direita] == 9) flag++;
			else if (ref[direita] == 0) ref[direita] = 2;
			i++;
		}
		if(x != lin-1) {
			if (ref[baixo] == 1 or ref[baixo] == 9) flag++;
			else if (ref[baixo] == 0) ref[baixo] = 2;
			i++;
		}
		if(y != 0) {
			if (ref[esquerda] == 1 or ref[esquerda] == 9) flag++;
			else if (ref[esquerda] == 0) ref[esquerda] = 2;
			i++;
		}
		//se "ref[atual]" esta rodeado de casas conquistadas dentre todas as comparacoes possiveis, recebe 9
		if (flag == i) ref[atual] = 9;
	}

	if (atual == (lin*col)-1) return; //caso base: quando chega ao final do vetor
	bordas(ref, lin, col, pos+1);
}



int main (int argc, char* argv[]) {
	//declarando variaveis
	char* nome_pgm;         //nome da imagem em pgm
	int linhas, colunas;    //numero de linhas e colunas da matriz de pixels da imagem
	int consultas;		//numero de consultas a serem realizadas
	int** coord;	        //coordenadas do inicio das consultas
	int* criterio;		//criterio para as consultas
	
	long long soma;         //soma dos valores dos pixels da consulta
	long long quantidade;	//quantidade dos valores ja conquistados na consulta
	int i;

	matrizes imagem;	//struct para armazenamento da matriz de pixels e matriz de referencia da conquista em forma de vetor

	//abrindo arquivos
	FILE* teste = fopen(argv[1], "r");
	fscanf(teste, "%ms", &nome_pgm);
	FILE* pgm = fopen(nome_pgm, "r");


	//recebendo o numero de consultas a serem feitas e alocando memoria
        fscanf(teste, "%d", &consultas);
        coord = (int**) malloc(consultas*sizeof(int*));
        criterio = (int*) malloc(consultas*sizeof(int));
        if(criterio == NULL or coord == NULL) {
                printf("Erro em alocar memoria.\n"); return 1;
        }

	//recebendo valores para coordenadas iniciais e criterios
        for (int i = 0; i < consultas; i++) {
                coord[i] = (int*)malloc(2*sizeof(int));
                fscanf(teste, "%d %d %d", &coord[i][0], &coord[i][1], &criterio[i]);
        }


	//recebendo o numero de linhas e colunas e alocando memoria
	fscanf(pgm, "%*s %d %d %*d", &colunas, &linhas);
	imagem.pixel = (int*) malloc(linhas*colunas*sizeof(int));
	imagem.referencia = (int*) calloc(linhas*colunas, sizeof(int));
	if (imagem.pixel == NULL or imagem.referencia == NULL) {
		printf("Erro em alocar memória.\n"); return 1;
	}
	//recebendo os valores dos pixels
	for (i = 0; i < linhas*colunas; i++) {
		fscanf(pgm, "%d", &imagem.pixel[i]);
		printf("%d ",imagem.pixel[i]);
		if ((i+1)%colunas==0) printf("\n");
	}
	printf("\n");
	
	
	//realizando as consultas atraves da funcao "conquista"
	for (i = 0; i < consultas; i++) {
		soma = 0; quantidade = 0;
		conquista(imagem, linhas, colunas, coord[i][0], coord[i][1], criterio[i], &soma, &quantidade);
	}
	
	for (i=1;i<=linhas*colunas;i++) {
		printf("%d ", imagem.referencia[i-1]);
		if (i%colunas == 0) printf("\n");
	}	

	//definindo a posicao das bordas atraves da funcao "bordas"	
	bordas(imagem.referencia, linhas, colunas, 0);
	
	for (i=1;i<=linhas*colunas;i++) {
		printf("%d ", imagem.referencia[i-1]);
		if (i%colunas == 0) printf("\n");
	}	
	//saida do programa
	for (i=0;i<linhas*colunas;i++) {
		if (imagem.referencia[i] == 1 or imagem.referencia[i] == 2) printf("(%d; %d)\n", (int)(i/colunas), i%colunas);
	}


	//realizando os devidos frees e fcloses
	fclose(pgm);
	fclose(teste);
	free (criterio);
	for (i = 0; i < consultas; i++) free(coord[i]);
	free (coord);
	free (imagem.pixel);
	free (imagem.referencia);

	return 0;
}
