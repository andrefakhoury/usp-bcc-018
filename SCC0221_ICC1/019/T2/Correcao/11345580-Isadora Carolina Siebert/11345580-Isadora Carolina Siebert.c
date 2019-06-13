/*
Isadora Carolina Siebert
numero USP: 11345580
Trabalho de ICC 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Funcao separar_perguntas
Parametros: int n para indicar de qual linha da matriz se trata e matriz de string
Retorna: vazio
Funcao que armazena em um vetor cada palavra da pergunta
*/
void separar_perguntas(int n, char palavra[][70])
{
    char **array;
    array = (char**)malloc(sizeof(char*) * 5);
    for(int i = 0; i < 5; i++)
    {
        array[i] = (char*)malloc(sizeof(char) * 20);
    }
    int i, j, Npalavras, k;
    Npalavras=1;
    for(i = 0; i < 69; i++)
    {
        if(palavra[n][i] != ' ')
        {
            array[j][k] = palavra[n][i];
            k++;
        }
        else
        {
            j++;
            k=0;
            Npalavras++;
        }
    }
    /*if(array[0] == 'quantos')
    {
      quantos(array[1], array[3], array[4]);
    }
    else
    {
      palavra(array[1], array[3], array[4]);
    }*/
}

/*
Funcao separar_sentencas
Parametros: int n para indicar de qual linha da matriz se trata; matriz de string
Retorna: vazio
Funcao que armazena em um vetor cada palavra da pergunta
*/
void separar_sentencas(int n, char palavra[][441])
{
    char **array;
    char array = [200][20];
    int i, j, Npalavras, k;
    Npalavras = 1;
    for(i = 0; i < 69; i++)
    {
        if(palavra[n][i] != ' ')
        {
            array[j][k] = palavra[n][i];
            k++;
        }
        else
        {
            j++;
            k=0;
            Npalavras++;
        }
    }
}


int main (void)
{
  int num_sentencas = 0, num_perguntas = 0;
  scanf("%d %d", &num_sentencas, &num_perguntas);

  //produto marca; (max 40 caracteres)
  //fraseØ(max 400 caracteres)

  //aloca dinamicamente as sentencas
  char **sentenca = malloc(num_sentencas * sizeof(char*));
  for(int i = 0; i < num_sentencas; i++)
  {
    sentenca[i] = malloc(441 * sizeof(char));
  }

  //aloca dinamicamente as perguntas
  char **pergunta = malloc(num_perguntas * sizeof(char*));
  for(int i = 0; i < num_perguntas; i++)
  {
    pergunta[i] = (char *)malloc(70 * sizeof(char));
  }
    getchar();

  //usuario digita as sentencas
  for(int i = 0; i < num_sentencas; i++)
  {
    fgets(sentenca[i], 439, stdin);
  }

  //usuario digita as perguntas
  for(int i = 0; i < num_perguntas; i++)
  {
    fgets(pergunta[i], 69, stdin);
  }
  
  //chama a funcao que separa as perguntas em vetores de palavras
  for(int i = 0; i < num_perguntas; i++)
  {
    separar_perguntas(pergunta[i], i);
  }

  //chama a funcao que separa as sentencas em vetores de palavras
  for (int i = 0; i < num_sentencas; i++)
  {
    separar_sentencas(sentenca[i], i);
  }

  return 0; 
}
