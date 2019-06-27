#include "img.h"

int **alocarMemoriaMalloc(int num_linhas, int num_colunas){
    /* Aloca memoria para uma matriz de m linhas e n colunas de forma dinamica utilizando malloc */

    int **matriz = (int **) malloc(num_linhas * sizeof(int *));
    
    if (matriz == NULL)
    {
        finalizarPrograma();
    }

    for (int i = 0; i < num_linhas; i++)
    {
        matriz[i] = (int *) malloc(num_colunas * sizeof(int));

        if (matriz[i] == NULL)
        {
            finalizarPrograma();
        }
    }

    return matriz;
}

int **alocarMemoriaCalloc(int num_linhas, int num_colunas){
    /* Aloca memoria para uma matriz de m linhas e n colunas de forma dinamica utilizando calloc, 
        uma vez que pretende-se inicializar a matriz de segmentos com zero */

    int **matriz = (int **) calloc(num_linhas, sizeof(int *));

    if (matriz == NULL)
    {
        finalizarPrograma();
    }

    for (int i = 0; i < num_linhas; i++)
    {
        matriz[i] = (int *) calloc(num_colunas, sizeof(int));

        if (matriz[i] == NULL)
        {
            finalizarPrograma();
        }
    }

    return matriz;
}

void finalizarPrograma(){
    /* Retorna erro em caso de falha de leitura do arquivo ou de alocação de memoria */

    printf("\nErro\n");
	exit(1);
}

imagem lerArquivo(const char *nome_arq){
    /* Le o arquivo .pgm e armazena os valores de linha, de coluna e da matriz de pixels, retornando a imagem */

    FILE *arq_img = NULL;
    int aux = 0; //aux armazena o pixel de cada posicao da matriz
    int cont = 1; //cont armazena a quantidade de linhas do arquivo
    imagem img;
    int i = 0, j = 0;

    arq_img = fopen(nome_arq, "r");

    if (arq_img == NULL)
    {
        finalizarPrograma();
    }

    while (!feof(arq_img))
    {
        if (getc(arq_img) == '\n')
        {
            cont++;
        }

        if (cont == 2)
        {

            fscanf(arq_img, "%d %d", &img.num_colunas, &img.num_linhas);
            img.matriz = alocarMemoriaMalloc(img.num_linhas, img.num_colunas);

        }else{

            if (cont > 3)
            {
                for (int i = 0; i < img.num_linhas; i++)
                {
                    for (int j = 0; j < img.num_colunas; j++)
                    {
                        fscanf(arq_img, "%d", &aux);
                        img.matriz[i][j] = aux;
                    }
                }
                
                break;
            }
        } 
    }

    fclose(arq_img);

    return img;
}

bool isValido(int pixel, float media, int criterio, int regiao){
    /* Se a mesma posicao na matriz de segmentos tiver valor zero, isto é, ainda não for segmentada, 
       verifica se |pixel - media| é menor ou igual ao criterio */

    if (regiao == 0)
    {
        if (fabs(pixel - media) <= criterio)
        {

            return true;
        }
    }
    
    return false;
}

imagem segmentarImagem(imagem img, imagem imgSegmentada, int x, int y, struct_media *media, int criterio, int indice_regiao){
    /* Segmenta, recursivamente, a imagem em regioes verificando todos os vizinhos das coordenadas (x,y) de entrada e dos vizinhos subsequentes */
    
    int pixel = 0, regiao = 0;
    
    /* Esse bloco atualiza a recursao, preenchendo com um numero inteiro maior do que zero a matriz de segmentos, e resolvendo a media */
    media->soma += img.matriz[x][y];
    media->qtd_segmentos++;
    media->resultado = (float) media->soma / media->qtd_segmentos;
    imgSegmentada.matriz[x][y] = indice_regiao;   
    
    //Verifica o vizinho acima
    if (x > 0)
    {
        pixel = img.matriz[x-1][y];
        regiao = imgSegmentada.matriz[x-1][y];

        if (isValido(pixel, media->resultado, criterio, regiao))
        {
            imgSegmentada = segmentarImagem(img, imgSegmentada, x - 1, y, media, criterio, indice_regiao);
        }
    }

    //Verifica o vizinho à direita
    if (y < img.num_colunas - 1)
    {
        pixel = img.matriz[x][y+1];
        regiao = imgSegmentada.matriz[x][y+1];
        
        if (isValido(pixel, media->resultado, criterio, regiao))
        {    
             imgSegmentada = segmentarImagem(img, imgSegmentada, x, y + 1, media, criterio, indice_regiao);
        }
    }

    //Verifica o vizinho abaixo
    if (x < img.num_linhas - 1)
    {
        pixel = img.matriz[x+1][y];
        regiao = imgSegmentada.matriz[x+1][y];
       
        if (isValido(pixel, media->resultado, criterio, regiao))
        {
            imgSegmentada = segmentarImagem(img, imgSegmentada, x + 1, y, media, criterio, indice_regiao);
        }
    }

    //Verifica o vizinho à esquerda
    if (y > 0)
    {
        pixel = img.matriz[x][y-1];
        regiao = (imgSegmentada).matriz[x][y-1];
         
        if (isValido(pixel, media->resultado, criterio, regiao))
        {
             imgSegmentada = segmentarImagem(img, imgSegmentada, x, y - 1, media, criterio, indice_regiao);
        }
    }

    //A condicao de parada da recursao é quando nao houver mais nenhum vizinho a segmentar
    return imgSegmentada;
}

void imprimirBordas(imagem imgSegmentada){
    /* Imprime as coordenadas das bordas da imagem segmentada, a partir da verificacao em cada pixel se existe algum vizinho de outra regiao */

    for (int i = 0; i < imgSegmentada.num_linhas; i++)
    {
        for (int j = 0; j < imgSegmentada.num_colunas; j++)
        {
            int region = imgSegmentada.matriz[i][j];

            //Inicializa todos os vizinhos com o mesmo valor de regiao do pixel analisado, para desconsiderar vizinhos invalidos (que ultrapassam o range da matriz)
            int region_up = region, region_down = region, region_left = region, region_right = region;

            if (i > 0) 
                region_up = imgSegmentada.matriz[i-1][j];
            
            if (j < imgSegmentada.num_colunas - 1) 
                region_right = imgSegmentada.matriz[i][j+1];
            
            if (i < imgSegmentada.num_linhas - 1) 
                region_down = imgSegmentada.matriz[i+1][j];
            
            if (j > 0) 
                region_left = imgSegmentada.matriz[i][j-1];

            if (region != region_up || region != region_down || region != region_left || region != region_right)
            {
                printf("(%d, %d)\n",i,j);
            }
        }
    }
}

void liberarMemoria(int **imagem, int **imagemSegmentada){
    /*Libera memoria das duas matrizes alocadas*/
    free(imagem);
    free(imagemSegmentada);
}