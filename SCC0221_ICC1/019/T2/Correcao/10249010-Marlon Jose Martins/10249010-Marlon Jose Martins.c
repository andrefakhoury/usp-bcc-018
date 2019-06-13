#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> //biblioteca incluida para o uso de variavel do tipo boolean. dessa forma, aprimorando a semantica do codigo

#define QTD_PALAVRAS 21 //definicao para quantidade de palavras por sentenca
#define LIST_ADJ 12 //definicao para quantidade de palavras numa lista de "adjetivos"
#define LIST_ADV 3 //definicao para quantidade de palavras na lista de adverbios  

typedef struct prod { //estrututa que serve como base para a formulacao de uma sentenca, o nome "Produto" e em virtude de toda sentenca estar vinculada a um produto
    char nome[20];
    char marca[20];
    char sent[QTD_PALAVRAS][19];
} Produto;

typedef struct perg { //estrutura que serve como base para a formulacao de uma pergunta
    char tipo[8];
    char atributo[19];
    Produto prod;
} Pergunta;

//prototipos das funcoes utilizadas no programa
void lerProd(Produto *prod, int nSent);
void lerPerg(Pergunta *perg, int nPerg);
void respPerg(Produto *prod, int nSent, Pergunta *perg, int nPerg);

//funcao utilizada para a leitura de sentencas
void lerProd(Produto *prod, int nSent) {
    int i, j;
    for (i = 0; i < nSent; i++) { //for utilizado para a leitura da quantidade (nSent) de sentencas feitas
        scanf("%s %s", prod[i].nome, prod[i].marca); //armazenamento do nome e marca do produto
        for(j = 0; j < QTD_PALAVRAS; j++) { //for utilizado para armazenar cada palavra da sentenca em um vetor do tipo char (string)
            scanf("%s", prod[i].sent[j]);
            if (strcmp(prod[i].sent[j], "Ø") == 0) //se a palavra da sentenca for "Ø" entao o for e encerrado (fim da sentenca)
                break;
        }
    }
    return;
}

//funcao utilizada para a leitura de perguntas
void lerPerg(Pergunta *perg, int nPerg) {
    int i;
    for (i = 0; i < nPerg; i++) { //for utilizado para a leitura da quantidade (nPerg) de perguntas feitas
        scanf("%s %s %s %s %s", perg[i].tipo, perg[i].atributo, 
            perg[i].prod.sent[0], perg[i].prod.nome, perg[i].prod.marca);
    }
    return;
}

