#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unused __attribute__((unused)); //Essa variavel global corrige um warning do compilador, o que me impede de usar o run.codes
                                    // warning: assignment makes integer from pointer without a cast [-Wint-conversion]

typedef struct {
	char nome_prod[40]; //Nome do produto, 2 * 20
	char desc[400];	//aqui seria a sentenca, 20 * 20
} Comentario;



/* Funcao para ler os comentarios
  lê e separa os comentarios (usando o caracter Ø)
  Parametros:
  sentencas - numero de comentarios que o usuário irá digitar
  Comentario* - ponteiro com vetor alocado
 */
Comentario* ler_comentarios(Comentario* lista_comment, int sentencas)
{
    int i;
    char comentarios[sentencas][440]; //Comentarios armazenados por matriz, ela se estara empilhada ate' essa funcao terminar, e' proposital

    for (i = 0; i < sentencas; i++) //lera a quantidade de sentencas
    {
        unused = scanf("%439[^'Ø']%*c", comentarios[i]); //le todo o comentario ate achar o sinal de diametro
        comentarios[i][440]= '\0'; //Define o ultimo elemento como final
        getchar(); //Pega o sinal

        char* token;
        token = strtok(comentarios[i], ";"); //funcao para separar strings
        strcpy(lista_comment[i].nome_prod, token); //alocando nome
        token = strtok(NULL, ";");
        strcpy(lista_comment[i].desc, token); //alocando a descricao
        //printf("\n\nNome do produto: %s\nSentenca: %s\n", lista_comment[i].nome_prod, lista_comment[i].desc);
    }
  return lista_comment;
}


/* Funcao para contar palavras
  Conta quantas palavras estão dentro de alguma sentenca armazenada na struct comentario*
  Parametros:
  	lista_comment - ponteiro da struct
    palavra - a palavra a ser buscada
    produto - o nome do item que deve constar a palavra
    sentencas - o numero de sentencas a ser buscado
  Retorno:
 	qtd - quantas palavras foram encontradas nos comentarios dos parametros especificados
 */
int contarpalavra (Comentario* lista_comment, char* palavra, char* produto, int sentencas)
{
    int i, qtd = 0; // i e j são apenas para os for's, qtd vai ser retornada no final
    char espaco[20] = " ";
    strcpy(palavra, strcat(palavra, espaco)); //concatenar espaco no comeco e no final, para isolar apenas a palavra
    strcpy(palavra, strcat(espaco,palavra));


    for (i=0; i < sentencas; i++) //corre a struct
    {
        if (strstr(lista_comment[i].nome_prod, produto)) //verifica na struct o nome do produto
        {
            char *tmp = lista_comment[i].desc; //iguala ao ponteiro inicial pra poder mexer futuramente
            while((tmp = strstr(tmp, palavra))) //verifica onde esta a palavra indicada, e se diferente de null
            {
               qtd++; //adiciona a ocorrencia daquela palavra
               tmp++; //seta para o novo ponteiro, para verificar novas palavras a partir daqui
            }
        }
    }
    return qtd;
}

/* Funcao para contar polaridade
  Conta quantas palavras estão dentro de alguma sentenca armazenada na struct comentario*
  Parametros:
  	lista_comment - ponteiro da struct
    polo - string "positiovos" ou "negativos"
    produto - o nome do item que deve constar a palavra
    sentencas - o numero de sentencas a ser buscado
  Retorno:
 	porcentagem de comentarios de acordo com o polo
 */
float contarpolaridade (Comentario* lista_comment, char* polo, char* produto, int sentencas)
{
    int i, j; // i e j são apenas para os for's, qtd vai ser retornada no final
    float pos = 0, neg = 0;
    //int tam_palavra = strlen(palavra); //tamanho da palavra
    char positivo[13][20] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima", "/0"};
    char negativo[13][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti","/0"};
    for (i = 0; i < sentencas; i++) //corre a struct
    {
        if (strstr(lista_comment[i].nome_prod,produto)) //verifica na struct o nome do produto
        {
            for (j = 0; j < 12; j++)
            {
                char *tmp = lista_comment[i].desc; //iguala ao ponteiro inicial pra poder mexer futuramente
                if(strstr(tmp, positivo[j])) //verifica onde esta a constante, e se diferente de null
                {
                   pos++; //adiciona a ocorrencia daquela constante
                   j = 13; //apos identificar o primeiro positivo sai do loop
                }
            }
            for (j = 0; j < 12; j++) // Muito semelhante ao codigo acima, mas aqui é somente para constante negativas
            {
                char *tmp = lista_comment[i].desc;
                if((tmp = strstr(tmp, negativo[j])))
                {
                   neg++;
                   j = 13;
                }
            }

        }
    }
    if (strcmp(polo,"negativos")){ return pos/(neg + pos)*100; } else { return (neg/(neg + pos))*100; };

    // Verifica qual o retorno esperado, e dado o retorno, calcula a porcetagem de incidencia e retorna
}


/* Funcao para ler perguntas
  le e analisa as perguntas, devolve suas respectivas respostas
  Parametros:
  	lista_comment - ponteiro da struct
    n_perguntas - numeros de perguntas a serem analisadas
    n_sentencas - numero de comentarios
 */
void ler_perguntas (Comentario* lista_comment, int n_perguntas, int n_sentencas)
{
    int j;
    char pergunta[100][100];
    for (j = 0; j < n_perguntas ; j++)
    {
        unused = scanf("%s %s %s %s %s", pergunta[0], pergunta[1], pergunta[2], pergunta[3], pergunta[4]);
        strcpy(pergunta[3], strcat(pergunta[3], " ")); //vou fazer concatenar as duas ultimas strings com um espaco, pois ela sao do mesmo objeto
        strcpy(pergunta[3], strcat(pergunta[3], pergunta[4]));
        strcpy(pergunta[4], "\0");
        if (!(strcmp(pergunta[0],"palavra"))) //Negativado pois a funcao strcmp volta 0 caso iguais
        {
            int qtd = contarpalavra (lista_comment, pergunta[1], pergunta[3], n_sentencas);
            printf("%d\n", qtd);
        }
        else
        {
            float porcento = contarpolaridade (lista_comment, pergunta[1], pergunta[3], n_sentencas);
            printf("%.1f%%\n", porcento);
            /*if (!(strcmp(pergunta[1],"positivos")))
            {}else{}*/
        }
    }
}

int main(void)
{
    int n_sentencas, n_perguntas;
    //float b;
    unused = scanf("%d %d", &n_sentencas, &n_perguntas);

    Comentario* lista_comment = malloc(sizeof(Comentario)*n_sentencas); //aloca os comenatarios dinamicamente
    lista_comment = ler_comentarios(lista_comment, n_sentencas);

    ler_perguntas(lista_comment, n_perguntas, n_sentencas);

	free(lista_comment);

    return 0;
}
