#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct _ponto{
    int linha;
    int coluna;
}ponto;

typedef struct __medpontos{
    double media;
    double soma;
    double n_seg;
}Smedia;

char* leitura_inicial(int *n);
int**  abrir_arquivo(char *nome_arquivo,int *linhas,int *colunas);
int** aloca_int(int linhas,int colunas,int n);
void repeticao(int n,int **imagem,int **imagem_segmentada,int linhas,int colunas);
Smedia segmentacao(int **imagem,int **imagem_segmentada,ponto inicio,int criterio,int regiao,int linhas,int colunas,Smedia inicial);
void borda(int **imagem_segmentada,int linhas,int colunas);
void limpar(int **matriz,int linhas,int colunas);

char* leitura_inicial(int *n)
{
    char* nome_arquivo;
    scanf(" %ms",&nome_arquivo); //FREE
    scanf("%d",n);
    return nome_arquivo;
}

int**  abrir_arquivo(char *nome_arquivo,int *linhas,int *colunas)
{
    FILE *arquivo;
    int **imagem,i,j;
    if((arquivo = fopen(nome_arquivo,"r"))==NULL)
    {
        printf("Erro na abertura!\n");
        exit(1);
    }

    fscanf(arquivo,"%*s %d %d %*d",colunas,linhas);

    imagem = aloca_int(*linhas,*colunas,0);

    //imagem = (int**) malloc(sizeof(int*)*(*linhas)); /

    //for(i=0;i<*linhas;i++)
    //{
    //    imagem[i]= (int*) malloc(sizeof(int)*(*colunas)); 
    //}

    for(i=0;i<*linhas;i++)
    {
        for(j=0;j<*colunas;j++)
        {
            fscanf(arquivo,"%d",&imagem[i][j]);
            //printf("%d ",imagem[i][j]);
        }
        //printf("\n");
    }

    fclose(arquivo);
    return imagem;
}

int** aloca_int(int linhas,int colunas,int n)
{
    int **matriz;
    int i,j;
    matriz = (int**) malloc(sizeof(int*)*linhas);

    for(i=0;i<linhas;i++)
    {
        matriz[i]= (int*) malloc(sizeof(int)*colunas);
    }

    if(n==1)
    {
        for(i=0;i<linhas;i++)
        {
            for(j=0;j<colunas;j++)
            {
                matriz[i][j]=0;
            }
        }
    }

    return matriz;
}

void repeticao(int n,int **imagem,int **imagem_segmentada,int linhas,int colunas)
{
    int i;
    ponto inicio;
    int criterio;
    Smedia dados;


    for(i=1;i<=n;i++)
    {
        scanf("%d %d %d",&inicio.linha,&inicio.coluna,&criterio);
        dados.soma=0;
        dados.n_seg = 0;
        segmentacao(imagem,imagem_segmentada,inicio,criterio,i,linhas,colunas,dados);
    }
    return;
}

