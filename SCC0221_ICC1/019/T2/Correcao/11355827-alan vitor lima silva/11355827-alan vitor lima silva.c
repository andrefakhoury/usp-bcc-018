#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char produtos_modelo[19]; //VETOR DE STRINGS QUE ARMAZENA O MODELO
    char produtos_marca[19]; //VETOR DE STRONGS QUE ARMAZENA A MARCA
    char frases[20][19]; //VETOR DE STRINGS QUE ARMAZENA CADA PALAVRA DE CADA COMENTARIO
    char ponto_virgula[19]; // VETOR DE STRINGS QUE ARMAZENA CADA PONTO E VIRGULA DO COMENTARIO
} linha;

typedef struct{
    char primeira_palavra[19]; //VETOR DE STRINGS QUE ARMAZENA A PRIMEIRA PALAVRA DA PERGUNTA
    char segunda_palavra[19];  //VETOR DE STRINGS QUE ARMAZENA A SEGUNDA PALAVRA DA PERGUNTA
    char em[19];               //VETOR DE STRINGS QUE ARMAZENA A TERCEIRA PALAVRA DA PERGUNTA
    char modelo[19];     //VETOR DE STRINGS QUE ARMAZENA O MODELO DO PRODUTO DA PERGUNTA
    char marca[19];       //VETOR DE STRINGS QUE ARMAZENA  A MARCA DO PRODUTO DA PERGUNTA
}linha_pergunta;


