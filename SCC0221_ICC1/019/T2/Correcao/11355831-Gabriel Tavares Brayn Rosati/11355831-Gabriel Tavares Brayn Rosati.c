#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DEBUG 0

//@author gtrosati
//Gabriel Tavares Brayn Rosati - Trabalho 2 - Prof. Moacir A. Ponti

//tipos de pergunta
typedef enum _tipos {palavra, quantos, erro} Tipo;

/* @param
 * str: string base para a busca
 * palavra: string que sera buscada em str
 * @return numero de ocorrencias de palavra dentro de str
 */
int contaPalavra(const char* str, const char* palavra) {

    int tam_str = (int) strlen(str);
    int tam_palavra = (int) strlen(palavra);

    int j = 0;
    int count = 0;

    for(int i = 0; i < tam_str; i++) {
        if(j == tam_palavra - 1 && str[i] == palavra[j] && str[i+1] == ' ') {
            count++;
            j = 0;
        } else if(str[i] == palavra[j]) j++;
        else j = 0;
    }

    return count;
}

/* @param 
 * perguntas: vetor com todas as strings (perguntas e comentarios)
 * ind: indice da pergunta a ser respondida no vetor
 * nro_comentarios: numero de strings que NAO sao perguntas
 * tipo: tipo da pergunta que foi respondida (passado por referencia)
 * ret_int: retorno de tipo inteiro (passado por referencia)
 * ret_float: retorno do tipo float (passado por referencia)
 * elogios: bag of words de palavras positivas
 * criticas: bag of words de palavras negativas
 * @return void, todos os valores modificados sao passados por referencia
 */
void respondePergunta(char** perguntas, int ind, int nro_comentarios, Tipo *tipo, int *ret_int, float *ret_float, char **elogios, char **criticas) {

    int cont;
    char aux;
    char buffer[50];
    char *alvo, *produto;
    int i = 0;
    char* ocorrencia = strstr(perguntas[ind], "palavra");
    *tipo = erro; // flag de erro inicializada caso nao entre em nenhum dos ifs
        
    if(ocorrencia != NULL) {

        *tipo = palavra;
        cont = 8; // indice da primeira letra da palavra alvo na pergunta
        memset(buffer, '\0', 50);

        while(true) {
            aux = perguntas[ind][cont];
            if(aux == ' ') break;
            buffer[i] = aux;
            cont++;
            i++;
        }

        alvo = (char*) malloc((50) * sizeof(char));
        memcpy(alvo, buffer, sizeof(buffer));
        if(DEBUG) puts(alvo);
        memset(buffer, '\0', 50);
        i = 0;
        cont += 4; //ignorando o trecho " em " na pergunta

        while(true) {
            aux = perguntas[ind][cont];
            if(aux == '\n' || aux == '\r' || aux == '\0') break;
            buffer[i] = aux;
            cont++;
            i++;
        }

        produto = (char*) malloc((50) * sizeof(char));
        memset(produto, '\0', 50);
        memcpy(produto, buffer, sizeof(buffer));

        if(DEBUG) {
            puts(produto);
            puts(alvo);
        }

        int vezes = 0;
        for(i = 0; i < nro_comentarios; i++) {
            if(contaPalavra(perguntas[i], produto)) vezes += contaPalavra(perguntas[i], alvo);
        }

        *ret_int = vezes;

    } else {

        ocorrencia = strstr(perguntas[ind], "quantos");
        if(ocorrencia != NULL) {

            *tipo = quantos;

            memset(buffer, '\0', 50);

            cont = 21; // indice da primeira letra do nome do produto
            while(true) {
                aux = perguntas[ind][cont];
                if(aux == '\n' || aux == '\r' || aux == '\0') break;
                buffer[i] = aux;
                cont++;
                i++;
            }
            
            produto = (char*) malloc(50 * sizeof(char));
            memset(produto, '\0', 50);
            memcpy(produto, buffer, sizeof(buffer));

            if(DEBUG) puts(produto);

            float total = 0.0;
            float vezes = 0.0;
            int inc = 0;

            ocorrencia = strstr(perguntas[ind], "positivos");
            if(ocorrencia != NULL) {

                for(int i = 0; i < nro_comentarios; i++) {
                    ocorrencia = strstr(perguntas[i], produto);
                    if(ocorrencia != NULL) {
                        total += 1.0;
                        for(int j = 0; j < 12; j++) {
                            ocorrencia = strstr(perguntas[i], ";");
                            inc = contaPalavra(ocorrencia, elogios[j]);
                            if(inc != 0) vezes += 1.0;
                        }
                    }
                }

                *ret_float = (vezes/total) * 100;

            } else {
                ocorrencia = strstr(perguntas[ind], "negativos");
                if(ocorrencia != NULL) {

                    for(int i = 0; i < nro_comentarios; i++) {
                        ocorrencia = strstr(perguntas[i], produto);
                        if(ocorrencia != NULL) {
                            total += 1.0;
                            for(int j = 0; j < 12; j++) {
                                ocorrencia = strstr(perguntas[i], ";");
                                inc = contaPalavra(ocorrencia, criticas[j]);
                                if(inc != 0) vezes += 1.0;
                            }
                        }
                    }

                *ret_float = (vezes/total) * 100;
                }
            }
        }
    }

    if(*tipo != erro) free(produto);
    if(*tipo == palavra) free(alvo);
}

int main() {

    char *bag_elogios[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char *bag_criticas[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lenta", "lento", "fragil", "desisti"};
    int nsent, nperg;
    
    scanf("%d %d\n", &nsent, &nperg);
    
    char** linhas = (char**) malloc((nsent + nperg) * sizeof(char*));
    
    for(int i = 0; i < nsent+nperg; i++) {
        linhas[i] = (char*) malloc(200 * sizeof(char));
        memset(linhas[i], '\0', 200);
    }

    size_t buffer = 200;

    // scan dos comentarios e perguntas
    // caracteres tratados em especial: '\r', '\n' e 'Ø'
    for(int i = 0; i < nsent+nperg; i++){   
        fflush(stdin);
        getline(&linhas[i], &buffer, stdin);
        if(DEBUG) printf("%s", linhas[i]);
    }
    if(DEBUG) printf("\n");
    
    int retorno_int = -1;
    float retorno_float = -1.0;
    Tipo t_assert = palavra;
    
    //este loop comeca na primeira pergunta
    for(int i = nsent; i < (nsent + nperg); i++) {

        respondePergunta(linhas, i, nsent, &t_assert, &retorno_int, &retorno_float, bag_elogios, bag_criticas);

        if(t_assert == palavra) {
            printf("%d\n", retorno_int);
        } else if(t_assert == quantos) {
            printf("%.1f%c\n", retorno_float, '%');
        } else {
            printf("Formato de pergunta invalido.\n");
        }
    }
    
    for(int i = 0; i < nsent + nperg; i++) {
        free(linhas[i]);
    }
    free(linhas);

    return 0;
}
    
