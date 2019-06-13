#include <stdio.h> // Biblioteca para leitura e escrita
#include <stdlib.h> // Biblioteca para alocacao de memoria
#include <string.h> // Biblioteca para manupulacao de strings

/* Definicao de constantes */

#define MAXBOW 200 // Define MAXBOW como o limite de palavras do Bag-of-Words
#define MAXPALAVRAS 21 // Define MAXPALAVRAS como o limite de palavras por comentario com um espaco extra para o simbolo
#define MAXCARACTERES 20 // Define MAXCARACTERES como o limite de caracteres por palavra
#define MAXPRODUTO 50 // Define MAXPRODUTO como limite de caracteres para um produto
#define TAMANHOTIPO 8 // Define TAMANHOTIPO como limite de caracteres para o tipo de pergunta
#define TAMANHOPOSITIVONEGATIVO 12 // Define TAMANHOPOSITIVONEGATIVO como numero de possiveis palavras positivas e negativas

/* Definicoes de tipos */

/* Define tipo de struct para guardar sentenca */
typedef struct{
    char *produto; // Armazena o nome do produto
    char **comentario; // Armazena as palavras do comentario
    int numeropalavras; // Armazena o numero de palavras no comentario
}sentencas;

/* Define tipo de struct para guardar perguntas */
typedef struct{
    char *tipo; // Armazena o tipo de pergunta
    char *palavrachave; // Armazena a palavra-chave da pergunta
    char *produto; // Armazena o produto em questao
}perguntas;

/* Define tipo de struct para guardar um Bag-of-Words do produto */
typedef struct{
    char *produto; // Armazena o nome do produto ao qual os comentarios se referem
    char **palavra; // Armazena um vetor de palavras do Bag-of-Words
    int **frequencia; // Armazena um vetor de contagem de cada palavra para cada comentario
}bagofwords;

/* Declaracao de funcoes */

void TestarAlocacao(void *ponteiro);
sentencas *LeituraComentarios(int numerosentencas);
char **ListagemDeProdutos(int *numeroprodutos, sentencas *feedback, int numerosentencas);
bagofwords *CriacaoBagofWords(char **listadeprodutos, int numeroprodutos);
int PreenchimentoBagofWords(bagofwords *BoW, int numeroprodutos, sentencas *feedback, int numerosentencas);
perguntas LeituraPergunta(void);
void PerguntaPalavra(perguntas questionario, sentencas *feedback, bagofwords *BoW, int numerosentencas, int numeroprodutos);
void PerguntaQuantos(perguntas questionario, sentencas *feedback, int numerosentencas);
void LiberarMemoriaPergunta(perguntas questionario);
void LiberarMemoria(sentencas *feedback, bagofwords *BoW, int numerosentencas, int numeroprodutos, int totalpalavras);

/* Definicao de funcoes */


/* Funcao de teste da alocacao do ponteiro */
void TestarAlocacao(void *ponteiro){
    if(ponteiro == NULL){ // Se a alocacao falhar
            printf("Nao ha memoria disponivel\n"); // Exibe mensagem de erro
            exit(1); // Encerra o programa
    }
    return;
}

