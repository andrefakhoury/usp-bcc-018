#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_MAXIMO_BAG       202
#define INDEX_POSITIVA       200
#define INDEX_NEGATIVA       201

#define PALAVRA_NEUTRA       0
#define PALAVRA_POSITIVA    +1
#define PALAVRA_NEGATIVA    -1
#define PALAVRA_INVERSORA   11

// Protótipos 
void limparBag(int*** bag, int tamBag);
int criarNovaBag(int*** bag, int* tamBag);

void limparVetorPalavras(char*** vetPalavras, int tamPalavras);
int  buscarPalavra(char** vetPalavras, int tamPalavras, char* palavra);
int  cadastrarPalavra(char*** vetPalavras, int* tamPalavras, char* palavra);

void limparVetorProdutos(char*** vetProdutos, int tamProdutos);
int  buscarProduto(char** vetProdutos, int tamProdutos, char* nomeProduto);
int  cadastrarProduto(char*** vetProdutos, int* tamProdutos, char* nomeProduto);

void trim(char* str);
int  verificarPalavra(char* str, char positivas[12][20], char negativas[12][20], char inversoras[3][10]);

int main(void){

    int     qtdSentencas = 0, qtdPerguntas = 0, indexProduto = 0, indexPalavra = 0; 
    char    *nomeProduto = NULL, *comentarioProduto = NULL;

    char**  vetProdutos = NULL;
    int     tamProdutos = 0;

    char**  vetPalavras = NULL;
    int     tamPalavras = 0;
    char    tempPalavra[36];

    int**   bagOfWords = NULL;
    int     tamBag = 0;
    
    char    positivas[12][20] = { "bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", 
                "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char    negativas[12][20] = { "detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", 
                "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    char    inversoras[3][10] = { "nao", "jamais", "nunca"};

    scanf(" %d %d", &qtdSentencas, &qtdPerguntas);
    
    /**
     * 1ª ETAPA DO TRABALHO 
     * Processando as entradas de sentenças e associando as palavras aos seus
     * respectivos produtos. 
     */
    for(int i = 0; i < qtdSentencas; i++){
        
        /**
         * Para cada sentença verifica se o produto já existe, senão insere
         * ele na nossa indexação de produtos e cria uma bag ele.
         */

        scanf(" %m[^;]%*c %m[^\n\r]", &nomeProduto, &comentarioProduto);
        
        trim(nomeProduto);
        trim(comentarioProduto);
        
        indexProduto = buscarProduto(vetProdutos, tamProdutos, nomeProduto);
        if(indexProduto == -1){
            indexProduto = cadastrarProduto(&vetProdutos, &tamProdutos, nomeProduto);
            criarNovaBag(&bagOfWords, &tamBag);
        }

        /**
         * Percorre cada uma das palavras verificando se elas existem na bag.
         * Caso não existe insere ela no nosso vetor de palavras conhecidas.
         * 
         * Em seguida, contabiliza a palavra no bag of words do produto.
         */
        int offset = 0, ehNegativa = 0, ehPositiva = 0, inverter = 0;
        sscanf(comentarioProduto, " %s", tempPalavra);
        while(strcmp("Ø", tempPalavra) != 0){
            //printf("temp: '%s'\n", tempPalavra);

            indexPalavra = buscarPalavra(vetPalavras, tamPalavras, tempPalavra);
            if(indexPalavra == -1)
                indexPalavra = cadastrarPalavra(&vetPalavras, &tamPalavras, tempPalavra);

            // Contabilizando a palavra no bag of words do produto
            bagOfWords[indexProduto][indexPalavra] += 1;

            // Verificando se a palavra é negativa, positiva ou altera o sentido
            // Além disso o inverter contabiliza se ela terá polaridade invertida ou não.
            int polaridade = verificarPalavra(tempPalavra, positivas, negativas, inversoras);
            inverter = (inverter > 0) ? inverter-1 : 0;

            if(polaridade == PALAVRA_POSITIVA)
                (inverter == 0) ? ehPositiva++ : ehNegativa++;
            else if(polaridade == PALAVRA_NEGATIVA)
                (inverter == 0) ? ehNegativa++ : ehPositiva++;
            else if(polaridade == PALAVRA_INVERSORA)
                inverter = 4;

            // Lendo a proxima palavra na sentença
            offset += strlen(tempPalavra) + 1;
            sscanf(comentarioProduto + offset, " %s", tempPalavra);
        }

        // Verificando se o comentário foi positivo ou negativo
        if(ehPositiva >= ehNegativa)
            bagOfWords[indexProduto][INDEX_POSITIVA] += 1;
        else
            bagOfWords[indexProduto][INDEX_NEGATIVA] += 1;


        free(nomeProduto);
        free(comentarioProduto);
    }

    /** 
     * 2ª ETAPA DO TRABALHO
     * Respondendo às perguntas feitas pelo programa. Primeiro o programa
     * identifica qual será o tipo de pergunta e em seguida faz as buscas.
     */
    for(int i = 0; i < qtdPerguntas; i++){
        scanf(" %s", tempPalavra);

        // 1º tipo: "palavra $palavra em $produto\n"
        if(strcmp(tempPalavra, "palavra") == 0){
            scanf(" %s %*s %m[^\n\r]", tempPalavra, &nomeProduto);
            // printf("Buscando '%s' em '%s'\n", tempPalavra, nomeProduto);

            trim(tempPalavra);
            trim(nomeProduto);

            indexProduto = buscarProduto(vetProdutos, tamProdutos, nomeProduto);
            indexPalavra = buscarPalavra(vetPalavras, tamPalavras, tempPalavra);
            
            if(indexProduto != -1 && indexPalavra != -1)
                printf("%d\n", bagOfWords[indexProduto][indexPalavra]);
            else 
                printf("Não achou %d %d\n", indexProduto, indexPalavra);

            free(nomeProduto);

        // 2º tipo: quantos negativos/positivos em %produto
        } else {
            scanf(" %s %*s %m[^\n\r]", tempPalavra, &nomeProduto);

            trim(tempPalavra);
            trim(nomeProduto);

            indexProduto = buscarProduto(vetProdutos, tamProdutos, nomeProduto);

            float qtdPositivos = (float) bagOfWords[indexProduto][INDEX_POSITIVA];
            float qtdNegativos = (float) bagOfWords[indexProduto][INDEX_NEGATIVA];

            if(strcmp("positivos", tempPalavra) == 0){
                printf("%.1f%%\n", 100.0*qtdPositivos/(qtdPositivos+qtdNegativos) );
            } else {
                printf("%.1f%%\n", 100.0*qtdNegativos/(qtdPositivos+qtdNegativos) );
            }

            free(nomeProduto);
        }
    }

    // Imprimindo o vetor de palavras
    // for(int i = 0; i < tamPalavras; i++)
    //    printf("'%s' ", vetPalavras[i]);

    // Desalocando a memória utilizada
    limparVetorProdutos(&vetProdutos, tamProdutos);
    limparVetorPalavras(&vetPalavras, tamPalavras);
    limparBag(&bagOfWords, tamBag);

    return 0;
}

/**
 * Funções que manipulam os produtos
 */
    void limparVetorProdutos(char*** vetProdutos, int tamProdutos){
        if(vetProdutos == NULL)
            return;

        for(int i = 0; i < tamProdutos; i++)
            free((*vetProdutos)[i]);

        free(*vetProdutos);
        *vetProdutos = NULL;
    }

    int buscarProduto(char** vetProdutos, int tamProdutos, char* nomeProduto){
        if(vetProdutos == NULL || tamProdutos == 0)
            return -1;
        for(int i = 0; i < tamProdutos; i++){
            if(strcmp(nomeProduto, vetProdutos[i]) == 0)
                return i;
        }
        return -1;
    }

    int cadastrarProduto(char*** vetProdutos, int* tamProdutos, char* nomeProduto){
        if(*vetProdutos == NULL || *tamProdutos == 0){ 
            *tamProdutos     += 1;
            *vetProdutos     = malloc(sizeof(char*));
            *vetProdutos[0]  = malloc(strlen(nomeProduto)+1);
            strcpy(*vetProdutos[0], nomeProduto);
            return 0;
        } else {
            *tamProdutos                 += 1;
            *vetProdutos                 = realloc(*vetProdutos, sizeof(char*) * (*tamProdutos));
            (*vetProdutos)[*tamProdutos-1] = malloc(strlen(nomeProduto)+1);
            strcpy((*vetProdutos)[*tamProdutos-1], nomeProduto);
            return *tamProdutos-1;
        }
        return 0;
    }

/**
 * Funções que manipulam o vetor de Palavras
 */ 
    void limparVetorPalavras(char*** vetPalavras, int tamPalavras){
        if(vetPalavras == NULL)
            return;

        for(int i = 0; i < tamPalavras; i++)
            free((*vetPalavras)[i]);

        free(*vetPalavras);
        *vetPalavras = NULL;
    }

    int buscarPalavra(char** vetPalavras, int tamPalavras, char* palavra){
        if(vetPalavras == NULL || tamPalavras == 0)
            return -1;
        for(int i = 0; i < tamPalavras; i++){
            if(strcmp(palavra, vetPalavras[i]) == 0)
                return i;
        }
        return -1;
    }

    int cadastrarPalavra(char*** vetPalavras, int* tamPalavras, char* palavra){
        if(*vetPalavras == NULL || *tamPalavras == 0){ 
            *tamPalavras     += 1;
            *vetPalavras     = malloc(sizeof(char*));
            *vetPalavras[0]  = malloc(strlen(palavra)+1);
            strcpy(*vetPalavras[0], palavra);
            return 0;
        } else {
            *tamPalavras                 += 1;
            *vetPalavras                 = realloc(*vetPalavras, sizeof(char*) * (*tamPalavras));
            (*vetPalavras)[*tamPalavras-1] = malloc(strlen(palavra)+1);
            strcpy((*vetPalavras)[*tamPalavras-1], palavra);
            return *tamPalavras-1;
        }
        return 0;
    }


/**
 * Funções que manipulam a Bag
 */
    void limparBag(int*** bag, int tamBag){
        if(*bag == NULL)
            return;
        for(int i = 0; i < tamBag; i++)
            free((*bag)[i]);
        free(*bag);
        *bag = NULL;
    }

    int criarNovaBag(int*** bag, int* tamBag){
        *tamBag     += 1;
        if( (*bag) == NULL || (*tamBag) == 0){
            (*bag)      = malloc(sizeof(int*));
            (*bag)[0]   = calloc(TAM_MAXIMO_BAG, sizeof(int));
            return 0;
        } else {
            (*bag)      = realloc((*bag), sizeof(int*) * (*tamBag));
            (*bag)[*tamBag-1]   = calloc(TAM_MAXIMO_BAG, sizeof(int));
            return *tamBag-1;
        }
    }

/**
 * Funções auxiliares
 */
    void trim(char* str){
        int len = strlen(str);
        while(str[len-1] == ' ')
            len--;
        str[len] = '\0';
    }

    int verificarPalavra(char* str, char positivas[12][20], char negativas[12][20], char inversoras[3][10]){

        for(int i = 0; i < 12; i++){
            if(strcmp(str, positivas[i]) == 0)
                return PALAVRA_POSITIVA;
            else if(strcmp(str, negativas[i]) == 0)
                return PALAVRA_NEGATIVA;
            else if(i < 3 && strcmp(str, inversoras[i]) == 0)
                return PALAVRA_INVERSORA;
        }
        return PALAVRA_NEUTRA;
    }