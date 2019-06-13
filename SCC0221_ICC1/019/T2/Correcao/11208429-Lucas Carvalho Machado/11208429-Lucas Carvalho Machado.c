/**
 *  Programa: Contando Palavras (Trabalho 2)
 * 
 *  Disciplina: SCC0221 - Introdução à Ciência da Computação I
 *  Professor: Rudinei Goularte
 * 
 *  Descrição: Processa automaticamente diversas linhas de comentários por meio do
 *             modelo "Bag of Words" e responde perguntas sobre os dados fornecidos.
 * 
 *  Aluno: Lucas Carvalho Machado (2019.01)
 */
#include <stdio.h>
#include <string.h>

typedef struct Palavra { // Estrutura base da representação "Bag of Words" (BoW). 
    char word[22];       // Cada 'palavra' é composta por uma string WORD 
    int frequencia;      // e um contador FREQUENCIA.
} palavra;

typedef struct Frase {   // Nível intermediário. Representa cada linha de comentário individualmente.
    palavra bow[202];    // Permite a criação de uma BOW (vetor de palavras) para cada comentário.
    int num_words;       // Também possui um contador de palavras únicas NUM_WORDS.
} frase;

typedef struct Produto {  // Nível mais alto da base de dados.
    char nome[22];        // Cada 'produto' tem um NOME, 
    frase comments[15];   // um vetor de frases COMMENTS,
    int num_comments;     // e um contador NUM_COMMENTS.
} produto;

// O elemento nulo (NULL) indica o fim do vetor de strings, facilitando iterar sobre seus elementos em loops.
const char *goodwords[13] = {
                            "bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei",
                            "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima", NULL
                            }; // Termos usados para elogiar produtos

const char *badwords[13] = {                                                                     
                            "detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio",
                            "pessima", "lento", "lenta", "fragil", "desisti", NULL
                           }; // Termos usados por usuários insatisfeitos

const char *reversepolarity[4] = {"nao", "jamais", "nunca", NULL}; // Advérbios de negação, capazes de "inverter a polaridade"

// Procura PRODUCT dentre os produtos de DATABASE.
// Retorna o seu índice, ou -1 se não for encontrado.
int indexOfProduto(const char *product, produto *database, int size);

// Procura WORD numa "Bag of Words".
// Retorna o seu índice, ou -1 se não for encontrada.
int indexOfWord(const char *word, produto *database, int product, int comment);

// Inclui NEW_WORD na localização fornecida.
// Inicializa sua 'frequencia' como 1 e atualiza o 'num_words' da BoW. 
void includeWord(const char *new_word, produto *database, int product, int comment);

// Remove espaços em branco indesejados à direita de STR.
void removeSpace(char *str);
 