/* Funcao de leitura dos comentarios e realizacao os tratamentos necessarios */
sentencas *LeituraComentarios(int numerosentencas){
    int contador, iterador; // Variaveis que necessitam inicializacao
    sentencas *feedback = NULL; // Ponteiro de vetor de structs para os comentarios

    /* Alocacao das structs de comentarios */
    feedback = (sentencas *) malloc(numerosentencas * sizeof(sentencas)); // Aloca memoria para o vetor de structs
    
    /* Laco para armazenar as sentencas */
    for(contador = 0; contador < numerosentencas; contador++){
        /* Leitura do produto */
        feedback[contador].produto = (char *) malloc(MAXPRODUTO * sizeof(char)); // Aloca memoria para o nome do produto
        TestarAlocacao(feedback[contador].produto); // Testa se a alocacao teve sucesso
        scanf(" %[^;]", feedback[contador].produto); // Le o nome do produto ate o caractere ';', ignorando \r\n anteriores
        feedback[contador].produto = (char *) realloc(feedback[contador].produto, (strlen(feedback[contador].produto)) * sizeof(char)); // Reajusta o tamanho alocado;
        feedback[contador].produto[strlen(feedback[contador].produto) - 1] = '\0'; // Corrige a string, trocando ' ' por '\0'

        /* Tratamento de buffer */
        scanf("%*[;]"); // Remove o caractere ';' do buffer
        
        /* Alocacao para o vetor de comentarios */
        feedback[contador].comentario = (char **) malloc(MAXPALAVRAS * sizeof(char *)); // Aloca memoria para o comentario
        TestarAlocacao(feedback[contador].comentario); // Testa se a alocacao teve sucesso
        
        /* Leitura do comentario */
        iterador = -1; // Inicializa o contador de modo que ao entrar no laco, sera somado 1 e tera valor 0
        
        do{ // Laco de alocacao, leitura e realocacao para cada palavra
            iterador++; // Avanca o iterador para a proxima palavra
            feedback[contador].comentario[iterador] = (char *) malloc(MAXCARACTERES * sizeof(char)); // Aloca memoria para a palavra do comentario
            TestarAlocacao(feedback[contador].comentario[iterador]); // Testa se a alocacao teve sucesso
            scanf(" %s", feedback[contador].comentario[iterador]); // Le a palavra eliminando espacos antes e depois, assim como o ultimo \r\n no fim do comentario
            feedback[contador].comentario[iterador] = (char *) realloc(feedback[contador].comentario[iterador], (strlen(feedback[contador].comentario[iterador])+1) * sizeof(char)); // Reajusta o tamanho alocado;
            TestarAlocacao(feedback[contador].comentario[iterador]); // Testa se a realocacao teve sucesso
        }while(strcmp(feedback[contador].comentario[iterador], "Ø") != 0); // Interrompe o laco ao ler o simbolo
        feedback[contador].numeropalavras = iterador; // Armazena o numero de palavras lidas
    }

    return feedback;
}

/* Funcao de listagem e contagem dos produtos distintos */
char **ListagemDeProdutos(int *numeroprodutos, sentencas *feedback, int numerosentencas){ // Variavel "numeroprodutos" e passada por referencia para retornar valor a main
    int contador, comparador, repeticoes; // Variaveis que necessitam inicializacao
    char **listadeprodutos = NULL; // Armazena uma lista de produtos distintos

    *numeroprodutos = 0; // Inicializa conteudo do ponteiro

    listadeprodutos = (char **) malloc(numerosentencas * sizeof(char *)); // Alocacao da lista de produtos distintos
    TestarAlocacao(listadeprodutos); // Testa se a alocacao teve sucesso

    /* Laco para armazenamento e contagem de produtos distintos */
    for(contador = 0; contador < numerosentencas; contador++){
        repeticoes = 0; // Inicializa ou reinicializa a variavel de contagem de repeticao a cada ciclo
        for(comparador = contador - 1; comparador >= 0; comparador--){ // Laco para comparacao com produtos anteriores
            if(strcmp(feedback[contador].produto, feedback[comparador].produto) == 0){ // Se for igual a um produto anterior
                repeticoes++; // Adiciona 1 a variavel de repeticoes
            }
        }
        if(repeticoes == 0){ // Se nao houver repeticoes
            listadeprodutos[*numeroprodutos] = (char *) malloc((strlen(feedback[contador].produto) + 1) * sizeof(char)); // Aloca memoria para o nome do produto na lista
            TestarAlocacao(listadeprodutos[*numeroprodutos]); // Testa se a alocacao teve sucesso
            strcpy(listadeprodutos[*numeroprodutos], feedback[contador].produto); // Copia o nome do produto para a lista de produtos
            (*numeroprodutos)++; // Novo produto e contabilizado
        }
    }

    /* Reajuste do tamanho da lista de produtos */
    if(numerosentencas != *numeroprodutos){ // Se houver produtos repetidos
        listadeprodutos = (char **) realloc(listadeprodutos, (*numeroprodutos) * sizeof(char *)); // Reduz o tamanho do vetor da lista
    }

    return listadeprodutos; // Retorna a lista de produtos
}

