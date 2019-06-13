#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct plv{
    char word[40];             //tamanho de cada palavra
}string;
typedef struct b{
    string vet_palavra[23];   //cria um vetor com todas as palavras de uma frase
    string produto[2];
    string perg_palavra;
    int tam;
    int quer_pos;
    int flag_pos,flag_neg;    //indica a quantidade de positivos ou negativos
    int tipo_perg;            //1 para procurar palavra   e   0 para porcentagem
}bag;
//prototipos das funcoes
void leitura(int sent,int perg,bag *frase,bag *pergunta);
void analise(int sent,int perg,bag *frase,bag *pergunta);
void tipoPergunta(int qnt,bag *pergunta);
int inverte(int n_pergunta,int n_frase,bag *frase,bag *pergunta,string *positivos,string *negativos);

void leitura(int sent,int perg,bag *frase,bag *pergunta){                   //faz a leitura das sentencas e das perguntas(armazena palavra por palavra)
    int i,j;
    for(i=0;i<sent;i++){
        j=0;
        while(strcmp("Ø",frase[i].vet_palavra[j-1].word)!=0){               //le cada palavra das sentencas ate chegar no Ø
            scanf("%s",frase[i].vet_palavra[j].word);
            j++;
        }
        frase[i].tam=j;                                                     //mostra a quantidade de elementos lidos
    }
    for(i=0;i<perg;i++){                                                    //le cada palavra das perguntas
        j=0;
        while(j<5){
            scanf("%s",pergunta[i].vet_palavra[j].word);
            j++;
        }
    }
    return;
}
void analise(int sent,int perg,bag *frase,bag *pergunta){                               //consegue identificar qual eh o produto da sentenca e da pergunta
    int i,j;
    for(i=0;i<sent;i++){
        j=0;
        while(strcmp(";",frase[i].vet_palavra[j-1].word)!=0){
            strcpy(frase[i].produto[j].word, frase[i].vet_palavra[j].word);             //pega qual eh a marca e o produto mencionado na sentenca
            j++;
        }
        strcat(frase[i].produto[0].word," ");               
        strcat(frase[i].produto[0].word,frase[i].produto[1].word);                       //junta a marca com o produto
    }
    for(i=0;i<perg;i++){
        strcpy(pergunta[i].produto[0].word, pergunta[i].vet_palavra[3].word);            //Tipo do produto
        strcpy(pergunta[i].produto[1].word, pergunta[i].vet_palavra[4].word);            //Marca do produto
        strcat(pergunta[i].produto[0].word," ");
        strcat(pergunta[i].produto[0].word,pergunta[i].produto[1].word);                 //junta a marca com o produto
    }    
    return;
}
void tipoPergunta(int qnt,bag *pergunta){
    int i;
    for(i=0;i<qnt;i++){
        if(strcmp("palavra",pergunta[i].vet_palavra[0].word)==0){                                      //verifica se a pergunta quer a % ou a quantidade de uma palavra
            pergunta[i].tipo_perg=1;
        }else{
            pergunta[i].tipo_perg=0;
        }
        strcpy(pergunta[i].perg_palavra.word,pergunta[i].vet_palavra[1].word);                         //pega se a pergunta eh sobre positivos ou negativos
        if(strcmp(pergunta[i].perg_palavra.word,"positivos")==0){   
            pergunta[i].quer_pos=1;
        }else{
            pergunta[i].quer_pos=0;
        }
        strcpy(pergunta[i].perg_palavra.word,pergunta[i].vet_palavra[1].word);                        //pega qual eh a palavra que deve ser procurada
    }
    return;
}
void resposta(int qnt_frase,int perg,bag *frase,bag *pergunta){
    int i,j,h,k,count,marcador,inv;
    string positivos[12]={{"bom"},{"maravilhoso"},{"otimo"},{"sensacional"},{"excelente"},{"adorei"},{"gostei"},{"amei"},{"eficiente"},{"boa"},{"maravilhosa"},{"otima"}};
    string negativos[12]={{"destestei"},{"odiei"},{"ruim"},{"pessimo"},{"terrivel"},{"raiva"},{"odio"},{"pessima"},{"lento"},{"lenta"},{"fragil"},{"desisti"}};
    for(i=0;i<perg;i++){
        count=0; 
        pergunta[i].flag_pos=0;
        pergunta[i].flag_neg=0;                
        if(pergunta[i].tipo_perg==1){                                                                        //vai procurar palavra sobre algum produto    
            for(j=0;j<qnt_frase;j++){                                                                        //percorrer as frases e procura aquelas que se referem ao mesmo produto
                if(strcmp(pergunta[i].produto[0].word,frase[j].produto[0].word)==0){                         //se o produto da pergunta eh o produto da sentenca
                    for(h=3;h<frase[j].tam;h++){                                                             //percorre a frase inteira
                        if(strcmp(pergunta[i].perg_palavra.word,frase[j].vet_palavra[h].word)==0){           //verifica se a palavra da frase eh a palavra buscada
                            pergunta[i].flag_pos++;
                        }
                    }
                }
            }
            printf("%d\n",pergunta[i].flag_pos);
        }else{                                                                                               //procura a % de termos positivos ou negativos  
            for(j=0;j<qnt_frase;j++){                                                                        //percorrer as frases e procura aquelas que se referem ao mesmo produto
                marcador=0;
                if(strcmp(pergunta[i].produto[0].word,frase[j].produto[0].word)==0){                         //se o produto da pergunta eh o produto da sentenca
                    inv=inverte(i,j,frase,pergunta,positivos,negativos);                                     //verifica se a sentenca possui uma inversao
                    count++;                                                                                 
                        for(h=3;h<frase[j].tam-1;h++){                                                       //percorre a frase inteira
                            if(inv==0){                                                                      //executa se ela nao estiver invertida
                                for(k=0;k<12;k++){                                                           //roda para verificar todas as palavras positivas
                                    if(pergunta[i].quer_pos==1){                                             //procura termos positivos
                                        if(strcmp(positivos[k].word,frase[j].vet_palavra[h].word)==0){       //verifica se a palavra da frase eh a palavra buscada
                                            marcador=1;
                                            pergunta[i].flag_pos++;                                   
                                            break;                                                            //se a frase possui um positivo, vai ser contada
                                        }
                                    }else{                                                                    //procura os termos negativos
                                        if(strcmp(negativos[k].word,frase[j].vet_palavra[h].word)==0){        //verifica se a palavra da frase eh a palavra buscada
                                            marcador=1;
                                            pergunta[i].flag_neg++;                                   
                                            break;                                                            //se a frase possui um negativo, vai ser contada
                                        }
                                    }
                                }
                                if(marcador==1)
                                    break;
                            }
                        }
                }
            }
            if(pergunta[i].quer_pos==1){                                                                     //imprime a quantidade dependendo de ser positiva ou negativa
                printf("%.1f%%\n",(float)pergunta[i].flag_pos*100/count);
            }else{
                printf("%.1f%%\n",(float)pergunta[i].flag_neg*100/count);
            }
        }
    }
    return;
}
int inverte(int n_pergunta,int n_frase,bag *frase,bag *pergunta,string *positivos,string *negativos){           //verifica se ha inversao na sentenca
    string w_inverte[3]={{"nao"},{"jamais"},{"nunca"}};
    int i,j,k,l,flag=0;
    for(i=3;i<frase[n_frase].tam-1;i++){                                                                        //roda todas as palavras da frase
        for(j=0;j<3;j++){                                                                                       //roda as palavras que inverte
            if(strcmp(w_inverte[j].word,frase[n_frase].vet_palavra[i].word)==0){                                //verifica se tem uma palavra que inverte
                for(k=i+1;k<i+4;k++){
                    for(l=0;l<12;l++){                                                                          //roda todas as palavras positivas
                        if(strcmp(positivos[l].word,frase[n_frase].vet_palavra[k].word)==0){                    //se achar uma palavra positiva conta no negativo
                            flag=1;
                            pergunta[n_pergunta].flag_neg++;
                            break;                                                                              //se a frase possui um positivo, vai ser contada
                        }
                        if(strcmp(negativos[l].word,frase[n_frase].vet_palavra[k].word)==0){                     //se achar uma palavra negativa conta no positivo
                            flag=1;
                            pergunta[n_pergunta].flag_pos++;
                            break; 
                        }
                        if(flag==1)
                            break;
                    }
                }
            }
        }
    }
    return flag;
}
int main(void){
    int qnt_sent, qnt_perg;
    scanf("%d %d",&qnt_sent,&qnt_perg);                  //le a quantidade de sentencas e perguntas
    bag *frase,*pergunta;                                
    frase=(bag*)malloc(qnt_sent*sizeof(bag));            //cria um vetor de palavra dinamicamente      frase eh o vetor de palavra das sentencas
    pergunta=(bag*)malloc(qnt_perg*sizeof(bag));         //cria um vetor de palavra dinamicamente      pergunta eh o vetor de palavra das perguntas
    leitura(qnt_sent,qnt_perg,frase,pergunta);           //faz a leitura das frases
    analise(qnt_sent,qnt_perg,frase,pergunta);           //verifica qual a marca e o produto
    tipoPergunta(qnt_perg,pergunta);                     //verifica o que a pergunta quer
    resposta(qnt_sent,qnt_perg,frase,pergunta);          //identifica qual a resposta buscada
    free(frase);                                         //desaloca o ponteiro frase
    free(pergunta);                                      //desaloca o ponteiro pergunta
return 0;
}