/*
 * Observacao: Eu nao utilizaei o conceito de bag of word, eu simplesmente estou salvando tudo em uma matriz de string
 * Cada celula da matriz eh uma palavra
 * A primeira linha da matriz refere ao nome do produto e a marca concatenadas separada por espaco
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PALAVRA 20 // 19 caracteres + caracter '\0'
#define MAX_PALAVRA 20

#define BUSCA_TIPO_PALAVRA 0
#define BUSCA_TIPO_NEGATIVOS 1
#define BUSCA_TIPO_POSITIVOS 2

#define NUM_PALAVRAS_POSITIVAS 12
#define NUM_PALAVRAS_NEGATIVAS 12
#define NUM_ADVERBIOS_NEGACAO 3

const char PALAVRAS_POSITIVAS[NUM_PALAVRAS_POSITIVAS][TAM_PALAVRA] =
    {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};

const char PALAVRAS_NEGATIVAS[NUM_PALAVRAS_NEGATIVAS][TAM_PALAVRA] =
    {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};

const char ADVERBIOS_NEGACAO[NUM_ADVERBIOS_NEGACAO][TAM_PALAVRA] =
    {"nao", "jamais", "nunca"};

// Armazena dados para fazer as buscas dentro da matriz de string
struct busca
{
    short tipo;
    char produto[TAM_PALAVRA * 2];

    /*
     * Usado em buscas do tipo PALAVRA para armazenar qual palavra deve ser contada
     * 
     * Nao eh usado em buscas do tipo NEGATIVO ou POSITIVO
     */
    char palavra[TAM_PALAVRA];

    /*
     * Usado em buscas do tipo PALAVRA para armazenar a quantidade de vezes que a palavra aparece na frase
     * 
     * Usado em buscas do tipo NEGATIVO ou POSITIVO para armazenar quantidade de comentarios positivos sobre o produto
     */
    int positivo;

    /*
     * Nao eh usado em buscas do tipo PALAVRA
     * 
     * Usado em buscas do tipo NEGATIVO ou POSITIVO para armazenar quantidade de comentarios negativos sobre o produto
     */
    int negativo;
};

/* ------- PROTOTIPOS DE FUNCOES ------- */

// Exibe um erro caso a pergunta digitada nao seja reconhecida na funcao scanb() e em funcoes que dependa da estrutura busca
void erro_busca(char *res);

// Exibe erro por falta de memoria disponivel durante alocacao dinamica
void erro_alocacao();

// Faz a seguinte concatenacao dest + " " + src , e armazena em dest
void prodcat(char *dest, char *src);

/*
 * Imprime a matriz de string na tela
 * (ajuda a testar e corrigir o codigo)
 */
void printm(char ***mat, int n);

// Le dados e armazena numa matriz de strings
void scanm(char ***mat, int n);

/*
 * Imprime o vetor de struct busca na tela
 * (ajuda a testar e corrigir o codigo)
 */
void printb();

// Le dados e armazena num vetor de struct busca
void scanb();

// Retorna uma matriz de strings alocada dinamicamente (obs: strings eh char *)
char ***aloca_matriz(int n);

// Retorna uma string de tamanho n alocada dinamicamente (obs: strings eh char *)
char *aloca_string(int n);

// Desaloca a matriz de strings liberando espaco na memoria
void desaloca_matriz_strings(char ***mat, int n);

// Processa todas as buscas presentes no vetor perguntas, preenchendo o campo da struct
void processa_perguntas(char ***palavras, struct busca *perguntas, int num_sentencas, int num_perguntas);

// Exibe respostas processadas
void exibe_respostas(struct busca *perguntas, int n);

/* --- FIM DOS PROTOTIPOS DE FUNCOES --- */

void erro_busca(char *pergunta)
{
    printf("Pergunta nao reconhecida (%s)\n", pergunta);
    exit(1);
    return;
}

void erro_alocacao()
{
    printf("Sem memoria disponivel para alocacao dinamica\n");
    exit(1);
    return;
}

void prodcat(char *dest, char *src)
{
    strcat(dest, " ");
    strcat(dest, src);
    return;
}

void printm(char ***mat, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("[%3d] -> (%-40s) ", i, mat[i][0]);
        for (j = 1; j < MAX_PALAVRA + 1; j++)
        {
            if (mat[i][j] != NULL)
            {
                printf("\"%s\" ", mat[i][j]);
            }
            else
            {
                printf("* ");
            }
        }
        printf("\n");
    }
    return;
}

void scanm(char ***mat, int n)
{
    int i, j;

    char aux1[TAM_PALAVRA];
    // TAM_PALAVRA * 2 pois para guardar a marca eh o tamanho da palavra mais ' ' mais o tamanho de outra palacra mais o '\0'
    char aux2[TAM_PALAVRA * 2];

    for (i = 0; i < n; i++)
    {
        scanf(" %s", aux2);
        scanf(" %s", aux1);
        prodcat(aux2, aux1);
        mat[i][0] = aloca_string(strlen(aux2));
        strcpy(mat[i][0], aux2);

        scanf(" %*c"); // Some com o ';'

        j = 1;
        while (j <= MAX_PALAVRA + 1) // MAX_PALAVRA + 1 para ter tempo de ler o "Ø"
        {
            scanf(" %s", aux1);
            if (strcmp(aux1, "Ø") == 0)
            {
                break;
            }
            mat[i][j] = aloca_string(strlen(aux1));
            strcpy(mat[i][j++], aux1);
        }
    }
    return;
}

