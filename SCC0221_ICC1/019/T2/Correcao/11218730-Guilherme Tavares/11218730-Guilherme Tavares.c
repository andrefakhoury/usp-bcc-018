#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char modelo[20];
    char descricao[21][20];

} bag_of_words;

int main(){
    
    int contador_dscr, num_sentencas,num_perguntas;
    int* verificador_avaliacoes;
    char input[21];
    char posi_nega[10]; // Recebe "positivos\0" ou "negativos\0"
    char pedido[20];// String que armazena a palavra a ser comparada nas avaliacoes
    char nome[20];  // Armazena o nome do produto que tera os comentarios analisados
    int recorrencia;
    float rec;
    int num_av_relativas; //Armazena o numero de avaliacoes referentes a um determinado produto
    char palavras_positivas[12][15] = {"bom\0", "maravilhoso\0", "otimo\0", "sensacional\0", "excelente\0", "adorei\0", "gostei\0", "amei\0", "eficiente\0", "boa\0", "maravilhosa\0", "otima\0"};
    char palavras_negativas[12][15] = {"detestei\0", "odiei\0", "ruim\0", "pessimo\0", "terrivel\0", "raiva\0", "odio\0", "pessima\0", "lento\0", "lenta\0", "fragil\0", "desisti\0"};
    float porcentagem;

    scanf("%d",&num_sentencas);
    scanf("%d",&num_perguntas);
    bag_of_words* avaliacoes;
    avaliacoes = malloc(sizeof(bag_of_words)*num_sentencas);
    verificador_avaliacoes = malloc(sizeof(int)*num_sentencas);

    //Recebe as sentencas dos usuarios
    for(int i = 0; i < num_sentencas; i++){
        scanf("%s", input);
        strcpy(avaliacoes[i].modelo, input);
        scanf("%s", input);
        strcat(avaliacoes[i].modelo, " ");
        strcat(avaliacoes[i].modelo, input);
        scanf("%s", input);
        if(strcmp(input, ";\0") != 0) return 1;
        contador_dscr = 0;
        while(strcmp(input, "Ø\0") != 0){
        
            scanf("%s",input);
            strcpy(avaliacoes[i].descricao[contador_dscr], input);
            
            contador_dscr++;
        }

    }



    //Recebe e armazena as perguntas feitas, e calcula o que foi pedido: 
    for(int i = 0; i < num_perguntas; i++){
        scanf("%s",input);
        if(strcmp(input, "palavra\0") == 0){ //Caso que conta a recorrencia de uma palavra especifica: 
            recorrencia = 0;
            scanf("%s", input);
            strcpy(pedido, input);
            scanf("%s",input); // recebe a palavra "em"
            if(strcmp(input, "em\0") != 0) return 1;

            scanf("%s", input);
            strcpy(nome, input);
            strcat(nome, " ");
            scanf("%s", input);
            strcat(nome, input);
            for(int j = 0; j < num_sentencas; j++){//Percorre o vetor com as avaliacoes
                contador_dscr = 0;
                if(strcmp(nome, avaliacoes[j].modelo) == 0){
                    while(strcmp(avaliacoes[j].descricao[contador_dscr], "Ø\0") != 0){//Percorre a descricao do vetor ate encontrar 'Ø'
                        //printf("Verificando(j = %d, contador_dscr = %d): %s %s\n",j, contador_dscr, avaliacoes[j].descricao[contador_dscr], pedido);//teste
                        if(strcmp(avaliacoes[j].descricao[contador_dscr], pedido) == 0){
                            recorrencia++;   
                            //printf("RECORRENCIA: %s ", avaliacoes[i].descricao[contador_dscr]);//teste
                        }
                        contador_dscr++;
                    }
                }
            }
            printf("%d\n",recorrencia); // Saída
        }else{ //caso que pede a porcentagem de comentarios negativos ou positivos
            scanf("%s",input);
            strcpy(posi_nega, input);
            
            scanf("%s", input); // recebe a palavra "em"
            if(strcmp(input, "em\0") != 0) return 1;
            
            scanf("%s", input);
            strcpy(nome, input);
            strcat(nome, " ");
            scanf("%s", input);
            strcat(nome, input);
            if(strcmp(posi_nega, "positivos\0") == 0) { // casos de comentarios positivos
                
                num_av_relativas = 0;
                for(int j = 0; j < num_sentencas; j++){ //Percorre as avaliacoes
                    
                    if(strcmp(avaliacoes[j].modelo, nome) == 0){
                        verificador_avaliacoes[j] = 1;
                        contador_dscr = 0;
                        num_av_relativas++;//Incrementa o numero de avaliacoes referentes ao produto pedido
                        while(strcmp(avaliacoes[j].descricao[contador_dscr], "Ø\0") != 0){ // Percorre as palavras da descricao
                            
                            for(int k = 0; k < 12; k++){
                                if(strcmp(avaliacoes[j].descricao[contador_dscr], palavras_positivas[k]) == 0){
                                    verificador_avaliacoes[j] = 0;
                                }
                            }
                            
                            contador_dscr++;
                        }

                    }else{
                        verificador_avaliacoes[j] = -1;
                    }                   

                }
                rec = 0;
                //Calcula a porcentagem de comentarios positivos: 
                for(int j = 0; j < num_sentencas; j++){
                    if(verificador_avaliacoes[j] == 0) {
                        rec++;
                    }
                }
                porcentagem = (rec / num_av_relativas);

                printf("%.1f%%\n",porcentagem*100);
            }else{ // caso de comentarios negativos
                num_av_relativas = 0;
                for(int j = 0; j < num_sentencas; j++){ //Percorre as avaliacoes
                    if(strcmp(avaliacoes[j].modelo, nome) == 0){
                        verificador_avaliacoes[j] = 0;
                        contador_dscr = 0;
                        num_av_relativas++;//Incrementa o numero de avaliacoes referentes ao produto pedido
                        while(strcmp(avaliacoes[j].descricao[contador_dscr], "Ø\0") != 0){ // Percorre as palavras da descricao
                            
                            for(int k = 0; k < 12; k++){
                                if(strcmp(avaliacoes[j].descricao[contador_dscr],palavras_negativas[k]) == 0){
                                    verificador_avaliacoes[j] = 1;
                                }
                            }
                            
                            contador_dscr++;
                        }

                    }else{
                        verificador_avaliacoes[j] = -1;
                    }                   

                }
                rec = 0;
                //Calcula a porcentagem de comentarios negativos: 
                for(int j = 0; j < num_sentencas; j++){
                    if(verificador_avaliacoes[j] == 1){
                        rec++;
                    }
                }
                porcentagem = (rec / num_av_relativas);

                printf("%.1f%%\n",porcentagem*100);
            }
        }   
    }
    
    return 0;
}