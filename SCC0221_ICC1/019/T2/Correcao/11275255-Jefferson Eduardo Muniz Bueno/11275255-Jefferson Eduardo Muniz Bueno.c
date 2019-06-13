#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****************ATENÇÃO*********************************

Caso o código esteja correto/com o número de acertos considerável, desconsidere isso, devo ter esquecido de retirar.

 
    Testei muito no terminal, e em compiladores que simulam ubuntu,
  e muitos casos davam certo. Mas, ao submeter no runcodes, a maior parte não tem resposta. E, algumas vezes, o que deveria ser o valor da porcentagem, se torna "-nan" (sem as aspas). Por exemplo, um "66.7%", se torna "-nan%"
    Pesquisei na internet sobre isso mas não achei nada sobre esse "-nan%".
 
 
  Link com imagens que exemplificam que funcionou: http://imgur.com/a/kGeU7MM

    Além disso, estou ciente de que ele não consegue intercalar perguntas, não sei porque.


*/

int main(void) {
    
    //Declaração e digitação do número de frases e perguntas
        int nFrase = 0, nPerg = 0;
        scanf("%d %d", &nFrase, &nPerg);

    //ALOCAÇÃO DE GRANDE PARTE DOS ARRAYS QUE SERÃO UTILIZADOS

        //Declaração e alocação dos produtos que serão digitados,
        //Com nFrase sendo o número máximo de vezes que os produtos serão citados.
        //Posteriormente, será feita a retirada dos nomes repetidos.
        //100 é um suposto limite para o número de caracteres no nome do produto.   
            char **produtos;
                produtos = malloc(nFrase * sizeof(char*));
                for(int i = 0; i < nFrase; i++){
                    produtos[i] = malloc(100 * sizeof(char));
                }     


        //Declaração e alocação das frases que serão digitadas,
        //Com nFrase sendo o número de frases,
        //e 200 o número de caracteres em cada frase.
            char **frases;
                frases = malloc(nFrase * sizeof(char*));
                for(int i = 0; i < nFrase; i++){
                    frases[i] = malloc(200 * sizeof(char));
                }


        //Declaração e alocação das perguntas que serão digitadas,
        //Com nPerg sendo o número de perguntas,
        //e 200 o número de caracteres em cada frase.
            char **Perguntas;
                Perguntas = malloc(nPerg * sizeof(char*));
                for(int i = 0; i < nPerg; i++){
                    Perguntas[i] = malloc(200 * sizeof(char));
                }


        //Declaração de vetor que será utilizado durante
        //a análise de uma das perguntas
            char *Perguntasprov;
            Perguntasprov = malloc(200 * sizeof(char));


        //Declaração e preenchimento do array de strings
        //que contém as palavras positivas
            char Palavras_positivas[12][20] = {
                                                "bom", 
                                                "maravilhoso", 
                                                "otimo", 
                                                "sensacional", 
                                                "excelente", 
                                                "adorei", 
                                                "gostei", 
                                                "amei", 
                                                "eficiente", 
                                                "boa", 
                                                "maravilhosa", 
                                                "otima"
                                              };       


        //Declaração e preenchimento do array de strings
        //que contém as palavras negativas
            char Palavras_negativas[12][20] = {
                                                "detestei", 
                                                "odiei", 
                                                "ruim", 
                                                "pessimo", 
                                                "terrivel", 
                                                "raiva", 
                                                "odio", 
                                                "pessima", 
                                                "lento", 
                                                "lenta", 
                                                "fragil", 
                                                "desisti"
                                              };        


    //Digitação dos nomes dos produtos,
    //seguidos de suas respectivas sentenças
        for(int i = 0; i < nFrase; i++){
            getchar();
            scanf("%[^;]s", produtos[i]);
            scanf("%[^\n\r]s", frases[i]);
        }


    //Remoção de um espaço que estava sobrando no fim da string,
    //pois o mesmo estava dando erro na análise das perguntas
        for(int i = 0; i < nFrase; i++){
          int len = strlen(produtos[i]);
          for(int j = len-1; j >= 0; j--){
            if(produtos[i][j] == ' '){
              produtos[i][j] = '\0';
              break;
            }
          }
        }


    //Digitação das perguntas.
        getchar();
        for(int i = 0; i < nPerg; i++){

          fgets(Perguntas[i], 100, stdin);
            }
        
    //Análise das perguntas a fim de emitir a resposta.
        for(int i = 0; i < nPerg; i++){
            
          //os floats abaixo serão usados somente para contabilizar
          //o números de frases positivas e negativas.
            float total = 0;    
            float positivas = 0;
            float negativas = 0;
            float resul = 0;

          //Neste if, verifica-se se a pergunta trata da porcentagem
          //de comentários positivos/negativos.
            if(strstr(Perguntas[i], "quantos") != NULL){
              //Neste, de trata dos positivos.    
                if(strstr(Perguntas[i], "positivos") != NULL){                  
                    for(int j = 0; j < nFrase; j++){
                      //Neste, somente prossegue se a pergunta 
                      //cita o produto em questão  
                        if(strstr(Perguntas[i], produtos[j]) != NULL){
                            for(int k = 0; k < 12; k++){
                              //Neste, verifica se há palavras positivas dentro
                              //das sentenças
                                if(strstr(frases[j], Palavras_positivas[k]) != NULL){
                                    positivas++;
                                    break;
                                }
                            }
                            total++;
                        }
                    }
                    resul = (positivas/total)*100;
                    printf("%.1f%%\n", resul);

                }
              //Neste, se não trata dos positivos,
              //trata dos negativos.                    
                else if(strstr(Perguntas[i], "negativos") != NULL){
                    for(int j = 0; j < nFrase; j++){
                      //Neste, novamente, somente prossegue se a
                      //pergunta cita o produto em questão                        
                        if(strstr(Perguntas[i], produtos[j]) != NULL){

                            for(int k = 0; k < 12; k++){
                                if(strstr(frases[j], Palavras_negativas[k]) != NULL){
                                    negativas++;
                                    break;
                                }
                            }
                            total++;
                        }
                    }
                    resul = (negativas/total)*100;
                    printf("%.1f%%\n", resul);

                }
            }
           
          //Aqui se faz a análise as perguntas que
          //pedem o número de x palavra citada em y produto.
            else if(strstr(Perguntas[i], "palavra") != NULL){

                 
              int tamfrase, tamtoken, achou, contagem = 0;


              for(int j = 0; j < nFrase; j++){
                //Neste, somente prossegue se a pergunta 
                //cita o produto em questão  
                  if(strstr(Perguntas[i], produtos[j]) != NULL){

                      strcpy(Perguntasprov, Perguntas[i]);

                      char *token;
                      token = strtok (Perguntasprov ," ,.-");

                      int contador = 2;
                      while (token != NULL && contador > 0){
                          token = strtok (NULL, " ,.-");
                          contador--;
                          if(contador == 1){
                            break;
                          }
                      }


                        if(contador == 1){
                          if(strstr(frases[j], token) != NULL){                         
                            
                            tamfrase = strlen(frases[j]);     
                            tamtoken = strlen(token); 



                            for(int o=0; o <= tamfrase-tamtoken; o++){
                                achou = 1;
                                for(int p=0; p<tamtoken; p++){
                                    if(frases[j][o + p] != token[p]){
                                        achou = 0;

                                        break;
                                    }
                                }

                                if(achou == 1){
                                    contagem++;


                                }
                            }






                          }
                        }
                  }              
              }
            printf("%d", contagem); 
            }
        }
    
    for(int i = 0; i < nFrase; i++){
      free(produtos[i]);
      free(frases[i]);
    }

    for(int i = 0; i < nPerg; i++){
      free(Perguntas[i]);
    }

    free(produtos);    
    free(frases);    
    free(Perguntas);    
    free(Perguntasprov);    

    return 0;
} 