void printb(struct busca *vet, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (vet[i].tipo == BUSCA_TIPO_PALAVRA)
        {
            printf("[%3d] -> tipo: Palavra      \tproduto: %-40s\tpalavra: %-45s\tquantidade: %d\n", i, vet[i].produto, vet[i].palavra, vet[i].positivo);
        }
        else if (vet[i].tipo == BUSCA_TIPO_POSITIVOS)
        {
            printf("[%3d] -> tipo: Positivo     \tproduto: %-40s\tpositivo: %-40d\tnegativo:%d\n", i, vet[i].produto, vet[i].positivo, vet[i].negativo);
        }
        else if (vet[i].tipo == BUSCA_TIPO_NEGATIVOS)
        {
            printf("[%3d] -> tipo: Negativo     \tproduto: %-40s\tpositivo: %-40d\tnegativo:%d\n", i, vet[i].produto, vet[i].positivo, vet[i].negativo);
        }
        else
        {
            printf("[%3d]!-> tipo: %d\tproduto: %-40s\tpalavra: %-40s\tpositivo: %-40d\tnegativo:%d\n", i, vet[i].tipo, vet[i].produto, vet[i].palavra, vet[i].positivo, vet[i].negativo);
        }
    }
    return;
}

void scanb(struct busca *vet, int n)
{
    int i;

    char aux[TAM_PALAVRA];

    for (i = 0; i < n; i++)
    {
        scanf(" %s", aux);
        if (strcmp(aux, "palavra") == 0)
        {
            vet[i].tipo = BUSCA_TIPO_PALAVRA;
            scanf(" %s %*s %s %s ", vet[i].palavra, vet[i].produto, aux); // %*s some com o "em"
            prodcat(vet[i].produto, aux);
            vet[i].positivo = 0;
        }
        else if (strcmp(aux, "quantos") == 0)
        {
            scanf(" %s ", aux);

            if (strcmp(aux, "positivos") == 0)
            {
                vet[i].tipo = BUSCA_TIPO_POSITIVOS;
            }
            else if (strcmp(aux, "negativos") == 0)
            {
                vet[i].tipo = BUSCA_TIPO_NEGATIVOS;
            }
            else
            {
                erro_busca(aux);
            }

            scanf(" %*s %s %s ", vet[i].produto, aux);
            prodcat(vet[i].produto, aux);
            vet[i].positivo = 0;
            vet[i].negativo = 0;
        }
        else
        {
            erro_busca(aux);
        }
    }
    return;
}

char ***aloca_matriz(int n)
{
    int i, j;
    char ***matriz; // ponteiro de ponteiro para uma string (string eh um ponteiro para char)
    matriz = (char ***)malloc(n * sizeof(char **));

    if (matriz == NULL)
    {
        erro_alocacao();
    }

    for (i = 0; i < n; i++)
    {
        // MAX_PALAVRA + 1 pois alem das palavras do comentario temos o nome do produto
        matriz[i] = (char **)malloc((MAX_PALAVRA + 1) * sizeof(char *));
        if (matriz[i] == NULL)
        {
            erro_alocacao();
        }

        /*
         * Cada string será alocada apenas se necessario
         * Para marcar celulas da matriz que nao receberam alocacao de string sera atribuido NULL ao ponteiro
         * (inicializa ponteiro para nao haver acessos a enderecos de memoria nao alocados para esse programa)
         */
        for (j = 1; j < MAX_PALAVRA + 1; j++)
        {
            matriz[i][j] = NULL;
        }
    }

    return matriz;
}

char *aloca_string(int n)
{
    char *str;
    str = (char *)malloc((n + 1) * sizeof(char));
    if (str == NULL)
    {
        erro_alocacao();
    }
    return str;
}

void desaloca_matriz_strings(char ***mat, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < MAX_PALAVRA + 1; j++)
        {
            if (mat[i][j] != NULL)
            {
                free(mat[i][j]);
            }
        }
        if (mat[i] != NULL)
        {
            free(mat[i]);
        }
    }
    if (mat != NULL)
    {
        free(mat);
    }
    return;
}

