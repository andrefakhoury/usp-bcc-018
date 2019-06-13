#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Leonardo L. R. Guerra - Trabalho 2 - Prof. Rudinei Goularte
//Nusp: 11275234
//obs: alguns casos nao estao dando erro no run.codes, mas funcionaram na minha maquina



int contaPalavra(const char* str, const char* palavra)
{

    int tam_str = (int) strlen(str);
    int tam_palavra = (int) strlen(palavra);

    int j = 0;
    int count = 0;
    for(int i = 0; i < tam_str; i++)
    {
        if(j == tam_palavra - 2 && str[i] == palavra[j])
        {
            count++;
            j = 0;
            i--;
        }
        else if(str[i] == palavra[j])
            j++;
        else
            j = 0;
    }

    return count;
}
                                        typedef enum _types {palavra, quantos, erro} type;


void respondePergunta(char** perguntas, int ind, int nro_comentarios, type *type, int *ret_int, float *ret_float, char **elogios, char **criticas)
{

    int cont;
    char aux;
    char buffer[50];
    char *alvo, *produto;
    int i = 0;
    char* ocorrencia = strstr(perguntas[ind], "palavra");
    *type = erro; // flag de erro inicializada caso nao entre em nenhum dos ifs

    if(ocorrencia != NULL)
    {

                *type = palavra;
                cont = 8; // indice da primeira letra da palavra alvo na pergunta

                while(true)
                {
                    aux = perguntas[ind][cont];
                    if(aux == ' ')
                        break;
                    buffer[i] = aux;
                    cont++;
                    i++;
                }
                buffer[--i] = '\0';
                alvo = (char*) malloc((50) * sizeof(char));
                memset(alvo, '\0', 50);
                memcpy(alvo, buffer, sizeof(buffer));

                i = 0;
                cont += 4; //ignorando a parte  " em " na pergunta
                while(true)
                {
                    aux = perguntas[ind][cont];
                    if(aux == '\n' || aux == '\r')
                        break;
                    buffer[i] = aux;
                    cont++;
                    i++;
                }
                        buffer[i] = '\0';
                        produto = (char*) malloc((50) * sizeof(char));
                        memset(produto, '\0', 50);
                        memcpy(produto, buffer, sizeof(buffer));

                int vezes = 0;

                    i=0 ;
                while(i<nro_comentarios){

                    if(contaPalavra(perguntas[i], produto))   {
                        vezes += contaPalavra(perguntas[i], alvo);
                    }
                        i++;
                }

                *ret_int = vezes;

            }
            else
            {

                ocorrencia = strstr(perguntas[ind], "quantos");
                if(ocorrencia != NULL)
                {

                    *type = quantos;

                    cont = 21; // posição da primeira letra do nome do produto
                    while(true)
                    {
                        aux = perguntas[ind][cont];
                        if(aux == '\n' || aux == '\r')
                            break;
                        buffer[i] = aux;
                        cont++;
                        i++;
            }
            buffer[i] = '\0';
            produto = (char*) malloc(50 * sizeof(char));
            memset(produto, '\0', 50);
            memcpy(produto, buffer, sizeof(buffer));



            float total = 0.0;
            float vezes = 0.0;
            int inc = 0;

            ocorrencia = strstr(perguntas[ind], "positivos");
            if(ocorrencia != NULL)
            {

                for(int i = 0; i < nro_comentarios; i++)
                {
                    ocorrencia = strstr(perguntas[i], produto);
                    if(ocorrencia != NULL)
                    {
                        total += 1.0;
                        for(int j = 0; j < 11; j++)
                        {
                            inc = contaPalavra(perguntas[i], elogios[j]);
                            vezes += (float) inc;
                        }
                    }
                }
                *ret_float = vezes/total;
            }
            else
            {
                ocorrencia = strstr(perguntas[ind], "negativos");
                if(ocorrencia != NULL)
                {
                    for(int i = 0; i < nro_comentarios; i++)
                    {
                        ocorrencia = strstr(perguntas[i], produto);
                        if(ocorrencia != NULL)
                        {
                            total += 1.0;
                            for(int j = 0; j < 11; j++)
                            {
                                inc = contaPalavra(perguntas[i], criticas[j]);
                                vezes += (float) inc;
                            }
                        }
                    }
                    *ret_float = vezes/total;
                }
            }
        }
    }

    if(*type != erro)
        free(produto);
    if(*type == palavra)
        free(alvo);
}


int main()
{

            char *bag_elogios[] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
            char *bag_criticas[] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lenta", "lento", "fragil", "desisti"};
            int nsent, nperg;

            scanf("%d %d\n", &nsent, &nperg);

            char** linhas = (char**) malloc((nsent + nperg) * sizeof(char*));
            int l=0;
            while(l<(nsent+nperg))
            {
                linhas[l] = (char*) malloc(200 * sizeof(char));
                memset(linhas[l], '\0', 200);
                l++ ;
            }

            size_t buffer = 200;

            // leitura dos comentarios e perguntas
            // caracteres tratados em especial: '\r', '\n' e 'Ø'
            int y=0;
            while(y<(nsent+nperg))
            {
                fflush(stdin);
                getline(&linhas[y], &buffer, stdin);
                y++;
            }


            int retorno_int = -1;
            float retorno_float = -1.0;
            type t_assert = palavra;

            //este loop comeca na primeira pergunta
            int k= 0;
            while(k< (nsent+ nperg))
            {

                respondePergunta(linhas, k, nsent, &t_assert, &retorno_int, &retorno_float, bag_elogios, bag_criticas);

                if(t_assert == palavra)
                {
                    printf("%d\n", retorno_int);
                }
                else if(t_assert == quantos)
                {
                    printf("%.1f%c\n", retorno_float, '%');
                }
                else
                {
                    printf("Formato de pergunta invalido.\n");
                }
                k++;
            }
             int o=0;
             while(o<(nsent+nperg)){

                free(linhas[o]);
            o++;
            }
            free(linhas);

            return 0;
}

