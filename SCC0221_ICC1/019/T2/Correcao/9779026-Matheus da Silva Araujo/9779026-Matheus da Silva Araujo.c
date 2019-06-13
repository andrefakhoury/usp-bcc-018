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

// Uma palavra � um vetor de chars (uma string) de tamanho m�ximo TAMANHO_DA_PALAVRA (que � 20, por condi��o do enunciado).
typedef char Palavra[TAMANHO_DA_PALAVRA];

// struct BagOfWords:
// BagOfWords (BOW) armazena um vetor din�mico de palavras distintas (tipo Palavra*, que � uma string de tamanho 20),
// e um vetor que armazena suas respectivas frequ�ncias.
// A palavra armazenada no i-�simo �ndice do vetor din�mico "palavras" tem sua respectiva frequ�ncia armazenada no
// i-�simo �ndice do vetor din�mico "frequencias". O BOW tamb�m armazena uma vari�vel para contar o n�mero de palavras
// armazenadas.
typedef struct
{
    Palavra* palavras;
    int* frequencias;
    size_t numeroDePalavras;
} BagOfWords;

// struct Produto:
// Cada produto pode ser representado por uma string (que representa o seu nome), uma vari�vel size_t que
// armazena quantos coment�rios foram feitos sobre esse produto e um vetor din�mico de BagOfWords, que armazena
// em cada uma das suas posi��es um BagOfWord para cada um dos coment�rios feitos sobre o produto. Deste modo,
// para cada produto temos um BagOfWords para cada coment�rio feito, permitindo contabilizar a frequ�ncia de cada
// palavra de cada coment�rio e tamb�m analisar quantos coment�rios s�o positivos ou negativos.
typedef struct
{
    char* nomeDoProduto;
    BagOfWords** vetorDeBows;
    size_t numeroDeComentarios;
} Produto;

// Dado como par�metro uma string (de tipo const char*), a fun��o tamanhoDaPalavra retorna o tamanho dessa string.
// Caso a string esteja vazia, o retorno � -1.
// O tipo do retorno da fun��o � size_t, que � o mesmo tipo do retorno da fun��o strlen.
size_t tamanhoDaPalavra(const char* string)
{
    if (string == NULL)
    {
        printf("Erro em tamanhoDaPalavra(): argumento invalido - string vazia\n");
        return -1;
    }

    return strlen(string);
}

// Dado um vetor que armazena elementos do tipo Produto* e o seu n�mero de elementos,
// a fun��o buscaPorProduto retorna o �ndice - de 0 a (quantidadeDeProdutos - 1) -  que
// armazena o produto cujo nome seja o mesmo da string fornecida como terceiro par�metro.
// Caso n�o haja produto com o nome buscado, a fun��o retorna -1.
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

// Dado um vetor de strings "vetor" e o seu n�mero de elementos, "tamanhoDoVetor",
// a fun��o buscaPorPalavra retorna o �ndice - de 0 a (tamanhoDoVetor - 1) - que armazena
// a string que seja igual a string fornecida como terceiro par�metro.
// Caso n�o haja string com o nome buscado, a fun��o retorna -1.
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

// Dado como par�metro o nome de um produto (do tipo const char*), a fun��o inicializaProduto cria
// uma vari�vel do tipo Produto* e o inicializa, retornando ele ao fim da fun��o.
// A vari�vel criada � inicializada com o nome do produto fornecido como par�metro,
// inicializa em 0 o n�mero de coment�rios e aloca um vetor din�mico de BOWs de tamanho 1.
Produto* inicializaProduto(const char* nomeDoProduto)
{
    if (nomeDoProduto == NULL)
    {
        printf("Erro em inicializaProduto - nomeDoProduto � NULL\n");
    }

    Produto* produto = calloc(1, sizeof(Produto));
    produto->nomeDoProduto = calloc(tamanhoDaPalavra(nomeDoProduto), sizeof(char));
    strcpy(produto->nomeDoProduto, nomeDoProduto);
    produto->numeroDeComentarios = 0;
    produto->vetorDeBows = calloc(1, sizeof(BagOfWords*));

    return produto;
}

