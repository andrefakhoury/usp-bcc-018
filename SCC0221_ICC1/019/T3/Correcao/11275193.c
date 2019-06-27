#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void translateimage(char **nameofile,int ***translatedimage,int ***mirrorimage,int *xmax,int *ymax){ 

    /*
    
    Nessa funcao eh lido todo o arquivo pgm que servira como base.
    Alem de ler tudo e guardar isso em uma array bidimensional chamada 'translatedimage'
    tambem eh criada uma outra array bidemensional chamada 'mirrorimage' que possui as mesmas
    dimensoes da 'translatedimage', mas com valor '0' em todas as regioes. 
    
    */
    
    FILE *toread;
    char trashstring[3];
    int trashint;
    scanf("%ms",nameofile);
    getchar();
    toread=fopen((*nameofile),"r");
    fscanf(toread,"%s %d %d %d",trashstring,ymax,xmax,&trashint);

    *translatedimage=malloc((*xmax)*sizeof(int*));
    *mirrorimage=malloc((*xmax)*sizeof(int*));
    for(int i=0;i<(*xmax);i++){
        (*translatedimage)[i]=calloc((*ymax),sizeof(int));
        (*mirrorimage)[i]=calloc((*ymax),sizeof(int));
        for(int j=0;j<(*ymax);j++){
            fscanf(toread,"%d",&((*translatedimage)[i][j]));
        }
    }

    fclose(toread);
}

int mainprocess(int ***translatedimage,int ***mirrorimage,int initialx,int initialy,int actualx, int actualy,int maxvar,float *totalvalue,float *totalmembers,int xmax,int ymax,int number){

    /*

    Em cada um dos "if's" sao averiguadas tres condicoes que devem ser concomitantes.
    Eh averiguado se existe o ponto adjacente - na ordem: superior, a direita, para baixo e a esquerda;.
    Eh averiguado se na matriz 'mirrorimage' esse ponto em questao eh zero.
    Eh averiguado se o modulo da diferenca entre esse ponto adjacente e a media dos termos eh menor ou igual ao valor do criterio.
    Caso essas tres condicoes sejam verdade, essa posicao adjacente muda seu valor de '0' para um numero especifico - que eh definido
    na funcao 'manyiterations'. O valor total - que ajuda a compor a media recebe uma adicao igual ao valor desse ponto adjacente na funcao 'translatedimage'
    E o numero total de membros da media tambem eh aumentado.
    Alem disso, para que esse processo ocorra como o esperado eh executada uma funcao recursiva desse mesmo 'mainproces' com a diverenca que os valores de x e y vao
    ser o x e o y desse termo adjacente.
    Esse processo vai se repetir ate algum dos termos executar todos os 4 if's e nao encontrar nada de novo e todos os anteriores tambem passem por isso ate voltar no
    primeiro, onde sera retornado nada de especial, mas a 'mirrorimage' estara alterada de modo a ser analisada na funcao 'showborders'.

    */

    if( ((actualx-1)>=0) && !((*mirrorimage)[actualx-1][actualy]) && (fabs(((float)((*translatedimage)[actualx-1][actualy]))-((*totalvalue)/(*totalmembers)))<=maxvar) ){
        (*mirrorimage)[actualx-1][actualy]=number;
        (*totalvalue)+=(*translatedimage)[actualx-1][actualy];
        (*totalmembers)+=1;

        mainprocess(translatedimage,mirrorimage,initialx,initialy,actualx-1,actualy,maxvar,totalvalue,totalmembers,xmax,ymax,number);
    }

    if( ((actualy+1)<ymax) && !((*mirrorimage)[actualx][actualy+1]) && (fabs(((float)((*translatedimage)[actualx][actualy+1]))-((*totalvalue)/(*totalmembers)))<=maxvar) ){
        (*mirrorimage)[actualx][actualy+1]=number;
        (*totalvalue)+=(*translatedimage)[actualx][actualy+1];
        (*totalmembers)+=1;

        mainprocess(translatedimage,mirrorimage,initialx,initialy,actualx,actualy+1,maxvar,totalvalue,totalmembers,xmax,ymax,number);
    }

    if( ((actualx+1)<xmax) && !((*mirrorimage)[actualx+1][actualy]) && (fabs(((float)((*translatedimage)[actualx+1][actualy]))-((*totalvalue)/(*totalmembers)))<=maxvar) ){
        (*mirrorimage)[actualx+1][actualy]=number;
        (*totalvalue)+=(*translatedimage)[actualx+1][actualy];
        (*totalmembers)+=1;

        mainprocess(translatedimage,mirrorimage,initialx,initialy,actualx+1,actualy,maxvar,totalvalue,totalmembers,xmax,ymax,number);
    }

    if( ((actualy-1)>=0) && !((*mirrorimage)[actualx][actualy-1]) && (fabs(((float)((*translatedimage)[actualx][actualy-1]))-((*totalvalue)/(*totalmembers)))<=maxvar) ){
        (*mirrorimage)[actualx][actualy-1]=number;
        (*totalvalue)+=(*translatedimage)[actualx][actualy-1];
        (*totalmembers)+=1;

        mainprocess(translatedimage,mirrorimage,initialx,initialy,actualx,actualy-1,maxvar,totalvalue,totalmembers,xmax,ymax,number);
    }
    return 0;
}


