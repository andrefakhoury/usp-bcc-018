#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 400 //maximo de caracteres em uma sentenca 

//struct para organizar os comentários e armazenar se são positivos ou negativos
typedef struct{
    char produto[30];
    int pos_neg;
}comentario;

//struct para organinizar o bag of words (dividir a sentença em palavras e contar quantas vezes elas aparecem)
typedef struct{
    int quantidade[20];
    char palavras[20][20];
    int num_palavras;
}Bow;

//struct para organizar as perguntas em tipo, palavra e produto requerido
typedef struct{
    char tipo_pergunta[20];
    char palavra_pergunta[20];
    char produto_pergunta[30];
}pergunta;

/* Funcao para verificar se uma sentenca é positiva ou negativa 
        Parametros
            Bow BagofWords - responsável por passar as palavras do Bow para realizar a comparacao
        Retorno
            int - inteiro que retorna 0 ou 1, se for 0 a sentenca é negativa e se for 1 é positiva 
*/
int positivo_ou_negativo (Bow BagofWords){
    char positivos[12][20];
    char negativos[12][20];
    char adverbios[3][10];
    //palavras dispostas dessa maneira para melhor leitura e organizacao
    strcpy(positivos[0],"bom\0");
    strcpy(positivos[1],"maravilhoso\0");
    strcpy(positivos[2],"otimo\0");
    strcpy(positivos[3],"sensacional\0");
    strcpy(positivos[4],"excelente\0");
    strcpy(positivos[5],"adorei\0");
    strcpy(positivos[6],"gostei\0");
    strcpy(positivos[7],"amei\0");
    strcpy(positivos[8],"eficiente\0");
    strcpy(positivos[9],"boa\0");
    strcpy(positivos[10],"maravilhosa\0");
    strcpy(positivos[11],"otimo\0");
    strcpy(negativos[0],"detestei\0");
    strcpy(negativos[1],"odiei\0");
    strcpy(negativos[2],"ruim\0");
    strcpy(negativos[3],"pessimo\0");
    strcpy(negativos[4],"terrivel\0");
    strcpy(negativos[5],"raiva\0");
    strcpy(negativos[6],"odio\0");
    strcpy(negativos[7],"pessima\0");
    strcpy(negativos[8],"lento\0");
    strcpy(negativos[9],"lenta\0");
    strcpy(negativos[10],"fragil\0");
    strcpy(negativos[11],"desisti\0");
    strcpy(adverbios[0],"nao\0");
    strcpy(adverbios[1],"jamais\0");
    strcpy(adverbios[2],"nunca\0");

    for(int i = 0;i<BagofWords.num_palavras;i++){
        for(int j = 0;j<12;j++){
            if(strcmp(BagofWords.palavras[i],positivos[j]) == 0){
                for(int k = 1;k<=3;k++){
                    for(int l = 0;l<3;l++){
                        if(strcmp(BagofWords.palavras[i-k],adverbios[l]) == 0) return 0;
                    }
                }
                return 1;
            }
            if(strcmp(BagofWords.palavras[i],negativos[j]) == 0){
                for(int k = 1;k<=3;k++){
                    for(int l = 0;l<3;l++){
                        if(strcmp(BagofWords.palavras[i-k],adverbios[l]) == 0) return 1;
                    }
                }
                return 0;
            }
        }
    }
    return 0;
}

/* Funcao para criar bag of words a partir da entrada do comentario sendo responsavel
por pegar palavra por palavra e verificar quantas vezes ela aparece
    Retorno:
        Bow - struct para armazenar o bag of words criado
*/
Bow cria_BagofWords(){
    Bow words;
    for(int a =0;a<20;a++) words.quantidade[a] = 1; //inicializa as quantidades de palavras com 1
    int l = 0,i,flag = 1;
    //for para receber as palavras e verificar se elas ja foram digitadas ou nao
    for(i = 0;i<20;i++){
        scanf(" %s",words.palavras[i]);
        if(strcmp(words.palavras[i],"Ø") == 0)break;
        if(i>=1){
            for(l = 0;l<i;l++){
                flag = strcmp(words.palavras[i],words.palavras[l]);
                if(flag == 0){
                words.quantidade[l]++;
                i--;
                break;
                }
            }
        }
    }
    i++;
    words.num_palavras = i;
    return words;
}