//funcao utilizada para responder as perguntas feitas
void respPerg(Produto *prod, int nSent, Pergunta *perg, int nPerg) {
    bool flag; //variavel do tipo boolean para casos de interrupcoes de um for
    int i, j, k, l, m, n; //variaveis para o uso de for's nessa funcao
    float resp, pos, neg, tot; //variaveis utilizaddas na manipulacao das respostas
    char listNeg[LIST_ADJ][12] = {{"detestei"}, {"odiei"}, {"ruim"}, {"pessimo"}, {"terrivel"}, 
        {"raiva"}, {"odio"}, {"pessima"}, {"lento"}, {"lenta"}, {"fragil"}, {"desisti"}}; //lista de "adjetivos" negativos que podem ser inseridos
    char listPos[LIST_ADJ][13] = {{"bom"}, {"maravilhoso"}, {"otimo"}, {"sensacional"}, {"excelente"},
        {"adorei"}, {"gostei"}, {"amei"}, {"eficiente"}, {"boa"}, {"maravilhosa"}, {"otima"}}; //lista de "adjetivos" positivos que podem ser inseridos
    char listAdv[LIST_ADV][7] = {{"nao"}, {"jamais"}, {"nunca"}}; //lista de adverbios que podem ser inseridos

    for (i = 0; i < nPerg; i++) { //for utilizado para percorrer as perguntas feitas
        resp = 0;
        if (strcmp(perg[i].tipo, "palavra") == 0) { //se a pergunta tiver como tipo "palavra" entao a manipulacao sera do tipo "quantidade de palavra em tal produto" 
            for (j = 0; j < nSent; j++) { //for utilizado para percorrer as sentencas feitas
                if (strcmp(perg[i].prod.nome, prod[j].nome) == 0 && strcmp(perg[i].prod.marca, prod[j].marca) == 0) { //se o produto da pergunta for igual ao produto da sentenca entao...
                    for (k = 0; k < QTD_PALAVRAS; k++) { //for utilizado para percorrer as palavras da sentenca que contem o produto igual ao da pergunta
                        if (strcmp(perg[i].atributo, prod[j].sent[k]) == 0) { //se a palavra da pergunta (perg[i].atributo) for igual a palavra da sentenca entao incrementa a quantidade dessa palavra no produto da pergunta (resp++) 
                            resp++;
                        }
                        if (strcmp(prod[j].sent[k], "Ø") == 0) //caso a palavavra da sentenca seja "Ø" entao o for para de percorrer a sentenca (fim da sentenca)
                            break;
                    }
                }
            }
            printf("%.0f\n", resp);
        } else { //senao a pergunta tem como tipo "quantos" entao a manipulacao sera do tipo "porcetagem de sentencas positivas ou negativas de tal produto"
            pos = 0; neg = 0; tot = 0; //inicializacao das variaveis para a manipulacao da resposta
            for (j = 0; j < nSent; j++) { //for utilizado para percorrer as sentencas feitas
                flag = false; //inicializacao da variavel do tipo boolean para a manipulacao das interrupcoes de for's
				//de forma analoga a codicao anterior, os if's e for's sao utilizados...
                if (strcmp(perg[i].prod.nome, prod[j].nome) == 0 && strcmp(perg[i].prod.marca, prod[j].marca) == 0) {
                    for (k = 0; k < QTD_PALAVRAS; k++) {
                        for (m = 0; m < LIST_ADV; m++) { //for para percorrer a lista de adverbios
                            if (strcmp(prod[j].sent[k], listAdv[m]) == 0) { //se a palavra da sentenca for um adverbio entao...
                                for (l = 1; l <= 3; l++) { //for para percorrer as proximas tres palavras da sentenca
                                    if (strcmp(prod[j].sent[k+l], "Ø") == 0)
                                        break;
                                    for (n = 0; n < LIST_ADJ; n++) { //for para percorrer a lista de "adjetivos"
                                        if (strcmp(prod[j].sent[k+l], listPos[n]) == 0) { //se a palavra da sentenca for um adjetivo positivo entao inverte a polaridade da frase para negativa
                                            neg++;
                                            flag = true; //mudanca do valor da variavel do tipo boolean para manipular o for
                                        } else if (strcmp(prod[j].sent[k+l], listNeg[n]) == 0) { //de forma analoga a codicao anterior, inverte a polaridade da frase para positiva
                                            pos++;
                                            flag = true; //analogo a codicao anterior
                                        }
                                        if (flag) break; //se o valor da variavel do tipo boolean for "true" entao encerra o for
                                    }
                                    if (flag) break;
                                }
                            } else { //senao for uma palavra adverbio entao...
                                for (l = 0; l < LIST_ADJ; l++) {
                                    if(strcmp(prod[j].sent[k], listNeg[l]) == 0) { //se a palavra for igual a alguma da lista de adj. negativos entao incrementa a quantidade de sentencas negativas de tal produto
                                        neg++;
                                        flag = true;
                                    } else if (strcmp(prod[j].sent[k], listPos[l]) == 0) { //de forma analoga, porem incrementa a quantidade de sentencas positivas de tal produto
                                        pos++;
                                        flag = true;
                                    }
                                    if (flag) break;
                                }
                            }
                            if (flag) break;
                        }         
                        if (flag) break;
                    }
                    tot++; //incremento do total de sentencas de tal produto
                }
            }
            
            if (strcmp(perg[i].atributo, "positivos") == 0) { //se a porcentagem requirada for de positivos (perg[i].atributo) entao...
                resp = (pos / tot) * 100;
            } else { //analogo a codicao anterior, porem a manipulacao sera com os dados negativos
                resp = (neg / tot) * 100;
            }

            printf("%.1f%%\n", resp);
        }
    }
    return;
}

int main(void) {
    int nSent, nPerg; //variaveis para receber o numero de sentencas e perguntas
    Produto *produto; //variavel do tipo "Produto" para armazenar um vetor de sentencas
    Pergunta *pergunta; //variavel do tipo "Pergunta" para armazenar um vetor de perguntas

    scanf("%d %d", &nSent, &nPerg);
    produto = (Produto*) malloc(nSent * sizeof(Produto)); //alocacao dinamica da quantidade de sentencas (nSent) para um vetor do tipo "Produto"
    pergunta = (Pergunta*) malloc(nPerg * sizeof(Pergunta)); //analogo a linha anterior, porem para o tipo "Pergunta"

    lerProd(produto, nSent); //chamada da funcao de leitura de sentencas
    lerPerg(pergunta, nPerg); //chamada da funcao de leitura de perguntas
    respPerg(produto, nSent, pergunta, nPerg); //chamada da funcao para responder as perguntas feitas

    free(produto); //deslocacao da memoria heap da variavel "produto"
    free(pergunta); //analogo a variavel "produto"

    return 0;
}