#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/*
 * PP - palavras positivas | PN - palavras negativas | PI - palavras negativas | Foram escritas no codigo fonte ja que nao serao alteradas por cada 
 * caso de teste
*/
char PP[12][19] = {"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};
char PN[12][19] = {"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
char PI[3][19] = {"nao","jamais","nunca"};

int main(void){
    /*
     *comentarios: lista com comentarios armazenados da seguinte forma: <nome_do_produto> ; <sentenca>
     *perguntas: armazenado uma pergunta por vez, depois de respondida, outra e' armazenada em cima
     */ 
    int n_comentarios = 0, n_perguntas = 0;
    scanf("%d %d", &n_comentarios, &n_perguntas);
    char comentarios[n_comentarios][24][19], perguntas[5][19];
    
    /*
     *leitura dos comentarios ate' o Ø
     */
    for(int i = 0; i < n_comentarios; i++){
        int k = 0;
        do{
            scanf("%s", comentarios[i][k]);
            k++;
        }while(strcmp(comentarios[i][k-1],"Ø")!=0);
    }
    
    /*
     *for com unidade iteradora a: loop para responder cada pergunta
     */
    for(int a = 0; a < n_perguntas; a++){
        
        /*
         * count_x(pos, neg, word):sao contadores de quantos vezes aparecem seu tipo nos comentarios
         * inversor: varivel para inverter a polaridade de um comentarios
         * s_x(pos, neg): sao quantidade de setencas de sinal
         */
        float count_pos = 0, count_neg = 0, s_pos=0, s_neg=0;
        int count_word = 0, inversor;
        
        /*
         * leitura da pergunta
         */
        for(int i = 0;i < 5;i++){
            scanf("%s", perguntas[i]);
        }
        
        /*
         * loop para ler os comentarios de acordo com a pergunta
         */
        for(int i = 0;i<n_comentarios;i++){
            if(strcmp(comentarios[i][0],perguntas[3])==0 && strcmp(comentarios[i][1],perguntas[4])==0){
                
                /*
                 * verifica se a palavras pertence a categoria positivos/negativos
                 */
                if(strcmp(perguntas[1],"positivos")==0||strcmp(perguntas[1],"negativos")==0){
                    inversor =-10;
                    int k = 3; /*iniciar a comparacao dos comentario com as palavras PP e PN a partir do comentario - posicao 3*/
                    count_pos=0;/*contador de palavras positivas*/
                    count_neg=0;/*contador de palavras negativas*/
                    /*
                     *loop ate' encontrar Ø
                     */
                    while(strcmp(comentarios[i][k],"Ø")!=0){
                        for(int j = 0; j<12; j++){
                            
                            /*
                             * verifica se ha' palavra positiva
                             */
                            if(strcmp(comentarios[i][k],PP[j])==0){
                                count_pos++;
                                /*inversor da palavra*/
                                if(k==inversor+1||k==inversor+2||k==inversor+3){
                                    count_neg++;
                                    count_pos--;
                                    inversor=-10;
                                }
                            }
                            
                            /*
                             * verifica se ha' palavra negativa
                             */
                            if(strcmp(comentarios[i][k],PN[j])==0){
                                count_neg++;
                                /*inversor da palavra*/
                                if(k==inversor+1||k==inversor+2||k==inversor+3){
                                    count_neg--;
                                    count_pos++;
                                    inversor=-10;
                                }
                            }
                        }
                        
                        /*
                         * acha palavra inversora de polaridade
                         */
                        if(strcmp(comentarios[i][k],PI[0])==0||strcmp(comentarios[i][k],PI[1])==0||strcmp(comentarios[i][k],PI[2])==0){
                            inversor=k;
                        }
                        k++;
                    }
                    /*
                         * aumenta a quantidade de sentecas positivas
                         */
                        if(count_pos>0){
                            s_pos++;
                        }
                        /*
                         * aumenta a quantidade de sentecas negativas
                         */
                        if(count_neg>0){
                            s_neg++;
                        }
                } else { /*caso no qual a pergunta pergunta por uma palavra generica*/
                    int k = 3;
                    
                    /*
                     * loop ate' encontrar Ø
                     */
                    while(strcmp(comentarios[i][k],"Ø")!=0){
                        
                        /*
                         * verifica se a palavra e' a palavra da pergunta
                         */
                        if(strcmp(comentarios[i][k],perguntas[1])==0){
                            count_word++; /*conta as palavras*/
                        }
                        k++; /*avanca para a proxima palavra da linha a ser analisada*/
                    }
                }
            }
        }
        /*impressao da resposta*/
        if(strcmp(perguntas[1],"positivos")==0){
            printf("%.1f%%\n", 100.0*s_pos/(s_neg+s_pos));
        } else {
            if(strcmp(perguntas[1],"negativos")==0){
                printf("%.1f%%\n", 100.0*s_neg/(s_neg+s_pos));
            } else {
                printf("%d\n", count_word);
            }
        }
    }
    return 0;
}
