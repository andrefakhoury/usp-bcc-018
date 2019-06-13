#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 400 // maximo de caracteres que cada sentenca tera

int verificarPolaridade (int i, char sentenca[][MAX], int inicio_p2) { // funcao que verifica a polaridade da sentenca

    char adverbios[] = "nao,jamais,nunca, ";
    int tamanho_palavra = 0; // variavel para o tamanho de uma palavra de adverbios
    int pos, ctrl_char; // variaveis para controle de posicao dos caracteres das palavras da sentenca[i] e de adverbios, respectivamente
    int inicio_palavra; // variavel para a posicao do inicio da palavra que esta em adverbios
    int ctrl_word; // variavel de controle para comparar palavras
    int tamanho_sentenca = strlen(sentenca[i]);
    int k = 0;
    int qtd_espacos = -1; // quantidade de espacos entre o adverbio anterior e a palavra de polaridade
    int pre_pos; // variavel que recebe valor 1 quando um adverbio esta numa posicao anterior a palavra de polaridade e 2 quando o mesmo adverbio esta numa posicao posterior a palavra de polaridade 
    int qtd_espacos2; // quantidade de espacos entre o adverbio posterior e a palavra de polaridade

    while (adverbios[k] != ' ') { // while que verifica se existe alguma palavra de adverbios dentro da sentenca[i]
        if (adverbios[k] != ',') { // condicional que forma a palavra dentro de adverbios, definindo o seu tamanho
            if (k == 0) {
                inicio_palavra = k;
            }
            tamanho_palavra++;
        } else { // caso em que a palavra chega ao fim: e verificada a existencia dessa palavra em sentenca[i]
            ctrl_char = inicio_palavra;
            ctrl_word = 0;
            for (pos = 0; pos < tamanho_sentenca; pos++) { // for que vai verificar se a palavra formada anteriormente existe em sentenca[i]
                if (sentenca[i][pos] == adverbios[ctrl_char]) { // if para verificacao de caracter por caracter
                    ctrl_char++;
                    ctrl_word++;
                    if (ctrl_word == tamanho_palavra) { // caso em que uma palavra de adverbios existe em sentenca[i]
                        if (sentenca[i][pos - tamanho_palavra] == ' ' && sentenca[i][pos + 1] == ' ') { // condicional que garante que os caracteres verificados em adverbios e sentenca[i] formam a mesma palavra
                            qtd_espacos = 0;          
                            pre_pos = 1;
                            for (int l = pos; l <= inicio_p2; l++) { // for que verifica quantos espacos tem entre o fim do adverbio em sentenca[i][pos] ate o inicio da palavra de polaridade sentenca[i][inicio_p2]
                                if (sentenca[i][l] == ' ') { // if que faz a contagem de espacos entre as palavras
                                    qtd_espacos++;
                                }
                            }
                            if (pos < tamanho_sentenca && qtd_espacos <= 3) { // condicional para procura de mais um possivel adverbio posterior
                                ctrl_char = inicio_palavra;
                                ctrl_word = 0;
                                qtd_espacos2 = 0;
                                for (int pos2 = pos; pos2 < tamanho_sentenca; pos2++) { // for que vai verificar se o adverbio anterior tambem aparece depois da palavra de polaridade
                                    if (sentenca[i][pos2] == adverbios[ctrl_char]) { // if para verificacao de caracter por caracter
                                        ctrl_char++;
                                        ctrl_word++;
                                        if (ctrl_word == tamanho_palavra) { // caso em que o adverbio anterior aparece depois da palavra de polaridade
                                            if (sentenca[i][pos2 - tamanho_palavra] == ' ' && sentenca[i][pos2 + 1] == ' ') { // condicional que garante que os caracteres verificados em adverbios e sentenca[i] formam a mesma palavra
                                                qtd_espacos2 = 0;
                                                pre_pos = 2;
                                                for (int m = inicio_p2; m <= pos2; m++) { // for que verifica quantos espacos tem entre o inicio da palavra de polaridade sentenca[i][inicio_p2] ate fim do adverbio em sentenca[i][pos2]
                                                    if (sentenca[i][m] == ' ') { // if que faz a contagem de espacos entre as palavras
                                                        qtd_espacos2++;
                                                    }
                                                }
                                                if (pre_pos == 2 && qtd_espacos2 <= 3) { // caso em que nao ha inversao de polaridade, pois uma palavra de polaridade cercada por dois adverbios nao tem polaridade invertida
                                                    return 2;
                                                } 
                                                break;
                                            }
                                        }
                                    } else {
                                        ctrl_char = inicio_palavra;
                                        ctrl_word = 0;
                                    }
                                }

                            }   
                        }
                    }
                } else {
                    ctrl_char = inicio_palavra;
                    ctrl_word = 0;
                }
            }
            if (k != 0) { // condicional responsavel por delimitar a posicao da string em que se tem o inicio de um adverbio
                inicio_palavra = k + 1;
            }
            tamanho_palavra = 0;
        }
        k++;
    }

    if (qtd_espacos <= 3 && qtd_espacos > 0) { 
        return 1; // caso em que ha inversao de polaridade
    } else {
        return 0; // caso em que nao ha inversao de polaridade
    }
}

