//Diany Pressato
//n_usp 11218820
//infelizmente n�o fiz a pergunta b�nus

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int num_comentarios, num_perguntas;

    scanf("%d %d", &num_comentarios, &num_perguntas);

    getchar(); //remove o \r ou \n que veio da entrada dos n�meros de coment�rios e n�mero de perguntas
    getchar(); //remove o \r ou \n que veio da entrada dos n�meros de coment�rios e n�mero de perguntas


    char* (*produto_comentario)[22] = calloc(num_comentarios, 22 * sizeof(char*));
    // a matriz "produto_comentario" armazena na sua primeira "coluna" (coluna 0) o nome do produto e sua respectiva marca;
    // nas demais posi��es, a matriz guarda strings que contem cada palavra do coment�rio inserido;
    //ou seja, � uma matriz com n�mero de linhas igual � vari�vel "num_coment�rios" que guarda 22 strings por linha, sendo
    //que cada string guarda uma �nica palavra do coment�rio;

    char comentario[400], comentario_formatado[400];
    //"comentario[400]" � o coment�rio que o usu�rio insere inicialmente;
    //"comentario_formatado[400]" ir� armazenar o coment�rio do usu�rio sem o s�mbolo de vazio e sem \r ou \n;


        for (int i = 0; i < num_comentarios; ++i){

            fgets(comentario, 400, stdin);

            int tamanho = (int) strlen(comentario);// "tamanho" armazena o tamanho do comentario inserido pelo usu�rio;

            strncpy(comentario_formatado, comentario, tamanho - 5);

            //nas entradas do usu�rio - com exce��o da �ltima - s�o compostas por um espa�o,
            // seguido do s�mbolo de vazio, de um \r, de um \n e de um \0;
            //ou seja, eliminamos os 5 �ltimos elementos da entrada do usu�rio e armazenamos a string resultante em "comentario_formatado";
            //este procedimento evita erros futuros de leitura e compara��o;

            comentario_formatado[tamanho - 5] = '\0';//insere \0 no fim da string "comentario_foramatado", para evitar futuros erros de leitura;

            char* separacao_de_palavras = strtok(comentario_formatado, " ;");//separa��o do produto de seu respectivo coment�rio;
            //exemplo: se o "comentario_formatado" come�a com "Tv Samsung ; ... ", "separacao_de_palavras" guarda o endere�o de "Tv";
            char nome_do_produto[200];

            strcpy(nome_do_produto, separacao_de_palavras);
            //copia o conte�do de "comentario_formatado" para nome do produto, j� que ap�s a string "comentario_formatado" sofrer a��o da fun��o
            //strtok, a string � modificada;

            strcat(nome_do_produto, " ");
            //coloca��o de um espa�o ap�s a string do produto;
            //continuadno o exemplo acima: "Tv ";

            separacao_de_palavras = strtok(NULL, " ;");// seapara��o da marca do produto do respectivo coment�rio;
            //em nosso exemplo, "separacao_de_palavras" � um ponteiro para "Samsung";

            strcat(nome_do_produto, separacao_de_palavras);
            //concatena o produto e a marca; em nosso exemplo, ficaria "Tv Samsung";

            produto_comentario[i][0] = strdup(nome_do_produto);
            //armazenamento do produto e de sua marca na primeira coluna de cada linha da
            //matriz produto_comentario; no exemplo, a primeira posi��o da primeira linha da matriz "produto_comentario" guarda a string "Tv Samsung"
            //atrav�s da fun��o strdup;

            separacao_de_palavras = strtok(NULL, " ;");
            //prosseguimos separando a string;


            int palavra_atual = 1;
            // no �ndice 0 da "coluna" da matriz s� � guardado o nome do rpoduto e sua respectiva marca;
            //dos �ndices 1 a 21, guardam-se as palavras do coment�rio; por isso "palavra_atual" come�a em 1, sendo iterada at� 21;



            while (separacao_de_palavras != NULL){
            //fragment��o das palavras do coment�rio e armazenamento de cada palavra a partir da segunda coluna da matriz;
            //relembrando que cada linha da matriz possui em sua primeira coluna o produto e a marca
            //e nas demais colunas, cada palavra do coment�rio;

                produto_comentario[i][palavra_atual] = strdup(separacao_de_palavras);
                separacao_de_palavras = strtok(NULL, " ;");
                ++palavra_atual;

            }


            while (palavra_atual < 22){
            //preenchimento das demais colunas restantes com strings vazias;
            //por exemplo, se na linha 1 armazenamos apenas 15 palavras, restam 7 colunas na matriz;
            //a estas 7 colunas restantes atribu�mos uma string vazia, a fim de evitar erros de compara��o no futuro;

                produto_comentario[i][palavra_atual] = strdup("");
                ++palavra_atual;

            }

        }



    char* pergunta = malloc(120*sizeof(char));


    for (int i=0; i<num_perguntas; i++){

        fgets(pergunta,120,stdin);


        int tamanho = strlen(pergunta);


        if (i != num_perguntas - 1){
            // asperguntas inseridas pelo usu�rio cont�m os caracteres \r e \n, com exce��o da �ltima pergunta inseridapelo usu�rio:
            //por isso a condi��o � iterar i at� "num_perguntas-1";

            pergunta[tamanho - 2] = '\0';
            //retirada \r e \n das entradas do usu�rio - com exce��o de sua �ltima entrada;
        }


        char* id_pergunta = strtok(pergunta, " ");// "id_pergunta" � o identificador da pergunta, seccionando a pergunta do usu�rio em "palavra" ou "quantos"
        char* id_busca = strtok(NULL, " ");//id_busca � o termo a ser buscado em nossa matriz; exemplo "bom" , "positivos";
        char* id_produto = strtok(NULL, " "); // id_produto identifica o produto; ex: id_produto pode ser "Tv";


        id_produto = strtok(NULL, " ");//retirada do espa�o entre o produto e sua respectiva amrca;
        char* id_marca = strtok(NULL, " ");//id_marca pode ser "Samsung", por exemplo;

        //a seguir, conca
        char id_produto_marca[50];
        strcpy(id_produto_marca, id_produto);
        strcat(id_produto_marca, " ");
        strcat(id_produto_marca, id_marca);//concatena��o do produto com sua respectiva marca e um espa�o entre ambos os termos;
        //este processo pode parecer estranho, mas � necess�rio devido ao fato de strtok alterar a string;


        char palavra[10] = "palavra";


        int comparacao = strcmp(id_pergunta, palavra);



        if(comparacao == 0){// se comparacao ==0, significa que a pergunta feita pelo usu�rio � do tipo "pergunta 1" deste trabalho; o programa ent�o deve buscar a palavra "apontada" pela variavel"busca" no produto "apontado" por "id_produto_marca";

            int contador_palavra = 0;


            for(int linhas_matriz = 0; linhas_matriz<num_comentarios; linhas_matriz++){


                if( strcmp(id_produto_marca, produto_comentario[linhas_matriz][0]) == 0 ){ // se o  primeiro elemento de cada linha da matriz come�ar com o produto que o usu�rio deseja, devemos percorrer tal linha em busca da palavra "id_busca";


                    for(int k=1; k<22; k++){

                        if (strcmp(produto_comentario[linhas_matriz][k], "") == 0){
                                //se a matriz possui 15 strings, existem 7 strings vazias restantes; n�o h� necessidade de ler as demais 7 palavras;
                                //por isso a existencia do break;
                            break;
                        }

                       if(strcmp(id_busca, produto_comentario[linhas_matriz][k]) == 0){//se o produto da amtriz for id�ntico ao buscado(id_busca), acabamos
                            //de encontrar um coment�rio que opine sobre a palavra buscada;adiciona-se 1 ao n�mero de ocorr�ncias desta palavra na amtriz;

                            contador_palavra++;
                       }
                    }
                }
            }

            printf("%d\n", contador_palavra);

        }


         else{ // a pergunta feita pelo usu�rio � do "tipo2" deste trabalho;

            int comentarios_totais_produto = 0;
            int contador_positivos_nesta_linha = 0;

            char positivos[15]= "positivos";


                if(strcmp(positivos, id_busca) == 0){//a pergunta deseja contar a porcentagem de coment�rios positivos

                    for(int linhas = 0; linhas < num_comentarios; linhas++){ //itera��o as linhas da matriz,
                            //j� que esta possui os produtos e suas respectivas marcas na coluna 0;


                        if( strcmp(id_produto_marca, produto_comentario[linhas][0]) == 0){ //se a linha da coluna 0 conter o produto
                                //que estamos buscando, adiciona-se 1 a comentario_totais_produtos, pois acabamos de encontrar
                                //um coment�rio que opine sobre este produto;

                            comentarios_totais_produto++;


                            char* termos_positivos[12]={"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};

                            int igualdade = 0;//vari�vel que ser� explicada no loop seguinte


                                for(int k= 1; k < 22 && (igualdade == 0); k++){

                                    for(int l= 0; l < 12; l++){


                                        if( strcmp(produto_comentario[linhas][k],termos_positivos[l]) == 0){

                                            contador_positivos_nesta_linha++;
                                            igualdade = 1; //quando igualdade � igual a 1, sa�mos do loop que itera l , e tamb�m sa�mos do loop que itera k,
                                            //pois desejamos seguir para a pr�xima linha da matriz: basta que haja um termo positivo no coment�rio para
                                            //que este seja considerado positivo;


                                            break;
                                        }
                                    }
                                }

                        }

                     }

                     float resposta= (((float)(contador_positivos_nesta_linha))/(comentarios_totais_produto))*100;//c�lculo dos coment�rios positivos divido pelo total de coment�rios;

                     printf("%.1f%%\n", resposta);

                }

                else { // significa que se deseja saber quantas coment�rios sobre o produto descrito por "id_produto" s�o negativos;


                    int contador_negativos_nesta_linha=0;

                    for(int linhas=0; linhas<num_comentarios; linhas++){ //itera��o as linhas da matriz,
                            //j� que esta possui os produtos e suas respectivas marcas na coluna 0;



                            if( strcmp(id_produto_marca, produto_comentario[linhas][0]) == 0){ //se a linha da coluna 0 conter o produto
                                //que estamos buscando, adiciona-se 1 a comentario_totais_produtos, pois acabamos de encontrar
                                //um coment�rio que opine sobre este produto;


                                comentarios_totais_produto ++;


                                char* termos_negativos[12]={"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
                                int igualdade = 0;


                                  for(int k=1; k<22 && igualdade == 0; k++){

                                    for(int l=0; l<12; l++){


                                        if( strcmp(produto_comentario[linhas][k],termos_negativos[l]) == 0){

                                            contador_negativos_nesta_linha++;
                                            igualdade = 1; //quando igualdade � igual a 1, sa�mos do loop que itera l , e tamb�m sa�mos do loop que itera k,
                                            //pois desejamos seguir para a pr�xima linha da matriz: basta que haja um termo negativo no coment�rio para
                                            //que este seja considerado negativo;


                                            break;
                                        }
                                    }
                                  }

                            }
                     }

                     float resposta = (((float)(contador_negativos_nesta_linha))/(comentarios_totais_produto ))*100;//c�lculo do percentual de coment�rios negativos em rela��o ao
                     //total de coment�riso sobre o produto desejado;

                     printf("%.1f%%\n", resposta);

                }
        }
    }


free (pergunta);//desaloca a entrada armazenada do usu�rio referente � pergunta digitada


for(int i = 0; i < num_comentarios; i++){

    for (int j = 0; j < 22; ++j)
    {
        free(produto_comentario[i][j]);//desalocando cada string da matriz "produto_comentario";
    }

}

free(produto_comentario);//desalocando a matriz "produto_comentario";


return 0;

}

//coment�rio aos monitores/professor: achei muito empolgante e criativo o fato do trabalho envolver um conceito simples de processamento natural de linguagem!
//isso mostra ao aluno como id�ias simples podem ser desenvolvidas e gerar grandes ferramentas, um grande motivacional;
//os coment�rios divertidos tornaram o trabalho prazeroso;
//as entradas com \n e \r foram as partes mais trabalhosas, al�m da aloca��o de matriz com ponteiros
//parab�ns aos envolvidos
