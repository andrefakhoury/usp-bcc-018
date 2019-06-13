#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

    /*palavras chave elogio*/

    char elogios[12][15] = {{"bom\0"}, {"maravilhoso\0"}, {"otimo\0"}, {"sensacional\0"}, {"excelente\0"}, {"adorei\0"}, {"gostei\0"}, {"amei\0"}, {"efiiente\0"}, {"boa\0"}, {"maravilhosa\0"}, {"otima"}};

    /*variaveis*/

    int s, p, i;
    char marca_do_produto[20][20],comentario[100][100],inutil[20][20];
    char tipo_perg[100][100], objet_perg[40][40], produto[20][20], marca[20][20],prod_marca[100][100];


    scanf("%d %d ", &s, &p);

    for(i=0; i<s; i++){

        /* ler produto e marca, concatenar ambos*/

        //scanf("%s", nome_do_produto[i]);
        scanf("%49[^;]%*c", marca_do_produto[i]);
        /*ler comentario, montar sentança concatenando com produto e marca*/
        scanf("%99[^\n]%*c", comentario[i]); //trocar \n pro simbulo estranho la

        if(marca_do_produto[i][strlen(marca_do_produto[i])-1] == ' ')
            marca_do_produto[i][strlen(marca_do_produto[i])-1] = '\0';
    }

    /*ler pergunta*/
    for(i=0; i<p; i++){
        scanf("%s %s %s %s %s", tipo_perg[i], objet_perg[i], inutil[i], produto[i], marca[i]);
        sprintf(prod_marca[i], "%s %s", produto[i], marca[i]);
    }
    for(i = 0; i < p; i++){

        /*procura a palavra chave e prepara a saida*/

        if(strcmp("palavra", tipo_perg[i]) == 0){ // a se pergunta começa com palavra
            int j;
            int resultado = 0;

            for(j=0; j < s; j++){

                if(strcmp(marca_do_produto[j], prod_marca[i]) == 0){ //checa se o produto é o mesmo da pergunta
                    char* end;
                    end = strstr(comentario[j], objet_perg[i]); //procura o que a pergunta que e soma um na variavel resultado 
                    while(end != NULL){                         // enquanto end for null o laço prossegue
                        resultado++;                            
                        end = strstr(end + 1, objet_perg[i]);
                    }
                }
            }
            printf("%d\n", resultado);
        } else { //se ela começa com quantos 
            int j, numero_de_frases = 0, numero_de_elogios = 0;
            float resultado = 0.0;
            char teste = 'N';
            for(j=0; j < s; j++){
                if(strcmp(marca_do_produto[j], prod_marca[i]) == 0){
                    numero_de_frases++;
                    int d = 0;
                    for(d=0; d < 12; d++){
                        char* end;
                        end = strstr(comentario[j], elogios[d]);
                        
                        if(end != NULL){
                            teste = 'S';
                            break;
                        }
                    }
                    if(teste == 'S'){
                        numero_de_elogios++;
                        teste = 'N';
                    }
                }
            }

            /*calcula a porcentagem*/

            if(objet_perg[i][0] == 'p'){
                resultado = numero_de_elogios * 100.0;
                resultado = resultado / numero_de_frases;
            } else {
                resultado = numero_de_frases - numero_de_elogios;
                resultado = resultado * 100.0;
                resultado = resultado / numero_de_frases;
            }
            printf("%.1f%c\n", resultado, '%');
        }
    }

    return 0;
}