// Dado uma string (do tipo char*) como par�metro, a fun��o insereComentario(char* comentario)
// aloca uma vari�vel do tipo BagOfWords*.
// Usamos a fun��o strtok, da biblioteca string.h, que permite dividir uma frase usando um delimitador fornecido.
// A fun��o strtok recebe como par�metros uma string a ser dividida e o delimitador. A string fornecida como par�metro
// ser� dividida em strings menores (chamadas de tokens). Cada vez que um valor igual ao delimitador for encontrado, a
// string � dividida em mais um peda�o (chamado de token). Quando n�o for poss�vel dividir mais nenhuma vez a string,
// a fun��o returna NULL.
// Exemplo:
// char* string = "normal_mapping/raycasting\shaders";
// strtok(string, "/\|") ir� dividir a string em tr�s strings menores (tokens) sem incluir os delimitadores.
// Cada chamada da fun��o strtok retorna o pr�ximo token. Dessa forma, a primeira chamada da fun��o ir� retornar "normal_mapping",
// a segunda "raycasting", a terceira "shaders" e uma quarta chamada retornar� NULL, pois n�o h� mais como subdividir a string original.
//
// Separamos a string fornecida em diversos tokens (usando " " como delimitador).
// Caso seja a primeira vez que um token seja encontrado, armazenamos ele em um �ndice do vetor palavras (contido em BagOfWords) e incrementamos
// o contador no vetor frequencia (tamb�m contido em BagOfWords) nesse mesmo �ndice. Usamos a vari�vel "indiceVago" para rastrear qual o pr�ximo �ndice
// que pode ser ocupado por um novo token. Caso um token encontrado j� tenha sido armazenado antes, apenas incrementamos o valor do vetor "frequencias"
// no �ndice que ocupa o token j� encontrado.
// Ao fim da fun��o, ela retorna o BagOfWords* constru�do, que agora armazena os tokens do coment�rio fornecido e a respectiva frequ�ncia
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

// ocorrenciasDaPalavra: fun��o que responde a primeira pergunta.
// Dados como par�metros um produto e uma palavra a ser procurada, a fun��o percorre
// o vetor din�mico que armazena BagOfWords "vetorDeBows" do par�metro "produto". Cada elemento desse vetor
// armazena, por sua vez, um vetor de strings "palavras" e um vetor das frequ�ncias de cada palavra, "frequencias".
// Percorrendo cada um dos BagOfWords (um BagOfWords para cada coment�rio), conseguimos contar quantas vezes o
// par�metro "palavraBuscada" se repete para o produto desejado.
// A fun��o retorna o n�mero de ocorr�ncias de "palavraBuscada" para o produto fornecido.
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