/* Funcao para criar a base das Bags-of-Words */
bagofwords *CriacaoBagofWords(char **listadeprodutos, int numeroprodutos){
    int contador; // Variaveis que precisam ser inicializadas
    bagofwords *BoW = NULL; // Vetor de Bags-of-Words

    /* Alocacao das structs para as Bags-of-Words */
    BoW = (bagofwords *) malloc(numeroprodutos * sizeof(bagofwords)); // Aloca memoria para as Bags-of-Words
    TestarAlocacao(BoW); // Testa se a alocacao teve sucesso
    
    /* Laco para alocacao dos espacos dentro das Bags-of-Words */
    for(contador = 0; contador < numeroprodutos; contador++){
        BoW[contador].produto = (char *) malloc((strlen(listadeprodutos[contador]) + 1) * sizeof(char)); // Aloca memoria para o produto que se refere
        TestarAlocacao(BoW[contador].produto); // Testa se a alocacao teve sucesso
        strcpy(BoW[contador].produto, listadeprodutos[contador]); // Preenche o nome do produto a partir da lista
        free(listadeprodutos[contador]); // Descarta da lista o nome do produto copiado 
        BoW[contador].palavra = (char **) malloc(MAXBOW * sizeof(char *)); // Aloca memoria para o vetor de palavras
        TestarAlocacao(BoW[contador].palavra); // Testa se a alocacao teve sucesso
        BoW[contador].frequencia = (int **) malloc(MAXBOW * sizeof(int *)); // Aloca memoria para a matriz de frequencia
        TestarAlocacao(BoW[contador].frequencia); // Testa se a alocacao teve sucesso
    }
    free(listadeprodutos); // Descarta a lista de produtos

    return BoW;
}

/* Funcao para o preenchimento das Bags-of-Words que retorna o numero de palavras preenchidas */
int PreenchimentoBagofWords(bagofwords *BoW, int numeroprodutos, sentencas *feedback, int numerosentencas){
    int contador, comparador1, comparador2, iterador, repeticoes; // Variaveis que necessitam de inicializacao
    int totalpalavras = 0; // Variaveis inicializadas
    
    /* Laco para preenchimento */
    /* Comentario */
    for(contador = 0; contador < numerosentencas; contador++){ // Percorre cada comentario
        /* Palavra do comentario */
        for(comparador1 = 0; comparador1 < feedback[contador].numeropalavras; comparador1++){ // Percorre cada palavra do comentario
            repeticoes = 0; // Inicializa ou reinicializa a variavel para cada palavra do comentario
            /* Verifica produtos ja adicionados */
            for(comparador2 = totalpalavras - 1; comparador2 > 0; comparador2--){ // Percorre os produtos ja adicionados a Bag-of-Words
                if(strcmp(feedback[contador].comentario[comparador1], BoW[0].palavra[comparador2]) == 0){ // Se a palavra do comentario ja foi adicionada antes
                    /* Procura a Bag-of-Words do produto */
                    for(iterador = 0; iterador < numeroprodutos; iterador++){ // Percorre o nome dos produtos das Bags-of-Words
                        if(strcmp(BoW[iterador].produto, feedback[contador].produto) == 0){ // Quando achar qual Bag-of-Words representa o produto do comentario
                            BoW[iterador].frequencia[comparador2][contador]++; // Adiciona 1 na contagem de palavras da matriz de frequencia
                            break; // Termina o laco de procura de produtos
                        }
                    }
                    repeticoes++; // Adiciona 1 ao contador de repeticoes para essa palavra
                }
            }
            /* Palavra nova */
            if(repeticoes == 0){ // Se nao foi encontradas repeticoes para essa palavra
                /* Repete para cada Bag-of-Words */
                for(iterador = 0; iterador < numeroprodutos; iterador++){ // Percore cada Bag-of-Words
                    /* Vetor de palavras */
                    BoW[iterador].palavra[totalpalavras] = (char *) malloc((strlen(feedback[contador].comentario[comparador1]) + 1) * sizeof(char)); // Aloca memoria para a palavra nova
                    TestarAlocacao(BoW[iterador].palavra[totalpalavras]); // Testa se a alocacao teve sucesso
                    strcpy(BoW[iterador].palavra[totalpalavras], feedback[contador].comentario[comparador1]); // Adiciona a palavra a Bag-of-Words
                    /* Vetor de contagem */
                    BoW[iterador].frequencia[totalpalavras] = (int *) calloc(numerosentencas, sizeof(int)); // Aloca memoria para uma coluna da matriz de contagem
                    TestarAlocacao(BoW[iterador].frequencia[totalpalavras]); // Testa se a alocacao teve sucesso
                    if(strcmp(BoW[iterador].produto, feedback[contador].produto) == 0){ // Se a Bag-of-Words e referente ao produto do comentario
                        BoW[iterador].frequencia[totalpalavras][contador]++; // Adiciona 1 a contagem
                    }
                }
                /* Contador de palavras preenchidas */
                totalpalavras++; // Adiciona 1 ao numero de palavras preenchidas
            }
        }
    }

    return totalpalavras; // Retorna o numero de palavras preenchidas
}

