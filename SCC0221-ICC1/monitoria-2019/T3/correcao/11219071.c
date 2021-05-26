#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define DEBUG(n,m,v) for(int i=0;i<n;i++)for(int j=0; j<m; j++) printf("%d ",v[i][j]);

typedef struct _pixel{ //struct para cada pixel
    int x;
    int y;
    int valor;
}px;

//Os argumentos dessa função são: a matriz de pixeis; a matriz auxiliar para criar as regiões segmentadas; as dimensões máximas da imagem;
//as coordenadas da busca; o criterio de busca; um índice para a busca; a soma dos valores dos pixeis buscados; e um contador de píxeis buscados.
void pesquisaImagem(px** imagePointer , int** matrizVerificadora , int linhaMax , int colunaMax , int linha , int coluna , int c , int index , int* soma , int* counter){
    matrizVerificadora[linha][coluna] = index + 1;//insere o pixel na região segmentada
    (*counter)++;//adiciona um à quantidade de pixeis 
    (*soma) += imagePointer[linha][coluna].valor;//adiciona o valor do pixel à soma
    //----------------pixel superior----------------------------------------------------------------------------------------------------------
    if(linha-1 >= 0 && coluna >= 0 && linha-1 < linhaMax && coluna < colunaMax){//verifica se o pixel existe
        if(matrizVerificadora[linha-1][coluna] == 0){//verifica se o pixel já está em alguma região segmentada
            if(fabs(imagePointer[linha-1][coluna].valor - ((float)(*soma) / (float)(*counter))) <= c){//verifica se o pixel atende o requisito
                pesquisaImagem(imagePointer , matrizVerificadora , linhaMax , colunaMax , linha-1 , coluna , c , index , soma , counter);//passa a pesquisa para o outro pixel
            }
        }
    }
    //----------------pixel direito----------------------------------------------------------------------------------------------------------
    if(linha >= 0 && coluna+1 >= 0 && linha < linhaMax && coluna+1 < colunaMax){//verifica se o pixel existe
        if(matrizVerificadora[linha][coluna+1] == 0){//verifica se o pixel já está em alguma região segmentada
            if(fabs(imagePointer[linha][coluna+1].valor - ((float)(*soma) / (float)(*counter))) <= c){//verifica se o pixel atende o requisito
                pesquisaImagem(imagePointer , matrizVerificadora , linhaMax , colunaMax , linha , coluna+1 , c , index , soma , counter);//passa a pesquisa para o outro pixel
            }
        }
    }
    //----------------pixel inferior----------------------------------------------------------------------------------------------------------
    if(linha+1 >= 0 && coluna >= 0 && linha+1 < linhaMax && coluna < colunaMax){//verifica se o pixel existe
        if(matrizVerificadora[linha+1][coluna] == 0){//verifica se o pixel já está em alguma região segmentada
        //printf ("%f\n", fabs(imagePointer[linha+1][coluna].valor - (*soma / (float)(*counter))));
            if(fabs(imagePointer[linha+1][coluna].valor - ((float)(*soma) / (float)(*counter))) <= c){//verifica se o pixel atende o requisito
                pesquisaImagem(imagePointer , matrizVerificadora , linhaMax , colunaMax , linha+1 , coluna , c , index , soma , counter);//passa a pesquisa para o outro pixel
            }
        }
    }
    //----------------pixel esquerdo----------------------------------------------------------------------------------------------------------
    if(linha >= 0 && coluna-1 >= 0 && linha < linhaMax && coluna-1 < colunaMax){//verifica se o pixel existe
        if(matrizVerificadora[linha][coluna-1] == 0){//verifica se o pixel já está em alguma região segmentada
            if(fabs(imagePointer[linha][coluna-1].valor - ((float)(*soma) / (float)(*counter))) <= c){//verifica se o pixel atende o requisito
                pesquisaImagem(imagePointer , matrizVerificadora , linhaMax , colunaMax , linha , coluna-1 , c , index , soma , counter);//passa a pesquisa para o outro pixel
            }
        }
    }

}

