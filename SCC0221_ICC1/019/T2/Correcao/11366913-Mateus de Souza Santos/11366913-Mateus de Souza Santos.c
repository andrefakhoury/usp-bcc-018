/*
    O run.codes buga dos casos 4~7. Foi testado no gcc em um notebook com ubuntu e nos dos labs e deu certos 7/7 (sem considerar os casos bônus).    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NumMaxPalavras 21
#define NumMaxCaracteres 19
#define TamanhoEntrada 420
#define MaxSentencas 100


//Protótipo das funções
void EntradadeDados(int num, char **entrada);
char** AlocarMemoriaEntrada(int num);
char** AlocarMemoria(int num, int tam);
void SepararProdutoseSentencas(int num, char **s, char **p, char ***words);
void LimparMemoriaString(char *str);
void LimparMemoriaVetString(char **str, int n);
void LimparString(char *str);
void Resultado(int num,char **p, char ***s, char *Tipo, char *Pergunta, char *Produto);

int main(){
    int num_sentencas, num_perguntas, cont, i;
    char **sentencas, **perguntas, **produtos, ***palavras, ***perguntasseparadas, 
    TipoDePergunta[20], ObjetoPergunta[20], Produto[40], FraseTemporaria[TamanhoEntrada], *aux;
    //Recebendo a primeira entrada c/ nº de perguntas e sentenças
    scanf("%d %d\n", &num_sentencas, &num_perguntas);
    
    //Alocando Memoria para a entrada
    sentencas = AlocarMemoriaEntrada(num_sentencas);
    produtos = AlocarMemoriaEntrada(num_sentencas);
    perguntas = AlocarMemoriaEntrada(num_perguntas);

    //Alocando memoria para outra variaveis
    //Para palavras
    palavras = (char ***) malloc((MaxSentencas*sizeof(char**)));
    for(i=0; i < MaxSentencas; i++)
        palavras[i] = AlocarMemoria(NumMaxPalavras, NumMaxCaracteres);
    //Para Perguntas
    perguntasseparadas= (char ***) malloc((num_perguntas*sizeof(char**)));
    for(i=0; i < MaxSentencas; i++)
        perguntasseparadas[i] = AlocarMemoria(NumMaxPalavras, NumMaxCaracteres);
    

    //Entrada das Sentencas e Perguntas 
    EntradadeDados(num_sentencas, sentencas);
    EntradadeDados(num_perguntas, perguntas);

    //Separar produtos e sentenças
    SepararProdutoseSentencas(num_sentencas, sentencas, produtos, palavras);

    // Separa a Pergunta em palavras e pede o resultado
    for(cont=0; cont < num_perguntas; cont++){
        //Copia o comentario  em uma variável auxiliar
        strcpy(FraseTemporaria, perguntas[cont]);
        //Separa as palavras das perguntas
        //Salva o tipo de pergunta
        aux = strtok(FraseTemporaria, " ");
        strcpy(TipoDePergunta, aux);
        //Salva qual é a pergunta
        aux = strtok(NULL, " ");
        strcpy(ObjetoPergunta, aux);
        aux = strtok(NULL, " ");
        //Salva o produto da pergunta
        aux = strtok(NULL, " ");
        strcpy(Produto, aux);
        //Salva o produto
        aux = strtok(NULL, " ");
        if((unsigned char)aux[strlen(aux)-1] == 10)
            aux[strlen(aux)-1] = '\0';
        strcat(Produto, " ");
        strcat(Produto, aux);
        //Função que Retorna o resultado para cada pergunta
        Resultado(num_sentencas, produtos, palavras, TipoDePergunta, ObjetoPergunta, Produto);
    }

    //Limpando a memoria
    LimparMemoriaVetString( sentencas, num_sentencas);
    LimparMemoriaVetString( perguntas, num_perguntas);
    return 0;
}

/*Função para alocar a memória
cria um ponteiro de ponteiro do tipo char, uma matriz de caracteres(ou vetor de strings)
e retorna esse ponteiro*/
char** AlocarMemoriaEntrada(int num){
    int cont;
    char **s;
    s = (char **) malloc(num * sizeof(char*));
    for(cont = 0; cont < num; cont++){
        s[cont] = (char*) malloc(TamanhoEntrada * sizeof(char));
    }
    return(s);
}