int main(void) {
 
    int num_frases, num_perguntas;
    int qtd_produtos = 0, soma_frequencias = 0, goodcomments = 0, badcomments = 0;

    // Variáveis usadas para armazenar índices da base de dados, fornecidos pelas funções indexOfProduto() e indexOfWord().
    // Inicializadas como -1 para indicar que nenhum índice lhes foi atribuído.
    int id_word = -1, id_produto = -1, id_comment = -1, polaridade = -1, inverte = -1;

    float porcentagem;
 
    char novo_produto[25], nova_palavra[25], pergunta[25], palavra_desejada[25], produto_desejado[25]; // Strings auxiliares
 
    produto produtos[25]; // Vetor de produtos que compõe a base de dados a ser construída a partir das entradas.

    scanf("%d %d", &num_frases, &num_perguntas);
 
    for (int i = 0; i < num_frases; i++) {

        scanf(" %[^;];", novo_produto); // Ler a entrada até o caractere ';' e armazenar temporariamente em 'novo_produto'
        removeSpace(novo_produto);      // Formatar a string, removendo o espaço em branco indesejado

        id_produto = indexOfProduto(novo_produto, produtos, qtd_produtos); // Procurar pelo produto na base de dados

        // Se não for encontrado, fazer o seu cadastro e atualizar a quantidade de produtos
        if (id_produto == -1) { 
            id_produto = qtd_produtos;
            strcpy(produtos[qtd_produtos++].nome, novo_produto);
        }

        id_comment = produtos[id_produto].num_comments; // Índice do comentário atual sobre o produto 'id_produto'
 
        // Loop que faz a leitura do comentário palavra por palavra, até o caractere 'Ø'
        scanf(" %s", nova_palavra);
        while (strcmp(nova_palavra, "Ø") != 0) { 
            id_word = indexOfWord(nova_palavra, produtos, id_produto, id_comment); // Procurar 'nova_palavra' na BoW

            if (id_word > -1) { 
                produtos[id_produto].comments[id_comment].bow[id_word].frequencia++; // Se encontrada, somar 1 à sua 'frequencia'
            } else {
                includeWord(nova_palavra, produtos, id_produto, id_comment); // Senão, incluí-la na Bag of Words
            }
            scanf(" %s", nova_palavra); // Ler a próxima palavra
        }

        produtos[id_produto].num_comments++; // Atualizar o nº de comentários sobre o produto 'id_produto'
    }

    for (int i = 0; i < num_perguntas; i++) {
        // Armazenando as palavras-chave das perguntas em strings auxiliares
        scanf(" %s %s", pergunta, palavra_desejada);
        scanf(" %*s %[^\n\r]", produto_desejado);

        // Armazenando o índice do produto em questão, para acesso dos elementos das structs
        id_produto = indexOfProduto(produto_desejado, produtos, qtd_produtos);

        // Há dois tipos de perguntas possíveis, que serão diferenciados analisando a string 'pergunta'
        if (strcmp(pergunta, "palavra") == 0) {
        // Pergunta A: quantas vezes os usuários usam 'palavra_desejada' em um comentário sobre 'produto_desejado'?

            // Para cada comentário j do produto 'id_produto', procurar pela 'palavra_desejada'
            soma_frequencias = 0;
            for (int j = 0; j < produtos[id_produto].num_comments; j++) {
                id_word = indexOfWord(palavra_desejada, produtos, id_produto, j);

                // Se encontrada, somar seu elemento 'frequencia' a uma variável acumuladora
                if (id_word > -1) {
                    soma_frequencias += produtos[id_produto].comments[j].bow[id_word].frequencia;
                }
            }

            printf("%d\n", soma_frequencias);
        } else { 
        // Pergunta B: quantas pessoas estão falando bem/mal do ‘produto_desejado’?
            goodcomments = 0; // Nº de comentários positivos
            badcomments = 0;  // e negativos, dado um produto.

            // Analisar uma a uma a polaridade dos comentários j sobre o produto 'id_produto'
            for (int j = 0; j < produtos[id_produto].num_comments; j++) {
                 
                polaridade = -1; // Variáveis p/ armazenar o índice da palavra que representa polaridade,
                inverte = -1;    // e do advérbio de negação, caso existam.

                // Procurando uma palavra positiva no comentário j
                int k = 0;
                while (goodwords[k] != NULL) {
                    id_word = indexOfWord(goodwords[k], produtos, id_produto, j);
                    if (id_word > -1) {
                        polaridade = id_word; // Se encontrada, armazena-se seu índice em 'polaridade'
                        break;
                    }
                    k++;
                }

                // Se um índice existente foi atribuido a 'polaridade', por hora o comentário j é positivo
                if (polaridade > -1) {

                    // Resta procurar um advérbio de negação que possivelmente inverteria sua polaridade
                    k = 0;
                    while (reversepolarity[k] != NULL) {
                        id_word = indexOfWord(reversepolarity[k], produtos, id_produto, j);

                        if (id_word > -1) {
                            inverte = id_word; // Se encontrado, armazena-se seu índice em 'inverte'

                            // Se o advérbio encontra-se a até 3 posições antes da palavra positiva, a polaridade é invertida.
                            if (polaridade - inverte <= 3 && polaridade - inverte >= 0) {
                                badcomments++;
                                break;
                            } else {  
                                inverte = -1; // Senão, 'inverte' é reinicializada para -1,
                            }
                        }
                        k++; // e procura-se por outro advérbio, até não haverem mais.
                    }

                    if (inverte == -1) { // A polaridade é mantida se nenhum advérbio encontrado
                        goodcomments++;  // satisfazer as condições acima, ou se não houver nenhum.
                    }
                } else {
                    // Caso nenhuma palavra positiva seja encontrada, então j tem uma palavra negativa 
                    k = 0;
                    while (badwords[k] != NULL) {
                        id_word = indexOfWord(badwords[k], produtos, id_produto, j);
                        if (id_word > -1) {
                            polaridade = id_word; // Procurando seu índice e armazenando em 'polaridade'
                            break;
                        }
                        k++;
                    }

                    // Procurando por advérbios de negação
                    k = 0;
                    while (reversepolarity[k] != NULL) {
                        id_word = indexOfWord(reversepolarity[k], produtos, id_produto, j);
                        if (id_word > -1) {
                            inverte = id_word;
                            if (polaridade - inverte <= 3 && polaridade - inverte >= 0) {
                                goodcomments++; // A polaridade foi invertida (logo o comentário é positivo)
                                break;
                            } else {
                                inverte = -1;   // Advérbio muito distante (recomeçar a procura)
                            }
                        }
                        k++;
                    }
                    if (inverte == -1) {
                        badcomments++; // Se o loop terminou sem alterção na polaridade, o comentário é negativo.
                    }
                }
            }
            
            // O cálculo da porcentagem de comentários positivos ou negativos é feito analisando a string coletada na entrada.
            // Usa-se casting para float, por se tratar de operações involvedo variáveis do tipo int.
            if (strcmp(palavra_desejada, "positivos") == 0) {
                porcentagem = (float) 100 * goodcomments / produtos[id_produto].num_comments;
            } else {
                porcentagem = (float) 100 * badcomments / produtos[id_produto].num_comments;
            }
            printf("%.1f%%\n", porcentagem);
        }
    }

    return 0;
}

// Código das funções utilizadas:
int indexOfProduto(const char *product, produto *database, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(database[i].nome, product) == 0) {
            return i;
        }
    }
    return -1;
}

int indexOfWord(const char *word, produto *database, int product, int comment) {
    for (int i = 0; i < database[product].comments[comment].num_words; i++) {
        if (strcmp(database[product].comments[comment].bow[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}
 
void includeWord(const char *new_word, produto *database, int product, int comment) {
    int i = database[product].comments[comment].num_words;
    database[product].comments[comment].num_words++;
    strcpy(database[product].comments[comment].bow[i].word, new_word);
    database[product].comments[comment].bow[i].frequencia = 1;
    return;
}

void removeSpace(char *str) {
    size_t size = strlen(str);
    str[size - 1] = '\0';
    return;
}