/* Funcao para leitura e tratamento de uma pergunta */
perguntas LeituraPergunta(void){
    perguntas questionario; // Struct para perguntas

    /* Leitura do tipo de pergunta */
    questionario.tipo = (char *) malloc(TAMANHOTIPO * sizeof(char)); // Aloca memoria para a palavra do tipo
    TestarAlocacao(questionario.tipo); // Testa se a alocacao teve sucesso
    scanf(" %s", questionario.tipo); // Le a palavra do tipo
    questionario.tipo = (char *) realloc(questionario.tipo, (strlen(questionario.tipo) * sizeof(char))+1); // Reajusta o tamanho alocado
    TestarAlocacao(questionario.tipo); // Testa se a realocacao teve sucesso

    /* Leitura da palavra-chave da pergunta */
    questionario.palavrachave = (char *) malloc(MAXCARACTERES * sizeof(char)); // Aloca memoria para a palavra-chave
    TestarAlocacao(questionario.palavrachave); // Testa se a alocacao teve sucesso
    scanf(" %s", questionario.palavrachave); // Le a palavra-chave
    questionario.palavrachave = (char *) realloc(questionario.palavrachave, (strlen(questionario.palavrachave) * sizeof(char))+1); // Reajusta o tamanho alocado
    TestarAlocacao(questionario.palavrachave); // Testa se a realocacao teve sucesso
    
    /* Tratamento de buffer */
    scanf(" em ");
    
    /* Leitura do produto em questao */
    questionario.produto = (char *) malloc(MAXPRODUTO * sizeof(char));
    TestarAlocacao(questionario.produto); // Testa se a alocacao teve sucesso
    scanf(" %[^\r\n]", questionario.produto); // Le o produto
    questionario.produto = (char *) realloc(questionario.produto, (strlen(questionario.produto) * sizeof(char))+1); // Reajusta o tamanho alocado
    TestarAlocacao(questionario.produto); // Testa se a realocacao teve sucesso

    return questionario;
}

/* Funcao para responder o tipo 1 de pergunta */
void PerguntaPalavra(perguntas questionario, sentencas *feedback, bagofwords *BoW, int numerosentencas, int numeroprodutos){
    int localizacaobow, localizacaoproduto; // Variaveis que necessitam inicializacao
    int contador = 0, resposta = 0; // Variaveis inicializadas
    
    /* Procura posicao da palavra-chave da pergunta no vetor de palavras dos Bags-of-Words */
    while(strcmp(questionario.palavrachave, BoW[0].palavra[contador]) != 0){ // O vetor de palavras é igual para todo Bag-of-Words, por isso BoW[0] e arbitrario
        contador++; // Avanca o contador ate achar a palavra
    }
    localizacaobow = contador; // Armazena a posicao da palavra
    
    /* Procura a Bag-of-Words do produto */
    for(contador = 0; contador < numeroprodutos; contador++){ // Percorre cada Bag-of-Words
        if(strcmp(questionario.produto, BoW[contador].produto) == 0){ // Quando achar o produto em questao
            localizacaoproduto = contador; // Armazena o indice da Bag-of-Words do produto
            break;
        }
    }

    /* Soma todas as contagens de frequencias da palavra-chave */
    for(contador = 0; contador < numerosentencas; contador++){ // Percorre os comentarios
        if(strcmp(BoW[localizacaoproduto].produto, feedback[contador].produto) == 0){ // Se o comentario se referir ao produto da Bag-of-Words
            resposta += BoW[localizacaoproduto].frequencia[localizacaobow][contador]; // Soma a contagem da palavra em uma variavel
        }
    }

    /* Imprime a resposta */
    printf("%d\n", resposta);

    return;
}

