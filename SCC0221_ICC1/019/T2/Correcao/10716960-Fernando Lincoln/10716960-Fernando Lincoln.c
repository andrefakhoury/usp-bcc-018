#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAX_PRODUTO_NOME 40
#define MAX_PRODUTOS 200
#define MAX_TAM_PALAVRA 20
#define MAX_PALAVRAS 200
#define MAX_COMENTARIO_PALAVRAS 20

// Definindo as palavras para cada tipo
const char *palavra_positiva[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
const char *palavra_negativa[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
const char *palavra_inversao[] = {"nao", "jamais", "nunca"};

// Tipos possíveis de palavras
enum tipo_palavra {positiva, negativa, inversao, neutra};

// Vetor que associa para cada id um nome de um produto
char id_produto[MAX_PRODUTOS][MAX_PRODUTO_NOME];
int tam_id_produto = 0;

// Vetor que associa para cada id uma palavra
char id_palavra[MAX_PALAVRAS][MAX_TAM_PALAVRA];
int tam_id_palavra = 0;

// Vetor que salva os comentários recebidos por cada produto
int quantidade_comentarios[MAX_PRODUTOS] = {0}; // Total de comentários para um produto
int comentarios_positivos[MAX_PRODUTOS] = {0};
int comentarios_negativos[MAX_PRODUTOS] = {0};

// Bag of Words - Vetor bidimensional [i, j] que grava o número de ocorrências de uma
// palavra j para cada produto i
int BoW[MAX_PRODUTOS][MAX_PALAVRAS] = {0};

int obter_id_produto(const char *produto); // Função para obter o id de um produto pelo nome
int registrar_produto(const char *produto); // Função para associar um produto a um id. Retorna o id associado

int obter_id_palavra(const char *palavra); // Função para obter o id de uma palavra
int registrar_palavra(const char *palavra); // Função para associar uma palavra a um id. Retorna o id associado

// Retorna se uma palavra é positiva, negativa, de inversão ou neutra
enum tipo_palavra checar_palavra(const char *palavra);

// Processa um comentário para um produto id_prod
void processar_comentario(int id_prod, const char *comentario);

int main(){
    int comentarios, perguntas;
    scanf("%d %d", &comentarios, &perguntas);

    // Laço para processar os comentários
    for (int i = 0;i < comentarios;i++){
        char produto[MAX_PRODUTO_NOME];
        char comentario[MAX_COMENTARIO_PALAVRAS*MAX_TAM_PALAVRA];

        // Obtém o nome completo do produto e o comentário
        scanf(" %[^;]; %[^\n\r]", produto, comentario);
        produto[strlen(produto)-1]='\0'; // Eliminando espaço
        comentario[strlen(comentario)-2]='\0'; // Eliminando espaço e o caractere Ø

        // Associa o nome do produto a id e processa o comentário para o mesmo
        int id = registrar_produto(produto);
        processar_comentario(id, comentario);
        quantidade_comentarios[id]++;
    }

    // Laço para processar as perguntas
    for (int j = 0;j<perguntas;j++){
        char palavra[5][MAX_TAM_PALAVRA];
        scanf("%s %s %s %s %s", palavra[0], palavra[1], palavra[2], palavra[3], palavra[4]);

        // Concatenando as duas últimas palavras do texto para formar o nome do produto
        char nome_produto[MAX_PRODUTO_NOME];
        strcpy(nome_produto, palavra[3]);
        strcat(nome_produto, " ");
        strcat(nome_produto, palavra[4]);

        // Obtendo o id do produto
        int produto = obter_id_produto(nome_produto);

        // Checando o tipo de pergunta através da primeira palavra
        if (strcmp(palavra[0], "palavra") == 0){
            // Tendo o id do produto e o id da palavra podemos obter a quantidade de
            // ocorrências dessa palavra para esse produto pelo BoW
            int codigo_da_palavra = obter_id_palavra(palavra[1]);
            printf("%d\n", BoW[produto][codigo_da_palavra]);
        }
        else{
            // Checa se é pedido os comentários positivos ou negativos e da a resposta
            float porcentagem = 0;
            if (strcmp(palavra[1], "positivos") == 0)
                porcentagem = (float)comentarios_positivos[produto]/(float)quantidade_comentarios[produto];
            else
                porcentagem = (float)comentarios_negativos[produto]/(float)quantidade_comentarios[produto];
            printf("%.1f%%\n", porcentagem*100.);
        }
    }

    return 0;
}

int obter_id_produto(const char *produto){
    // Busca por todo o vetor id_produto o id do produto
    for (int i = 0;i < tam_id_produto;i++){
        if (strcmp(produto, id_produto[i]) == 0)
            return i;
    }
    // Caso o produto não esteja associado, retorna -1
    return -1;
}

int registrar_produto(const char *produto){
    // Registra o produto em um id somente se ele não estiver associado
    // ainda, ou seja, se o id for igual a -1
    int id = obter_id_produto(produto);
    if (id == -1){
        strcpy(id_produto[tam_id_produto], produto);
        id = tam_id_produto;
        tam_id_produto++;
    }
    return id;
}

int obter_id_palavra(const char *palavra){
    // Busca por todo o vetor id_palavra o id da palavra
    for (int i = 0;i < tam_id_palavra;i++){
        if (strcmp(palavra, id_palavra[i]) == 0)
            return i;
    }
    // Caso a palavra não esteja associada, retorna -1
    return -1;
}

int registrar_palavra(const char *palavra){
    // Registra a palavra em um id somente se ele não estiver associado
    // ainda, ou seja, se o id for igual a -1
    int id = obter_id_palavra(palavra);
    if (id == -1){
        strcpy(id_palavra[tam_id_palavra], palavra);
        id = tam_id_palavra;
        tam_id_palavra++;
    }
    return id;
}

enum tipo_palavra checar_palavra(const char *palavra){
    // Itera pelos vetores constantes palavra_positiva[], palavra_negativa[] e palavra_inversao[]
    // buscando pela palavra, retornando assim seu tipo
    for (int i = 0;i<12;i++){
        if (strcmp(palavra, palavra_positiva[i]) == 0)
            return positiva;
    }
    for (int i = 0;i<12;i++){
        if (strcmp(palavra, palavra_negativa[i]) == 0)
            return negativa;
    }
    for (int i = 0;i<3;i++){
        if (strcmp(palavra, palavra_inversao[i]) == 0)
            return inversao;
    }
    return neutra;
}

void processar_comentario(int id_prod, const char *comentario){
    int t = strlen(comentario);     // Tamanho do comentário
    char palavra[MAX_TAM_PALAVRA];  // Esse vetor gravará a palavra encontrada ao iterar pelo comentário
    int tamanho = 0;                // Tamanho da palavra encontrada
    int index_inversao = -4;        // Posição em que for encontrada uma palavra de inversão
    int index_palavra = 0;          // Posição da atual palavra encontrada
    int avaliado = 0;               // Grava se o comentário ja foi avaliado

    // Iterando por todos os caracteres do comentário
    for(int i = 0;i<t;i++){
        char c = comentario[i]; // Atual caractere

        // Se c for um "espaço", foi encontrada uma palavra
        if (c == ' '){
            // Se não tem tamanho, não é uma palavra. Exemplo: "dois espaços"
            if (tamanho == 0) continue;
            palavra[tamanho] = '\0';
            tamanho = 0;

            // Associando a palavra a um id e salvando no bag of words do produto
            // ao qual está sendo processado o comentário
            int id_palavra = registrar_palavra(palavra);
            BoW[id_prod][id_palavra]++;

            // Se o comentário ainda não foi avaliado, avalie
            if (!avaliado){
                // Checando o tipo da palavra para avaliar o comentário
                switch(checar_palavra(palavra)){
                    case inversao:
                        index_inversao = index_palavra; // Salvando a posição da palavra de inversão
                        break;

                    case positiva:
                        // Analisa se existe inversão de polaridade e avalia o comentário
                        if (index_palavra-index_inversao <= 3) comentarios_negativos[id_prod]++;
                        else comentarios_positivos[id_prod]++;
                        avaliado = 1;
                        break;

                    case negativa:
                        // Analisa se existe inversão de polaridade e avalia o comentário
                        if (index_palavra-index_inversao <= 3) comentarios_positivos[id_prod]++;
                        else comentarios_negativos[id_prod]++;
                        avaliado = 1;
                        break;

                    case neutra:
                        // Se for neutra, não faz nada
                        break;
                }
            }

            // Incrementa a posição da palavra para a próxima
            index_palavra++;
        }
        else{
            // Salva o caractere na palavra que está sendo lida
            palavra[tamanho] = c;
            tamanho++;
        }
    }
}