int main(void){
    //variáveis para armazenar respcitvamente:
    //números de frases e de perguntas, flags para checar se as palavras são iguais,
    //contagem para ver quantas palavras ou positivos e negativos existem em determinado produto
    //num_f_produto para contar quantos comentários existem de determinado produto 
    int num_f, num_p,flag1,flag2,flag3,contagem = 0,num_f_produto = 0;
    float porcentagem;
    scanf("%d%d",&num_f,&num_p);

    //variáveis para determinar o tipo de pergunta feita a partir do strcmp()
    char tipo_pergunta1[20] = "palavra\0";
    char tipo_pergunta2[20] = "positivos\0";

    //variáveis de structs responsáveis por organizar e dividir as perguntas e os comentários em partes relevantes 
    comentario frases[num_f];
    pergunta questoes[num_p];
    Bow BagofWords[num_f];

    //entrada e organização dos comentários
    for(int i = 0;i<num_f;i++){
        scanf(" %[^;]",frases[i].produto);
        frases[i].produto[strlen(frases[i].produto)-1] = '\0';
        getchar();                                              //impede a leitura do ";"
        BagofWords[i] = cria_BagofWords();
        frases[i].pos_neg = positivo_ou_negativo(BagofWords[i]);
        for(int j = 0;j<BagofWords[i].num_palavras;j++){
        }
    }
    
    //entrada e organização das perguntas 
    for(int i = 0;i<num_p;i++){
        scanf(" %[^ ]",questoes[i].tipo_pergunta);
        scanf(" %[^ ]",questoes[i].palavra_pergunta);
        getchar(); getchar(); getchar();                  //"joga fora" partes sem importância da pergunta
        scanf(" %[^\n\r]",questoes[i].produto_pergunta);
    }
    
    // for responsáve por comparar as strings determinando qual o tipo da pergunta e entregando a resposta
    for(int i = 0;i<num_p;i++){
        contagem = 0;
        num_f_produto = 0;
        flag1 = strcmp(tipo_pergunta1,questoes[i].tipo_pergunta);
        //caso pergunte quantas palavras
        if(flag1 == 0){                    
            for(int j = 0;j<num_f;j++){
                flag2 = strcmp(questoes[i].produto_pergunta,frases[j].produto);
                if(flag2 == 0){
                    for(int k = 0;k<BagofWords[j].num_palavras;k++){
                        flag3 = strcmp(questoes[i].palavra_pergunta,BagofWords[j].palavras[k]);
                        if(flag3 == 0) contagem += BagofWords[j].quantidade[k];
                    }
                }
            }
            printf("%d\n",contagem);
        //caso pergunte positivos ou negativos
        }else{                                
            for(int j = 0;j<num_f;j++){
                flag2 = strcmp(questoes[i].produto_pergunta,frases[j].produto);
                if(flag2 == 0){
                    flag3 = strcmp(questoes[i].palavra_pergunta,tipo_pergunta2);
                    if(flag3 == 0){                         //positivos
                        for(int k = 0;k<num_f;k++){
                            flag3 = strcmp(questoes[i].produto_pergunta,frases[k].produto);
                            if(flag3 == 0){
                                if(frases[k].pos_neg == 1)contagem++;
                                num_f_produto++;
                            }
                        }
                    }else{                              //negativos
                        for(int k = 0;k<num_f;k++){
                            flag3 = strcmp(questoes[i].produto_pergunta,frases[k].produto);
                            if(flag3 == 0){
                                if(frases[k].pos_neg == 0)contagem++;
                                num_f_produto++;
                            }
                        }
                    }
                }
            }
            porcentagem = (float)contagem/(float)num_f_produto*100;
            printf("%.1f%%\n",porcentagem);
        }
    }

 return 0;
}
