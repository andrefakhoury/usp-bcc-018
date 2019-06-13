#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    
    int n_sentencas, n_perguntas,i,j=0,k,n_cont2=0;
    float porcentagem, n_cont=0, n_total=0;
    scanf("%d %d",&n_sentencas, &n_perguntas);
    char *palavras;
    char vetor_frases[n_sentencas][30][20];
    char vetor_perguntas[n_perguntas][20][20];
    int tam_frase[30];

     palavras = (char*)malloc(sizeof(char)*20); //alocando dinamicamente espaço para leitor de palavras
   
    for(i=0;i<n_sentencas;i++){//para cada comentario,
        do{		      //lendo cada palavra do comentario e armazenando em um vetor
            scanf ("%s", palavras);
            strcpy (vetor_frases[i][j], palavras);
            j++;
        }while(strcmp (palavras, "Ø") !=0);
        tam_frase[i]=j;//armazenando o numero de palavras que ha em cada comentario
        j=0;
    }
    for(i=0;i<n_perguntas;i++){//para cada pergunta,
        for(j=0;j<5;j++){     //lendo cada palavra da pergunta e armazenando em um vetor
            scanf ("%s", palavras);
            strcpy (vetor_perguntas[i][j], palavras);
        }
    }
    
    for(i=0;i<n_perguntas;i++){//executando cada pergunta
        if(strcmp(vetor_perguntas[i][0],"quantos") == 0){//se a pergunta começar com a palavra quantos e
            if(strcmp(vetor_perguntas[i][1], "positivos") == 0){//depois vier a palavra positivos
                for(j=0;j<n_sentencas;j++){
                    if(strcmp(vetor_perguntas[i][4], vetor_frases[j][1]) == 0){//verificando se o produto da pergunta corresponde ao do comentario
                        n_total++;
                        for(k=3;k<tam_frase[j];k++){//verificando se há palavras positivas
                            if(strcmp(vetor_frases[j][k],"bom")==0 || strcmp(vetor_frases[j][k],"maravilhoso")==0 || strcmp(vetor_frases[j][k],"otimo")==0 || strcmp(vetor_frases[j][k],"sensacional")==0 || strcmp(vetor_frases[j][k],"excelente")==0 || strcmp(vetor_frases[j][k],"adorei")==0 || strcmp(vetor_frases[j][k],"gostei")==0 || strcmp(vetor_frases[j][k],"amei")==0 || strcmp(vetor_frases[j][k],"eficiente")==0 || strcmp(vetor_frases[j][k],"boa")==0 || strcmp(vetor_frases[j][k],"maravilhosa")==0 || strcmp(vetor_frases[j][k],"otima")==0 ){
                                n_cont++;
                                break;
                            }
                        }
                    }
                
                }
            porcentagem=n_cont*100/n_total;
            printf("%.1f%%\n",porcentagem);
            n_cont=0;
            n_total=0;
            }
            else
            if(strcmp(vetor_perguntas[i][1], "negativos") == 0){//ou se depois vier a palavra negativos
                for(j=0;j<n_sentencas;j++){
                    if(strcmp(vetor_perguntas[i][4], vetor_frases[j][1]) == 0){//verificando se o produto da pergunta corresponde ao do comentario
                        n_total++;
                        for(k=3;k<tam_frase[j];k++){//verificando se ha palavras negativas
                            if(strcmp(vetor_frases[j][k],"detestei")==0 || strcmp(vetor_frases[j][k],"odiei")==0 || strcmp(vetor_frases[j][k],"ruim")==0 || strcmp(vetor_frases[j][k],"pessimo")==0 || strcmp(vetor_frases[j][k],"terrivel")==0 || strcmp(vetor_frases[j][k],"raiva")==0 || strcmp(vetor_frases[j][k],"odio")==0 || strcmp(vetor_frases[j][k],"pessima")==0 || strcmp(vetor_frases[j][k],"lento")==0 || strcmp(vetor_frases[j][k],"lenta")==0 || strcmp(vetor_frases[j][k],"fragil")==0 || strcmp(vetor_frases[j][k],"desisti")==0 ){
                                n_cont++;
                                break;
                            }

                        }
                    }
                
                }
            porcentagem=n_cont*100/n_total;
            printf("%.1f%%\n",porcentagem);
            n_cont=0;
            n_total=0;
            }
                
            }
            if(strcmp(vetor_perguntas[i][0], "palavra") == 0){//se a pergunta comecar com palavra
                for(j=0;j<n_sentencas;j++){
                    if(strcmp(vetor_perguntas[i][4],vetor_frases[j][1]) == 0){//verificando se o produto da pergunta corresponde ao do comentario
                        for(k=3;k<tam_frase[j];k++){
                            if(strcmp(vetor_perguntas[i][1],vetor_frases[j][k]) == 0){//fazendo a contagem do numero de vezes que a palavra perguntada aparece nos comentarios
                                n_cont2++;
                            }
                            
                        }
                    }
                }
                printf("%d\n",n_cont2);
                n_cont2=0;
            }
    }
    
    
    return 0;
}
