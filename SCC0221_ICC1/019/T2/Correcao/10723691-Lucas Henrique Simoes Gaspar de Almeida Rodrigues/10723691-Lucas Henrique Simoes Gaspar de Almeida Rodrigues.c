#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct frase {
    char objeto[25];
    char comentario[200];
} Frase;

typedef struct questao {
    char tipo[30]; //quanto/palavra 
    char objetos[25];
} Questao;

/*  Esta função procura no comentario se existe alguma palavra que elogie, ou critique
    (depende da matriz passada por parametro), retorna esse numero de palavras.
    @parametros: Frase - uma struct do tipo frase
                 char** - matriz de char (matElogios ou matInsultos)
    @retorno:    int - numero de palavras que coincidiram, zero se não coincidiu nenhuma
*/
int procuraPalavrasString(Frase linha, char mat[12][11]){

    int aux = 0;
    char *ret = NULL;
    for(int i = 0; i < 12; i ++){
        ret = strstr(linha.comentario, mat[i]);
        if(ret != NULL) aux++;
    }
    return aux;
}

int main(){

    int nrFrases, nrQuestoes, restoString, cont = 0, porcentagem = 0;
    char *string, strQuestao[100]; //string = usada para ler os comentarios; strQuestao = usada para ler as questoes
    
    //matrizes usadas para comparar as palavras que elogiam ou insultam nos comentários
    char matElogios[12][11] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char matInsultos[12][11] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    
    scanf("%d %d", &nrFrases, &nrQuestoes);

    Frase linha[nrFrases]; //armazena as informações do comentario, separando o produto e marca do comentario
    Questao questoes[nrQuestoes]; //armazena as informações da questão, separando o produto daquilo que se é perguntado

    for(int i = 0; i < nrFrases; i++){
        cont = 0;
        scanf("%m[^Ø]Ø", &string); //le ate ao caracter e nao armazena ele

        do{
            linha[i].objeto[cont] = string[cont]; //armazena o objeto e marca no vetor de structs
            cont++;
        }while(linha[i].objeto[cont - 1] != ';');
        
        linha[i].objeto[cont - 2] = '\0';
        
        restoString = strlen(string) - cont; //calcula onde começa o comentario

        for(int j = 0; j < restoString; j++){
            linha[i].comentario[j] = string[cont + 1]; //armazena o comentario no vetor de structs
            cont++;
        }

        free(string);
    }

    getc(stdin);

    for(int i = 0; i < nrQuestoes; i++){
        porcentagem = 0;
        cont = 17;

        scanf("%[^\n\r]", strQuestao); //le a questão ate \n ou \r

        //este trecho abaixo copia as informaçoes para a struct, separando objeto de pergunta 
        if(strncmp(strQuestao, "quantos positivos", cont) == 0){

            strncpy(questoes[i].tipo, strQuestao, cont);
            questoes[i].tipo[cont + 1] = '\0';
            
            restoString = strlen(strQuestao) - cont;

            for(int j = 0; j < restoString; j++){
                questoes[i].objetos[j] = strQuestao[cont + 4];
                cont++;
            }

            int aux = 0;
            for(int j = 0; j < nrFrases; j++){
                //por que esse strcmp da erradooooo??? 
                if(strcmp(questoes[i].objetos, linha[j].objeto) == 0){ 
                    aux++; //incrementa sempre que o objeto da questão aparecer em uma frase
                   if(procuraPalavrasString(linha[j], matElogios) != 0) porcentagem++; //incrementa quando uma frase tem um elogio
                }
            }

            printf("%.1f\n", (float)porcentagem/(float)aux); //imprime a poercentagem de comentarios bons

        } else if(strncmp(strQuestao, "quantos negativos", cont) == 0){
            
            strncpy(questoes[i].tipo, strQuestao, cont);
            questoes[i].tipo[cont] = '\0';
            
            restoString = strlen(strQuestao) - cont;

            for(int j = 0; j < restoString; j++){
                questoes[i].objetos[j] = strQuestao[cont + 4];
                cont++;
            }

            int aux = 0;
            for(int j = 0; j < nrFrases; j++){
                //por que esse strcmp da erradooooo??? 
                if(strcmp(questoes[i].objetos, linha[j].objeto) == 0){ 
                    aux++;
                   if(procuraPalavrasString(linha[j], matInsultos) != 0) porcentagem++;  //incrementa quando uma frase tem um insulto
                }
            }

            printf("%.1f\n", (float)porcentagem/(float)aux); //imprime a porcentagem de comentarios ruins
        }


    }

    return 0;
}

/*TODO
parte de palavras x em y a
arrumar eventuais problemas
*/