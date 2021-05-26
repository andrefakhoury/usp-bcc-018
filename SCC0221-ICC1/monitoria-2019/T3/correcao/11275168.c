#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct { //Struct dos pontos de clique do usuário
	int x;  // Coordenada x do clique
	int y;  // Coordenada y do clique
	int c;  // Critério de conquista 'C' do clique
} pontos;

typedef struct { // Struct dos pixels de borda
    int x;  // Coordenada x do pixel
	int y;  // Coordenada y do pixel
}pixels;

/* Função de segmentação de regiões que recebe as coordenadas x e y do ponto de clique, o número de linhas e de colunas
da matriz de pixels, um marcador que identifica aquela região, o critério de conquista, a média dos valores dos pixels,
o número de pixels pertencentes à região, a soma total dos valores desses pixels, a matriz de pixels e a matriz de regiões. */
void delimitador(int x, int y, int n, int m, int marcador, int c, float *media,
int *cont, float *total, int **mat, int **reg) {
   if (x < 0 || x == n || y < 0 || y == m) // Se o ponto em questão está fora dos limites da matriz
 	return; // Retroceda um pixel
   if (reg[x][y] != 0)	// Se o ponto em questão já pertence a uma região segmentada
 	return; // Retroceda um pixel
   if (fabs(*media - mat[x][y]) > c) /* Se a diferença entre os valores do pixel em questão e a média dos
    							valores dos pixels pertencentes à região for maior que o critério de conquista */
 	return; // Retroceda um pixel
   reg[x][y] = marcador; // O elemento correspondente na matriz de regiões é registrado naquela região
   *total += mat[x][y];	// É somado o valor daquele pixel ao montante total
   *cont += 1;	// O número de pixels pertencentes à região segmentada é incrementado
   *media = *total/(*cont);	// A média é atualizada
   delimitador(x - 1, y, n, m, marcador, c, media, cont, total, mat, reg); // Chamada recursiva para o pixel acima
   delimitador(x, y + 1, n, m, marcador, c, media, cont, total, mat, reg); // Chamada recursiva para o pixel à direita
   delimitador(x + 1, y, n, m, marcador, c, media, cont, total, mat, reg); // Chamada recursiva para o pixel abaixo
   delimitador(x, y - 1, n, m, marcador, c, media, cont, total, mat, reg); // Chamada recursiva para o pixel à esquerda
}

/* Função de verificação dos pixels de borda que recebe a matriz de regiões, seu número de linhas e de colunas, 
a quantidade de pixels de borda e um vetor de pixels */
void verificaborda(int **reg, int n, int m, int *qtd, pixels *pixel) { 
    	for (int i = 0; i < n; i++) {	// Loop que interage com o número de linhas
        	for (int j = 0; j < m; j++){	// e com o número de colunas
            	if (i > 0) {	// Se o pixel tem coordenada i > 0, pode-se fazer a checagem com o pixel acima
                	if (reg[i][j] != reg[i - 1][j]) {	// Se o pixel acima está numa região diferente
                    	pixel[*qtd].x = i;	// O elemento 'qtd' do vetor de pixels recebe
                    	pixel[*qtd].y = j;	// as coordenadas i e j do pixel de borda
                    	*qtd += 1;	// Incremente o número de pixels de borda
                    	continue; // Pule para a próxima iteração, pois esse pixel já foi verificado
                	}
            	}
            	if (i < n - 1) { // Se o pixel tem coordenada i < n - 1, pode-se fazer a checagem com o pixel abaixo
                	if (reg[i][j] != reg[i + 1][j]) { // Se o pixel abaixo está numa região diferente
                    	pixel[*qtd].x = i; // O elemento 'qtd' do vetor de pixels recebe
                    	pixel[*qtd].y = j; // as coordenadas i e j do pixel de borda
                    	*qtd += 1; // Incremente o número de pixels de borda
                    	continue; // Pule para a próxima iteração, pois esse pixel já foi verificado
                	}
            	}
            	if (j > 0) { // Se o pixel tem coordenada j > 0, pode-se fazer a checagem com o pixel à esquerda
                	if (reg[i][j] != reg[i][j - 1]) { // Se o pixel à esquerda está numa região diferente
                    	pixel[*qtd].x = i; // O elemento 'qtd' do vetor de pixels recebe
                    	pixel[*qtd].y = j; // as coordenadas i e j do pixel de borda
                    	*qtd += 1; // Incremente o número de pixels de borda
                    	continue; // Pule para a próxima iteração, pois esse pixel já foi verificado
                	}
            	}
            	if (j < m - 1) { // Se o pixel tem coordenada j < m - 1, pode-se fazer a checagem com o pixel à direita
                	if (reg[i][j] != reg[i][j + 1]) { // Se o pixel à direita está numa região diferente
                    	pixel[*qtd].x = i; // O elemento 'qtd' do vetor de pixels recebe
                    	pixel[*qtd].y = j; // as coordenadas i e j do pixel de borda
                    	*qtd += 1; // Incremente o número de pixels de borda
                    	continue; // Pule para a próxima iteração, pois esse pixel já foi verificado
                	}
            	}
        	}
    	}
	}