int main()
{
    int n; // DEFINICAO DO NUMERO DE SENTENÇAS
    int p; // DEFINICAO DO NUMERO DE PERGUNTAS
    scanf("%d %d", &n, &p); //LEMOS OS DOIS VALORES

    linha l[n]; //CADA ESPACO DESSE VETOR TERA O MODELO, A MARCA E O COMENTARIO DO PRODUTO;

    int i, j, k, m, d, v; // DEFINIÇÃO DE VARIÁVEIS AUXILIARES

    for(i=0; i<n; i++){ //RODA O NUMERO DE LINHAS
        for(j=0; j<1; j++){
            scanf(" %s", l[i].produtos_modelo); //LE O MODELO DO PRODUTO E ARMAZENA EM UM VETOR DE STRINGS
        }
        for(d=0;d<1; d++){
            scanf(" %s",l[i].produtos_marca); //LE  A MARCA DO PRODUTO E ARMAZENA EM UM VETOR DE STRINGS
        }
          for(m=0; m<1; m++){ // RODA A QUANTIDADE DE PONTO E VIRGULA DA SENTENCA
            scanf(" %s", l[i].ponto_virgula); //LE O PONTO E VIRGULA E ARMAZENA
          }
        for(k=0; k<20; k++){             // RODA A QUANTIDADE DE PALAVRAS DA SENTENCA
           scanf(" %s", l[i].frases[k]); // LE A SENTENCA E ARMAZENA EM UM VETOR DE STRINGS
            if(l[i].frases[k][0] < 0){   // VE SE A SENTENCA CHEGOU NO CARACTER  Ø
                break;    // PARA O FOR QUANDO CHEGAR NO CARACTER  Ø
            }

            }
        }


    linha_pergunta lp[p]; // CADA ESPACO DESSE VETOR TERA UMA PERGUNTA

    for(i=0; i<p; i++){           // RODA O NUMERO DE PERGUNTAS
        for(j=0; j<1; j++) {      //RODA A PRIMEIRA PALAVRA DA PERGUNTA
            scanf("%s", lp[i].primeira_palavra);  // LE A PRIMEIRA PALAVRA DA PERGUNTA E ARMAZENA EM UM VETOR DE STRING
        }
        for(k=0; k<1; k++){       // RODA A SEGUNDA PALAVRA DA PERGUNTA
            scanf("%s", lp[i].segunda_palavra);  // LE A SEGUNDA PALAVRA DA PERGUNTA E ARMAZENA EM UM VETOR DE STRINGS
        }
        for(m=0; m<1; m++){        // RODA A TERCEIRA PALAVRA DA PERGUNTA
            scanf("%s", lp[i].em);  // LE A TERCEIRA PALAVRA DA PERGUNTA E ARMAZENA EM UM VETOR DE STRINGS
        }
        for(d=0; d<1; d++) {           // RODA O MODELO
                scanf(" %s", lp[i].modelo);  // LE O MODELO  PERGUNTA E ARMAZENA EM UM VETOR DE STRINGS

    }
        for(v=0; v<1; v++){     // RODA A MARCA
            scanf(" %s", lp[i].marca);  // LE A MARCA DA PERGUNTA E ARMAZENA EM UM VETOR DE STRINGS
        }

    }

    char positivos[12][19] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"}; // DEFINICAO DE UMA MATRIZ DE STRING COM COMENTARIOS POSITIVOS
    char negativos[12][19] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};             // DEFINICAO DE UMA MATRIZ DE STRING COM COMENTARIOS NEGATIVOS
    float porcP;    // DEFINIAO DA PORCENTAGEM DE POSITIVOS
    float porcN;     // DEFINICAO DA PORCENTAGEM DE NEGATIVOS


    for(i=0; i<p; i++){  // RODA A QUANTIDADE DE PERGUNTAS

        float contP = 0 ;  // DEFINICAO DA QUANTIDADE DE PALAVRAS POSITIVAS
        float contN = 0 ;  // DEFINICAO DA QUANTIDADE DE PALAVRAS NEGATIVAS
        int qnt = 0 ;     // DEFINICAO DA QUANTIDADE DE PALAVRAS REPETIDAS

        if(strcmp(lp[i].primeira_palavra, "palavra")==0){ // VE SE A PRIMEIRA PALAVRA DA PERGUNTA E IGUAL A "PALAVRA"
                for(k=0; k<n; k++){                                    // RODA A QUANTIDADE DE SENTENCAS
                if(strcmp(lp[i].modelo, l[k].produtos_modelo)==0 && strcmp(lp[i].marca, l[k].produtos_marca)==0){  // VERIFICA SE O MODELO E MARCA DA PERGUNTA E O MESMO DA SENTENCA
                      for(j=0; j<20; j++){                          // RODA O TAMANHO DA SENTENCA

                        if(strcmp(l[k].frases[j], lp[i].segunda_palavra)==0){ // VERIFICA SE NA SENTENCA TEM ALGUMA PALAVRA IGUAL A SEGUNDA PALAVRA DA PERGUNTA

                            qnt++;  // SE TIVER ADCIONA UM NA QUANTIDADE DE PALAVRAS
                        }

                      }


                }

           }
           printf("%d\n", qnt);  // IMPRIMI A QUANTIDADE DE PALAVRAS

        }

         else if (strcmp(lp[i].primeira_palavra, "quantos")==0){    // VE SE A PRIMEIRA PALAVRA DA PERGUNTA E IGUAL A "QUANTOS"
            for(k=0; k<n; k++){  // RODA A QUANTIDADE DE SENTENCAS
                int a = 0;
                if(strcmp(lp[i].modelo, l[k].produtos_modelo)==0 && strcmp(lp[i].marca, l[k].produtos_marca)==0 ){  // VERIFICA SE O MODELO E MARCA DA PERGUNTA E O MESMO DA SENTENCA

                 for(j=0; j<20; j++){             // RODA O TAMANHO DA SENTENÇA

                  for(m=0; m<12; m++) {             // RODA O TAMANHO DA MATRIZ POSITIVOS

                    if(strcmp(l[k].frases[j], positivos[m])==0){  // VE SE PALAVRAS DAS MATRIZ FRASES E POSITIVOS SAO IGUAIS

                            contP++;                                // SE FOREM IGUAIS ADCIONA UM NA QUANTIDADE DE POSITIVOS
                            a++;
                            break;


                        }
                        else if(strcmp(l[k].frases[j], negativos[m])==0){ // VE SE PALAVRAS DA MATRIZ FRASES E NEGATIVOS SAO IGUAIS

                            contN++; // SE FOREM IGUAIS ADCIONA UM NA QUANTIDADE DE NEGATIVOS
                            a++;
                            break;

                        }

                    }
                    if(a==1){
                        break;
                    }
               }



                }


            }
            porcP = ((contP)/(contP + contN))*100;    // ATRIBUI UM VALOR A VARIAVEL PORCP
            porcN = ((contN)/(contP + contN))*100;    // ATRIBUI UM VALOR A VARIAVEL PORCN
            if(strcmp(lp[i].segunda_palavra, "positivos")==0){  //VE SE A SEGUNDA PALAVRA DA PERGUNTA E POSITIVOS
                printf("%.1f%%\n", porcP); //SE FOR IMPRIMI PORCP
            }
            else{
                printf("%.1f%%\n", porcN); // SE NAO FOR IMPRIMI PORCN
            }

              }

        }




    return 0;
}