void lerPergunta_1 (int i, int j, int tamanho_pergunta, int repeticao, char sentenca[][MAX], float* resposta, int caso, int* resposta_ctrl, int* resp_n) { // funcao que le a pergunta[j] sobre o produto[i] e a responde em resposta[j]

    char positivos[] = "bom,maravilhoso,otimo,sensacional,excelente,adorei,gostei,amei,eficiente,boa,maravilhosa,otima, ";
    char negativos[] = "detestei,odiei,ruim,pessimo,terrivel,raiva,odio,pessima,lento,lenta,fragil,desisti, ";
    char caso_tipo[100]; // variavel que vai receber o conteudo de positivos[] ou negativos[]
    int tamanho_palavra = 0; // variavel para o tamanho de uma palavra de caso_tipo
    int pos, ctrl_char; // variaveis para controle de posicao dos caracteres das palavras da pergunta[j] e de caso_tipo, respectivamente
    int inicio_palavra; // variavel para a posicao do inicio da palavra que esta em caso_tipo
    int ctrl_word; // variavel de controle para comparar palavras
    int tamanho_sentenca = strlen(sentenca[i]);

    if (repeticao == 0) { // condicional que adiciona 1 a resposta_ctrl[j] quando essa funcao esta sendo executada pela primeira para a leitura de sentenca[i]
        resposta_ctrl[j]++;
    }

    switch (caso) {
        case 1: // caso em que a pergunta e sobre positivos 
            strcpy(caso_tipo, positivos);
        break;
        case 0: // caso em que a pergunta e sobre negativos
            strcpy(caso_tipo, negativos);
        break;
    }

    int inicio_p2; // variavel que guarda a posicao da primeira letra da palavra que aparece em caso_tipo e em sentenca[i] ( essa palavra sera a palavra de polaridade na funcao verificarPolaridade)
    int existe = 0; // variavel que confirma a existencia ou nao de uma palavra negativa ou positiva de sentenca[i] em caso_tipo
    int k = 0;
    while (caso_tipo[k] != ' ') { // while que verifica se existe alguma palavra de caso_tipo dentro da sentenca[i]
        if (caso_tipo[k] != ',') { // condicional que forma uma palavra de caso_tipo, definindo o seu tamanho
            if (k == 0) {
                inicio_palavra = k;
            }
            tamanho_palavra++;
        } else { // caso em que a palavra chega ao fim, e verificada a existencia dessa palavra em sentenca[i]
            ctrl_char = inicio_palavra;
            ctrl_word = 0;
            for (pos = 0; pos < tamanho_sentenca; pos++) { // for que vai verificar se a palavra formada anteriormente existe em sentenca[i]
                if (sentenca[i][pos] == caso_tipo[ctrl_char]) { // if para verificacao de caracter por caracter
                    ctrl_char++;
                    ctrl_word++;
                    if (ctrl_word == tamanho_palavra) { // caso em que uma palavra de sentenca[i] existe em caso_tipo
                        if (sentenca[i][pos - tamanho_palavra] == ' ' && sentenca[i][pos + 1] == ' ') { // condicional que garante que os caracteres verificados em pergunta[j] formam a mesma palavra 
                            inicio_p2 = pos - tamanho_palavra + 1;
                            existe = 1;
                            break;
                        }
                    }
                } else {
                    ctrl_char = inicio_palavra;
                    ctrl_word = 0;
                }
            }
            if (k != 0) { // condicional responsavel por delimitar a posicao da string em que se tem o inicio de uma palavra
                inicio_palavra = k + 1;
            }
            tamanho_palavra = 0;
        }
        k++;
    }

    switch (repeticao) {
        case 0:
            if (existe == 1) { // caso em que a a palavra de caso_tipo existe na sentenca[i] quando a funcao lerPergunta_1 e executada pela primeira vez
                if (verificarPolaridade (i, sentenca, inicio_p2) == 0) { // caso em que nao ha inversao de polaridade na primeira execucao
                    resp_n[j] = resp_n[j] + existe;
                    resposta[j] = (float) resp_n[j] / (float) resposta_ctrl[j];
                } else { // caso em que ha inversao de polaridade na prmeira execucao da funcao
                    existe = 0;
                    resp_n[j] = resp_n[j] + existe;
                    resposta[j] = (float) resp_n[j] / (float) resposta_ctrl[j];            
                }
            } else { // caso em que a palavra de caso_tipo nao existe na sentenca[i] na primeira execucao, a funcao sera executada uma segunda vez para confirmar inversao de polaridade
                if (caso == 1) { // caso em que a pergunta[j] era sobre positivos
                    lerPergunta_1 (i, j, tamanho_pergunta, 1, sentenca, resposta, 0, resposta_ctrl, resp_n);
                } else { // caso em que a pergunta[j] era sobre negativos
                    lerPergunta_1 (i, j, tamanho_pergunta, 1, sentenca, resposta, 1, resposta_ctrl, resp_n);
                }    
            }
        break;
        case 1:
            if (existe == 1) { // caso em que a a palavra de caso_tipo existe na sentenca[i] quando a funcao lerPergunta_1 e executada uma segunda vez
                if (verificarPolaridade (i, sentenca, inicio_p2) == 0) { // caso em que nao ha inversao de polaridade na segunda execucao
                    existe = 0;
                    resp_n[j] = resp_n[j] + existe;
                    resposta[j] = (float) resp_n[j] / (float) resposta_ctrl[j];
                } else { // caso em que ha inversao de polaridade na segunda execucao
                    resp_n[j] = resp_n[j] + existe;
                    resposta[j] = (float) resp_n[j] / (float) resposta_ctrl[j];            
                }
            } else {// caso em que a palavra de caso_tipo nao existe na sentenca[i] na segunda execucao
                    resp_n[j] = resp_n[j] + existe;
                    resposta[j] = (float) resp_n[j] / (float) resposta_ctrl[j];
            }
        break;
    }
}

