#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void varedura(int **pixels, int **mnew, int x, int y, float criterio, int c, int l, int i, float *media, int* aux){  //função para ocorrer a varedura da imagem para sua segmentação (através de recursão)
    float compara;  //variável para comparar com o critério

    if(mnew[x][y] != 0){ //se já foi conquistado, não faz a recursão
        return;
    }
    
    else{

        mnew[x][y] = i + 1; //conquista
        
        //verificação pixel de cima
        if(x-1 >= 0) { //verifica se o pixel adjacente existe
            compara = pixels[x - 1][y] - *media; //valor a ser comparado com com o critério
            compara = fabs(compara); //módulo para fazer a comparação com o critério 
            if(compara <= criterio && mnew[x - 1][y] == 0){ //caso o pixel de cima atende ao critério e ainda não foi dominado, entra na recursão
                *media = *media * *aux; 
                *aux = *aux + 1;
                *media = (*media + pixels[x - 1][y])/(*aux); //alteração da média para a recursão
                varedura(pixels, mnew, x - 1, y, criterio, c, l, i, media, aux); //entrar na recursão
            }
        }

        //verificação pixel da direita
        if(y+1 < c){ //verifica se o pixel adjacente existe
            compara = pixels[x][y + 1] - *media; //valor a ser comparado com com o critério
            compara = fabs(compara);  //módulo para fazer a comparação com o critério
            if(compara <= criterio && mnew[x][y + 1] == 0){ //caso o pixel de cima atende ao critério e ainda não foi dominado, entra na recursão
                *media = *media * *aux;
                *aux = *aux + 1;
                *media = (*media + pixels[x][y + 1])/(*aux); //alteração da média para a recursão
                varedura(pixels, mnew, x, y + 1, criterio, c, l, i, media, aux); //entrar na recursão
            }
        }
        
        //verificação pixel debaixo
        if(x+1 < l){ //verifica se o pixel adjacente existe
            compara = pixels[x + 1][y] - *media; //valor a ser comparado com com o critério
            compara = fabs(compara); //módulo para fazer a comparação com o critério
            if(compara <= criterio && mnew[x + 1][y] == 0){ //caso o pixel de cima atende ao critério e ainda não foi dominado, entra na recursão
                *media = *media * *aux;
                *aux = *aux + 1;
                *media = (*media + pixels[x + 1][y])/(*aux); //alteração da média para a recursão
                varedura(pixels, mnew, x + 1, y, criterio, c, l, i, media, aux); //entrar na recursão
            }
        }
        
        //verificação pixel da esquerda
        if(y-1 >= 0){ //verifica se o pixel adjacente existe
            compara = pixels[x][y - 1] - *media; //valor a ser comparado com com o critério
            compara = fabs(compara); //módulo para fazer a comparação com o critério
            if(compara <= criterio && mnew[x][y - 1] == 0){  //caso o pixel de cima atende ao critério e ainda não foi dominado, entra na recursão
                *media = *media * *aux;
                *aux = *aux + 1;
                *media = (*media + pixels[x][y - 1])/(*aux); //alteração da média para a recursão
                varedura(pixels, mnew, x, y - 1, criterio, c, l, i, media, aux); //entrar na recursão
            }
        }
    }
    return;
}


void saida(int **m, int l, int c){ //função para imprimir as bordas das áreas segmentadas
    int count; //variável de contagem para caso um pixel seja diferente de um adjacente 
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            count = 0;
            if(i > 0){ 
                if(m[i - 1][j] != m[i][j]){ //verificação pixel de cima
                    count++;
                }
            }
            if(j+1 < c){ 
                if(m[i][j + 1] != m[i][j]){ //verificação pixel da direita
                    count++;
                }
            }
            if(i+1 < l){ 
                if(m[i + 1][j] != m[i][j]){ //verificação pixel de baixo
                    count++;
                }
            }
            if(j > 0){ 
                if(m[i][j - 1] != m[i][j]){ //verficação pixel da esquerda
                    count++;
                }
            }
            if(count != 0){ //caso algum pixel seja diferente de seu adjacente, ele está na borda da área seqmentada
                printf("(%d, %d)\n", i, j); //impressão do pixel de borda
            }
        }
    }
    return;
}


int main (void){
    int casos; // para leitura do número casos
    char* nomearq = malloc(50*sizeof(char));
    int **mp; //matriz com os pixels
    int **mnew; //matriz com as áreas segmentadas
    int l, c; //l representa linhas e c colunas do arquivo
    float media; //media pra passar para comparação de pixels na função varedura
    int aux; //auxiliar para media
    FILE* imagem;

    scanf("%s", nomearq); //leitura do nome do arquivo pmg 
    
    //alocação de memória para a matriz de pixels
    imagem = fopen(nomearq, "r"); //abertura do arquivo para leitura

    char trash[10]; //para a leitura do P2 inútil
    fscanf(imagem, "%s", trash);
    fscanf(imagem, "%d %d", &c, &l); //lendo as linhas e colunas do arquivo
    
    //alocação de memória para a matriz de pixels
    mp = (int **) malloc(l * sizeof(int*)); 
    for(int i = 0; i < l; i++){
        mp[i] = (int *) malloc(c * sizeof(int));
    }

    int trashint; //variável para lixo da terceira linha do arquivo
    fscanf(imagem, "%d", &trashint);
    
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            fscanf(imagem, "%d", &mp[i][j]); //matriz de pixels
        }
    }

    fclose(imagem);  //fechando o arquivo

    //alocação de memória para a matriz de borda
    mnew = (int **) malloc(l * sizeof(int*)); //obs.: esse int pode ser short
    for(int i = 0; i < l; i++){
        mnew[i] = (int *) malloc(c * sizeof(int));
    } 

    //matriz p reconhecer a borda
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            mnew[i][j] = 0;
        }
    }

    scanf("%d", &casos);  //número de toques do usuário

    for(int i = 0; i < casos; i++){
        int x, y; //coordenadas fornecidas pelo usuário
        float cr; //critério fornecido pelo usuário
        scanf("%d %d", &x, &y);  //leitura das coordenadas
        scanf("%f", &cr); //leitura do critério
        aux = 1;  //auxiliar para calcular a média
        media = mp[x][y];  //media para fazer o cálculo fo critério
        varedura(mp, mnew, x, y, cr, c, l, i, &media, &aux); //função para segmentar
    }

    saida(mnew, l, c);  //função para imprimir saída

    //liberar memória das matrizes
    for(int i = 0; i < l; i++){
        free(mnew[i]);
        free(mp[i]);
    }
    free(mnew);
    free(mp);
    free(nomearq);

    return 0;
}