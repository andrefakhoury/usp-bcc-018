#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/**
 *  readFile():
 *      -char *filename: nome do arquivo com a imagem;
 *      -int *sizeX, *sizeY: enderecos para armarzenar as dimensoes da imagem;
 *  
 *  Retorna o endereco para a matriz referente aos pixels da imagem.
**/
int **readFile(char *filename, int *sizeX, int *sizeY){
    FILE *image = NULL;

    image = fopen(filename, "r"); 

    fscanf(image, "P2\n");
    fscanf(image, "%d %d\n", sizeY, sizeX);
    fscanf(image, "255\n");

    int **img = malloc(*sizeX*sizeof(int*));
    for(int i=0; i<*sizeX; i++){
        img[i] = malloc(*sizeY*sizeof(int));
    }

    for(int i=0; i<*sizeX; i++){
        for(int j=0; j<*sizeY; j++){
            fscanf(image, "%d", &img[i][j]);
        }
    }

    fclose(image);

    return img;
}


/**
 *  busca():
 *      -int x, y: coordenadas do pixel;
 *      -int c: criterio;
 *      -int sizeX, sizeY: dimensoes da imagem;
 *      -int ***pixel: endereco da matrix referente aos pixels da imagem;
 *      -int ***region: endereco da matriz onde sera guardada a regiao de cada pixel;
 *      -int *region_size: endereco da variavel com o tamanho atual da regiao sendo processada;
 *      -int *soma: endereco da variavel com a soma dos valores de todos os pixels pertencentes a regiao no momento;
 *      -int *X, *Y: endereco dos vetores para facilitar a checkagem nos vizinhos;
 * 
 *  Faz uma busca em profundidade de pixels que pertencam a mesma regiao.
**/
void busca(int x, int y, int c, int sizeX, int sizeY, int ***pixel, int ***region, int *region_size, int *soma, int *X, int *Y){

    for(int i=0; i<4; i++){
        if(x + X[i] >=0 && x + X[i] < sizeX && y + Y[i] >=0 && y + Y[i] < sizeY){
            
            /**
             *  Para eliminar a imprecisao de utilizar numeros reais,
             *  ao inves de utilizar:
             *      |valor_do_pixel - media| <= criterio
             *  Foi utilizado:
             *      |valor_do_pixel * tam_da_regiao - soma| <= criterio * tam_da_regiao
            **/
            if(abs((*pixel)[x+X[i]][y+Y[i]]*(*region_size) - *soma) <= c*(*region_size) && (*region)[x+X[i]][y+Y[i]] == -1){
                (*region)[x+X[i]][y+Y[i]] = (*region)[x][y];

                *soma = *soma + (*pixel)[x+X[i]][y+Y[i]];

                (*region_size)++;

                busca(x+X[i], y+Y[i], c, sizeX, sizeY, pixel, region, region_size, soma, X, Y);
            }
        }
    }
    
}


/**
 *  processTouches():
 *      -char* filename: nome do arquivo com a imagem;
 *      -int *sizeX, *sizeY: enderecos para armarzenar as dimensoes da imagem;
 *  
 *  Retorna o endereco para a matriz com a regiao de cada pixel.
**/
int **processTouches(char *filename, int *sizeX, int *sizeY){
    int **pixel = NULL; //guarda o valor de cada pixel.
    int **region = NULL; //guarda a regiao a que o pixel pertence, region[i][j] = -1 se o pixel (i, j) nao pertencer a nenhuma regiao ainda.

    int num_touches = 0;
    int *x = NULL, *y = NULL; //guardam as coordenadas de cada toque.
    int *c = NULL; //guarda o criterio de cada toque. 


    pixel = readFile(filename, sizeX, sizeY);

    region = malloc(*sizeX*sizeof(int*));
    for(int i=0; i<*sizeX; i++){
        region[i] = malloc(*sizeY*sizeof(int));
        memset(region[i], -1, *sizeY*sizeof(int));
    }
    

    scanf("%d", &num_touches);

    x = malloc(num_touches*sizeof(int));
    y = malloc(num_touches*sizeof(int));
    c = malloc(num_touches*sizeof(int));

    for(int i=0; i<num_touches; i++){
        scanf("%d %d %d", &x[i], &y[i], &c[i]);
    }


    /**
     *  Vetores para auxiliar a olhar os vizinhos:
     *      (x+X[i], y+Y[i]) de i: 0->3, sao os deslocamentos respectivamente
     *      para cima, direita, baixo e esquerda.     
    **/
    int *X = malloc(4*sizeof(int));
    X[0] = -1, X[1] = 0, X[2] = 1, X[3] = 0;
    int *Y = malloc(4*sizeof(int));
    Y[0] = 0, Y[1] = 1, Y[2] = 0, Y[3] = -1;

    /**
     *  Processa cada toque e realiza a busca caso o pixel selecionado
     *  ainda nao pertenca a um regiao. 
    **/
    for(int i=0; i<num_touches; i++){
        if(region[x[i]][y[i]] != -1) continue;

        int region_size = 1;
        int soma = pixel[x[i]][y[i]];
        region[x[i]][y[i]] = i;

        busca(x[i], y[i], c[i], *sizeX, *sizeY, &pixel, &region, &region_size, &soma, X, Y);
    }


    free(x);
    free(y);
    free(c);
    free(X);
    free(Y);
    for(int i=0; i<*sizeX; i++){
        free(pixel[i]);
    }
    free(pixel);


    return region;
}


/**
 *  printBorders():
 *      -int **segmentedImg: matriz com a regiao de cada pixel;
 *      -int sizeX, sizeY: dimensoes da imagem;
**/
void printBorders(int **segmentedImg, int sizeX, int sizeY){
    //Vetores para auxiliar a olhar os vizinhos.
    int *X = malloc(4*sizeof(int));
    X[0] = -1, X[1] = 0, X[2] = 1, X[3] = 0;
    int *Y = malloc(4*sizeof(int));
    Y[0] = 0, Y[1] = 1, Y[2] = 0, Y[3] = -1;


    for(int x=0; x<sizeX; x++){
        for(int y=0; y<sizeY; y++){
            for(int k=0; k<4; k++){
                if(x + X[k] >=0 && x + X[k] < sizeX && y + Y[k] >=0 && y + Y[k] < sizeY){
                    if(segmentedImg[x+X[k]][y+Y[k]] != segmentedImg[x][y]){
                        printf("(%d, %d)\n", x, y);
                        
                        break;
                    }
                }
            }
        }
    }


    free(X);
    free(Y);
}


int main(){
    char *filename = NULL;

    int **segmentedImg = NULL;
    int sizeX = 0, sizeY = 0;


    filename = malloc(15);
    scanf("%s", filename);


    segmentedImg = processTouches(filename, &sizeX, &sizeY);    


    printBorders(segmentedImg, sizeX, sizeY);


    free(filename);
    for(int i=0; i<sizeX; i++){
        free(segmentedImg[i]);
    }
    free(segmentedImg);

    return 0;
}