// Fun��o contadorDeOpinioes: responde a segunda pergunta e a pergunta b�nus.
//
// Dados como par�metros um produto e uma opini�o (representada por um inteiro: 0 para opini�o positiva e 1 para opini�o negativa),
// assim como fizemos com a fun��o oncorrenciasDaPalavra, percorremos o vetor din�mico de BagOfWords do produto (vetorDeBows) e
// analisamos quantos coment�rios s�o positivos ou negativos (a depender do par�metro "opiniao").
// Como apenas estamos interessados em saber se um coment�rio � positivo ou negativo, assim que encontramos uma palavra positiva
// ou negativa incrementamos a vari�vel contador e sa�mos do loop,
// pois n�o importa quantas palavras s�o positivas (ou negativas) para um dado coment�rio, apenas queremos saber se ele � positivo ou n�o.
//
// Fazemos isso para cada coment�rio. Ao fim da busca, retornamos a raz�o entre o contador e o n�mero de coment�rios multiplicado por 100 (para
// representar o valor em forma de fra��o).
double contadorDeOpinioes(const Produto* produto, int opiniao)
{
    // Armazenamos as opini�es positivas no vetor elogios[], as opini�es negativas em criticas[] e as palavras de invers�o de polaridade em inversor[].
    // A matriz de strings opinioes[] armazena no �ndice 0 o vetor elogios[] e no �ndice o vetor criticas[].
    const char* elogios[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    const char* criticas[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    const char** opinioes[] = {elogios, criticas};
    const char* inversor[] = {"nao", "jamais", "nunca"};

    int contador = 0;

    // Percorremos cada um dos coment�rios armazenados para esse produto (lembrando que h� um BagOfWords para cada coment�rio)
    for (int i = 0; i < produto->numeroDeComentarios; ++i)
    {
        int encontrado = 0;

        // Visitamos todas as palavras armazenados no i-�simo BagOfWords (cada BagOfWords est� armazenado em "vetorDeBows").
        // A vari�vel "encontrado" rastreia se j� determinamos se esse coment�rio � positivo ou negativo; caso j� tenhamos determinado
        // a opini�o desse coment�rio, podemos prosseguir para o pr�ximo.
        for (int j = 0; j < produto->vetorDeBows[i]->numeroDePalavras && !encontrado; ++j)
        {
            // Para cada palavra do BagOfWords, verificamos se ela coincide com alguma das palavras referentes � "opiniao"
            // usando o vetor opinioes[opiniao].

            for (int k = 0; k < NUMERO_DE_OPINIOES; ++k)
            {
                if (strcmp(produto->vetorDeBows[i]->palavras[j], opinioes[opiniao][k]) == 0)
                {
                    // Caso tenhamos encontrado uma palavra que esteja no vetor de opinioes[opiniao], incrementamos o contador.
                    // No entanto, devemos checar (at� tr�s posi��es antes, isto �, at� a posi��o j - 3, contanto que j - 3 >= 0)
                    // se n�o h� nenhum inversor de polaridade. Caso haja, decrementamos o contador.
                    // Por exemplo, se buscamos coment�rios positivos e encontramos "eficiente" antecido por "nunca foi", na verdade
                    // esse coment�rio � negativo e n�o positivo. Mas se encontramos "eficiente" sem nenhum inversor que o antecede,
                    // ent�o o coment�rio � realmente positivo.

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

                // A outra possibilidade de encontrar um coment�rio com a opini�o que buscamos � encontrar a palavra
                // com opini�o CONTR�RIA a buscada antecida por um inversor de polaridade em at� j - 3 posi��es anteriores
                // (contanto que j - 3 >= 0). Por exemplo, se buscamos coment�rios positivos e encontramos a palavra "ruim"
                // antecedida por "nunca achei", na verdade esse coment�rio � positivo e n�o negativo.
                // A vari�vel "opiniaoInversa" calcula qual a opini�o contr�ria � opini�o buscada e verificamos se
                // h� uma palavra no BagOfWords que tamb�m esteja no vetor opinioes[opiniaoInversa] e seja antecedida
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

// Fun��o esvaziaBancoDeProdutos: dado um ponteiro para o banco de produtos e o n�mero
// de produtos alocados, a fun��o libera a mem�ria alocada na heap.
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
        produto[tamanhoDaPalavra(produto) - 1] = '\0'; // c�digo para remover o espa�o antes do ;

        scanf(" %400[^\n\r]*c", comentario);

        comentario[tamanhoDaPalavra(comentario) - 1] = '\0'; // c�digo remover o identificador de fim de senten�a

        // retorna o �ndice em que se encontra um Produto que tenha mesmo nome do que a string "produto";
        // retorna -1 caso n�o haja tal produto
        int id = buscaPorProduto(bancoDeProdutos, quantidadeDeProdutos, produto);

        // Caso ainda n�o exista um produto correspondente � essa entrada, reservamos mais espa�o na mem�ria
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

        // Aumentamos o espa�o do "vetorDeBows" do produto fornecido nessa entrada e armazenamos o BagOfWords
        // do coment�rio correspondente � entrada atual.
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
        // Concatenamos tokens[3] e tokens[4] separados por espa�o e armazenamos em produtoProcurado
        // para poder fazer a busca no bancoDeProdutos.
        snprintf(produtoProcurado, sizeof(produtoProcurado), "%s %s", tokens[3], tokens[4]);

        int id = buscaPorProduto(bancoDeProdutos, quantidadeDeProdutos, produtoProcurado);

        // Caso a pergunta inicie com "palavra", trata-se da primeira pergunta.
        if (strcmp(tokens[0], "palavra") == 0)
        {
            printf("%d\n", ocorrenciasDaPalavra(bancoDeProdutos[id], tokens[1]));
        }
        else if (strcmp(tokens[0], "quantos") == 0) // Caso a pergunta inicie com "quantos", trata-se da segunda pergunta e pergunta b�nus.
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

    // Liberamos a mem�ria din�mica alocada
    esvaziaBancoDeProdutos(bancoDeProdutos, quantidadeDeProdutos);
}