Smedia segmentacao(int **imagem,int **imagem_segmentada,ponto inicio,int criterio,int regiao,int linhas,int colunas,Smedia dados)
{
    ponto prox;
   // printf("%d %d %d\n",inicio.linha,inicio.coluna,criterio);
    if(imagem_segmentada[inicio.linha][inicio.coluna]==0)
    {
        imagem_segmentada[inicio.linha][inicio.coluna]=regiao;
      //  printf("a media eh %.4lf no ponto %d %d\n",dados.media,inicio.linha,inicio.coluna);
        dados.n_seg++;
        dados.soma+=imagem[inicio.linha][inicio.coluna];
        dados.media = dados.soma/dados.n_seg;
      //  printf("%lf\n",dados.media);
        if(inicio.linha!=0)
        {
          //  printf("o ponto %d %d analisou o de cima\n",inicio.linha,inicio.coluna);
            if(fabs(imagem[inicio.linha-1][inicio.coluna] - dados.media) <= criterio && imagem_segmentada[inicio.linha-1][inicio.coluna]==0)
            {
                prox.linha=inicio.linha-1;
                prox.coluna=inicio.coluna;
                dados = segmentacao(imagem,imagem_segmentada,prox,criterio,regiao,linhas,colunas,dados);
            }   
        }
        dados.media = dados.soma/dados.n_seg;
       // printf("a media eh %.4lf no ponto %d %d depos de ver cima\n",dados.media,inicio.linha,inicio.coluna);
        if(inicio.coluna!=colunas-1)
        {
           // printf("o ponto %d %d analisou o da direita\n",inicio.linha,inicio.coluna);
            if (fabs(imagem[inicio.linha][inicio.coluna+1] - dados.media) <= criterio && imagem_segmentada[inicio.linha][inicio.coluna+1]==0)
            {
                prox.linha=inicio.linha;
                prox.coluna=inicio.coluna+1;
                dados = segmentacao(imagem,imagem_segmentada,prox,criterio,regiao,linhas,colunas,dados);
            }
            
        }
        dados.media = dados.soma/dados.n_seg;
       // printf("a media eh %.4lf no ponto %d %d depos de ver direita\n",dados.media,inicio.linha,inicio.coluna);
        if(inicio.linha!=linhas-1)
        {
           // printf("o ponto %d %d analisou o de baixo\n",inicio.linha,inicio.coluna);
            if (fabs(imagem[inicio.linha+1][inicio.coluna] - dados.media) <= criterio && imagem_segmentada[inicio.linha+1][inicio.coluna]==0)
            {
                prox.linha=inicio.linha+1;
                prox.coluna=inicio.coluna;
                dados = segmentacao(imagem,imagem_segmentada,prox,criterio,regiao,linhas,colunas,dados);
            }
        }
        dados.media = dados.soma/dados.n_seg;
     //   printf("a media eh %.4lf no ponto %d %d depos de ver baixo\n",dados.media,inicio.linha,inicio.coluna);
        if(inicio.coluna!=0)
        {
         //   printf("o ponto %d %d analisou o da esquerda\n",inicio.linha,inicio.coluna);
            if (fabs(imagem[inicio.linha][inicio.coluna-1] - dados.media) <= criterio && imagem_segmentada[inicio.linha][inicio.coluna-1]==0)
            {
                prox.linha=inicio.linha;
                prox.coluna=inicio.coluna-1;
                dados = segmentacao(imagem,imagem_segmentada,prox,criterio,regiao,linhas,colunas,dados);
            }
        }
        dados.media = dados.soma/dados.n_seg;
      //  printf("a media eh %.4lf no ponto %d %d depos de ver esquerda\n",dados.media,inicio.linha,inicio.coluna);
    }
  //  printf("o ponto %d %d retornou %lf de media\n",inicio.linha,inicio.coluna,dados.media);
    return dados;
}

void borda(int **imagem_segmentada,int linhas,int colunas)
{
    int i,j;
    bool foi = false;

    for(i=0;i<linhas;i++)
    {
        for(j=0;j<colunas;j++)
        {
            foi=false;
            if(i!=0)
            {
                if(imagem_segmentada[i-1][j]!=imagem_segmentada[i][j])
                {
                    foi=true;            
                    printf("(%d, %d)\n",i,j);            
                }
            }
            if(j!=colunas-1 && foi==false)
            {
                if(imagem_segmentada[i][j+1]!=imagem_segmentada[i][j])
                {
                    foi=true;
                    printf("(%d, %d)\n",i,j);              
                }
            } 
            if(i!=linhas-1 && foi==false)
            {
                if(imagem_segmentada[i+1][j]!=imagem_segmentada[i][j])
                {
                    foi=true;
                    printf("(%d, %d)\n",i,j);               
                }
            } 
            if(j!=0 && foi==false)
            {
                if(imagem_segmentada[i][j-1]!=imagem_segmentada[i][j])
                {
                    foi=true;
                    printf("(%d, %d)\n",i,j);             
                }
            }  
        }
    }
    return;
}

void limpar(int **matriz,int linhas,int colunas)
{
    int i;

    for(i=0;i<linhas;i++)
    {
        free(matriz[i]);
    }
    free(matriz);
    return;
}

int main(void)
{
    char *nome_arquivo;
    int n,**imagem,**imagem_segmentada,linhas,colunas;

    nome_arquivo=leitura_inicial(&n);
    imagem=abrir_arquivo(nome_arquivo,&linhas,&colunas);
    imagem_segmentada = aloca_int(linhas,colunas,1);
    repeticao(n,imagem,imagem_segmentada,linhas,colunas);
    /*for(i=0;i<linhas;i++)
    {
        for(j=0;j<colunas;j++)
       {
            printf("%d",imagem_segmentada[i][j]);
        }
        printf("\n");
    }*/
    borda(imagem_segmentada,linhas,colunas);
    free(nome_arquivo);
    limpar(imagem,linhas,colunas);
    limpar(imagem_segmentada,linhas,colunas);
    return 0;
}