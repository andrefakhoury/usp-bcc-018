#include "img.h"

int main(void){
    char nome_arq[20];
    int indice_regiao = 1;
    int quant_consultas = 0;
    imagem img, imgSegmentada;
    struct_media media;

    scanf("%[^\n\r]s", nome_arq);

    img = lerArquivo(nome_arq);

    scanf("%d", &quant_consultas);

    imgSegmentada.matriz = alocarMemoriaCalloc(img.num_linhas, img.num_colunas);
    imgSegmentada.num_linhas = img.num_linhas;
    imgSegmentada.num_colunas = img.num_colunas;

    /*Esse bloco le as entradas e, se a posição ainda não foi segmentada, 
      chama a funcao segmentarImagem incrementando o indice_regiao a cada consulta*/
    for(int i = 0; i < quant_consultas; i++)
    {
        int x, y, criterio;
        scanf("%d %d %d", &x, &y, &criterio);
        if (x >= 0 && x < img.num_linhas && y >= 0 && y < img.num_colunas)
            if (imgSegmentada.matriz[x][y] == 0)
            {
                media.qtd_segmentos = 0;
                media.soma = 0;
                media.resultado = 0;

                imgSegmentada = segmentarImagem(img, imgSegmentada, x, y, &media, criterio, indice_regiao++);
            }
    }

    imprimirBordas(imgSegmentada);

    liberarMemoria(img.matriz, imgSegmentada.matriz);

    return 0;
}