void lerPergunta_0 (int i, int j, int tamanho_pergunta, char sentenca[][MAX], char pergunta[][100], float* resposta) { // funcao que le a pergunta[j] sobre o produto[i] e a responde em resposta[j]

    int tamanho_sentenca = strlen(sentenca[i]);
    int tamanho_palavra = 0; // variavel para o tamanho de uma palavra de pergunta[j]
    int pos, ctrl_char; // variaveis para controle de posicao dos caracteres das palavras da sentenca[i] e da pergunta[j], respectivamente
    int inicio_palavra; // variavel para a posicao do inicio da palavra que esta na pergunta
    int ctrl_word; // variavel de controle para comparar palavras


    for (int k = 0; k < tamanho_pergunta; k++) { // for que fara a contagem de palavras
        if (pergunta[j][k] != ' ') { // condicional que forma uma palavra de pergunta[j], definindo o seu tamanho
            if (k == 0) {
                inicio_palavra = k;
            }
            tamanho_palavra++;
        } else { // caso em que a palavra chega ao fim, e verificada se essa palavra existe e quantas vezes aparece em sentenca[i]
            ctrl_char = inicio_palavra;
            ctrl_word = 0;
            for (pos = 0; pos < tamanho_sentenca; pos++) { // for que vai verificar se a palavra formada anteriormente existe em sentenca[i]
                if (sentenca[i][pos] == pergunta[j][ctrl_char]) { // if para verificacao de caracter por caracter
                    ctrl_char++;
                    ctrl_word++;
                    if (ctrl_word == tamanho_palavra) { // caso em que uma palavra de pergunta[i] existe em sentenca[j]
                        if (sentenca[i][pos - tamanho_palavra] == ' ' && sentenca[i][pos + 1] == ' ') { // condicional que garante que os caracteres verificados em sentenca[i] e pergunta[j] formam a mesma palavra 
                            resposta[j]++;
                            ctrl_char = inicio_palavra;
                            ctrl_word = 0;
                        }
                    }
                } else {
                    ctrl_char = inicio_palavra;
                    ctrl_word = 0;
                }
            }
            if (k != 0) { // condicional responsavel por delimitar a posicao da string em que se tem o inicio de uma palavra
                inicio_palavra = k + 1;
            }
            tamanho_palavra = 0;
        }
    }
}

int verificarPergunta (int j, char pergunta[][100]) { // funcao que verifica se a pergunta[j] e sobre quantidade de palavras ou sobre negativos e positivos
    
    char palavra_pos[] = "positivos";
    char palavra_neg[] = "negativos";
    char* ptr; // ponteiro que recebera a palavra "positivos" ou "negativos"

    ptr = strstr(pergunta[j], palavra_pos);

    if (ptr == NULL) {
        ptr = strstr(pergunta[j], palavra_neg);
        if (ptr != NULL) { // caso em que ptr recebe "negativos", a pergunta e sobre negativos
            return 0;
        } 
        return -1;
    } else { // caso em que ptr recebe "positivos", a pergunta e sobre positivos
        return 1;
    }

}