px** readFile (char* arq, int* linhaMax , int* colunaMax){//função que lê o arquivo, guarda os valores dos pixeis numa matriz e devolve o endereço da matriz
    FILE* fp;
    px** matrizImagem;
    int aux;
    fp = fopen(arq , "r");
    fscanf(fp , "%*s %d %d %*d" , colunaMax , linhaMax);
    matrizImagem = (px**) malloc (*linhaMax * sizeof(px*));
    for(int i = 0 ; i < *linhaMax ; i++){
        matrizImagem[i] = (px*) malloc(*colunaMax * sizeof(px));
    }
    for (int i = 0 ; i < *linhaMax ; i++){
        for (int j = 0 ; j < *colunaMax ; j++){
            fscanf(fp , "%d" , &aux);
            matrizImagem[i][j].valor = aux;
            matrizImagem[i][j].x = i;
            matrizImagem[i][j].y = j;
             
        }
    }
    fclose(fp);
    return matrizImagem;
}

int main(void){
    char* arq;//string nome do arquivo
    int k , coluna , linha , c;//Lê as entradas fora do arquivo
    int linhaMax, colunaMax;//dimensões da matrix de pixeis da imagem
    int soma = 0;//soma dos valores dos pixeis a ser usada na função de busca
    px** imagePointer;//ponteiro para a matriz de pixeis da imagem
    scanf("%ms" , &arq);//aloca e guarda o nome do arquivo dinamicamente numa string
    scanf("%d" , &k);//recebe as entradas configuradoras
    imagePointer = readFile(arq , &linhaMax , &colunaMax);//lê o arquivo e devolve o endereço da matriz criada para armazenar a matriz de píxeis da imagem
    //--------------Criando um matriz auxiliar que vai representar os grupos de píxeis pesquisados-------------------------------------------------
    int** matrizVerificadora;
    matrizVerificadora = (int**) malloc (linhaMax * sizeof(int*));
    for(int i = 0 ; i < linhaMax ; i++){
        matrizVerificadora[i] = (int*) malloc(colunaMax * sizeof(int));
        for(int j = 0 ; j < colunaMax ; j++){
            matrizVerificadora[i][j] = 0;
        }
    }
    //------------------------------------iterando para fazer cada pesquisa por input--------------------------------------------------------------
    for (int i = 0 ; i < k ; i++){
        soma = 0;
        int counter = 0;
        scanf("%d %d %d" , &linha , &coluna , &c);
        if (matrizVerificadora[linha][coluna] == 0){
            pesquisaImagem(imagePointer , matrizVerificadora , linhaMax , colunaMax , linha , coluna  , c , i , &soma , &counter);
        }
    } 

    //-----------------------------------output---------------------------------------------------------------------------------------------------
    int imprimiu;
    for(int i = 0 ; i < linhaMax ; i++){
        for(int j = 0 ; j < colunaMax ; j++){
            imprimiu = 0;
            //pixel de cima
            if(i-1 >= 0 && j >= 0 && i-1 < linhaMax && j < colunaMax){//verifica se o pixel existe
                if(!imprimiu && abs(matrizVerificadora[i][j] - matrizVerificadora[i-1][j]) != 0){
                    printf("(%d, %d)\n" , i , j);
                    imprimiu = 1;
                }
            //pixel da direita
            }if(i >= 0 && j+1 >= 0 && i < linhaMax && j+1 < colunaMax){//verifica se o pixel existe
                if(!imprimiu && abs(matrizVerificadora[i][j] - matrizVerificadora[i][j+1]) != 0){
                    printf("(%d, %d)\n" , i , j);
                    imprimiu = 1;
                }
            //pixel de baixo
            }if(i+1 >= 0 && j >= 0 && i+1 < linhaMax && j < colunaMax){//verifica se o pixel existe
                if (!imprimiu && abs(matrizVerificadora[i][j] - matrizVerificadora[i+1][j]) != 0){
                    printf("(%d, %d)\n" , i , j);
                    imprimiu = 1;
                }
            //pixel da esquerda
            }if(i >= 0 && j-1 >= 0 && i < linhaMax && j-1 < colunaMax){//verifica se o pixel existe
                if(!imprimiu && abs(matrizVerificadora[i][j] - matrizVerificadora[i][j-1]) != 0){
                    printf("(%d, %d)\n" , i , j);
                    imprimiu = 1;
                }
            }
        }
    } 
    //------------------------------------liberando a memoria alocada------------------------------------------------------------------------------
    for(int i = 0 ; i < linhaMax ; i++){
        free(matrizVerificadora[i]);
        free(imagePointer[i]);
    }
    free(matrizVerificadora);
    free(imagePointer);
    free(arq);

    return 0;
}