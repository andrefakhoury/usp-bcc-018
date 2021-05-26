#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/* Variáveis Globais(utilizei-as pelo motivo de existir variaveis que são usadas em quase todas as funções */
int n1=0;
int n2=0;
int first_x=0;
int first_y=0;
/*Cálculo das médias */
double med(double b,double* averg_value,double* var_s){
    (*(averg_value)) = ((*(var_s))/(b));
    return (*(averg_value));
}
/*Função que preenche uma matriz, como a apresentada no pdf */
void segmentation(int** matriz,int** matriz_sec,int* x,int* y,int* fator,int* N_in,int* n_elements,double* averg_value,int* flag,int* N_def,double* var_s){
    if((*(averg_value))==0){
        first_x=(*(x));
        first_y=(*(y));   
    }
    /*No início de novas parâmetros, a média é zero e são especificados os valores iniciais */
    if( (*(flag))==1 ){
        if(  fabs((( matriz[(*(x))][(*(y))] - (*(averg_value)))  ) <=   (*(fator))  && (matriz_sec[(*(x))][(*(y))])==0) || ((*(averg_value))==0)){
            if(matriz_sec[(*(x))][(*(y))]==0){
                    matriz_sec[(*(x))][(*(y))]=((*(N_def))+1);
                    (*(flag))=0;
                    (*(n_elements))=((*(n_elements))+1);
                    (*(var_s))=(*(var_s))+(double)(matriz[(*(x))][(*(y))]);
                    (*(averg_value))=med(((double)(*(n_elements))),averg_value,var_s);   
            }
        }else{
            (*(flag))=3;
        }
    }
    /*O código acima define uma flag, que ativa a inclusão de um novo elemento na parte segmentada da vez */
    if(((*(x))-1)>=0 && (*(flag))== 0 ){
        if( ( fabs(matriz[((*(x))-1)][(*(y))] - (*(averg_value)))  ) <=   (*(fator))  && (matriz_sec[((*(x))-1)][(*(y))])==0   ){
            (*(x))=((*(x))-1);
            (*(flag))=1;
            segmentation(matriz,matriz_sec,x,y,fator,N_in,n_elements,averg_value,flag,N_def,var_s);
            (*(x))=((*(x))+1);
        }
    }if( ((*(y))+1) < n2 && (*(flag))==0 ){
        if( ( fabs(matriz[(*(x))][((*(y))+1)] - (*(averg_value)))  ) <=   (*(fator))  && (matriz_sec[(*(x))][((*(y))+1)])==0 ){
            (*(y))=((*(y))+1);
            (*(flag))=1;
            segmentation(matriz,matriz_sec,x,y,fator,N_in,n_elements,averg_value,flag,N_def,var_s);
            (*(y))=((*(y))-1);
        }
    }if( ((*(x))+1) < n1 && (*(flag))==0 ){
        if( fabs(( matriz[((*(x))+1)][(*(y))] - (*(averg_value)))  ) <=   (*(fator)) && (matriz_sec[((*(x))+1)][(*(y))])==0 ){
            (*(x))=((*(x))+1);
            (*(flag))=1;
            segmentation(matriz,matriz_sec,x,y,fator,N_in,n_elements,averg_value,flag,N_def,var_s);
            (*(x))=((*(x))-1);
        }
    }if( ((*(y))-1)  >= 0 && (*(flag))==0 ){
        if( fabs(( matriz[(*(x))][((*(y))-1)] - (*(averg_value)))  ) <=   (*(fator))  && (matriz_sec[(*(x))][((*(y))-1)])==0 ){
            (*(y))=((*(y))-1);
            (*(flag))=1;
            segmentation(matriz,matriz_sec,x,y,fator,N_in,n_elements,averg_value,flag,N_def,var_s);
            (*(y))=((*(y))+1);
        }
    }
    /*Acima estão as condições de seleção ordendas, cima, direita,baixo, esquerda. Ela checa seo valor se encaixa baseando-se no módulo da média - valor da matriz, se isso for verdadeiro
    a condicional move o elemento para a próxima posição e ativa a flag executando novamente a função */
    // if( (*(N_def)) < (*(N_in)) && (*(x))==first_x && (*(y))==first_y){
    //     (*(N_def))= ((*(N_def))+1);
    //     (*(x))=(*(x+(*(N_def))));
    //     (*(y))=(*(y+(*(N_def))));
    //     (*(fator))=(*(fator+(*(N_def))));
    //     (*(averg_value))=0;
    //     (*(var_s))=0;
    //     (*(n_elements))=0;
    //     (*(flag))=1;
    //     segmentation(matriz,matriz_sec,x,y,fator,N_in,n_elements,averg_value,flag,N_def,var_s);
    // }
}
/* Acima é a condição de um novo segmento, primeiro ele executa as condições direcionais e desfaz esse caminho para adicionar os pontos restantes, apos isso
ele começa uma nova sequência quando a condicional é menor que o máximo de execuções, e está no mesmo ponto de início de x e y */
int show_segment(int** matriz_sec){
      if(first_y<n2 && first_x<n1){
          if(matriz_sec[first_x][first_y]>0){
            if((first_x-1)>=0 ){
                if(matriz_sec[first_x-1][first_y]==0 || matriz_sec[first_x-1][first_y]==-1){
                    matriz_sec[first_x][first_y]=-2;
                    matriz_sec[first_x-1][first_y]=-1;
                }
            }if( (first_y+1) < n2  ){
                if(matriz_sec[first_x][first_y+1]==0 || matriz_sec[first_x][first_y+1]==-1){
                    matriz_sec[first_x][first_y]=-2;
                    matriz_sec[first_x][first_y+1]=-1;
                }
            
            }if( (first_x+1)  < n1  ){
                if(matriz_sec[first_x+1][first_y]==0 || matriz_sec[first_x+1][first_y]==-1 ){
                    matriz_sec[first_x][first_y]=-2;
                    matriz_sec[first_x+1][first_y]=-1;
                }
            
            }if( (first_y-1)  >= 0  ){
                if(matriz_sec[first_x][first_y-1]==0 || matriz_sec[first_x][first_y-1]==-1){
                    matriz_sec[first_x][first_y]=-2;
                    matriz_sec[first_x][first_y-1]=-1;
                }

            }
        }
            first_y=first_y+1;
            show_segment(matriz_sec);
    }else{
        first_y=0;
        first_x=first_x+1;
        if(first_x<n1 && first_y<n2)show_segment(matriz_sec);
    }
/*Essa função seleciona os segmentos que seriam mostrados na saída, ele seleciona-os da mesma forma do pdf trocando 
números maiores que 0 por -1,caso sejam bordas ou um x, ou -2 , que são números de segmentos com x ao redor(cima,direita,baixo,esquerda) */
    return 0;
}
int main (void){
    char name[13];
    int N_in=0;
    FILE* img_name=NULL;

    scanf("%s", name);

    img_name=fopen(name,"r");
    
    if(img_name==NULL){
        printf("error");
        exit(0);
    }

    fscanf(img_name,"%*s");
    fscanf(img_name,"%d %d",&n2,&n1);
    fscanf(img_name,"%*d");
    /*Cria as matrizes */
    int** matriz;
    int** matriz_sec;

    matriz=calloc(n1,sizeof(int*));
    for(int u=0; u<n1; u++)matriz[u]=calloc(n2,sizeof(int));
    
    for(int i=0; i<n1; i++){
        for(int j=0; j<n2; j++){
            fscanf(img_name,"%d",&matriz[i][j]);
        }
    }
    /*Importação de valores */
    scanf("%d",&N_in);

    int* x= calloc(N_in,sizeof(int));
    int* y= calloc(N_in,sizeof(int));
    int* fator= calloc(N_in,sizeof(int));
    int* N_def=calloc(1,sizeof(int));
    int* n_elements=calloc(1,sizeof(int));
    double* averg_value=calloc(1,sizeof(double));
    int* flag=calloc(1,sizeof(int));
    double* var_s= calloc(1,sizeof(double));
    /*Variáveis dinâmicas utilizadas */
    (*(flag))=1;

    matriz_sec =calloc(n1,sizeof(int*));
    for(int c=0; c<n1; c++)matriz_sec[c]=calloc(n2,sizeof(int));

    for(int f=0; f<N_in; f++)scanf("%d %d %d", &x[f], &y[f], &fator[f]);
    segmentation(matriz,matriz_sec,x,y,fator,&N_in,n_elements,averg_value,flag,N_def,var_s);
    
    first_x=0;
    first_y=0;
    /*Reutilização de variáveis globais pós segmentação */
    show_segment(matriz_sec);
    for(int i=0; i<n1; i++){
        for(int j=0; j<n2; j++){
            if(matriz_sec[i][j]==-1 || matriz_sec[i][j]==-2)printf("(%d, %d)\n",i,j);
        }
    }
    for(int i=0; i<n1; i++){
        free(matriz_sec[i]);
        free(matriz[i]);
    }

    /*Liberação e nulificação dos ponteiros */
    free(matriz);
    matriz=NULL;
    free(matriz_sec);
    matriz_sec=NULL;
    free(x);
    x=NULL;
    free(y);
    y=NULL;
    free(fator);
    fator=NULL;
    free(N_def);
    N_def=NULL;
    free(n_elements);
    n_elements=NULL;
    free(averg_value);
    averg_value=NULL;
    free(flag);
    flag=NULL;
    free(var_s);
    var_s=NULL;
    return 0;
}