//Função para alocar memoria de ponteiros p/ strings
char** AlocarMemoria(int num, int tam){
    int cont;
    char **s;
    s = (char **) malloc(num * sizeof(char*));
    for(cont = 0; cont < num; cont++){
        s[cont] = (char*) malloc(tam * sizeof(char));
    }
    return(s);
}

// Usa a função fgets para coletar toda a entrada de sentenças e perguntas
void EntradadeDados(int num, char **entrada){
    int i;
    for(i=0; i < num; i++){
        fgets(entrada[i], TamanhoEntrada, stdin);
    }
}

//Função para separar produtos e setenças
void SepararProdutoseSentencas(int num, char **s, char **p, char ***words){
        int cont, i = 0;
        char FraseTemporaria[TamanhoEntrada], *aux;
        for(cont=0; cont < num; cont++){
            //Salva em uma variavel a entrada a ser dividida
            strcpy(FraseTemporaria, s[cont]);
            // Salva o Produto
            aux = strtok(FraseTemporaria, ";");
            strcpy(p[cont], aux);
            // Salva a Sentença
            aux = strtok(NULL, ";");
            strcpy(s[cont], aux);
    }

    // Separa a sentenças em palavras
    for(cont=0; cont < num; cont++){
        //Copia o comentario  em uma variável auxiliar
        strcpy(FraseTemporaria, s[cont]);
        //Separa as palavras
        aux = strtok(FraseTemporaria, " ");
        while(aux != NULL){
            strcpy(words[cont][i], aux);
            aux = strtok(NULL, " ");
            i++;
        }      
        i=0;
    }
}

//Função para ver o resultado
void Resultado(int num,char **p, char ***s, char *Tipo, char *Pergunta, char *Produto){
    int DarBreak, cont, i, quantidadedepos=0, k, qtdSent = 0;
    char Positivos[12][14] = {{"bom\0"}, {"maravilhoso\0"}, {"otimo\0"}, {"sensacional\0"}, {"excelente\0"}, {"adorei\0"}, {"gostei\0"}, {"amei\0"}, {"eficiente\0"}, {"boa\0"}, {"maravilhosa\0"}, {"otima\0"}};
    float resposta=0.0;
    
    //For para percorrer as sentenças
    for(cont = 0; cont < num; cont++){
        //Para limpar o espaço vazio do p[cont]
        if(p[cont][strlen(p[cont])-1] == ' ')
            p[cont][strlen(p[cont])-1] = '\0';
        
        //conferir se o produto da setença é o da pergunta
        if(strcmp(p[cont], Produto) == 0){
            qtdSent++;
            //saber qual o tipo de pergunta
            if(strcmp(Tipo, "palavra") == 0){
                //percorrer as palavras da setenças
                for(int i = 0; i < NumMaxPalavras; i++){
                    if(strcmp(s[cont][i], Pergunta) == 0){
                        resposta++;
                    }
                }   
            } else {
                DarBreak = 1;
                //conferir se na sentença tem termos positivos
                for(i = 0; i < NumMaxPalavras; i++){
                    if(DarBreak == 0)
                        break;
                    for(k = 0; k < 12; k++){
                        //caso encontre alggum termo positivo
                        if(strcmp(s[cont][i], Positivos[k]) == 0){
                            quantidadedepos++;
                            DarBreak = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    //Exibindo a resposta
    if(strcmp(Tipo, "palavra") == 0){
        printf("%d\n", (int)resposta);
    } else {
        if(strcmp(Pergunta, "positivos") == 0)
        {
            resposta = ((float)quantidadedepos*100.0)/(float)qtdSent;
        }
        else
        {
            resposta = ((float)(qtdSent-quantidadedepos)*100.0)/(float)qtdSent;
        }
        printf("%.1f%c\n", resposta, '%');
    }

}


//Função para limpar memória

void LimparMemoriaVetString(char **str, int n){
    /*for(int i = 0; i < n; i++)
        free(str[i]);*/
    free(str);
}
