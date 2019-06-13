#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> /*serve para reconhecer o Ø*/
#define tamanho 30 /*tamanho de caracteres de cada palavara*/

/*estrutura Bag of Words, os nomes dos elementos correspondem a suas funções exercidas */
typedef struct BagOfWords {
    char representacaoBow[200][tamanho];
    int numeroPalavraChave;
    int numeroPosiOuNeg;  /*conta o número de comentários positivos ou negativos, dependendo da perguta*/
    int contaProduto;
} BOW;

/*estrutura INFORMACAO, os nomes dos elementos correspondem a suas funções exercidas */
typedef struct INFORMACAO {
    char produto[tamanho];
    char marca[tamanho];
    char sentenca[22][tamanho];
    int PalavrasNum;        /*número de palavras do comentário sobre um produto*/
} info;

/* estrutura PERGUNTA, guarda as palavras que formam uma pergunta*/
typedef struct PERGUNTA {
    char frase[5][tamanho];
}pergunta;

/*faz uma lista de palavraas positivas ou negativas, depende da entrada,
 palavra[tamanho] pode ser "positivos" ou negativos" e isso decide qual lista de palavras será criada
 listaDePalavras guarda as palavras positivas ou negativas*/
void listaPositOuNeg (char palavra[tamanho], char listaDePalavras[12][tamanho]) {
    if (strcmp(palavra, "positivos") == 0) {
        strcpy(listaDePalavras[0], "bom");
        strcpy(listaDePalavras[1], "maravilhoso");
        strcpy(listaDePalavras[2], "otimo");
        strcpy(listaDePalavras[3], "sensacional");
        strcpy(listaDePalavras[4], "excelente");
        strcpy(listaDePalavras[5], "adorei");
        strcpy(listaDePalavras[6], "gostei");
        strcpy(listaDePalavras[7], "amei");
        strcpy(listaDePalavras[8], "eficiente");
        strcpy(listaDePalavras[9], "boa");
        strcpy(listaDePalavras[10], "maravilhosa");
        strcpy(listaDePalavras[11], "otima");
    }
    else {
        strcpy(listaDePalavras[0], "destestei");
        strcpy(listaDePalavras[1], "odiei");
        strcpy(listaDePalavras[2], "ruim");
        strcpy(listaDePalavras[3], "pessimo");
        strcpy(listaDePalavras[4], "terrivel");
        strcpy(listaDePalavras[5], "raiva");
        strcpy(listaDePalavras[6], "odio");
        strcpy(listaDePalavras[7], "pessima");
        strcpy(listaDePalavras[8], "lento");
        strcpy(listaDePalavras[9], "lenta");
        strcpy(listaDePalavras[10], "fragil");
        strcpy(listaDePalavras[11], "desisti");
    }
}

/*função que cria a variável do tipo info*/
info LeInfo() {
    int ContaPalavra = 0; /*variável pra contar as palavras do comentário*/
    info Inf_1;

    scanf(" %s %s ; ", Inf_1.produto, Inf_1.marca);

    /*o do while verifica o ponto de parada*/
    do {
        scanf("%s", Inf_1.sentenca[ContaPalavra]);
        ContaPalavra++;
    } while(strcmp(Inf_1.sentenca[ContaPalavra - 1] , "Ø") != 0);

    Inf_1.PalavrasNum = ContaPalavra - 1; /*atualização da variável PalavrasNum desconsiderando o espaço com o demarcador do fim do comentário*/

    return Inf_1;
}

/*Função que cria variável do tipo pergunta*/
pergunta LePergunta() {
    pergunta P;
    int ContaPalavras = 0; /*variável pra contar as palavras da pergunta*/

    /*o número de palavras das perguntas é fixo e é 5*/
    while (ContaPalavras < 5) {
         scanf(" %s", P.frase[ContaPalavras]);
         ContaPalavras++;
    }

    return P;
}

/*função para criar uma Bag of Words
 VetorDeInfo é o vetor de informações com os comentários e produtos,
 produto, marca e palavraChave sao os produtos, marcas e palavraChace relacionados à pergunta
 tipo é o tipo da pergunta (1 para termo x no produto y e 2 para positivos ou negativos pro produto z
 comentariosNum é o número de comentários
 listaPosiOuNeg é lista de palavras positivas ou negativas */