void verificarProduto (int n_sentencas, int n_perguntas, char sentenca[][MAX], char pergunta[][100], char produto[][50], float* resposta, int* resposta_ctrl, int* resp_n) { // funcao que le cada produto[i] e verifica se ele esta em alguma pergunta[j]
    int tamanho_produto, tamanho_pergunta; // variaveis de controle para comparar palavras nas strings
    int char_ctrl; // variavel de controle para comparar caracteres 
    int controle; // variavel de controle para verificar se um produto esta presente em alguma pergunta
    int caso; // variavel para verificar o tipo de pergunta
    for (int i = 0; i < n_sentencas; i++) { // for que vai percorrer cada linha i da lista produto
        tamanho_produto = strlen(produto[i]) - 1; // tamanho da string em produto[i], excluindo o espaco
        controle = 0;
        char_ctrl = 0;
        for (int j = 0; j < n_perguntas; j++) { // for que verifica se o produto[i] esta presente em alguma pergunta[j]
            tamanho_pergunta = strlen(pergunta[j]);
            for (int k = 0; k < tamanho_pergunta; k++) { // for para verificacao de caracter por caracter em produto[i] e pergunta[j]
                if (produto[i][char_ctrl] == pergunta[j][k]) {
                    controle++;
                    char_ctrl++;
                    if (controle == tamanho_produto) { // caso em que a palavra de produto[i] e achada em pergunta[j]
                        break;
                    }
                } else {
                    controle = 0;
                    char_ctrl = 0;
                }
            }
            if (controle == tamanho_produto) { // caso em que a palavra de produto[i] e achada em pergunta[j]: a pergunta[j] sera verificada, a sentenca[i] sera lida e a pergunta[j] respondida
                caso = verificarPergunta (j, pergunta);
                if (caso == -1) { // caso em que a pergunta e sobre quantidade de palavras
                    lerPergunta_0 (i, j, tamanho_pergunta, sentenca, pergunta, resposta);
                    resp_n[j] = -1;
                } else { // caso em que a pergunta e sobre positivos ou negativos
                    lerPergunta_1 (i, j, tamanho_pergunta, 0, sentenca, resposta, caso, resposta_ctrl, resp_n);
                }
            }
        }
    }
}

int main (void) {

    int n_sentencas, n_perguntas;
    scanf("%d %d ", &n_sentencas, &n_perguntas);

    char sentenca[n_sentencas][MAX]; // matriz(em forma de lista) que armazena as sentencas (bag of words), um em cada linha, na ordem de entrada
    char pergunta[n_perguntas][100]; // matriz(em forma de lista) que armazena as sentencasas perguntas, um em cada linha, na ordem de entrada
    char produto[n_sentencas][50]; // matriz(em forma de lista) que armazena os produtos, um em cada linha, na ordem de entrada
    float* resposta; // ponteiro para vetor que representa em cada linha 'i' a resposta de cada pergunta[i]
    resposta = calloc(n_perguntas, sizeof(int));
    int* resposta_ctrl; // ponteiro para vetor que representa em cada linha 'i' a quantidade de vezes em que a pergunta[i] foi respondida
    resposta_ctrl = calloc(n_perguntas, sizeof(int));
    int* resp_n; // ponteiro para vetor que representa em cada linha 'i' a quantidade de vezes em que a pergunta[i] foi positivada ou negativada (recebe valor negativo quando a pergunta nao e sobre positivo/negativo)
    resp_n = calloc(n_perguntas, sizeof(int));
 
    for (int i = 0; i < n_sentencas; i++) { // for que le e armazena os produtos e as sentencas
        scanf("%[^;]s", produto[i]);
        fgetc(stdin); // consome o ';'
        fgets(sentenca[i], MAX, stdin);
    }

    for (int i = 0; i < n_perguntas; i++) { // for que le e armazena as perguntas
        fgets(pergunta[i], 100, stdin);
    }

    verificarProduto(n_sentencas, n_perguntas, sentenca, pergunta, produto, resposta, resposta_ctrl, resp_n);

    for (int i = 0; i < n_perguntas; i++) { // for que imprime as respostas
        if (resp_n[i] >= 0) {
            resposta[i] = resposta[i] * 100;
            printf("%.1f%% \n", resposta[i]);
        } else {
            printf("%.0f \n", resposta[i]);
        }
    }
    
    free(resposta);
    free(resposta_ctrl);
    free(resp_n);

    return 0;
}