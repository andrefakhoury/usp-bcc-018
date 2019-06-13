#include<stdio.h> //Biblioteca padrao
#include<stdlib.h> // Biblioteca 
#include<string.h> //Biblioteca para funcoes string

int main (void){
    
    // Variaveis para quantidade de sentencas
    int numfrases, numperguntas;

    // Variaveis dos comentarios
    char prodmarca[100][250];
    char frase[100][250];

    // Variaveis das perguntas
    char pergunta_primeiro[100][250];
    char pergunta_segundo[100][250];
    char pergunta_terceiro[100][250];
    char pergunta_modelo[100][250];
    char pergunta_produto[100][250];
    char pergunta_prodmarca[100][250];

    // Variaveis do Bag of Words
    char BoWnegativo[20][12] = {{"detestei\0"},{"odiei\0"},{"ruim\0"},{"pessimo\0"},{"terrivel\0"},{"raiva\0"},{"odio\0"},{"pessima\0"},{"lento\0"},{"lenta\0"},{"fragil\0"},{"desisti\0"}};

    // Leitura da quantidade de sentencas
    scanf("%d %d", &numfrases, &numperguntas);

    // Leitura dos comentarios
    // Eliminacao de um lixo da memoria
    for(int i=0; i<numfrases; i++){
        char gargageCollector[3];
        scanf("%c %40[^;]%*c %200[^Ø^\n]%*c", gargageCollector, prodmarca[i], frase[i]);
            if(prodmarca[i][strlen(prodmarca[i])-1] == ' '){ // Eliminacao do espaco
                prodmarca[i][strlen(prodmarca[i])-1] = '\0'; // Substituicao por um \0
            }
    }

    // Leitura das perguntas
    scanf("%s", pergunta_primeiro[0]);
    for(int i=0; i<numperguntas; i++){
        scanf("%s", pergunta_primeiro[i]);
        scanf("%s", pergunta_segundo[i]);
        scanf("%s", pergunta_terceiro[i]); 
        scanf("%s", pergunta_produto[i]);
        scanf("%s", pergunta_modelo[i]);

        //concatenacao do produto+modelo
        strcat(pergunta_prodmarca[i], pergunta_produto[i]);
        strcat(pergunta_prodmarca[i], " ");
        strcat(pergunta_prodmarca[i], pergunta_modelo[i]);
    }

    
    /* Selecao do 'if' conforme a primeira palavra da pergunta
    * Caso 1: primeira palavra da pergunta e' "palavra"
    *         e se espera como resposta a quantidade de vezes que
    *         aparece determinado adjetivo a um produto
    *
    * Caso 2: primeira palavra da pergunta e' "quantos"
    *         e se espera como resposta a porcentagem de
    *         comentarios elogiosos sobre insatisfeitos (ou vice-versa)
    */
    for(int i=0; i<numperguntas;i++){
        if(strcmp(pergunta_primeiro[i],"palavra") == 0){ // Caso 1
            int pontos = 0;
            for(int j = 0; j < numfrases; j++){
                if(strcmp(prodmarca[j], pergunta_prodmarca[i]) == 0){ // Comparacao de strings para selecao do comentario conforme a pergunta
                    char tempFrase[250];
                    strcpy(tempFrase, frase[j]); // Atribuicao de frase[j] `a tempFrase
                    char* dividir = strtok(tempFrase, " \0"); // Funcao strtok para separacao da string frase[j] conforme o " \0"
                    while(dividir != NULL){
                        if(strcmp(dividir, pergunta_segundo[i]) == 0){ // Comparacao do comentario e da pergunta para contagem de palavras
                            pontos++;
                        }
                    dividir = strtok(NULL, " \0");
                    }
                }
            }
            printf("%d\n", pontos);

        } else 
        if(strcmp(pergunta_primeiro[i], "quantos") == 0){ // Caso 2
            int contagem = 0;
            int contagem_negativa = 0;
            for(int j = 0; j < numfrases; j++){
                if(strcmp(prodmarca[j], pergunta_prodmarca[i]) == 0){ // Comparacao de strings para selecao do comentario conforme a pergunta
                    contagem++;
                    int tem = 0;
                    char tempFrase[250];
                    strcpy(tempFrase, frase[j]); // Atribuicao da string frase[j] `a tempFrase
                    char* dividir = strtok(tempFrase, " \0");
                    while(dividir != NULL){
                        for(int k = 0; k < 20; k++){
                            if(strcmp(BoWnegativo[k], dividir) == 0){ // Comparacao de strings para verificar a existencia 
                                                                      // de palavras do Bag of Words negativo
                                tem++;
                            }
                        }
                        dividir = strtok(NULL, " \0");
                    }

                    if(tem > 0)
                        contagem_negativa++;
                }
            }

            // Execucao da comparacao para a conta de porcentagem
            if(strcmp(pergunta_segundo[i], "negativos\0") == 0){ 
                printf("%.1f%c\n", (float)((float)contagem_negativa * 100.0) / (float)contagem, '%');
            } else {
                printf("%.1f%c\n", (float)((float)(contagem - contagem_negativa) * 100.0) / (float)contagem, '%');
            }
        }
    }

    return 0;
}