/* Funcao para responder o tipo 2 de pergunta */
void PerguntaQuantos(perguntas questionario, sentencas *feedback, int numerosentencas){
    int contador, iterador, comparador, sucesso; // Variaveis que necessitam inicializacao
    int alcanceinversao = 0; // Variaveis inicializadas
    float positivo = 0, negativo = 0; // Variaveis de resultado
    
    /* Vetor de strings constantes para consulta */
    char palavraspositivas[TAMANHOPOSITIVONEGATIVO][12] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"}; // Lista de palavras positivas
    char palavrasnegativas[TAMANHOPOSITIVONEGATIVO][12] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"}; // Lista de palavras negativas
    char palavrasinversao[3][7] = {"nao", "jamais", "nunca"}; // Lista de palavras inversoras de polaridade

    /* Laco de vericacao de polaridade */
    /* Comentario */
    for(contador = 0; contador < numerosentencas; contador++){
        if(strcmp(questionario.produto, feedback[contador].produto) == 0){
            sucesso = 0; // Inicializa ou reinicializa a variavel de sucesso
            /* Palavra do comentario */
            for(iterador = 0; iterador < feedback[contador].numeropalavras; iterador++){
                /* Checagem nos vetores de consulta */
                for(comparador = 0; comparador < TAMANHOPOSITIVONEGATIVO; comparador++){
                    /* Checagem de inversao */
                    if(comparador < 3){ // Checa o vetor de inversao
                        if(strcmp(palavrasinversao[comparador], feedback[contador].comentario[iterador]) == 0){ // Se fizer parte do vetor
                            alcanceinversao = 4; // Inverte palavras com distancia ate 3 (4[atual] -> 3[primeiro], 2[segundo], 1[terceiro])
                            continue; // Avanca para a proxima palavra
                        }
                    }
                    /* Checagem de polaridade */
                    if(strcmp(palavraspositivas[comparador], feedback[contador].comentario[iterador]) == 0){ // Se fizer parte do vetor de positivos
                        if(alcanceinversao == 0){ // Se nao tiver no alcance de uma palavra de inversao
                            positivo++; // Adiciona 1 na contagem de comentarios positivos
                            sucesso = 1; // Sucesso em achar a polatidade e verdadeiro
                            break; // Conclui o laco de checagem
                        }else{ // Ou se tiver no alcance de uma palavra de inversao
                            negativo++; // Adiciona 1 na contagem de comentarios negativos
                            sucesso = 1; // Sucesso em achar a polaridade e verdadeiro
                            break; // Conclui o laco de checagem
                        }
                    }else if(strcmp(palavrasnegativas[comparador], feedback[contador].comentario[iterador]) == 0){ // Ou se fizer parte do vetor de negativos
                        if(alcanceinversao == 0){ // Se nao tiver no alcance de uma palavra de inversao
                            negativo++; // Adiciona 1 na contagem de comentarios negativos
                            sucesso = 1; // Sucesso em achar a polatidade e verdadeiro
                            break; // Conclui o laco de checagem
                        }else{ // Ou se tiver no alcance de uma palavra de inversao
                            positivo++; // Adiciona 1 na contagem de comentarios positivos
                            sucesso = 1; // Sucesso em achar a polatidade e verdadeiro
                            break; // Conclui o laco de checagem
                        }
                    }
                }

                /* Verificacao de condicoes */
                if(sucesso){ // Se ja achou a polaridade
                    break; // Sai do laco que percorre as palavras do mesmo comentario
                }
                if(alcanceinversao > 0){ // Se esta contando o alcance a partir de uma palavra de inversao 
                    alcanceinversao--; // Diminui 1 no alcance para o proximo teste
                }
            }
        }
    }

    /* Resultado dos testes */
    if(strcmp(questionario.palavrachave, "positivos") == 0){ // Se a pergunta pediu os positivos
        printf("%.1f%%\n", (positivo / (positivo + negativo)) * 100); // Imprime a porcentagem de positivos
    }else if(strcmp(questionario.palavrachave, "negativos") == 0){ // Se a pergunta pediu os negativos
        printf("%.1f%%\n", (negativo / (positivo + negativo)) * 100); // Imprime a porcentagem de negativos
    }

    return;
}

/* Funcao para liberar memoria da struct de pergunta */
void LiberarMemoriaPergunta(perguntas questionario){
    free(questionario.tipo); // Libera memoria do tipo
    free(questionario.palavrachave); // Libera memoria da palavra-chave
    free(questionario.produto); // Libera memoria do produto

    return;
}

