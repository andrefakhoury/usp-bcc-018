#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structs
//como as sentenças serão armazenadas
typedef struct entrada{
    char produto[30];
    char frase[381];
}Sentenca;

//Funções
//guarda e separa o produto da frase
Sentenca* func_sentenca(int phrases); 
Sentenca* func_sentenca(int phrases){
    //aloc dinamica da qtde de structs entradas necessarias
    Sentenca *n_frases;
    n_frases=(Sentenca*)malloc(sizeof(Sentenca)*(phrases));
    // recebe produto e frase
    for (int i=0;i<phrases;i++)
        scanf(" %[^;]; %[^Ø] Ø",&n_frases[i].produto,&n_frases[i].frase);
    return n_frases; 
}

// recebe as perguntas e aloca em uma matriz de char
char** func_pergunta(int questions);
char** func_pergunta(int questions){
    //aloc dinamica da qtde de vetores de char necessarios
    char **n_pergunta=NULL;
    n_pergunta=(char**)malloc(sizeof(char*)*(questions));
    for (int i=0;i<questions;i++){
        char** pergunta[10][381];
        //reseta o scanf
        scanf("%*[^\n]");
        scanf("%*c"); 

        scanf("%[^\n]",&pergunta[i]);
        n_pergunta[i]=pergunta[i];
    }
    return n_pergunta;  
}

// PERGUNTA: PALAVRA [word] EM [produto]
int bag(Sentenca* product, char* ask, int phrases);
int bag(Sentenca* product, char* ask, int phrases){

        //identifica qual a palavra perguntada e o produto
        char* pergunta[5];
        pergunta[0]=strtok(ask," ");
        pergunta[1]=strtok(NULL," "); //palavra desejada
        pergunta[2]=strtok(NULL," ");
        pergunta[3]=strtok(NULL," "); //primeira palavra do produto
        pergunta[4]=strtok(NULL," "); //segunda  palavra do produto
        strcat(pergunta[1]," ");
        strcat(pergunta[3],pergunta[4]); //guarda o produto em um vetor char só
        char* auxiliar[50];

        //restaura a pergunta original
        snprintf(auxiliar,sizeof(ask)," %s", pergunta[1]);
        strcat(ask, auxiliar);

        // Contador da palavra pergunta[1] em product[j].frase
        int num_words=0, i=0;
        char* nome_produto[2];
        char* n_palavra[20];
        for (int j=0;j<phrases;j++){
            // Separa as duas palavras que formam o produto em dois char* diferentes
            nome_produto[0]=strtok(product[j].produto," ");
            nome_produto[1]=strtok(NULL," \0");
            if (strstr(pergunta[3],nome_produto[0])!=NULL && strstr(pergunta[3],nome_produto[1])!=NULL){ 
                char* localiza_palavra=0;
                localiza_palavra=strstr(product[j].frase,pergunta[1]);
                //Verifica se a palavra desejada aparece pelo menos uma vez
                if(localiza_palavra!=NULL){
                    //Verifica quantas vezes a palavra aparece na frase
                    do{
                        num_words++;
                        localiza_palavra+=strlen(pergunta[1]);
                        localiza_palavra=strstr(localiza_palavra,pergunta[1]);
                    }while(localiza_palavra!=NULL);
                }
            }
            // Reseta o product[j].produto 
            char* aux[30];
            snprintf(aux,sizeof(nome_produto[1])," %s", nome_produto[1]);
            strcat(product[j].produto, aux);
        } 
        printf("%d\n", num_words); 
    return 0;
}

// PERGUNTA: QUANTOS [polaridade] EM [produto]
// seleciona polaridade, lê e seleciona conjunto de frases do produto, devolve porcentagem
float people(Sentenca* product, char* ask, int phrases);
float people(Sentenca* product, char* ask, int phrases){
    int polaridade=0;
    float percentual=0.0;
    float total_polar=0.0,total_phrases=0.0;

    // Identifica a polaridade (positivos/negativos)
    if (strstr(ask,"positivos")!=NULL){
        polaridade++;
    }

    // Lista de palavras
    char* bad_words[12]={"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
    char* good_words[12]={"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei", "eficiente","boa","maravilhosa","otima"};
    char* nome_produto[2];
    if (polaridade==0){ 
        //"quantos NEGATIVOS em product" 
        for (int j=0;j<phrases;j++){
            // Separa as duas palavras que formam o produto em dois char* diferentes
            nome_produto[0]=strtok(product[j].produto," ");
            nome_produto[1]=strtok(NULL," \0");
            // Conta o numero de frases que falam sobre o produto e o numero de frases que contem um elemento da lista de palavras
            if (strstr(ask,nome_produto[0])!=NULL && strstr(ask,nome_produto[1])!=NULL){ 
                total_phrases++;
                for(int i=0;i<12;i++){
                    if (strstr(product[j].frase,bad_words[i])!=NULL){
                        total_polar++;
                        break;
                    }
                }              
            }
            // Reseta o product[j].produto 
            char* aux[30];
            snprintf(aux,sizeof(nome_produto[1])," %s", nome_produto[1]);
            strcat(product[j].produto, aux);
        }
    }
    else{
        //"quantos POSITIVOS em product"
        for (int j=0;j<phrases;j++){
            // Separa as duas palavras que formam o produto em dois char* diferentes
            nome_produto[0]=strtok(product[j].produto," ");
            nome_produto[1]=strtok(NULL," \0");
            // Conta o numero de frases que falam sobre o produto e o numero de frases que contem um elemento da lista de palavras
            if (strstr(ask,nome_produto[0])!=NULL && strstr(ask,nome_produto[1])!=NULL){
                total_phrases++;
                for(int i=0;i<12;i++){
                    if (strstr(product[j].frase,good_words[i])!=NULL){
                        total_polar++;
                        break;
                    }
                }              
            }
            // Reseta o product[j].produto 
            char* aux[30];
            snprintf(aux,sizeof(nome_produto[1])," %s", nome_produto[1]);
            strcat(product[j].produto, aux);
        }
    }
    
    // calcula e exibe a porcentagem já formatada
    percentual=(total_polar/total_phrases)*100;
    printf("%.1f%%\n", percentual);
    return 0.0;
}

//MAIN
int main(){

    // Variáveis p/ armazenar QTDE de sentenças e perguntas    
    int num_sentenca,num_pergunta;
    scanf("%d %d",&num_sentenca,&num_pergunta);

    // Guarda as sentenças e perguntas
    Sentenca* entrada=func_sentenca(num_sentenca);
    char** matriz_pergunta=func_pergunta(num_pergunta);

    // Identifica a pergunta e analisa todas as frases pelas funções people e bag, para todas as perguntas
    for (int i=0;i<num_pergunta;i++){
        if (strstr(matriz_pergunta[i],"quantos")!=NULL){
            people(entrada,matriz_pergunta[i], num_sentenca);
        }
        else 
            bag(entrada,matriz_pergunta[i], num_sentenca);
    }

    // Desalocações
    free(entrada);
    free(matriz_pergunta);
}
