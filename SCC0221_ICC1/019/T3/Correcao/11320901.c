#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Alocacao dinamica e liberacao de memoria
void aloca(int**matriz,int altura, int largura) //Funcao que aloca a memoria para os vetores das matrizes
{
    for(int i=0;i<altura;i++)
    {
        matriz[i] = malloc(largura*sizeof(int));
    }
}

void desaloca(int**matriz,int altura) //Funcao que libera memoria guardada para as vetores das matrizes 
{ 
    for(int i=0;i<altura;i++)
    {
        free(matriz[i]);
    }
}
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
void flmatriz(FILE* fp,int largura,int altura,int*** matriz) // Guarda os valores do arquivo em uma matriz
{
    int flag = 1;
    while(flag != EOF)
    {
        for(int i = 0;i<altura;i++)
        {
            for(int j=0;j<largura;j++)
            {
                flag = fscanf(fp,"%d",&((*matriz)[i][j])); // Armazena todos
            }
        }
    }
}
//------------------------------------------------------------------
void printMatriz(int**matriz,int largura,int altura) //Mostra todos os elementos da matriz
{
    for(int i=0;i<altura;i++)
    {
        for(int j=0;j<largura;j++)
        {
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}
//-----------------------------------------------------------------
float media(float accum,float count)
{
    return accum/count;
}
void andaMat(int*** matriz, int linha,int coluna,float* count, int criterio, float* accum, int largura,int altura, int i)
{
    if ((*matriz)[linha][coluna] < 0) return;
    *accum += (float)(*matriz)[linha][coluna];
    *count += 1;
    //printf("(%d,",linha);
    //printf("%d) \n",coluna);
    //printf("%d \n",(*matriz)[linha][coluna]);
    (*matriz)[linha][coluna] = -1*i;
    if(linha-1 >= 0 && fabs((float)(*matriz)[linha-1][coluna] - media(*accum,*count)) <= criterio && (*matriz)[linha-1][coluna] > 0 )
    {
        andaMat(matriz,linha-1,coluna,count,criterio,accum,largura,altura,i);
    }
    if(coluna+1 < largura && fabs((float)(*matriz)[linha][coluna+1]-media(*accum,*count)) <= criterio && (*matriz)[linha][coluna+1] > 0)
    {
        andaMat(matriz,linha,coluna+1,count,criterio,accum,largura,altura,i);
    }
    if(linha+1 < altura && fabs((float)(*matriz)[linha+1][coluna] - media(*accum,*count)) <= criterio && (*matriz)[linha+1][coluna] > 0)
    {
        andaMat(matriz,linha+1,coluna,count,criterio,accum,largura,altura,i);
    }
    if(coluna-1 >= 0 && fabs((float)(*matriz)[linha][coluna-1]-media(*accum,*count)) <= criterio && (*matriz)[linha][coluna-1] > 0)
    {
        andaMat(matriz,linha,coluna-1,count,criterio,accum,largura,altura,i);
    }
}

int main(int argc, char* argv[])
{
    //Declaracao de variaveis
    char* flname;
    flname = malloc(20*sizeof(char));
    int times;
    int** matriz;
    int altura, largura,byte; 
    float count =1;
    char* trash;
    trash = malloc(20*sizeof(char));

    //Entrada do nome da imagem do teste;
    scanf("%s",flname);
    getchar();
    scanf("%d",&times);
    //Abrindo arquivo e fazendo a leitura para armazenar numa matriz;
    FILE* fp = fopen(flname,"r");
    fscanf(fp,"%s %d %d %d",trash,&largura,&altura,&byte);
    matriz = malloc(altura*sizeof(int*));
    aloca(matriz,altura,largura);
    flmatriz(fp,largura,altura,&matriz);
    //printf("leitura \n");
    //printMatriz(matriz,largura,altura);
    //printf("\n");
    //printf("\n");
    
    //-------------------------------------------------------------//
    

        
    float accum = 0;
    int linha, coluna,criterio;
    for(int i =0;i < times;i++)
    {
        scanf("%d %d %d",&linha,&coluna,&criterio);
        accum = 0;
        count = 0;
        andaMat(&matriz,linha,coluna,&count,criterio,&accum,largura,altura,i+1);
        //printMatriz(matriz,largura,altura);
        //printf("\n");
    }
    for(int j=0;j<altura;j++)
    {
        for(int k =0;k<largura;k++)
        {
            int borda = 0;

            int aux = matriz[j][k] < 0 ? -matriz[j][k] : 0;

            if (j-1 >= 0) {
                int aux1 = matriz[j-1][k] < 0 ? -matriz[j-1][k] : 0;
                if (aux != aux1) borda = 1;
            }

            if (k-1 >= 0) {
                int aux1 = matriz[j][k-1] < 0 ? -matriz[j][k-1] : 0;
                if (aux != aux1) borda = 1;
            }

            if (j+1 < altura) {
                int aux1 = matriz[j+1][k] < 0 ? -matriz[j+1][k] : 0;
                if (aux != aux1) borda = 1;
            }

            if (k+1 < largura) {
                int aux1 = matriz[j][k+1] < 0 ? -matriz[j][k+1] : 0;
                if (aux != aux1) borda = 1;
            }

            if (borda) printf("(%d, %d)\n", j, k);
        }
    }
    
    
    
    
    
    //------------------------ liberar memoria -------------------//
    free(flname);
    free(trash);
    desaloca(matriz,altura);
    free(matriz);
    fclose(fp);
    return 0;
}