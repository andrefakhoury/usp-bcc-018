#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	float criterio;
	float** pixels;
	int** matriz_conquistas;
	float soma;
	float num_repeticoes;
	int teste_n;
	int n;
	int m;
	float media;
}pacote; //economiza memoria ao apenas se passar 1 endereço na funçao segmentador


void segmentador(int lin, int col,pacote *p){

	if(lin>= p->m || col>= p->n || lin<0 || col<0){ //verifica se o ponto esta dentro da matriz
		return;
	}
	if(p->matriz_conquistas[lin][col]!=0){	//verifica se a posiçao ja foi conquistada
		return;
	}

	/*trata o primeiro caso igualando o valor do pixel ao da media, o que nunca sera maior
	que o criterio*/
	if(p->num_repeticoes!=0){	
	p->media = p->soma/p->num_repeticoes; //caso nao seja o primeiro caso a media é a soma/num_repetiçoes
	}else{
		p->media = p->pixels[lin][col]; 
	}

	if(fabs(p->media-p->pixels[lin][col]) > p->criterio){ //verifica o se o ponto atende o criterio
		return;
	}
	/* caso o pixel atenda a todos os requisitos anteriores ele é conquistado, o numero de repetiçoes aument em 1
	e seu valor é adicionado a soma*/
	p->matriz_conquistas[lin][col] = p->teste_n; 
	p->num_repeticoes += 1;
	p->soma += p->pixels[lin][col];

	//apos isso os pixels de cima, da direita, de baixo e da esquerda sao testados nessa ordem
		
		segmentador(lin-1,col,p);
	
		segmentador(lin,col+1,p);
	
		segmentador(lin+1,col,p);
	
		segmentador(lin,col-1,p);
}



int main(void)
{
	pacote p;
	FILE* arq;
	char* filename;
	int** matriz_conquistas;
	float n; // numero de colunas
	float m; //numero de linhas
	float num_testes;
	float* lin, *col, *criterio;
	float** pixels;
	float lixo;


	scanf("%ms",&filename);
	arq = fopen(filename,"r");

	fscanf(arq,"P2");
	fscanf(arq,"%f %f",&n,&m);
	fscanf(arq,"%f",&lixo);

	//malloca a matriz de pixels e calloca a de conquistas
	pixels = (float**)malloc(sizeof(float*)*m);
	matriz_conquistas = (int**)calloc(m,sizeof(int*));
	for (int i = 0; i < m; ++i)
	{
	matriz_conquistas[i] = (int*)calloc(n,sizeof(int));
	pixels[i] = (float*)malloc(sizeof(float)*n);
	}

	//le a matriz de pixels
	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){
			fscanf(arq,"%f",&pixels[i][j]);
		}
	}

	//le o numero de testes e aloca dinamicamente os arrays de cordenadas e  criterio
	scanf("%f",&num_testes);
	lin = (float*)malloc(sizeof(float)*num_testes);
	col = (float*)malloc(sizeof(float)*num_testes);
	criterio = (float*)malloc(sizeof(float)*num_testes);

	//le as cordenadas e o criterio de cada teste
	for (int i = 0; i < num_testes; ++i){
		scanf("%f %f %f",&lin[i], &col[i], &criterio[i]);		
	}
	//armazena algumas variaveis na struct pacote
	p.pixels = pixels;
	p.n = n;
	p.m = m;
	p.matriz_conquistas = matriz_conquistas;
	//chama a funçao de segmentaçao num_testes vezes passando as respectivas variaveis
	for (int i = 0; i < num_testes; ++i){	
	 	p.criterio = criterio[i];
		p.teste_n = 1+i;
		p.soma = 0;
		p.num_repeticoes = 0;
		segmentador(lin[i],col[i],&p);
	}
	/*identifica e imprime os pixels de borda,sendo este qualquer pixels com um vizinho
	de valor diferente na matriz  de conquistas*/
	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){
			#define cima  (i-1 >= 0 && matriz_conquistas[i][j]!=matriz_conquistas[i-1][j])
			#define direita  (j+1 < n && matriz_conquistas[i][j]!=matriz_conquistas[i][j+1])
			#define baixo  (i+1 < m && matriz_conquistas[i][j]!=matriz_conquistas[i+1][j])
			#define esquerda (j-1 >= 0 && matriz_conquistas[i][j]!=matriz_conquistas[i][j-1])
			if(cima || direita || baixo || esquerda){
				printf("(%d, %d)\n",i,j);
			}
		}
	}

	//livera toda memoria alocada dinamicamente
	free(filename);
	for (int i = 0; i < m; ++i)
	{
		free(pixels[i]);
		free(matriz_conquistas[i]);
	}
	free(pixels);
	free(matriz_conquistas);
	free(lin);
	free(col);
	free(criterio);
	fclose(arq);

	return 0;
}