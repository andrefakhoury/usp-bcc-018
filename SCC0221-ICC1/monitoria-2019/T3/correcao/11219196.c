#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    int linha;
    int coluna;
    float cr;
} pontos;

typedef struct
{
    float media;
    float soma;
    int cont;
} media;


void func_rec(int m, int n, float** img, int** map, int linha, int coluna, float cr, int r, media* retorno);

int main()
{
    int k, n, m, r=1;
    char arqname[40], lixo[4];
    scanf("%s", arqname);
    scanf("%d", &k);
    pontos *consult = malloc(k*sizeof(pontos));
    media retorno;
    for(int i=0; i<k; i++)
    {
        scanf("%d %d %f", &consult[i].linha, &consult[i].coluna, &consult[i].cr);
    }

    //inicio da leitura do arquivo de imagem
    FILE *arq = fopen(arqname, "r");
    fscanf(arq, "%s", lixo);
    fscanf(arq, "%d %d", &n, &m);
    fscanf(arq, "%*d");
    float **img = (float**)malloc(m*sizeof(float*));
    int **map = (int**)calloc(m,sizeof(int*));
    for(int i=0; i<m; i++)
    {
        img[i] = (float*)malloc(n*sizeof(float));
        map[i] = (int*)calloc(n,sizeof(int));
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            fscanf(arq, "%f", &img[i][j]);
        }
    }
    fclose(arq);
    //fim da leitura do arquivo de imagem

    //chamada da função recursiva
    for(int i=0; i<k; i++)
    {
        if (map[consult[i].linha][consult[i].coluna]==0)
        {
            retorno.media = img[consult[i].linha][consult[i].coluna]; //estado inicial da media para cada verificação
            retorno.soma = img[consult[i].linha][consult[i].coluna]; //estado incial da soma para cada verificação
            retorno.cont = 1; //estado inicial do contador de numeros que pertencem a regiao segmentada para cada verificacao
            map[consult[i].linha][consult[i].coluna]=r;
            func_rec(m, n, img, map, consult[i].linha, consult[i].coluna, consult[i].cr, r, &retorno);
            r++;
        }
    }

    /*
    Este bloco faz a verificacao das bordas e printa
    */
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if (i==0 && j==0 && (map[i][j] != map[i+1][j] || map[i][j] != map[i][j+1]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i==0 && j!=0 && j!=(n-1) && (map[i][j] != map[i+1][j] || map[i][j] != map[i][j-1] || map[i][j] != map[i][j+1]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i==0 && j==(n-1) && (map[i][j] != map[i+1][j] || map[i][j] != map[i][j-1]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i!=0 && i!=(m-1) && j==0 && (map[i][j] != map[i][j+1] || map[i][j] != map[i-1][j] || map[i][j] != map[i+1][j]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i!=0 && i!=(m-1) && j!=0 && j!=(n-1) && (map[i][j] != map[i+1][j] || map[i][j] != map[i-1][j] || map[i][j] != map[i][j+1] || map[i][j] != map[i][j-1]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i!=0 && i!=(m-1) && j==(n-1) && (map[i][j] != map[i-1][j] || map[i][j] != map[i+1][j] || map[i][j] != map[i][j-1]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i==(m-1) && j==0 && (map[i][j] != map[i-1][j] || map[i][j] != map[i][j+1]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i==(m-1) && j!=0 && j!=(n-1) && (map[i][j] != map[i-1][j] || map[i][j] != map[i][j-1] || map[i][j] != map[i][j+1]))
            {
                printf("(%d, %d)\n", i, j);
            }
            if (i==(m-1) && j==(n-1) && (map[i][j] != map[i-1][j] || map[i][j] != map[i][j-1]))
            {
                printf("(%d, %d)\n", i, j);
            }
        }
    }

    //liberacao das matrizes e da struct alocadas dinamicamente
    free(consult);
    for(int i=0; i<m; i++)
    {
        free(img[i]);
        free(map[i]);
    }
    free(img);
    free(map);
}

/*
Funcao recursiva:
-se divide em 4 condicionais que indicam a direcao a ser verificada na seguinte ordem:
    -cima
    -direita
    -baixo
    -esquerda
-a cada condicional a funcao e chamada novamente e faz as atualizacoes de variaveis necessarias
*/
void func_rec(int m, int n, float** img, int** map, int linha, int coluna, float cr, int r, media* retorno)
{

    /*
    Em cada um dos condicionais temos as seguintes acoes:
    -atualizacao da soma
    -atualizacao do contador
    -atualizacao da media
    -atualizacao do mapeamento
    -chamada recursiva da funcao
    */

    if((linha-1)>=0 && fabs(img[linha-1][coluna] - retorno->media) <= cr && map[linha-1][coluna] == 0)
    {
        retorno->soma += img[linha-1][coluna];
        retorno->cont++;
        retorno->media = retorno->soma/retorno->cont;
        map[linha-1][coluna] = r;
        func_rec(m, n, img, map, linha-1, coluna, cr, r, retorno);
    }
    if((coluna+1)<n && fabs(img[linha][coluna+1] - retorno->media) <= cr && map[linha][coluna+1] == 0) // direita
    {
        retorno->soma += img[linha][coluna+1];
        retorno->cont++;
        retorno->media = retorno->soma/retorno->cont;
        map[linha][coluna+1] = r;
        func_rec(m, n, img, map, linha, coluna+1, cr, r, retorno);
    }
    if((linha+1)<m && fabs(img[linha+1][coluna] - retorno->media) <= cr && map[linha+1][coluna] == 0) // baixo
    {
        retorno->soma += img[linha+1][coluna];
        retorno->cont++;
        retorno->media = retorno->soma/retorno->cont;
        map[linha+1][coluna] = r;
        func_rec(m, n, img, map, linha+1, coluna, cr, r, retorno);
    }
    if((coluna-1)>=0 && fabs(img[linha][coluna-1] - retorno->media) <= cr && map[linha][coluna-1] == 0) // esquerda
    {
        retorno->soma += img[linha][coluna-1];
        retorno->cont++;
        retorno->media = retorno->soma/retorno->cont;
        map[linha][coluna-1] = r;
        func_rec(m, n, img, map, linha, coluna-1, cr, r, retorno); 
    }
    return;
}