BOW CriandoBoW (info *VetorDeInfo, char produto[tamanho], char marca[tamanho], int comentariosNum, char palavraChave[tamanho],
 char listaPosiOuNeg[12][tamanho], int tipo) {
BOW tabela; /*variavel tabela do tipo BOW para guardar as alterações feitas nessa função*/
    int i, j, kBoW, kTipo2, indice, existeNoBow, ehPosiOuNeg = 0, palavraNoBoW = 0, contaPalavraChave = 0, contaEhPosiOuNeg = 0, contaProduto = 0;

    /*o for do i = 0 corresponde a leitura do vetor de informações dos produtos, comentariosNum é o número de comentários da entrada do programa*/
    for (i = 0; i < comentariosNum; i++) {

        /*o primeiro if verifica se o produtoe a marca do elemento i do vetor é o produto relacionado à questão*/
        if (strcmp(VetorDeInfo[i].produto, produto) == 0 && strcmp(VetorDeInfo[i].marca, marca) == 0) {

            /*o for do j corresponde a leitura do comentário do elemento i do vetor de informação, PalavrasNum é o número de palavras de cada comentário*/
            for (j = 0; j < VetorDeInfo[i].PalavrasNum; j++) {

                kBoW = 0; /*kBow é variável pro while que verifica as palavras no Bag of Words*/
                existeNoBow = 0; /*variável é 0 quando a palavra não existe na tabela e 1 se existe*/

                while (existeNoBow == 0 && kBoW <= palavraNoBoW) {
                    /*o if verifica se a palavra j do comentario i está no BoW ou não*/

                    if (strcmp(VetorDeInfo[i].sentenca[j], tabela.representacaoBow[kBoW]) == 0) {
                        existeNoBow = 1;
                    }

                    kBoW++;
                }

                /*se a palavra j do comentário i não existir, ela é acrescentada no BoW*/
                if (existeNoBow == 0) {
                    strcpy(tabela.representacaoBow[kBoW - 1], VetorDeInfo[i].sentenca[j]);
                    palavraNoBoW++;
                }

                /*se a pergunta for do tipo 1, o contador de palavra chave é atualizado */
                if (tipo == 1) {
                    if (strcmp(VetorDeInfo[i].sentenca[j], palavraChave) == 0) {
                        contaPalavraChave++;
                    }
                }
            }
            /*se a pergunta for do tipo 2, o while e o for verificam se a palavra do comentário pertence ao vetor de palavras positivas ou negativas*/
            if (tipo == 2) {
                indice = 0;
                /*a variável j ainda está no seu valor máximo que corresponde ao número de palavras do comentário*/
                while (indice <= j) {
                    for (kTipo2 = 0; kTipo2 < 12; kTipo2++) {
                        if (strcmp(VetorDeInfo[i].sentenca[indice], listaPosiOuNeg[kTipo2]) == 0) {
                            /*if verifica se o comentário já foi classificado como elogio ou crítica*/
                            if (ehPosiOuNeg == 0) {
                                contaEhPosiOuNeg++;
                                ehPosiOuNeg = 1;
                            }
                        }
                    }
                    indice++;
                }
                contaProduto++;
                ehPosiOuNeg = 0;
            }
        }
    }

    /*atualiza a variável tabela do tipo BOW*/
    if (tipo == 1) {
        tabela.numeroPalavraChave = contaPalavraChave;
    }
    else {
        tabela.numeroPosiOuNeg = contaEhPosiOuNeg;
        tabela.contaProduto = contaProduto;
    }

    return tabela;
}

/*função que responde as perguntas, P é a pergunta, vetorDeInfo é o vetor com os comentários e os produtos, sentencaNum é o número de sentenças*/
void RespondendoPergunta (pergunta P, info *vetorDeInfo, int sentencaNum) {
    int TipoDeQuestao = 0; /*questão tipo 1 ou 2*/
    char produto[tamanho], marca[tamanho], termoChave[tamanho]; /*palavras importantes para responder a pergunta*/
    BOW bowTabela; /*variável do tipo BOW para ajudar a responder as perguntas*/

    /*atribuição das variáveis strings*/
    strcpy(produto, P.frase[3]);
    strcpy(marca, P.frase[4]);
    strcpy(termoChave, P.frase[1]);

    /*if para verificar o tipo de pergunta*/
    if (strcmp(P.frase[0], "palavra") == 0) {
        TipoDeQuestao = 1;
    }
    else {
        TipoDeQuestao = 2;
    }
/*if para chamar a função CriandoBoW e responder a pergunta*/
    if (TipoDeQuestao == 1) {
        bowTabela = CriandoBoW(vetorDeInfo, produto, marca, sentencaNum, termoChave, NULL, TipoDeQuestao);
        printf("%d\n", bowTabela.numeroPalavraChave);
    }

    if (TipoDeQuestao == 2) {
        char listaElogioCritica[12][tamanho];
        float resposta = 100.0;

        /*função listaPosiOuNeg para escolher lista de elogios ou de críticas*/
        listaPositOuNeg(termoChave, listaElogioCritica);
        bowTabela = CriandoBoW(vetorDeInfo, produto, marca, sentencaNum, termoChave, listaElogioCritica, TipoDeQuestao);
        printf("%.1f%%\n", (resposta * bowTabela.numeroPosiOuNeg) / bowTabela.contaProduto);
    }
}

int main()
{
    setlocale(LC_ALL, ""); /*serve para reconhecer o simbolo Ø*/

    /*variáveis para guardar perguntas, csentenças e a quantidade e para imprimir as respostas*/
    int sentencaNum, perguntaNum, i;
    info *VetorDeInfo;
    pergunta *VetorDePergunta;

    scanf("%d %d", &sentencaNum, &perguntaNum);
    VetorDeInfo = (info*)malloc(sizeof(info) * sentencaNum);
    VetorDePergunta = (pergunta*)malloc(sizeof(pergunta) * perguntaNum);

    /*leitura das informações e das perguntas*/
    for(i = 0; i < sentencaNum; i++) {
        VetorDeInfo[i] = LeInfo();
    }
    for (i = 0; i < perguntaNum; i++) {
        VetorDePergunta[i] = LePergunta();
    }

    /*for para responder as perguntas*/
    for (i = 0; i < perguntaNum; i++) {
        RespondendoPergunta(VetorDePergunta[i], VetorDeInfo, sentencaNum);
    }

    free(VetorDeInfo);
    free(VetorDePergunta);
    return 0;
}