#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _comentario{//define um struct para armazenar o comentarios mais facilmente
    char produto[30];
    char marca[30];
    char texto[200];
} comentario;

typedef struct _pergunta{//define um struct para armazenar a pergunta mais facilmente
    char produto[30];
    char marca[30];
    char palavra[30];
} pergunta;

int verificador(char* palavra , char* chave){//compara duas strings caracter por caracter e retorna 1 se forem iguais ou 0 se forem diferentes
    if (strlen(palavra) != strlen(chave)){
        return 0;
    }

    for (int i = 0 ; i < strlen(chave); i++){
        if (palavra[i] != chave[i]){
            return 0;
        }
    }
    return 1;
}

int contadorPalavra(char* texto , char* chave){
    int j = 0;
    int contador = 0;
    char palavra[30];
    for(int i = 0 ; i < strlen(texto) ; i++){//separa o texto por palavra e verifica cada palavra para ver se é igual a palavra chave que se procura
        if(texto[i] == ' '){
            palavra[j] = '\0';
            contador += verificador(palavra , chave);
            j = 0;
            } else{
            palavra[j] = texto[i];
            j++;
        }
    }
    return contador;
}


int main(void){
    //declara arrays de srting que o programa usará para verificar a polaridade dos comentários posteriormente
    char positivos[12][30] = {"bom" , "maravilhoso" , "otimo" , "sensacional" , "excelente" , "adorei" , "gostei" , "amei" , "eficiente" , "boa" , "maravilhosa" , "otima"};
    char negativos[12][30] = {"detestei" , "odiei" , "ruim" , "pessimo" , "terrivel" , "raiva" , "odio" , "pessima" , "lento" , "lenta" , "fragil" , "desisti"};
    //char inversores[3][7] = {"nao" , "jamais" , "nunca"};

    int acumulador = 0;//variavel auxiliar para contar a repetição das palavras entre respostas (caso 1) e quantas sentenças são positivas ou negativas (caso 2)
    float resp;//variavel auxiliar para a conta da porcentagem
    int validComent = 0;//variavel auxiliar para contar quantos comentarios referem-se a um mesmo produto
    char aux[10];//auxiliar de leitura de string


    int numComent , numPerg;// variaveis para receber o numero de comentarios e o numero de perguntas
    scanf("%d %d" , &numComent , &numPerg);

    comentario* coment;
    coment = (comentario *) malloc(numComent * sizeof(comentario));//cria um array de comentarios para armazenar os inputs
    for (int i = 0 ; i < numComent ; i++){
        scanf(" %s %s ; %[^\n\r]s" , coment[i].produto , coment[i].marca , coment[i].texto);//faz a leitura dos comentarios
    }

    pergunta *question;
    question = (pergunta *) malloc(numPerg * sizeof(pergunta));//cria um array de perguntas para armazenar os inputs
    //--------------------------------------------------------------------------------------------------------------------------
    for (int i = 0 ; i < numPerg ; i++){//faz a leitura já dividindo com os ifs se é a pergunta do primeiro ou do segundo tipo
        acumulador = 0;
        validComent = 0;//reseta contadores
        scanf(" %s" , aux);
        if (strcmp(aux , "palavra") == 0){
            scanf(" %s %*s %s %s" , question[i].palavra , question[i].produto , question[i].marca);
            for (int j = 0 ; j < numComent ; j++){//itera pelos comentarios
                if (strcmp(coment[j].produto , question[i].produto) == 0 && strcmp(coment[j].marca , question[i].marca) == 0){//confere se a pergunta e o comentario falam sobre o mesmo produto
                    int cur = contadorPalavra(coment[j].texto , question[i].palavra);
                    acumulador += cur;
                }
            }
            printf("%d\n" , acumulador);

//---------------------------------------------------------------------------------------------------------------------------------
        } else if (strcmp(aux , "quantos") == 0){
            scanf(" %s %*s %s %s" , question[i].palavra , question[i].produto , question[i].marca);
            if (strcmp(question[i].palavra , "positivos") == 0){//if seleciona se a pergunta pediu por positivos ou por negativos
                for (int j = 0 ; j < numComent ; j++){//itera pelos comentarios
                    if (strcmp(coment[j].produto , question[i].produto) == 0 && strcmp(coment[j].marca , question[i].marca) == 0){//confere se a pergunta e o comentario falam sobre o mesmo produto
                        validComent++;
                        for (int k = 0 ; k < 12 ; k++){//itera pelos valores da array de palavras positivas
                            if (contadorPalavra(coment[j].texto , positivos[k]) > 0){//verifica se há uma palavra positiva no comentario
                                acumulador++;
                                break;//para de analisar caso já encontre uma palavra positiva
                            }
                        }
                    }
                }
                float den = (float) validComent;
                float num = (float) acumulador;//convertendo minhas variáveis para float para poder fazer a divisão
                resp = 100*(num/den);
                printf("%.1f%%\n" , resp);//imprime a porcentagem das respostas

//------------------------------------------------------------------------------------------------------------------------------------
            } else {
                for (int j = 0 ; j < numComent ; j++){//itera pelos comentarios
                    if (strcmp(coment[j].produto , question[i].produto) == 0 && strcmp(coment[j].marca , question[i].marca) == 0){//confere se a pergunta e o comentario falam sobre o mesmo produto
                        validComent++;
                        for (int k = 0 ; k < 12 ; k++){//itera pelos valores da array de palavras negativas
                            if (contadorPalavra(coment[j].texto , negativos[k]) > 0){//verifica se há uma palavra negativa no comentario
                                acumulador++;
                                break;//para de analisar caso já encontre uma palavra negativa
                            }
                        }
                    }
                }
                float den = (float) validComent;
                float num = (float) acumulador;//convertendo minhas variáveis para float para poder fazer a divisão
                resp = 100*(num/den);
                printf("%.1f%%\n" , resp);//imprime a porcentagem das respostas
            }
        }
    }


    free(coment);
    free(question);
    return 0;
}