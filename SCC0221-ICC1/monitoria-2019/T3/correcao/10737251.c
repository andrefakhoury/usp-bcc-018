#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*Funcao: aloca_tabela - aloca um array 2D dinamicamente
 *
 * Tipo: short int**
 * 
 * Parametros:
 * *tipo: int
 * * * n_linhas: numero de array 1D
 * * * n_colunas: numero de variaveis por array 1D
 *
 * Return: endereco do array 2D alocado dinamicamente
 */
short int** aloca_tabela(int n_linhas, int n_colunas){
    short int** tabela = malloc(sizeof(short int*)*n_linhas);
    if(tabela==NULL){
        printf("nao foi possivel alocar\n");
    }
    for(int i=0;i<n_linhas;i++){
        tabela[i]=malloc(sizeof(short int)*n_colunas);
        if(tabela[i]==NULL){
            printf("nao foi possivel alocar\n");
        }
    }
    return tabela;
}

/*Funcao: aloca_array_char - aloca um array 1D de char
 * 
 * Tipo: char*
 * 
 * Parametros:
 * * tipo: int
 * * * n -numero de chars a ser alocado
 *
 * Return: endereco do array 1D alocado dinamicamente
 */
char* aloca_array_char(int n){
    char* array = malloc(sizeof(char)*n);
    if(array==NULL){
        printf("nao foi possivel alocar vetor de char\n");
    }
    return array;
}

/*Funcao: absoluto - calcula o valor absoluto de um float
 * 
 * Tipo: float
 * 
 * Parametros:
 * * tipo: float
 * * * a - numero passado para a funcao
 *
 * Return: valor absoluto do numero passado para a funcao
 */
float absoluto(float a){
    if(a<0){
        return -a;
    } else {
        return a;
    }
}

/*Funcao: segmentar - segmenta a regiao da imagem
 * 
 * Tipo: Void
 *
 * Parametros:
 * * Tipo: short int
 * * * x, y, c - parametros do ponto a ser analisado
 * * Tipo: int
 * * * n - indice da regiao segmentada
 * * * n_linhas, n_colunas - numero de linhas e colunas que imagem e area_seg têm
 * * Tipo: float*
 * * * media, c_media(count de numeros na media) - passa o endereco dessas variaveis
 * * Tipo: short int***
 * * * imagem, area_seg - passa os enderecos desses arrays 2D para q sempre esteje atualizado
 */
void segmentar(short int x, short int y, short int c, int n,int n_linhas, int n_colunas, float* media, float* c_media, short int*** imagem, short 
int*** area_seg){
    /*sementacao do ponto ao entar em segmentar*/
    (*area_seg)[x][y]=n;
    
    /*
     * as 4 regioes abaixo tem a mesma ideia, mudando os parametros:
     * o primeiro if verifica se existe o ponto e se ele ja foi ou nao segmentado
     * o segundo if verifica se o ponto a ser analisado(cima/direita/baixo/esquerda) faz parte da regiao segmentada
     * * se sim, ele calcula a nova media e adiciona mais um a c_media e chama a funcao no ponto que acabou de ser analisado
     */
    /*cima*/
    if(x>0 && (*area_seg)[x-1][y]==0){
        if(absoluto((*imagem)[x-1][y]-(*media))<=c){
            (*media) = ((*media)*(*c_media)+(*imagem)[x-1][y])/((*c_media)+1);
            (*c_media)++;
            segmentar(x-1,y,c,n,n_linhas,n_colunas,media,c_media,imagem,area_seg);
        }
    }
    
    /*direita*/
    if(y<n_colunas-1 && (*area_seg)[x][y+1]==0){
        if(absoluto((*imagem)[x][y+1]-(*media))<=c){
            (*media) = ((*media)*(*c_media)+(*imagem)[x][y+1])/((*c_media)+1);
            (*c_media)++;
            segmentar(x,y+1,c,n,n_linhas,n_colunas,media,c_media,imagem,area_seg);
        }
    }
    
    /*embaixo*/
    if(x<n_linhas-1 && (*area_seg)[x+1][y]==0){
        if(absoluto((*imagem)[x+1][y]-(*media))<=c){
            (*media) = ((*media)*(*c_media)+(*imagem)[x+1][y])/((*c_media)+1);
            (*c_media)++;
            segmentar(x+1,y,c,n,n_linhas,n_colunas,media,c_media,imagem,area_seg);
        }
    }
    
    /*esquerda*/
    if(y>0 && (*area_seg)[x][y-1]==0){
        if(absoluto((*imagem)[x][y-1]-(*media))<=c){
            (*media) = ((*media)*(*c_media)+(*imagem)[x][y-1])/((*c_media)+1);
            (*c_media)++;
            segmentar(x,y-1,c,n,n_linhas,n_colunas,media,c_media,imagem,area_seg);
        }
    }

}