void processa_perguntas(char ***palavras, struct busca *perguntas, int num_sentencas, int num_perguntas)
{
    int negacao;
    int pi, pj; // Contadores para palavras
    int qi;     // Contador para perguntas
    int ci;     // Contador para PALAVRAS_POSITIVAS, PALAVRAS_NEGATIVAS, ADVERBIOS_NEGACAO
    int flag;   // Para saber se ja foi possivel definir se a frase eh negativa ou positiva para poder pular para proxima

    // Embora pareca que 3 for aninhados vai consumir muito tempo, o terceiro for nao faz mais que MAX_PALAVRA operacoes
    // Entao a complexidade eh proximo a O(num_palavras*num_perguntas)
    for (pi = 0; pi < num_sentencas; pi++)
    {
        for (qi = 0; qi < num_perguntas; qi++)
        {
            if (strcmp(palavras[pi][0], perguntas[qi].produto) == 0)
            {
                negacao = 0;
                flag = 0;
                switch (perguntas[qi].tipo)
                {
                case BUSCA_TIPO_PALAVRA:
                    // Esse for nao consomem muito tempo pois tem o numero de iteracoes maxima definido por constantes
                    for (pj = 1; pj < MAX_PALAVRA && palavras[pi][pj] != NULL; pj++)
                    {
                        if (strcmp(palavras[pi][pj], perguntas[qi].palavra) == 0)
                        {
                            perguntas[qi].positivo++;
                        }
                    }
                    break;

                case BUSCA_TIPO_POSITIVOS:
                case BUSCA_TIPO_NEGATIVOS:
                    for (pj = 0; pj < MAX_PALAVRA && palavras[pi][pj] != NULL; pj++)
                    {
                        // Os for's abaixo nao consomem muito tempo pois tem o numero de iteracoes maxima definido por constantes

                        for (ci = 0; ci < NUM_PALAVRAS_POSITIVAS; ci++)
                        {
                            if (strcmp(palavras[pi][pj], PALAVRAS_POSITIVAS[ci]) == 0)
                            {
                                if (negacao > 0)
                                {
                                    perguntas[qi].negativo++;
                                    negacao--;
                                    flag = 1;
                                    break;
                                }
                                else
                                {
                                    perguntas[qi].positivo++;
                                    negacao--;
                                    flag = 1;
                                    break;
                                }
                            }
                        }

                        for (ci = 0; ci < NUM_PALAVRAS_NEGATIVAS; ci++)
                        {
                            if (strcmp(palavras[pi][pj], PALAVRAS_NEGATIVAS[ci]) == 0)
                            {
                                if (negacao > 0)
                                {
                                    perguntas[qi].positivo++;
                                    negacao--;
                                    flag = 1;
                                    break;
                                }
                                else
                                {
                                    perguntas[qi].negativo++;
                                    negacao--;
                                    flag = 1;
                                    break;
                                }
                            }
                        }
                        negacao--;

                        // Como eu ja encontrei se o comentario e positivo ou negativo eu nao preciso continuar buscar palavras no comentario
                        if (flag)
                        {
                            break;
                        }

                        for (ci = 0; ci < NUM_ADVERBIOS_NEGACAO; ci++)
                        {
                            if (strcmp(palavras[pi][pj], ADVERBIOS_NEGACAO[ci]) == 0)
                            {
                                negacao = 3;
                                break;
                            }
                        }
                    }
                    break;

                default:
                    printf("%d\n", perguntas[pi].tipo);
                    erro_busca("processa_perguntas()");
                    exit(1);
                    break;
                }
            }
        }
    }
    return;
}

void exibe_respostas(struct busca *perguntas, int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        switch (perguntas[i].tipo)
        {
        case BUSCA_TIPO_PALAVRA:
            printf("%d\n", perguntas[i].positivo);
            break;

        case BUSCA_TIPO_POSITIVOS:
            printf("%.1f%%\n", ((double)perguntas[i].positivo) / (perguntas[i].positivo + perguntas[i].negativo) * 100);
            break;

        case BUSCA_TIPO_NEGATIVOS:
            printf("%.1f%%\n", ((double)perguntas[i].negativo) / (perguntas[i].positivo + perguntas[i].negativo) * 100);
            break;

        default:
            erro_busca("exibe_resposta()");
            break;
        }
    }
    switch (perguntas[n - 1].tipo)
    {
    case BUSCA_TIPO_PALAVRA:
        printf("%d", perguntas[n - 1].positivo);
        break;

    case BUSCA_TIPO_POSITIVOS:
        printf("%.1f%%", ((double)perguntas[n - 1].positivo) / (perguntas[n - 1].positivo + perguntas[n - 1].negativo) * 100);
        break;

    case BUSCA_TIPO_NEGATIVOS:
        printf("%.1f%%", ((double)perguntas[n - 1].negativo) / (perguntas[n - 1].positivo + perguntas[n - 1].negativo) * 100);
        break;

    default:
        erro_busca("exibe_resposta()");
        break;
    }

    return;
}

int main(void)
{
    char ***palavras; // ponteiro de ponteiro para uma string (string eh um ponteiro para char)
    int num_sentencas, num_perguntas;
    scanf("%d %d", &num_sentencas, &num_perguntas);

    palavras = aloca_matriz(num_sentencas);
    scanm(palavras, num_sentencas);

    struct busca *perguntas = (struct busca *)malloc(num_perguntas * sizeof(struct busca));
    if (perguntas == NULL)
    {
        erro_alocacao();
    }

    scanb(perguntas, num_perguntas);

    processa_perguntas(palavras, perguntas, num_sentencas, num_perguntas);
    exibe_respostas(perguntas, num_perguntas);

    desaloca_matriz_strings(palavras, num_sentencas);
    free(perguntas);

    return 0;
}