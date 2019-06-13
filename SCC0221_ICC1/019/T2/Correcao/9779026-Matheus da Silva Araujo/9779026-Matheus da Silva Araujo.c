/*
Nome: Matheus da Silva Araujo
NUSP: 9779026
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_DA_PALAVRA 20
#define TAMANHO_DO_BOW 200
#define TAMANHO_DA_FRASE 500
#define NUMERO_DE_OPINIOES 12
#define ELOGIO 0
#define CRITICA 1
#define NUMERO_DE_INVERSORES 3

// Uma palavra é um vetor de chars (uma string) de tamanho máximo TAMANHO_DA_PALAVRA (que é 20, por condição do enunciado).
typedef char Palavra[TAMANHO_DA_PALAVRA];

// struct BagOfWords:
// BagOfWords (BOW) armazena um vetor dinâmico de palavras distintas (tipo Palavra*, que é uma string de tamanho 20),
// e um vetor que armazena suas respectivas frequências.
// A palavra armazenada no i-ésimo índice do vetor dinâmico "palavras" tem sua respectiva frequência armazenada no
// i-ésimo índice do vetor dinâmico "frequencias". O BOW também armazena uma variável para contar o número de palavras
// armazenadas.
typedef struct
{
    Palavra* palavras;
    int* frequencias;
    size_t numeroDePalavras;
} BagOfWords;

// struct Produto:
// Cada produto pode ser representado por uma string (que representa o seu nome), uma variável size_t que
// armazena quantos comentários foram feitos sobre esse produto e um vetor dinâmico de BagOfWords, que armazena
// em cada uma das suas posições um BagOfWord para cada um dos comentários feitos sobre o produto. Deste modo,
// para cada produto temos um BagOfWords para cada comentário feito, permitindo contabilizar a frequência de cada
// palavra de cada comentário e também analisar quantos comentários são positivos ou negativos.
typedef struct
{
    char* nomeDoProduto;
    BagOfWords** vetorDeBows;
    size_t numeroDeComentarios;
} Produto;

// Dado como parâmetro uma string (de tipo const char*), a função tamanhoDaPalavra retorna o tamanho dessa string.
// Caso a string esteja vazia, o retorno é -1.
// O tipo do retorno da função é size_t, que é o mesmo tipo do retorno da função strlen.
size_t tamanhoDaPalavra(const char* string)
{
    if (string == NULL)
    {
        printf("Erro em tamanhoDaPalavra(): argumento invalido - string vazia\n");
        return -1;
    }

    return strlen(string);
}

// Dado um vetor que armazena elementos do tipo Produto* e o seu número de elementos,
// a função buscaPorProduto retorna o índice - de 0 a (quantidadeDeProdutos - 1) -  que
// armazena o produto cujo nome seja o mesmo da string fornecida como terceiro parâmetro.
// Caso não haja produto com o nome buscado, a função retorna -1.
int buscaPorProduto(Produto** produtos, int quantidadeDeProdutos, const char* string)
{
    for (int i = 0; i < quantidadeDeProdutos; ++i)
    {
        if (strcmp(produtos[i]->nomeDoProduto, string) == 0)
        {
            return i;
        }
    }

    return -1;
}

// Dado um vetor de strings "vetor" e o seu número de elementos, "tamanhoDoVetor",
// a função buscaPorPalavra retorna o índice - de 0 a (tamanhoDoVetor - 1) - que armazena
// a string que seja igual a string fornecida como terceiro parâmetro.
// Caso não haja string com o nome buscado, a função retorna -1.
int buscaPorPalavra(const char** vetor, int tamanhoDoVetor, char* string)
{
    for (int i = 0; i < tamanhoDoVetor; ++i)
    {
        if (strcmp(vetor[i], string) == 0)
        {
            return i;
        }
    }

    return -1;
}

// Dado como parâmetro o nome de um produto (do tipo const char*), a função inicializaProduto cria
// uma variável do tipo Produto* e o inicializa, retornando ele ao fim da função.
// A variável criada é inicializada com o nome do produto fornecido como parâmetro,
// inicializa em 0 o número de comentários e aloca um vetor dinâmico de BOWs de tamanho 1.
Produto* inicializaProduto(const char* nomeDoProduto)
{
    if (nomeDoProduto == NULL)
    {
        printf("Erro em inicializaProduto - nomeDoProduto é NULL\n");
    }

    Produto* produto = calloc(1, sizeof(Produto));
    produto->nomeDoProduto = calloc(tamanhoDaPalavra(nomeDoProduto), sizeof(char));
    strcpy(produto->nomeDoProduto, nomeDoProduto);
    produto->numeroDeComentarios = 0;
    produto->vetorDeBows = calloc(1, sizeof(BagOfWords*));

    return produto;
}

// Dado uma string (do tipo char*) como parâmetro, a função insereComentario(char* comentario)
// aloca uma variável do tipo BagOfWords*.
// Usamos a função strtok, da biblioteca string.h, que permite dividir uma frase usando um delimitador fornecido.
// A função strtok recebe como parâmetros uma string a ser dividida e o delimitador. A string fornecida como parâmetro
// será dividida em strings menores (chamadas de tokens). Cada vez que um valor igual ao delimitador for encontrado, a
// string é dividida em mais um pedaço (chamado de token). Quando não for possível dividir mais nenhuma vez a string,
// a função returna NULL.
// Exemplo:
// char* string = "normal_mapping/raycasting\shaders";
// strtok(string, "/\|") irá dividir a string em três strings menores (tokens) sem incluir os delimitadores.
// Cada chamada da função strtok retorna o próximo token. Dessa forma, a primeira chamada da função irá retornar "normal_mapping",
// a segunda "raycasting", a terceira "shaders" e uma quarta chamada retornará NULL, pois não há mais como subdividir a string original.
//
// Separamos a string fornecida em diversos tokens (usando " " como delimitador).
// Caso seja a primeira vez que um token seja encontrado, armazenamos ele em um índice do vetor palavras (contido em BagOfWords) e incrementamos
// o contador no vetor frequencia (também contido em BagOfWords) nesse mesmo índice. Usamos a variável "indiceVago" para rastrear qual o próximo índice
// que pode ser ocupado por um novo token. Caso um token encontrado já tenha sido armazenado antes, apenas incrementamos o valor do vetor "frequencias"
// no índice que ocupa o token já encontrado.
// Ao fim da função, ela retorna o BagOfWords* construído, que agora armazena os tokens do comentário fornecido e a respectiva frequência
// de cada um desses tokens.
BagOfWords* insereComentario(char* comentario)
{
    BagOfWords* bow = calloc(1, sizeof(BagOfWords));
    bow->palavras = calloc(TAMANHO_DO_BOW, sizeof(Palavra));
    bow->frequencias = calloc(TAMANHO_DO_BOW, sizeof(int));

    int indiceVago = 0;

    char* token = strtok(comentario, " ");

    while (token != NULL)
    {
        int encontrado = 0;
        for (int i = 0; i < indiceVago; ++i)
        {
            if (strcmp(bow->palavras[i], token) == 0)
            {
                ++bow->frequencias[i];
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            strcpy(bow->palavras[indiceVago], token);
            ++bow->frequencias[indiceVago];
            ++indiceVago;
        }

        token = strtok(NULL, " ");
    }

    bow->numeroDePalavras = indiceVago;

    return bow;
}

// ocorrenciasDaPalavra: função que responde a primeira pergunta.
// Dados como parâmetros um produto e uma palavra a ser procurada, a função percorre
// o vetor dinâmico que armazena BagOfWords "vetorDeBows" do parâmetro "produto". Cada elemento desse vetor
// armazena, por sua vez, um vetor de strings "palavras" e um vetor das frequências de cada palavra, "frequencias".
// Percorrendo cada um dos BagOfWords (um BagOfWords para cada comentário), conseguimos contar quantas vezes o
// parâmetro "palavraBuscada" se repete para o produto desejado.
// A função retorna o número de ocorrências de "palavraBuscada" para o produto fornecido.
int ocorrenciasDaPalavra(const Produto* produto, const char* palavraBuscada)
{
    int contador = 0;

    for (int j = 0; j < produto->numeroDeComentarios; ++j)
    {
        for (int k = 0; k < produto->vetorDeBows[j]->numeroDePalavras; ++k)
        {
            if (strcmp(produto->vetorDeBows[j]->palavras[k], palavraBuscada) == 0)
            {
                contador += produto->vetorDeBows[j]->frequencias[k];
            }
        }
    }

    return contador;
}

// Função contadorDeOpinioes: responde a segunda pergunta e a pergunta bônus.
//
// Dados como parâmetros um produto e uma opinião (representada por um inteiro: 0 para opinião positiva e 1 para opinião negativa),
// assim como fizemos com a função oncorrenciasDaPalavra, percorremos o vetor dinâmico de BagOfWords do produto (vetorDeBows) e
// analisamos quantos comentários são positivos ou negativos (a depender do parâmetro "opiniao").
// Como apenas estamos interessados em saber se um comentário é positivo ou negativo, assim que encontramos uma palavra positiva
// ou negativa incrementamos a variável contador e saímos do loop,
// pois não importa quantas palavras são positivas (ou negativas) para um dado comentário, apenas queremos saber se ele é positivo ou não.
//
// Fazemos isso para cada comentário. Ao fim da busca, retornamos a razão entre o contador e o número de comentários multiplicado por 100 (para
// representar o valor em forma de fração).
double contadorDeOpinioes(const Produto* produto, int opiniao)
{
    // Armazenamos as opiniões positivas no vetor elogios[], as opiniões negativas em criticas[] e as palavras de inversão de polaridade em inversor[].
    // A matriz de strings opinioes[] armazena no índice 0 o vetor elogios[] e no índice o vetor criticas[].
    const char* elogios[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    const char* criticas[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    const char** opinioes[] = {elogios, criticas};
    const char* inversor[] = {"nao", "jamais", "nunca"};

    int contador = 0;

    // Percorremos cada um dos comentários armazenados para esse produto (lembrando que há um BagOfWords para cada comentário)
    for (int i = 0; i < produto->numeroDeComentarios; ++i)
    {
        int encontrado = 0;

        // Visitamos todas as palavras armazenados no i-ésimo BagOfWords (cada BagOfWords está armazenado em "vetorDeBows").
        // A variável "encontrado" rastreia se já determinamos se esse comentário é positivo ou negativo; caso já tenhamos determinado
        // a opinião desse comentário, podemos prosseguir para o próximo.
        for (int j = 0; j < produto->vetorDeBows[i]->numeroDePalavras && !encontrado; ++j)
        {
            // Para cada palavra do BagOfWords, verificamos se ela coincide com alguma das palavras referentes à "opiniao"
            // usando o vetor opinioes[opiniao].

            for (int k = 0; k < NUMERO_DE_OPINIOES; ++k)
            {
                if (strcmp(produto->vetorDeBows[i]->palavras[j], opinioes[opiniao][k]) == 0)
                {
                    // Caso tenhamos encontrado uma palavra que esteja no vetor de opinioes[opiniao], incrementamos o contador.
                    // No entanto, devemos checar (até três posições antes, isto é, até a posição j - 3, contanto que j - 3 >= 0)
                    // se não há nenhum inversor de polaridade. Caso haja, decrementamos o contador.
                    // Por exemplo, se buscamos comentários positivos e encontramos "eficiente" antecido por "nunca foi", na verdade
                    // esse comentário é negativo e não positivo. Mas se encontramos "eficiente" sem nenhum inversor que o antecede,
                    // então o comentário é realmente positivo.

                    for (int reverseJ = j - 1; reverseJ >= 0 && j - reverseJ <= 3; --reverseJ)
                    {
                        for (int negacao = 0; negacao < NUMERO_DE_INVERSORES; ++negacao)
                        {
                            if (strcmp(produto->vetorDeBows[i]->palavras[reverseJ], inversor[negacao]) == 0)
                            {
                                --contador;
                                reverseJ = -1;
                                break;
                            }
                        }
                    }

                    ++contador;
                    encontrado = 1;
                    break;
                }

                if (encontrado)
                {
                    break;
                }

                // A outra possibilidade de encontrar um comentário com a opinião que buscamos é encontrar a palavra
                // com opinião CONTRÁRIA a buscada antecida por um inversor de polaridade em até j - 3 posições anteriores
                // (contanto que j - 3 >= 0). Por exemplo, se buscamos comentários positivos e encontramos a palavra "ruim"
                // antecedida por "nunca achei", na verdade esse comentário é positivo e não negativo.
                // A variável "opiniaoInversa" calcula qual a opinião contrária à opinião buscada e verificamos se
                // há uma palavra no BagOfWords que também esteja no vetor opinioes[opiniaoInversa] e seja antecedida
                // pelo inversor de polaridade.
                int opiniaoInversa = 1 - opiniao;
                if (strcmp(produto->vetorDeBows[i]->palavras[j], opinioes[opiniaoInversa][k]) == 0)
                {
                    for (int reverseJ = j - 1; reverseJ >= 0 && j - reverseJ <= 3; --reverseJ)
                    {
                        for (int negacao = 0; negacao < NUMERO_DE_INVERSORES; ++negacao)
                        {
                            if (strcmp(produto->vetorDeBows[i]->palavras[reverseJ], inversor[negacao]) == 0)
                            {
                                ++contador;
                                encontrado = 1;
                                reverseJ = -1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return (100.0 * ((double) contador / produto->numeroDeComentarios));
}

// Função esvaziaBancoDeProdutos: dado um ponteiro para o banco de produtos e o número
// de produtos alocados, a função libera a memória alocada na heap.
void esvaziaBancoDeProdutos(Produto** produtos, int quantidadeDeProdutos)
{
    for (int i = 0; i < quantidadeDeProdutos; ++i)
    {
        for (int j = 0; j < produtos[i]->numeroDeComentarios; ++j)
        {
            free(produtos[i]->vetorDeBows[j]->palavras);
            free(produtos[i]->vetorDeBows[j]->frequencias);
            free(produtos[i]->vetorDeBows[j]);
        }

        free(produtos[i]->nomeDoProduto);
        free(produtos[i]->vetorDeBows);
        free(produtos[i]);
    }

    free(produtos);
}

int main()
{
    int numeroSentencas, numeroPerguntas;

    scanf("%d %d", &numeroSentencas, &numeroPerguntas);

    int quantidadeDeProdutos = 0;

    char produto[TAMANHO_DA_FRASE], comentario[TAMANHO_DA_FRASE];

    Produto** bancoDeProdutos = calloc(1, sizeof(Produto));

    for (int i = 0; i < numeroSentencas; ++i)
    {
        scanf(" %400[^;]%*c", produto);
        produto[tamanhoDaPalavra(produto) - 1] = '\0'; // código para remover o espaço antes do ;

        scanf(" %400[^\n\r]*c", comentario);

        comentario[tamanhoDaPalavra(comentario) - 1] = '\0'; // código remover o identificador de fim de sentença

        // retorna o índice em que se encontra um Produto que tenha mesmo nome do que a string "produto";
        // retorna -1 caso não haja tal produto
        int id = buscaPorProduto(bancoDeProdutos, quantidadeDeProdutos, produto);

        // Caso ainda não exista um produto correspondente à essa entrada, reservamos mais espaço na memória
        // de bancoDeProdutos para armazenar esse novo produto.
        if (id == -1)
        {
            ++quantidadeDeProdutos;
            id = quantidadeDeProdutos - 1;
            Produto** temp = realloc(bancoDeProdutos, quantidadeDeProdutos * sizeof(Produto));

            if (temp != NULL)
            {
                bancoDeProdutos = temp;
            }

            bancoDeProdutos[id] = inicializaProduto(produto);
        }

        // Aumentamos o espaço do "vetorDeBows" do produto fornecido nessa entrada e armazenamos o BagOfWords
        // do comentário correspondente à entrada atual.
        size_t numeroDeComentarios = (++bancoDeProdutos[id]->numeroDeComentarios);
        BagOfWords** bow = realloc(bancoDeProdutos[id]->vetorDeBows, numeroDeComentarios * sizeof(BagOfWords*));

        if (bow != NULL)
        {
            bancoDeProdutos[id]->vetorDeBows = bow;
            bancoDeProdutos[id]->vetorDeBows[numeroDeComentarios - 1] = insereComentario(comentario);
        }
    }

    char pergunta[TAMANHO_DA_FRASE];
    char tokens[5][TAMANHO_DA_PALAVRA];

    for (int i = 0; i < numeroPerguntas; ++i)
    {
        scanf(" %[^\n\r]", pergunta);

        char* token = strtok(pergunta, " ");

        for (int j = 0; j < 5 && token != NULL; ++j)
        {
            strcpy(tokens[j], token);

            token = strtok(NULL, " ");
        }

        char produtoProcurado[2 * TAMANHO_DA_PALAVRA];
        // Concatenamos tokens[3] e tokens[4] separados por espaço e armazenamos em produtoProcurado
        // para poder fazer a busca no bancoDeProdutos.
        snprintf(produtoProcurado, sizeof(produtoProcurado), "%s %s", tokens[3], tokens[4]);

        int id = buscaPorProduto(bancoDeProdutos, quantidadeDeProdutos, produtoProcurado);

        // Caso a pergunta inicie com "palavra", trata-se da primeira pergunta.
        if (strcmp(tokens[0], "palavra") == 0)
        {
            printf("%d\n", ocorrenciasDaPalavra(bancoDeProdutos[id], tokens[1]));
        }
        else if (strcmp(tokens[0], "quantos") == 0) // Caso a pergunta inicie com "quantos", trata-se da segunda pergunta e pergunta bônus.
        {
            int opiniao;
            if (strcmp(tokens[1], "positivos") == 0)
            {
                opiniao = ELOGIO;
            }
            else
            {
                opiniao = CRITICA;
            }

            printf("%.1lf%%\n", contadorDeOpinioes(bancoDeProdutos[id], opiniao));
        }
    }

    // Liberamos a memória dinâmica alocada
    esvaziaBancoDeProdutos(bancoDeProdutos, quantidadeDeProdutos);
}
