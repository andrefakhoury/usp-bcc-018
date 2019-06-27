/*Trabalho destinado a disciplina de ICC I
Nome: Yago Poletto Salgado                                      Número USP: 10724455
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipos das funcoes que serao usadas
int **alocaMatriz(int linhas, int colunas);
void desalocaMatriz(int **matriz, int linhas);
int modulo(int num);
void conquista_pixel(int x, int y, int **matriz, const int linhas, const int colunas, const int criterio, int chamada, int total, const int pixel);
void checa_borda(int i, int j, int **matriz, int linhas, int colunas);

int main (void){
    //Declarando e recebendo variaveis iniciais de controle
    char arquivo[64];
    int k;
    scanf("%s", arquivo);
    scanf("%d", &k);
    int *x = (int*)malloc(sizeof(int)*k);
    if(x == NULL){
        exit (1);
    }
    int *y = (int*)malloc(sizeof(int)*k);
    if(y == NULL){
        exit (1);
    }
    int *c = (int*)malloc(sizeof(int)*k);
    if(c == NULL){
        exit (1);
    } 
    for(int i=0; i<k; i++){
        scanf("%d%d%d\n", &x[i], &y[i], &c[i]);
    }

    char *aux = (char*)malloc(sizeof(char)*256);
    if(aux == NULL){
        exit (1);
    }

    //Abrindo arquivo
    FILE *p = fopen(arquivo,"r");

    int linhas, colunas;

    fgets(aux,256,p); //Ignorando a primeira linha

    //Guardando a largura e a altura da imagem
    fgets(aux,256,p);
    colunas = atoi(strtok(aux," "));
    linhas = atoi(strtok(NULL, " \n\r\0"));

    fgets(aux,256,p); //Ignorando a terceira linha

    int **matriz = alocaMatriz(linhas, colunas);
    //Preenchendo a matriz com a imagem recebida pelo arquivo
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            fscanf(p, "%d", &matriz[i][j]);
        }
    }

    //Fechando arquivo
    fclose(p);

    int **matriz_copia = alocaMatriz(linhas,colunas);
    //Criando uma matriz copia para analise
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matriz_copia[i][j] = matriz[i][j];
        }
    }

    int chamada=0, total=0;
    //Segmentacao da imagem em regioes
    for(int i=0; i<k; i++){
        conquista_pixel(x[i], y[i], matriz, linhas, colunas, c[i], chamada, total, matriz[x[i]][y[i]]);
    }

    //Procurando por bordas nas regioes estabelecidas
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            if(matriz_copia[i][j] != matriz[i][j]){
                checa_borda(i, j, matriz, linhas, colunas);
            }
        }
    }

    //Desalocando memoria na heap
    desalocaMatriz(matriz, linhas);
    free(x);
    free(y);
    free(c);
    free(aux);

    return 0;
}

/*Funcao que aloca uma matriz na heap.
 *Argumentos: numero de linhas (int), numero de colunas (int).
 *Retorno: ponteiro para a matriz alocada dinamicamente (int**).
*/
int **alocaMatriz(int linhas, int colunas){
    int **matriz = (int**)calloc(linhas,sizeof(int*));
    for(int i=0; i<linhas; i++){
        matriz[i] = (int*)calloc(colunas,sizeof(int));
    }
   
    if(matriz == NULL){
        exit (1);
    }
   
    return matriz;
}

/*Funcao que desaloca uma matriz na heap.
 *Argumentos: ponteiro para a matriz (int**), numero de linhas (int).
*/
void desalocaMatriz(int **matriz, int linhas){
    for(int i=0; i<linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

/*Funcao que calcula modulo de um numero.
 *Argumentos: numero (int).
 *Retorno: modulo do numero (int).
*/
int modulo(int num){
    if(num<0){
        return (-num);
    }
    return num;
}

/*Funcao recursiva que conquista pixels da imagem, agrupando-os em uma regiao.
 *Argumentos: coordenada x (int), coordenada y (int), matriz (int**), numero de linhas (const int), numero de colunas (const int), valor do criterio (const int), numero da chamada (int), soma de valores (int), valor do pixel (int).
*/
void conquista_pixel(int x, int y, int **matriz, const int linhas, const int colunas, const int criterio, int chamada, int total, const int pixel){
    if(chamada == 0){
        int aux = matriz[x][y];
        matriz[x][y] = pixel;
        conquista_pixel(x - 1, y, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
        conquista_pixel(x, y + 1, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
        conquista_pixel(x + 1, y, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
        conquista_pixel(x, y - 1, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
    }else{

        if(x < 0 || y < 0 || x == linhas || y == colunas || (modulo(matriz[x][y] - (total/chamada)) > criterio)){
            return;
        }
        int aux = matriz[x][y];
        matriz[x][y] = pixel;
        conquista_pixel(x - 1, y, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
        conquista_pixel(x, y + 1, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
        conquista_pixel(x + 1, y, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
        conquista_pixel(x, y - 1, matriz, linhas, colunas, criterio, chamada+1, total+aux, pixel);
    }
}

/*Funcao que checa se o pixel da imagem esta na borda dela, e imprime a posicao desse pixel.
 *Argumentos: coordenada i (int), coordenada j (int), matriz (int**), numero de linhas (int), numero de colunas (int).
*/
void checa_borda(int i, int j, int **matriz, int linhas, int colunas){

    if(i-1 >= 0){
        if(matriz[i][j] != matriz[i-1][j]){
            printf("(%d, %d)\n", i, j);
            return;
        }
    }
    if(i+1 < linhas){
        if(matriz[i][j] != matriz[i+1][j]){
            printf("(%d, %d)\n", i, j);
            return;
        }
    }
    if(j-1 >= 0){
        if(matriz[i][j] != matriz[i][j-1]){
            printf("(%d, %d)\n", i, j);
            return;
        }
    }
    if(j+1 < colunas){
        if(matriz[i][j] != matriz[i][j+1]){
            printf("(%d, %d)\n", i, j);
            return;
        }
    }

    return;
}