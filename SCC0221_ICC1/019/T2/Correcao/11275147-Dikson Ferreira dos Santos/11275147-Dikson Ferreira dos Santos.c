//Trabalho realizado/identado/debugado por Dikson Ferreira dos Santos, sob instruções do prof. Rudinei Goularte.
//Esse programa tem o intuito de ser o protótipo de um analisador de comentários, avaliando perguntas simples sobre opiniões de compradores.
// :D 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char posit[][30] = { 
    "bom", "maravilhoso", "otimo", "sensacional",
    "excelente", "adorei", "gostei", "amei", 
    "eficiente", "boa", "maravilhosa", "otima" 
}; // 12 palavras-chave positivas :D
char negat[][30] = { 
    "detestei", "odiei", "ruim", "pessimo", 
    "terrivel", "raiva", "odio", "pessima", 
    "lento", "lenta", "fragil", "desisti" 
}; // ...e 12 palavras-chave negativas D:

int negativos[10] = {0}; //Arrays que indicam quantos negativos/positivos existem em cada produto.
int positivos[10] = {0};

int idprod(char prodaux[], char prod[][30], int* nprod); //Prototipo de funcao que retorna o numero de um produto.
int idpal(char palavra[], char words[][30], int* npal); //Prototipo de funcao que retorna o numero de uma palavra no bow.
void le(int* nprod, int* npal, char words[][30], int bow[][201], char prod[][30]); //Protótipo de função para ler uma linha da entrada e associar as palavras aos produtos.

int idprod(char prodaux[], char prod[][30], int* nprod){
    int j;
    for (j=0; j<*nprod; j++) if (strcmp(prodaux, prod[j])==0) return j;
    return -1;
}

int idpal(char palavra[], char words[][30], int* npal){
    int j;
    for (j=0; j<*npal ;j++) if (strcmp(palavra, words[j])==0) return j;
    return -1;
}

void le(int* nprod, int* npal, char words[][30], int bow[][201], char prod[][30]){
    char fprod[30], fsent[500]; //Strings para armazenar o nome de produto e o comentario.
    scanf(" %[^;]; %[^\n\r]", fprod, fsent);
    fprod[strlen(fprod)-1]='\0'; //Retira o ultimo espaço.
    fsent[strlen(fsent)-2]='\0'; // Retira o símbolo do O cortado.
    int i, j, id; //id será o número associado a um produto.
    for (i=0; i<=*nprod; i++){
        if (i==*nprod){ // Identifica que não foi encontrado um produto. Cria um novo produto.
            id = i;
            strcpy(prod[id], fprod);
            (*nprod)++;
            break;
        }
        if (strcmp(fprod, prod[i])==0) { //Encontra o número do produto.
            id = i;
            break;
        }
    } 
    char straux[40];
    int l = 0, r = 0; //Servirão para separar a string maior em várias strings menores.
    int flag = 1;
    while(l<strlen(fsent)){
        if (fsent[l]!=' '){
            r = l;
            while(fsent[r+1]!='\0' && fsent[r+1]!=' ') r++;
            for (j=0; j<=r-l; j++) straux[j]=fsent[l+j];
            straux[r-l+1]='\0';
            l = r + 1;
            //se essa palavra for negativa eu tenho que dizer que tem um comentario negativo
            for (j=0; j<12; j++) if (strcmp(posit[j], straux)==0){
                if (flag) positivos[id]++; //Caso a flag esteja ativada, ele adiciona esse comentario como um positivo e desativa a flag.
                flag = 0;
            }
            for (j=0; j<12; j++) if (strcmp(negat[j], straux)==0){
                if (flag) negativos[id]++; //O mesmo que o de cima.
                flag = 0;
            }
            for (j=0; j<=*npal; j++){
                if (j==*npal){ //Nao encontrou uma palavra no BoW.
                    strcpy(words[j], straux);
                    (*npal)++;
                    bow[id][j]++;
                    break;
                }
                if (strcmp(straux, words[j])==0) { //Encontrou uma palavra na BoW. Adiciona essa palavra na bag.
                    bow[id][j]++;
                    break;
                }
            }
        }
        l++;
    }
}

int main(){
    int nsen, nperg, nprod = 0, npal = 0, i, j; //N de sentenças, de perguntas, de produtos, palavras e dois iteradores.
    char prod[10][30]; //Array com os produtos.
    int bow[10][201]; // Registra as frequências de cada palavra
    for (i=0; i<10; i++) for (j=0; j<201; j++) bow[i][j]=0; 
    char words[201][30]; // Armazena todas as palavras.
    scanf("%d%d", &nsen, &nperg);
    for (i=0; i<nsen; i++) le(&nprod, &npal, words, bow, prod);

    char perg[500], prodaux[30], palaux[30]; // Strings para armazenar o comentário inteiro e auxiliares.

    int neg, pos, id, l, r; //Número de comentarios negativos, positivos. Um id para o produto e dois iteradores.
    for (i=0; i<nperg; i++){
        scanf(" %[^\n]", perg);
        for (j=0; j<=strlen(perg); j++) if (perg[j]==13) perg[j]=0; //Admito que é uma gambiarra. Por algum motivo, o programa estava pondo o caractere 13 onde era para ser 0 ('\0').
        if (perg[0]=='q'){ // Indica que a pergunta é do tipo "quantos positivos/negativos em X"
            for (j=0;;j++){
                prodaux[j]=perg[j+21]; //A partir do char 21, a string contém o nome do produtp.
                if (perg[j+21]=='\0'){
                    prodaux[j]=' '; prodaux[j]='\0';
                    break;
                }
            }
            id = idprod(prodaux, prod, &nprod);
            neg = negativos[id]; //Negativos do produto "id".
            pos = positivos[id]; //Positivos do produto "id".
            if (perg[8]=='n') printf("%.1f%%\n", (float)(100*neg)/(pos+neg));
            if (perg[8]=='p') printf("%.1f%%\n", (float)(100*pos)/(pos+neg));
        }
        else if (perg[0]=='p') { //A pergunta é do tipo "palavra Y em X"
            l = r = 8;
            while (perg[r+1]!=' ') r++;
            for (j=0; j<=r-l; j++) palaux[j]=perg[l+j];
            palaux[r-l+1]='\0'; //Esse palaux guarda a palavra que a pergunta pede. 
            l = r+5; r = l;
            while (perg[r+1]!='\0') r++;
            for (j=0; j<=r-l; j++) prodaux[j]=perg[l+j];
            prodaux[r-l+1]='\0'; //Ja esse prodaux guarda o produto.
            printf("%d\n", bow[idprod(prodaux, prod, &nprod)][idpal(palaux, words, &npal)]);
        }
    }
    return 0;
}