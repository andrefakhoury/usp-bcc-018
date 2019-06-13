

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    char prod[20];
    int positivo;
    int negativo;
} produto;
typedef struct{
    char nome[20];
    int ocorrencia;
} palavra;

/*Função para armazenamento de palavras comuns positivas e negativas.
 *caso a pergunta seja de quantos comentários eram positivos ou negativos
 *em relação ao produto.
 */
palavra* lista_de_palavras(){
    palavra* lista_palavra=malloc(sizeof(palavra)*26);
    strcpy(lista_palavra[0].nome,"bom");
    strcpy(lista_palavra[1].nome,"maravilhoso");
    strcpy(lista_palavra[2].nome,"otimo");
    strcpy(lista_palavra[3].nome,"sensacional"); 
    strcpy(lista_palavra[4].nome,"excelente");
    strcpy(lista_palavra[5].nome,"adorei");
    strcpy(lista_palavra[6].nome,"gostei");
    strcpy(lista_palavra[7].nome,"amei");
    strcpy(lista_palavra[8].nome,"eficiente");
    strcpy(lista_palavra[9].nome,"boa");
    strcpy(lista_palavra[10].nome,"maravilhosa");
    strcpy(lista_palavra[11].nome,"otima");
    strcpy(lista_palavra[12].nome,"detestei");
    strcpy(lista_palavra[13].nome,"odiei");
    strcpy(lista_palavra[14].nome,"ruim");
    strcpy(lista_palavra[15].nome,"pessimo");
    strcpy(lista_palavra[16].nome,"terrivel");
    strcpy(lista_palavra[17].nome,"raiva");
    strcpy(lista_palavra[18].nome,"odio");
    strcpy(lista_palavra[19].nome,"pessima");
    strcpy(lista_palavra[20].nome,"lento");
    strcpy(lista_palavra[21].nome,"lenta");
    strcpy(lista_palavra[22].nome,"fragil");
    strcpy(lista_palavra[23].nome,"desisti");
    strcpy(lista_palavra[24].nome,"positivos");
    strcpy(lista_palavra[25].nome,"negativos");
    
    return lista_palavra;

}

/*Função de leitura dos comentários.
 *Primeira mente a função lê o produto(até o ";"), e em seguida o comentário relativo a este produto(até o "\n" com o marcador "Ø").
 *Parametros:
 *  int f - Numero de comentarios a ser lido.
 *  char comentarios[][400] - Matriz que armazena os diferentes comentarios em strings.
 *  produto* lista_produto - Verto de struct onde sera armazenada o nome dos produtos comentados.
 */
void leitura_de_comentarios(int f,char comentarios[][400],produto* lista_produto){
    getchar();
    for(int i=0;i<f;i++){
        comentarios[i][399]='\0';        
        scanf("\n%20[^';']%*c ",lista_produto[i].prod);                
        scanf("%400[^'\n']%*c",comentarios[i]);
    }
    
}
/*Função de leitura das perguntas.
 *Lê e armazena as perguntas em um vetor de strings.
 *Parametros:
 *  int p - Numero de perguntas a ser lida.
 *  char vetp[][100] - vetor de strings onde as perguntas serao armazenadas.
 */
void leitura_de_pergunta(int p,char vetp[][100]){
    
    for(int i=0;i<p;i++){
        vetp[i][99]='\0';                
        scanf("%99[^'\n']%*c",vetp[i]);
        getchar();
        
    }
}

/*Função que avalia e imprime o que foi pedido.
 *recebe a palavra a ser contada e conta nos comentarios do produto recebido.
 *ou identifica se o comentario foi positivo ou negativo e gera uma porcentagem.
 *Parametros:
 *  int f - Numero de comentarios.
 *  int p - Numero de perguntas.
 *  produto* lista_produto - Vetor de produtos(referente aos comentarios) lidos.
 *  char comentarios[][400] - Vetor de strings que contem os comentarios.
 *  palavra* lista_palavra - Vetor de palavras possiveis nos comentarios(positivas ou negativas).
 *  char palap[][20] - Vetor de palavras a serem avaliadas.
 *  char prodp[][40] - Vetor de produtos a serem avaliados.
 */ 
