#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    int nSentencas; int nPerguntas; //variáveis que armazenam o numero de sentenças e perguntas que serão amputadas
    char** sentencas; char** perguntas; //variáveis que armazenam as sentenças e as perguntas em si (cada uma em um índice)
    char*** senDivididas; char*** perDivididas; //variáveis que armazenam as sentenças e as perguntas em si, só que dividido em palavras
    int* flagSentencas; int* flagPerguntas; //variáveis que armazenam a quantidade de palavras existentes em cada sentença e pergunta

    scanf("%d %d ", &nSentencas, &nPerguntas); //lê dois inteiros e os insere em nSentencas e nPerguntas

    sentencas = malloc(nSentencas*sizeof(char*)); //aloca espaços do tamanho de char* na heap
    perguntas = malloc(nPerguntas*sizeof(char*)); //aloca espaços do tamanho de char* na heap

    senDivididas = malloc(nSentencas*sizeof(char**)); //aloca espaços do tamanho de char** na heap
    perDivididas = malloc(nPerguntas*sizeof(char**)); //aloca espaços do tamanho de char** na heap

    flagSentencas = calloc(nSentencas, sizeof(int)); //aloca espaços do tamanho de int na heap e insere 0
    flagPerguntas = calloc(nPerguntas, sizeof(int)); //aloca espaços do tamanho de int na heap e insere 0

    for(int i = 0; i < nSentencas; i++){
        senDivididas[i] = malloc(30*sizeof(char*)); //aloca espaços do tamanho de char* na heap em cada indice da variavel de tipo char**
        sentencas[i] = malloc(250*sizeof(char)); //aloca espaços do tamanho de char na heap em cada indice da variavel de tipo char*
        
        fgets(sentencas[i], 250, stdin); //lê cada linha de char e armazena em cada indice de sentencas

        senDivididas[i][0] = strtok(sentencas[i], "; Ø\r"); //começa a separar cada linha de sentencas em palavras, tirando ";", " ", "Ø" e "\r"  

        while(senDivididas[i][flagSentencas[i]] != NULL) { //continua a separar cada linha de sentencas em palavras, tirando ";", " ", "Ø" e "\r"
            flagSentencas[i]++; //incrementa 1 a cada nova palavra separada
            senDivididas[i][flagSentencas[i]] = strtok(NULL, "; Ø\r");
        }
    }

    for(int i = 0; i < nPerguntas; i++){
        perDivididas[i] = malloc(30*sizeof(char*)); //aloca espaços do tamanho de char* na heap em cada indice da variavel de tipo char**
        perguntas[i] = malloc(250*sizeof(char)); //aloca espaços do tamanho de char na heap em cada indice da variavel de tipo char*
        
        fgets(perguntas[i], 250, stdin); //lê cada linha de char e armazena em cada indice de perguntas

        perDivididas[i][0] = strtok(perguntas[i], " \r"); //começa a separar cada linha de perguntas em palavras, tirando ";", " ", "Ø" e "\r"

        while(perDivididas[i][flagPerguntas[i]] != NULL) { //continua a separar cada linha de sentencas em palavras, tirando ";", " ", "Ø" e "\r"
            flagPerguntas[i]++; //incrementa 1 a cada nova palavra separada
            perDivididas[i][flagPerguntas[i]] = strtok(NULL, " \r");
        }
    }

    for(int i = 0; i < nPerguntas; i++){
        char produtoPergunta[30]; //variavel que armazena o nome do produto que será verificado
        strcpy(produtoPergunta, perDivididas[i][3]); // insere a primeira parte do nome na variavel
        strcat(produtoPergunta, " "); //insere o espaço
        strcat(produtoPergunta, perDivididas[i][4]); //insere a segunda parte do nome na variavel
        strtok(produtoPergunta, "\n"); //retira o '\n' do final da string, permitindo a comparação
        
        if(strcmp(perDivididas[i][0], "palavra") == 0){  //verifica se a primeira palavra da pergunta é "palavra" para determinar o que será feito
            int qtdPalavra = 0; //variavel que armazena a quantidade de vezes que a palavra solicitada aparece
            char palavra[20];  //variavel que armazena a palavra solicitada
            strcpy(palavra, perDivididas[i][1]); // insere o nome na variavel

            for(int a = 0; a < nSentencas; a++){ //É verificado cada frase para ver se há a palavra
                char produtoSentenca[30]; //variavel que armazena o nome do produto da frase
                strcpy(produtoSentenca, senDivididas[a][0]); // insere a primeira parte do nome na variavel
                strcat(produtoSentenca, " "); //insere o espaço
                strcat(produtoSentenca, senDivididas[a][1]); //insere a segunda parte do nome na variavel

                if(strcmp(produtoSentenca, produtoPergunta) == 0){ //é testado se o nome do produto da frase é o produto da pergunta
                    for(int b = 2; b < flagSentencas[a]; b++){  //é verificado cada palavra da frase para ver se alguma é a palavra escolhida
                        if(strcmp(senDivididas[a][b], palavra) == 0){
                            qtdPalavra++; //caso afirmativo é incrementada a variavel
                        }
                    }
                }
            }

            printf("%d\n", qtdPalavra); //print da quantidade de vezes que a palavra aparece
        }
        else if(strcmp(perDivididas[i][0], "quantos") == 0){ //verifica se a primeira palavra da pergunta é "quantos" para determinar o que será feito
            //char* adverbios[] = {"nao", "jamais", "nunca"}; //arrays com os adverbios, palavras positivas e negativas que serão usadas para verificar a polaridade das frases
            char* positivos[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
            char* negativos[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
            
            if(strcmp(perDivididas[i][1], "positivos") == 0){ //verifica se a segunda palavra da pergunta é "positivos" para determinar o que será feito
                float qtdPositivos = 0; //variavel que armazena a quantidade de frases positivas
                float qtdFrases = 0; //variavel que armazena a quantidade de frases totais
                for(int a = 0; a < nSentencas; a++){ //É verificado cada frase para ver se há palavras positivas
                    char produtoSentenca[30]; //variavel que armazena o nome do produto da frase
                    strcpy(produtoSentenca, senDivididas[a][0]); // insere a primeira parte do nome na variavel
                    strcat(produtoSentenca, " "); // insere o espaço
                    strcat(produtoSentenca, senDivididas[a][1]); // insere a segunda parte do nome na variavel
                    int stop = 0; // flag que determina se os blocos de repetição serão quebrados

                    if(strcmp(produtoSentenca, produtoPergunta) == 0){ //é testado se o nome do produto da frase é o produto da pergunta
                        qtdFrases++; //é incrementado 1 a variavel que armazena a quantidade de frases totais
                        for(int b = 2; b < flagSentencas[a]; b++){ //é verificado cada palavra da frase para ver se alguma é uma palavra positiva
                            for(int c = 0; c < 12; c++){ //é testado cada palavra positiva do array
                                if(strcmp(senDivididas[a][b], positivos[c]) == 0){ //é verificado cada palavra da frase para ver se alguma é a palavra escolhida
                                    qtdPositivos++; //caso afirmativo é incrementada a variavel
                                    stop = 1; //caso afirmativo a flag de break é acionada
                                }
                                if(stop == 1)
                                    break;
                            }
                            if(stop == 1)
                                break;
                        }
                    }
                }
                float porcentagem = (qtdPositivos/qtdFrases)*100; // é calculada a porcentagem
                printf("%.1f%%\n", porcentagem); //é feito o print da porcentagem
            }
            else if(strcmp(perDivididas[i][1], "negativos") == 0){ //verifica se a segunda palavra da pergunta é "negativos" para determinar o que será feito
                float qtdNegativos = 0;//variavel que armazena a quantidade de frases negativas
                float qtdFrases = 0; //variavel que armazena a quantidade de frases totais
                for(int a = 0; a < nSentencas; a++){ //É verificado cada frase para ver se há palavras negativas
                    char produtoSentenca[30]; //variavel que armazena o nome do produto da frase
                    strcpy(produtoSentenca, senDivididas[a][0]); // insere a primeira parte do nome na variavel
                    strcat(produtoSentenca, " "); //insere o espaço
                    strcat(produtoSentenca, senDivididas[a][1]); // insere a segunda parte do nome na variavel
                    int stop = 0; // flag que determina se os blocos de repetição serão quebrados

                    if(strcmp(produtoSentenca, produtoPergunta) == 0){ //é testado se o nome do produto da frase é o produto da pergunta
                        qtdFrases++; //é incrementado 1 a variavel que armazena a quantidade de frases totais
                        for(int b = 2; b < flagSentencas[a]; b++){ //é verificado cada palavra da frase para ver se alguma é uma palavra negativa
                            for(int c = 0; c < 12; c++){ //é testado cada palavra negativa do array
                                if(strcmp(senDivididas[a][b], negativos[c]) == 0){ //é verificado cada palavra da frase para ver se alguma é a palavra escolhida
                                    qtdNegativos++; //caso afirmativo é incrementada a variavel
                                    stop = 1; //caso afirmativo a flag de break é acionada
                                }
                                if(stop == 1)
                                    break;
                            }
                            if(stop == 1)
                                break;
                        }
                    }
                }
                float porcentagem = (qtdNegativos/qtdFrases)*100; // é calculada a porcentagem
                printf("%.1f%%\n", porcentagem); //é feito o print da porcentagem
            }
        }
    }

    //é liberada as memorias alocadas da heap
    free(flagPerguntas);
    free(flagSentencas);
    free(perguntas);
    free(sentencas);
    free(senDivididas);
    free(perDivididas);
}