/* Funcao para liberar memoria das alocacoes dinamicas restantes */
void LiberarMemoria(sentencas *feedback, bagofwords *BoW, int numerosentencas, int numeroprodutos, int totalpalavras){
    int contador, iterador; // Variaveis que necessitam de inicializacao

    /* Liberacao de memoria das structs de comentario */
    for(contador = 0; contador < numerosentencas; contador++){ // Percorre cada comentario
        free(feedback[contador].produto); // Libera memoria do produto mencionado
        iterador = 0; // Inicializa o iterador que percorrera o comentario
        while(strcmp(feedback[contador].comentario[iterador], "Ø") != 0){ // Enquanto nao chegar ao fim
            free(feedback[contador].comentario[iterador]); // Libera memoria de cada palavra
            iterador++; // Avanca o iterador
        }
        free(feedback[contador].comentario[iterador]); // Libera memoria do simbolo de fim
        free(feedback[contador].comentario); // Libera memoria do vetor de palavras do comentario
    }
    free(feedback); // Libera memoria do vetor de structs de comentario

    /* Liberacao de memoria das Bags-of-Words */
    for(contador = 0; contador < numeroprodutos; contador++){ // Percorre as Bags-of-Words
        for(iterador = 0; iterador < totalpalavras; iterador++){ // Percorre cada coluna da matriz de contagem e palavra
            free(BoW[contador].frequencia[iterador]); // Libera memoria da coluna da matriz de contagem
            free(BoW[contador].palavra[iterador]); // Libera memoria da coluna do vetor de palavra
        }
        free(BoW[contador].produto); // Libera memoria do nome do produto
        free(BoW[contador].palavra); // Libera memoria do vetor de palavra
        free(BoW[contador].frequencia); // Libera memoria da matriz de contagem
    }
    free(BoW); // Libera memoria do vetor de Bags-of-Words
}

int main(void){
    /* Declaracao de variaveis */
    int numerosentencas, numeroperguntas, numeroprodutos, totalpalavras, contador; // Variaveis que necessitam inicializacao
    char **listadeprodutos = NULL; // Vetor de produtos distintos
    sentencas *feedback = NULL; // Vetor de structs para os feedbacks
    bagofwords *BoW = NULL; // Vetor de structs para as Bags-of-Words
    perguntas questionario; // Struct para uma pergunta

    /* Execucao do programa */

    /* Leitura do tamanho da entrada */
    scanf("%d %d", &numerosentencas, &numeroperguntas); // Le o numero de sentencas e de perguntas
    
    /* Leitura e processamento dos comentarios */
    feedback = LeituraComentarios(numerosentencas); // Realiza a leitura dos comentarios para a variavel feedback
    listadeprodutos = ListagemDeProdutos(&numeroprodutos, feedback, numerosentencas); // Cria uma lista de produtos e calcula o numero de produtos na variavel "numeroprodutos"
    
    /* Formacao da Bag-of-Words */
    BoW = CriacaoBagofWords(listadeprodutos, numeroprodutos); // Cria a Bag-of-Words
    totalpalavras = PreenchimentoBagofWords(BoW, numeroprodutos, feedback, numerosentencas); // Preenche a Bag-of-Words e retorna o total de palavras preenchidas
    
    /* Leitura e resposta de cada pergunta */
    for(contador = 0; contador < numeroperguntas; contador++){ // Laco para leitura e resposta de perguntas
        questionario = LeituraPergunta(); // Le a pergunta
        if(strcmp(questionario.tipo, "palavra") == 0){ // Se a pergunta comecar com "palavra"
            PerguntaPalavra(questionario, feedback,  BoW, numerosentencas, numeroprodutos); // Responde a pergunta com o numero de palavras
        }else if(strcmp(questionario.tipo, "quantos") == 0){ // Ou se a pergunta comecar com "quantos"
            PerguntaQuantos(questionario, feedback, numerosentencas); // Responde a porcentagem de comentarios positivos
        }
        LiberarMemoriaPergunta(questionario); // Libera a memoria usada para armazenar a pergunta
    }
    
    /* Finalizacao do programa */
    LiberarMemoria(feedback, BoW, numerosentencas, numeroprodutos, totalpalavras); // Libera todas as alocacoes dinamicas restantes

    return 0;
}