void generalfunction(int ***translatedimage,int ***mirrorimage,int xmax,int ymax,int number){
    
    /*

    Essa funcao le as cordenadas e a difenca maxima e caso a cordenada dada seja igual a zero,
    ou seja, nao foi ocupada, ela passara pelo 'mainprocess', caso nao, o processo segue com o fim dessa funcao.

    */

    int initialx=0,initialy=0,maxvar=0;
    float totalvalue=0,totalmembers=1;
    scanf("%d %d %d",&initialx,&initialy,&maxvar);
    if((*mirrorimage)[initialx][initialy]==0){
        totalvalue=(float)((*translatedimage)[initialx][initialy]);
        (*mirrorimage)[initialx][initialy]=number;

        mainprocess(translatedimage,mirrorimage,initialx,initialy,initialx,initialy,maxvar,&totalvalue,&totalmembers,xmax,ymax,number);    
    }
}

void manyiterations(int *repetitions,int ***translatedimage,int ***mirrorimage,int xmax,int ymax){
    
    // Essa funcao serve para repetir os processos fundamentais a resolucao do problema o numero de vezes que foi requerido.
    
    scanf("%d",repetitions);
    for(int i=0;i<(*repetitions);i++){
        generalfunction(translatedimage,mirrorimage,xmax,ymax,(i+1));
    }
}

void showborders(int **mirrorimage,int xmax,int ymax){
    /*
    
    Nessa funcao sao testadas as condicoes da 'mirrorimage' em todos os pontos dela para saber se esses pontos sao uma 'borda'
    ou não. Para que ele seja uma borda, pelo menos um dos pontos adjacentes a ele deve existir e ter uma numeracao diferente da sua

    */

    for(int i=0;i<xmax;i++){
        for(int j=0;j<ymax;j++){
            if(((i-1>=0) && (mirrorimage[i-1][j]!=mirrorimage[i][j]))||((j+1<ymax) && (mirrorimage[i][j+1]!=mirrorimage[i][j]))||((i+1<xmax) && (mirrorimage[i+1][j]!=mirrorimage[i][j]))||((j-1>=0) && (mirrorimage[i][j-1]!=mirrorimage[i][j]))){
                printf("(%d, %d)\n",i,j);
            }
        }
    }
}

void freeforall(char *nameofile,int **translatedimage,int **mirrorimage,int xmax){
    
    // Nessa funcao, todas as variaveis que foram alocadas dinamicamente recebem o free adequado
    
    for(int i=0;i<xmax;i++){
        free(translatedimage[i]);
        free(mirrorimage[i]);
    }
    free(translatedimage);
    free(mirrorimage);
    free(nameofile);
}

int main(void){
    char *nameofile=NULL;
    int repetitions,xmax,ymax;
    int **translatedimage=NULL;
    int **mirrorimage=NULL;

    translateimage(&nameofile,&translatedimage,&mirrorimage,&xmax,&ymax);
    manyiterations(&repetitions,&translatedimage,&mirrorimage,xmax,ymax);
    showborders(mirrorimage,xmax,ymax);
    freeforall(nameofile,translatedimage,mirrorimage,xmax);

    return 0;
}