void avalia_comentario(int f,int p,produto* lista_produto,char comentarios[][400],palavra* lista_palavra,char palap[][20],char prodp[][40]){
    char aux[20],end[10];
    char a='%';    
        
    end[9]='\0';
    strcpy(end,"Ø");
    aux[19]='\0';
    //loop de avaliaçao(numero de perguntas).
    for(int t=0;t<p;t++){        
        int occ=0;
        float positivo=0.0,negativo=0.0;
        float percp=0.0,percn=0.0;
        //passa por  todos os comentarios.
        for(int i=0;i<f;i++){
            float positivo2=0.0,negativo2=0.0;
            //analisa somente aqueles comentarios relativos ao produto a ser avaliado.
            if(strcmp(prodp[t],lista_produto[i].prod)==0){
                int op=0;
                //loop que analisa cada palavra e verifica se é igual a palavra recebida da função avalia_pergunta.
                for(int j=0;j<20;j++){
                    //le a primeira string e "op" faz com que mova para a proxima string dentro de comentarios[i](string sendo lida).
                    sscanf(comentarios[i]+op,"%s",aux);
                    op+=strlen(aux)+1;
                    //caso a string seja igual ao marcador "Ø" finaliza o loop.
                    if(strcmp(aux,end)==0){
                        j=21;
                    }
                    //caso a palavra recebida seja igual a string lida de comentarios[i] marca uma ocorrencia.
                    if(strcmp(aux,palap[t])==0){
                        occ++;
                    }
                    //verifica a existencia de palavras positivas e negativas no comentario para avalia-lo.
                    for(int x=0;x<24;x++){
                        
                        if(strcmp(lista_palavra[x].nome,aux)==0){
                            if(x<12){
                                positivo2+=1;
                                x=25;
                            }else{
                                negativo2+=1;
                                x=25;
                            }
                        }
                    }                                        

                }
                //avalia o comentario(positivo ou negativo em relaçao ao produto).
                if(positivo2>negativo2){
                    positivo++;
                }else{
                    negativo++;
                }
            }
            
            
        }
        //transforma em porcentagem arazao de positivo/negativo com numero de comentarios.
        percp=(positivo/(positivo+negativo))*100;
        percn=(negativo/(positivo+negativo))*100;
        //imprime oque foi pedido na pergunta.
        if(strcmp(palap[t],lista_palavra[24].nome)==0){
            printf("%.1f",percp);
            printf("%c\n",a);
        }else if(strcmp(palap[t],lista_palavra[25].nome)==0){
            printf("%.1f",percn);
            printf("%c\n",a);
        }else{
            printf("%d\n",occ);
        }
        


    }    

}

/*Função que avalia a pergunta.
 *Determina qual palavra a ser contada , ou que tipo de comentario é(positivo ou negativo).
 *e identifica de qual produto sera feito.
 *Parametros:
 *  int p - Numero de perguntas a serem feitas.
 *  char vetp[][100] - Vetor de strings com as perguntas a serem analisadas.
 *  char palap[][20] - Vetor de strings que armazenara as palavras a serem contadas.
 *  char prodp[][40] - Vetor de strings que armazenara o produto do qual os comentarios serao avaliados.
 */
void avalia_pergunta(int p,char vetp[][100],char palap[][20],char prodp[][40]){
    char aux1[20],aux3[20],aux2[2];
    aux1[19]='\0';
    aux3[19]='\0';    
    aux2[1]='\0';
    aux2[0]=' ';
    
    for(int j=0;j<p;j++){
        palap[j][19]='\0';
        prodp[j][0]='\0';
        sscanf(vetp[j],"%s %s %s %40[^'\n''\r']%*c",aux1,palap[j],aux3,prodp[j]);        
        strcat(prodp[j],aux2);                
        
    }

}

/*Função que libera os mallocs.
 *Parametros:
 *  produto* lista_produto - lista de produtos lidos nos comentarios.
 *  palavra* lista_palavra - lista de palavras positivas e negativas.
 */
void libera(produto* lista_produto,palavra* lista_palavra){
    free(lista_produto);
    free(lista_palavra);
}

int main(void){
    //declaraçao de numero de comentarios e perguntas a serem lidas.
    int Nfrases=0,Nperguntas=0;
     scanf("%d %d",&Nfrases,&Nperguntas);

     //declaraçao de vetores de strings que armazenarao comentarios perguntas e palavraras especificas.
    char comentarios[Nfrases][400],vetp[Nperguntas][100],palap[Nperguntas][20],prodp[Nperguntas][40];
    
    //criaçao de vetor com produtos a serem lidos nos comentarios e de possiveis palavras
    palavra* lista_palavra=lista_de_palavras();    
    produto* lista_produto=malloc(sizeof(produto)*Nfrases);

    //identificaçao de palavras e contagem desses nos comentarios dos produtos respectivos.
    leitura_de_comentarios(Nfrases,comentarios,lista_produto);        
    leitura_de_pergunta(Nperguntas,vetp);
    avalia_pergunta(Nperguntas,vetp,palap,prodp);    
    avalia_comentario(Nfrases,Nperguntas,lista_produto,comentarios,lista_palavra,palap,prodp);

    libera(lista_produto,lista_palavra);

    return 0;
}