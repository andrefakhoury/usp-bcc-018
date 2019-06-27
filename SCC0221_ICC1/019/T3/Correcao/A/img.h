#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct _imagem{
    int **matriz;
    int num_linhas;
    int num_colunas;
} imagem;

typedef struct _media{
    int soma;
    int qtd_segmentos;
    float resultado;
} struct_media;

int **alocarMemoriaMalloc(int num_linhas, int num_colunas);
int **alocarMemoriaCalloc(int num_linhas, int num_colunas);
imagem lerArquivo(const char *nome_arq);
bool isValido(int pixel, float media, int criterio, int regiao);
imagem segmentarImagem(imagem img, imagem imgSegmentada, int x, int y, struct_media *media, int criterio, int indice_regiao);
void imprimirBordas(imagem imgSegmentada);
void liberarMemoria(int **imagem, int **imagemSegmentada);
void finalizarPrograma();
