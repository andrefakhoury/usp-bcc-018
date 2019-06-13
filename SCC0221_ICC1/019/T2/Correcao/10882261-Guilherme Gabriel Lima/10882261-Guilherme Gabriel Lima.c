// Trabalho 2 – Funções, Vetores e Matrizes
/* O programa em questão irá ler receber duas entradas de inteiros
que irão corresponder a quantidade de comentários sobre determinados
produtos e perguntas acerca dos mesmos*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    /*variaveis que correspondem a primeira linha de input do programa*/
    int number_of_comments = 0, number_of_questions = 0;
    /*variavéis utilizadas para loops*/
    int i = 0, j = 0, k = 0, z = 0;
    /*variavéis para computar a quantidade de adjetivos positivos e negativos que determinado produto recebe*/
    float positivo = 0.0, negativo = 0.0, total = 0.0;
    /*vetor de produtos que serão avaliados*/
    char product[50][50];
    /*vetor de comentários feitos pelos clientes*/
    char comments[100][100];
    /*vetor de perguntas sobre qualidade dos produtos*/
    char questions[50];
    /*vetor para as marcas que serão avaliadas*/
    char marca[50];
    /*vetor para os adjetivos que serão buscadas pelo programa*/
    char adjetivo[50];
    /*vetor auxiliar*/
    char comments_broken[150];
    /*ponteiro auxiliar da função strtok*/
    char *aux;
    /*variavel para contar adjetivos*/
    int count = 0;
    /*variavel para contar quantidade de comentários sobre cada produto a ser avaliado*/
    float count_marca = 0;
    /*variavel que recebe a porcentagem de comentários positivos e negativos*/
    double porcen_words = 0;
    /*vetor de adjetivos positivos*/
    char palavras_positivas[20][20] = {"bom",
                                       "maravilhoso",
                                       "otimo",
                                       "sensacional",
                                       "excelente",
                                       "adorei",
                                       "gostei",
                                       "amei",
                                       "eficiente",
                                       "boa",
                                       "maravilhosa",
                                       "otima"};
    /*vetor de adjetivos negativos*/
    char palavras_negativas[20][20] = {"detestei",
                                       "odiei",
                                       "ruim",
                                       "pessimo",
                                       "terrivel",
                                       "raiva",
                                       "odio",
                                       "pessima",
                                       "lento",
                                       "lenta",
                                       "fragil",
                                       "desisti"};

    scanf(" %d %d", &number_of_comments, &number_of_questions);

    for (i = 0; i < number_of_comments; i++)
    {

        scanf(" %[^;];", product[i]);

        scanf(" %[^\n\r]", comments[i]);
    }

    for (i = 0; i < number_of_questions; i++)
    {

        scanf(" %s", questions);

        scanf(" %s em", adjetivo);

        scanf(" %[^\r\n]", marca);

        strncat(marca, " ", 1);

        if (strcmp(questions, "palavra") == 0) // primeira parte do trabalho que consiste na contagem de adjetivos negativos/positivos
        {
            for (j = 0; j < number_of_comments; j++)
            {
                if (strcmp(marca, product[j]) == 0)
                {
                    strncpy(comments_broken, comments[j], sizeof(comments[j]));
                    aux = strtok(comments_broken, " ");
                    /* o vetor comments foi copiado para um segundo vetor (comments_broken) para esse ser fragmentado pela função strtok.
                    Esse processo foi adotado já que a ação da strtok é definitiva, logo, um vetor auxiliar se fez necessário. */
                    while (aux != NULL)
                    {

                        if (strcmp(adjetivo, aux) == 0)
                        {
                            count++;
                        }
                        aux = strtok(NULL, " ");
                    }
                }
            }
            printf("%d\n", count);
            count = 0;
        }

        else if (strcmp(questions, "quantos") == 0) // segunda parte do trabalho que consiste na porcentagem de comentários positivos/negativos
        {

            for (z = 0; z < number_of_comments; z++)
            {
                if (strcmp(marca, product[z]) == 0)
                {
                    count_marca++;

                    strncpy(comments_broken, comments[z], sizeof(comments[z]));
                    aux = strtok(comments_broken, " ");
                    while (aux != NULL)
                    {

                        if (strcmp(adjetivo, aux) == 0)
                        {
                            count++;
                        }

                        for (k = 0; k < 12; k++)
                        {
                            if (strcmp(palavras_positivas[k], aux) == 0)
                            {
                                positivo++;
                            }
                        }
                        for (k = 0; k < 12; k++)
                        {
                            if (strcmp(palavras_negativas[k], aux) == 0)
                            {
                                negativo++;
                            }
                        }
                        aux = strtok(NULL, " ");
                    }
                }
            }

            if (positivo > negativo)
            {
                porcen_words = positivo * 100 / count_marca;
                printf("%.1lf%%\n", porcen_words);
            }
            if (negativo > positivo)
            {
                porcen_words = negativo * 100 / count_marca;
                printf("%.1lf%%\n", porcen_words);
            }
            if (negativo == positivo)
            {
                total = positivo + negativo;
                porcen_words = total * 100 / count_marca;
                printf("%.1lf%%\n", porcen_words);
            }
        }
    }
    return 0;
}