int main(void){
    
    /*
     * variaveis utilizadas:
     * tipo: int
     * * n_analises - numero de pontos a ser analisados
     * * n_linhas - numero de linhas da imagem
     * * n_colunas - numero de colunas da imagem
     * tipo: short int
     * * x, y, c - parametros do ponto a ser analisado
     */
    int n_analises, n_linhas, n_colunas;
    short int x = 0, y = 0, c = 0;
    
    /*cria char* para armazenar o nome do arquivo*/
    char* nome_arquivo=aloca_array_char(15);
    /* recebe o nome do arquivo e ajusta o array retirando o \r */
    scanf("%s", nome_arquivo);
    if(nome_arquivo[strlen(nome_arquivo)-1]!='m'){
        nome_arquivo[strlen(nome_arquivo)-1]='\0';
    }
    
    /* abre o arquivo */
    FILE* arquivo = fopen(nome_arquivo,"r");
    
    /*
     * inform_inutil - tipo: char* - recebe as informacoes do arquivo que nao serao utilizadas
     */
    char* inform_inutil=aloca_array_char(5);
    
    /*escaneia as informacoes da imagem ate' chegar nos valores da imagem*/
    fscanf(arquivo, "%s", inform_inutil);
    fscanf(arquivo, "%d %d", &n_colunas, &n_linhas);
    fscanf(arquivo, "%s", inform_inutil);
    
    /*cria dois short int** - um para armazenar a imagem  e outro para criar a regiao segmentada*/
    short int** imagem = aloca_tabela(n_linhas, n_colunas);
    short int** area_seg = aloca_tabela(n_linhas, n_colunas);
    for(int i=0;i<n_linhas;i++){
        for(int j=0;j<n_colunas;j++){
            fscanf(arquivo, "%hi", &imagem[i][j]);
            area_seg[i][j]=0;
        }
    }
    
    /*fecha o arquivo*/
    fclose(arquivo);
    
    scanf("%d",&n_analises);
    /*
     * loop para analisar os pontos
     * se o ponto ja foi segmentado o loop vai para o proximo ponto
     */
    for(int i=0;i<n_analises;i++){
        scanf("%hi %hi %hi", &x, &y, &c);
        if(area_seg[x][y]==0){
            
            /*tipo float:
             * media - recebe o valor do ponto inicial
             * c_media - e' o contador de quantos numeros fazem parte da media */
            float media = imagem[x][y], c_media = 1;
            segmentar(x,y,c,i+1,n_linhas,n_colunas,&media,&c_media,&imagem,&area_seg);
        }
    }
    
    /*
     * algoritmo para comparar os elementos a volta dele e imprimir se um deles for diferente
     * aux - ponto a ser analisado
     * auxc - auxiliar de cima | auxb - auxiliar de baixo | auxe - auxiliar da esquerda | auxd - auxiliar da direita
     */
    int aux,auxc,auxd,auxe,auxb;
    for(int i = 0;i<n_linhas;i++){
        for(int j=0;j<n_colunas;j++){
            aux=area_seg[i][j];
            if(i>0){
                auxc=area_seg[i-1][j];
            } else {
                auxc = aux;
            }
            if(j>0){
                auxe=area_seg[i][j-1];
            } else {
                auxe=aux;
            }
            if(i<n_linhas-1){
                auxb=area_seg[i+1][j];
            } else {
                auxb=aux;
            }
            if(j<n_colunas-1){
                auxd=area_seg[i][j+1];
            } else {
                auxd=aux;
            }
            if(aux==auxb && aux==auxc && aux==auxd && aux==auxe){
            } else{
                printf("(%d, %d)\n", i, j);
            }
        }
    }
    
    /*
     * limberacao da memoria dinamica
     */
    free(nome_arquivo);
    free(inform_inutil);
    for(int i=0;i<n_linhas;i++){
        free(imagem[i]);
        free(area_seg[i]);
    }
    free(imagem);
    free(area_seg);
    
    return 0;
}