// Função de alocação dinâmica de matrizes, recebendo seu número de linhas e de colunas
int **alocamatriz(int n, int m) {
    int **mat;	// Ponteiro duplo
   	mat = (int **) malloc(sizeof(int *) * n);	// Alocação do vetor de ponteiros
    if ((mat = (int **) malloc(sizeof(int *) * n)) == NULL) { // Se a alocação foi malsucedida
        printf("Erro na alocação de memória"); 	// Avise isso
        exit(1);
    }  
 	 
   	for (int i = 0; i < n; i++) {
        mat[i] = (int *) malloc(sizeof(int) * m); // Alocação dos vetores de inteiros
        if ((mat[i] = (int *) malloc(sizeof(int) * m)) == NULL) {	// Se a alocação foi malsucedida
           	printf("Erro na alocação de memória");	// Avise isso
        	exit(1);
    	}
   	}
   	return mat; // Retorno do endereço base 
}

// Função de liberação de memória ocupada por matrizes, que recebe uma matriz e o número de linhas da matriz
void liberamatriz (int **mat, int n) { 
    for (int i = 0; i < n; i++) {	// Loop que interage com o número de linhas
        free(mat[i]);	// Liberação da memória ocupada por cada vetor para inteiros
    }
    free(mat);	// Liberação da memória ocupada pelo vetor de ponteiros
}

/* Função de leitura dos valores dos pixels da matriz, recebendo um ponteiro para arquivo, duas matrizes (de pixels
e de regiões), e o número de linhas e de colunas da matriz */ 
void leitura(FILE *fp, int **mat, int **matreg, int n, int m) { 
   for (int i = 0;  i < n;  i++) {		// Loop que interage com o número de linhas
    	for (int j = 0; j < m; j++) {	// e com o número de colunas
            fscanf(fp, " %d",  &mat[i][j]);	// Leia um inteiro presente no arquivo, no caso pertencente à matriz
            matreg[i][j] = 0;	// O elemento correspondente na matriz de regiões é zerado para a posterior segmentação
    	}
	}
}

int main(void) {
	FILE *fp; // Ponteiro para arquivo
	char *arq = (char *) malloc(sizeof(char) * 20);   // String que armazena o nome do arquivo
	int  **mat, **matreg, k, cont, marcador = 0, n, m, qtd = 0; /* Matriz de pixels, matriz de regiões,
    número de cliques, contador de pixels que satisfazem as condições, marcador para cada segmentação, 
    número de linhas da matriz, número de colunas da matriz e quantidade de pixels de borda, respectivamente. */
	float total, media; // Soma total dos valores dos pixels e a media deles, respectivamente.
	pontos *ponto;	// Ponteiro para a struct ponto
	pixels *pixel; // Ponteiro para a struct pixel
    
	scanf("%s %d", arq, &k); // Leitura do nome do arquivo e do número de cliques
    ponto = (pontos *) malloc(sizeof(pontos) * k); // Alocação dinâmica de 'k' espaços para um vetor de pontos
   
   for (int i = 0; i < k; i++) {
        scanf("%d %d %d", &ponto[i].x, &ponto[i].y, &ponto[i].c); /* Leitura das coordenadas
		dos cliques e dos respectivos critérios de conquista */
   }
    
	fp = fopen(arq, "r"); // Abertura do arquivo para leitura
	if (fp == NULL) {	// Se a abertura foi malsucedida, avise isso
        printf("Erro na abertura do arquivo");
        exit(1);
	}
    
	fscanf(fp, "%*s %d %d %*d",  &m, &n); // Leitura do número de colunas e do número de linhas da matriz de pixels
	pixel = (pixels *) malloc(sizeof(pixels) * n * m); // Alocação dinâmica de 'n * m' espaços para o vetor de pixels
	mat = alocamatriz(n, m); // Alocação dinâmica para a matriz de pixels de acordo com o nº de linhas e colunas
	matreg = alocamatriz(n, m); // Alocação dinâmica para a matriz de regiões de acordo com o nº de linhas e colunas
	leitura(fp, mat, matreg, n, m); // Leitura dos elementos da matriz e tratamentos correspondentes
	fclose(fp);	// Fechamento do arquivo
    
	for (int i = 0; i < k; i++) { // Loop que interage com o número de cliques
    	if (matreg[ponto[i].x][ponto[i].y] == 0) { // Se o ponto de clique ainda não pertence a uma região segmentada 
        	marcador++; // O marcador de regiões é atualizado
        	cont = 0; // O número de pixels da região é zerado
        	total = 0; // A soma total dos pixels é zerada
         	media = mat[ponto[i].x][ponto[i].y]; // A média recebe o valor correspondente ao ponto de clique
        	delimitador(ponto[i].x, ponto[i].y, n, m, marcador, ponto[i].c,
&media, &cont, &total, mat, matreg);	// Chamada da função de segmentação a partir do ponto de clique
    	}
	}
    
	verificaborda(matreg, n, m, &qtd, pixel); /* Chamada da função de verificação de pixels de borda
	 									com a matriz de regiões preenchida. */ 
    
	for (int i = 0; i < qtd; i++)	// Loop que interage com a quantidade de pixels de borda
    	printf("(%d, %d)\n", pixel[i].x, pixel[i].y);	// Impressão das coordenadas dos pixels de borda na tela
    
	free(arq);
	free(pixel);
	free(ponto);			// Parte do código para a liberação da memória ocupada por vetores e matrizes

	liberamatriz(mat, n);
	liberamatriz(matreg, n);
    
   
	return 0;
}



