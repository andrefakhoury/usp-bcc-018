#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* A funcao selecao utiliza os criterios estabelecidos pelo trabalho para conquistar os pixels da imagem fornecida (no caso, transforma-los em -1) de
 forma recursiva.
 Entradas:
 int M - numero de linhas da imagem
 int N - numero de colunas da imagem
 int pixel[M][N] - a imagem
 int m - coordenada y do pixel a ser conquistado
 int n - coordenada x do pixel a ser conquistado
 int criterio - o criterio fornecido pelo input do usuario
 int total - a soma de todos os numeros ja conquistados pela funcao
 int cont - a quantidade de numeros que foram conquistados pela funcao
*/
void selecao (int M, int N, int** pixel, int m, int n, int criterio, int* total, int* cont, int regiao) {
   
    // Variaveis para o calculo da media
    *cont += 1;
    *total += pixel[m][n];
   
    // Um jeito de conquistar o pixel e' troca-lo para um valor diferente dos entre 0 e 255.
    pixel[m][n] = -regiao; /////// AQUI eu troquei pra -regiao, assim eu sei em que regiao segmentada eu estou
   
    // Os if's abaixo verificam para cima, direita, baixo e esquerda, respectivamente, na seguinte ordem: O proximo pixel e' legivel? Ele ja faz parte
    // da selecao? Ele obedece ao criterio? Se sim, conquiste ele.
    if (  m > 0 && pixel[m-1][n] >= 0 && fabs( pixel[m-1][n] - (*total) / (float)(*cont) ) <= criterio) selecao (M, N, pixel, m-1, n, criterio, total, cont, regiao);
    if (n < N-1 && pixel[m][n+1] >= 0 && fabs( pixel[m][n+1] - (*total) / (float)(*cont) ) <= criterio) selecao (M, N, pixel, m, n+1, criterio, total, cont, regiao);
    if (m < M-1 && pixel[m+1][n] >= 0 && fabs( pixel[m+1][n] - (*total) / (float)(*cont) ) <= criterio) selecao (M, N, pixel, m+1, n, criterio, total, cont, regiao);
    if (  n > 0 && pixel[m][n-1] >= 0 && fabs( pixel[m][n-1] - (*total) / (float)(*cont) ) <= criterio) selecao (M, N, pixel, m, n-1, criterio, total, cont, regiao);
}

int main() {
   
    // Abrindo o arquivo
    char nome_arquivo[30];
    scanf("%s", nome_arquivo);
    FILE *imagem = fopen(nome_arquivo, "r");
   
    // Ignorando uma informacao inutil da imagem
    fscanf(imagem, "%*s");
   
    // Leitura das dimensoes imagem
    int M, N;
    fscanf(imagem, "%d %d", &N, &M);
   
    // Mais uma informacao inutil
    fscanf(imagem, "%*d");
   
    // Alocacao e leitura da imagem
    int** pixel = (int**) malloc( M * sizeof(int*) );
    for (int m = 0; m < M; m++) pixel[m] = (int*) malloc( N * sizeof(int) );
    for (int m = 0; m < M; m++) for (int n = 0; n < N; n++) fscanf(imagem, "%d", &pixel[m][n]);
    
    // Leitura e processamento das consultas
    int qtd_consultas;
    scanf("%d", &qtd_consultas);
   
    for (int i = 0; i < qtd_consultas; i++) {
       
        int n, m, criterio;
        scanf("%d %d %d", &n, &m, &criterio);
       
        if (pixel[n][m] >= 0) { // Esse if impede que o mesmo pixel seja selecionado duas vezes
            int total = 0;
            int cont = 0;
            selecao(M, N, pixel, n, m, criterio, &total, &cont, i+1); //// AQUI eu estou colocando em que regiao segmentada os pixels vao estar - depende do numero do `click` correspondente
        }
    }

    // Verificacao dos vizinhos
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            // O if esta identado de forma a ser mais compreensivel
            if (
                (pixel[m][n] < 0 && 
                (
                                        (   m > 0 && pixel[m][n] != pixel[m-1][n] ) ||
                                        ( n < N-1 && pixel[m][n] != pixel[m][n+1] ) ||
                                        ( m < M-1 && pixel[m][n] != pixel[m+1][n] ) ||
                                        (   n > 0 && pixel[m][n] != pixel[m][n-1] ) ))
                ||
                (pixel[m][n] >= 0 && (
                                        (   m > 0 && pixel[m-1][n] < 0 ) ||
                                        ( n < N-1 && pixel[m][n+1] < 0 ) ||
                                        ( m < M-1 && pixel[m+1][n] < 0 ) ||
                                        (   n > 0 && pixel[m][n-1] < 0 ) ))
                ) printf("(%d, %d)\n", m, n);
        }
    }

    // Dealocacao da imagem
    for (int i = 0; i < M; i++) free(pixel[i]);
    free(pixel);
    fclose(imagem);
   
    return 0;
}