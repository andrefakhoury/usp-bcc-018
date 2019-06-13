#include <string.h>                                            //   Observa��es / Mea culpa: Todos os casos teste propostos pelo run.codes (inclusive o b�nus) funcionam normalmente nos compiladores
#include <stdio.h>                                             // que utilizo. Fiquei dezenas de horas depurando o programa, mas n�o encontrei o porqu� de n�o funcionar no run.codes.
#include <stdlib.h>                                            //   Algumas altera��es no c�digo original foram realizadas por conta de o run.codes simplesmente n�o compilar,
#include <math.h>                                              // ou por conta do ERRO "Falha de segmenta��o". Espero que n�o sejam discontados tantos pontos, mas o que vale � o aprendizado.
                                                               //   Gostaria de solicitar, caso o senhor saiba o problema de meu programa, uma explica��o detalhada, n�o quero 
                                                               // que esse problema se repita futuramente.
                                                               //   Como professor, caso o senhor tenha acesso a documentos que expliquem o funcionamento do compilador do run.codes,
                                                               // gostaria de solicit�-los, caso n�o seja inconveniente. 
                                                               
//prot�tipo de fun��es:
void adiciona_nada (char ** matrix, int linhas, int colunas);  // Essa fun��o recebe uma matrix char e preenche-a pelo caractere ' ' .
char ** recebe_sentenca (int n_sentencas);                     // ''  ''  ''  as senten�as digitadas e guarda-a em uma matrix char.
char ** recebe_pergunta(int n_perguntas);					   // ''  ''  ''  as perguntas e retorna uma matrix char contendo informa��es . 				
int out(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta ); // '' '' trabalha com os dados recebidos para a pergunta "1" .
float out2(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta ); // '' '' trabalha com os dados recebidos para a pergunta "2" .

void adiciona_nada (char ** matrix, int linhas, int colunas)
{
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)      //  A fun��o percorre todas as posi��es da matriz e preenche-a com o caracter ' '.
			matrix[i][j] = ' ';
	
	return ;
}
char ** recebe_sentenca (int n_sentencas)
{
	int i, j;
	char c, **cc;
	
	if (n_sentencas == 1)                                       //  A matriz � alocada dinamicamente, dadas as "n_sentencas", a matriz "cc" que guardar�
	{                                                           //o nome dos dispositivos e as senten�as digitadas, com limite m�ximo de 400 caracteres.
		cc = (char**) malloc (2 * sizeof(char));                
		for(i = 0; i < 2; i++)                                  //  Ap�s a aloca��o, a fun��o "adiciona_nada" preenche a matriz pelo caractere ' ', para
			cc[i] = (char*) malloc (400*sizeof(char));          //limp�-la de lixos presentes na mem�ria onde a matriz foi alocada.
		adiciona_nada (cc, 2, 400);                             
	}
	else
	{
		cc = (char**) malloc(n_sentencas * sizeof(char*));      //OBS: O if/else para o caso "n_sentencas == 1" foi definido por conta
		for(i = 0; i < n_sentencas; i++)                        // do run.codes alarmar o ERRO "Falha de segmenta��o", apesar de o programa
			cc[i] = (char*) malloc (400*sizeof(char));          // funcionar normalmente em outros compiladores.
		adiciona_nada (cc, n_sentencas, 400);                       
	}
	i = 0;
	j = 0;
	setbuf(stdin, NULL);                                        //  O setbuf nesse caso elimina o caracter anteriormente digitado "\n"          
	
	while (scanf("%c", &c)==1)                                  //  Nessa parte, o que � digitado como senten�a � gravado na matriz,
	{                                                           //incluindo todos os caracteres digitados, exceto '\n'.
		if (c != '\n')                                          //  Ao reconhecer o caracter '\n', a matriz passa a gravar a senten�a
			cc[i][j] = c;                                       //na pr�xima linha da matriz.
		j++;
		if (c == '\n')
		{
			i++;               
			j = 0;
		}
		if (i == n_sentencas)                                   //  O while se encerra no momento em que a vari�vel 'i' � igual
			break;                                              //ao 'n_sentencas', que � o n�mero m�ximo de senten�as a ser gravado.      
	}
	return cc;		                                            
}
char ** recebe_pergunta(int n_perguntas)
{
	int i, j;
	char **pp ;
	char **l ;
	char c;
	
	if (n_perguntas == 1)
	{
		pp = (char**) malloc (2 * sizeof(char*));                   //  Foram definidas duas matrizes char, a primeira (pp) recebe a pergunta digitada, 
		for(i = 0; i < 2; i++)                                      // a segunda matriz (l) ser� detalhada a seguir.
			pp[i] = (char*) malloc (50*sizeof(char));
	
		l = (char**) malloc (2 * sizeof(char*));
		for(i = 0; i < 2; i++)
			l[i] = (char*) malloc (40 * sizeof(char));
	
		adiciona_nada(pp, 2, 50);
		adiciona_nada(l, 2, 40);
	}
	
	else
	{
		pp = (char**) malloc (n_perguntas * sizeof(char*));
		for(i = 0; i < n_perguntas; i++)
			pp[i] = (char*) malloc (50*sizeof(char));
	
		l = (char**) malloc (n_perguntas * sizeof(char*));
		for(i = 0; i < n_perguntas; i++)
			l[i] = (char*) malloc (40 * sizeof(char));
	
		adiciona_nada(pp, n_perguntas, 50);
		adiciona_nada(l, n_perguntas, 40);		
	}
		
	i = j = 0;

	setbuf(stdin, NULL);
	
	while (scanf("%c", &c)==1)
	{
		if (c != '\n')
			pp[i][j] = c;
		j++;                                                       //   A matriz (pp) recebe todas a perguntas digitadas.
		if (c == '\n')
		{
			i++;
			j = 0;
		}
		if (i == n_perguntas)
			break;
	}

	for (i = 0; i < n_perguntas; i++)
	{
		if(pp[i][0] == 'p')
		{
			l[i][0] = '1';
			c = 'a', j = 1;                                       //   Nesta parte, h� uma convers�o dos dados recebidos por "pp".
			while (c != ' ')                                      //   Dadas que sempre as perguntas come�am com o caractere 'p' ou 'q' 
			{                                                     // e 'p' sempre refere-se � pergunta de n�mero 1, e 'q' sempre se refere
				l[i][j] = pp[i][j + 7];                           // � pergunta de n�mero 2, a matriz "l" recebe essa informa��o e a guarda sempre
				c = pp[i][j + 8];                                 // na primeira posi��o de cada uma de suas linhas.
				j++;
			}
			while (pp[i][j+11] != ' ' || pp[i][j+12] != ' ')      //   Ap�s constar '1' na primeira posi��o da linha, � guardada
			{                                                     // a palavra no qual se quer contar, a partir da segunda posi��o.
				l[i][j + 1] = pp[i][j+11];                        //   � pulada uma posi��o, e a em seguida � guardado o nome do dispositivo
				j++;                                              // no qual se pretende procurar a palavra.
			}
		}
		if(pp[i][0] == 'q')
		{
			l[i][0] = '2';
			c = 'a', j = 0;                                        //  Ap�s constar '2' na primeira posi��o da linha, � guardada na segunda posi��o
	                                                               // o caractere 'n' para negativos e 'p' para positivos.
			if (pp[i][8] == 'n'){
				while (pp[i][j+20] != ' ' || pp[i][j+21] != ' ')   //  A seguir, � pulada uma posi��o e � guardado o nome do dispositivo digitado.
				{
					l[i][j + 2] = pp[i][j+20];
					j++;
				}
				l[i][1] = 'n';
			}
	
			if (pp[i][8] == 'p')
			{
				while (pp[i][j+20] != ' ' || pp[i][j+21] != ' ')
				{
					l[i][j + 2] = pp[i][j+20];
					j++;
				}
				l[i][1] = 'p';
			}			

		}
	}
	if (n_perguntas == 1){
		for(i = 0; i < 2; i++)                //  Dada que n�o ser� mais utilizada, a matriz "pp" � liberada.
			free(pp[i]);
		free(pp);
	}
	return l;                                 //  Todas as informa��es �teis da pergunta digitada s�o armazenadas na matriz "l"
}                                             //e retornadas;
int out(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta )
{
	int i, j, cont = 0, TAM = 0, tam = 0;
	char c, dispositivo[30], palavra[21];
	
	for (i = 0; i < 21; i++)              //  S�o definidos dois vetores de caracteres, que servem como
		dispositivo[i] = ' ';             // comparadores.
	
	for (i = 0; i < 30; i++)
		palavra[i] = ' ';
	
	if (a_pergunta[linha][0] == '1')
	{
		c = '1', j = 0;
		while(c != ' ')
		{
			j++;
			if (a_pergunta[linha][j] != ' ')
				palavra[j-1] = a_pergunta[linha][j];      //  O vetor "palavra" recebe a palavra no qual ser� utilizada para compara��o,
			c = a_pergunta[linha][j];                     // contida na matriz "a_pergunta", de sua segunda posi��o at� o caractere ' '.
		}
		tam = j-1;                                        //  A vari�vel "tam" representa o n�mero de caracteres contidos em "palavra".
		j++;
		while (a_pergunta[linha][j] != ' ' || a_pergunta[linha][j+1] != ' ')     //   Esse while percorre todas as posi��es depois do caractere ' '
		{                                                                        // que separa a "palavra" e o nome do dispositivo, na matriz "a_pergunta"
			dispositivo[TAM] = a_pergunta[linha][j];                             // e para quando h� dois caracteres ' ' consecutivos.
			j++;
			TAM++;                                                               //   A vari�vel "TAM" representa o n�mero de caracteres presentes 
		}                                                                        // no nome do dispositivo a ser avaliado.

		char *apenas_sentenca;                                                   //   O vetor "apenas_sentenca" guarda, incluindo ';', a senten�a,
		apenas_sentenca = (char*) malloc ((400 - (TAM+1))*sizeof(char));	     // sem o nome do dispositivo, como foi guardado na fun��o "recebe_sentenca".
		
		for(i = 0; i < n_sentencas; i++)
		{
			if(strncmp(dispositivo, a_sentenca[i], TAM) == 0)                    //   Caso o nome do dispositivo seja o mesmo presente no in�cio da matriz "a_sentenca" ...
			{
				
				for(j = TAM+1; j < 400; j++)
					apenas_sentenca[j - (TAM+1)] = a_sentenca[i][j];             //   O vetor de caractere "apenas_sentenca" recebe aqui a senten�a sem o nome do dispositivo.
				
				char delim[] = " ";
				
				char *word = strtok(apenas_sentenca, delim);                     //   
				
				while (word != NULL)
				{	
		
					if (strncmp(word, palavra, tam) == 0 && word[tam] == 0)      //   O vetor "apenas_sentenca" � "cortado" em strings recebidas por "word" 
						cont++;                                                  // e "palavra" � comparada com cada palavra presente no vetor "apenas_sentenca".
					word = strtok(NULL, delim);                                  //   H� uma contagem cada vez que "palavra" � igual a "word".
				}
			}
		}
		free(apenas_sentenca);          // "apenas_sentenca" foi alocada dinamicamente, portanto � liberta aqui, ap�s n�o possuir mais utilidade na fun��o.
	}
	return cont;                    //   A fun��o retorna o n�mero de vezes que a palavra perguntada apareceu, dado o nome do dispositivo.
}
float out2(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta )
{
	int i, j, k, TAM = 0, cont=0, cont2;
	char dispositivo[30];
	
	for (i = 0; i < 21; i++)
		dispositivo[i] = ' ';
	
	char polaridade[3][7] = {"nao", "jamais", "nunca"};
	int vet_pol[3] = {3, 6, 5};
	
	char ruim[12][9] = {"detestei", "odiei"  , "ruim" , "pessimo", "terrivel", "raiva",                        //   S�o abaixo definidas as strings que representam "positivos" ou "negativos.
	                    "odio"    , "pessima", "lento", "lenta"  , "fragil"  , "desisti"};                     //   S�o tamb�m definidos os tamanhos dessas strings, e guardados em um vetor inteiro.
	int vet_ruim[12] = {8, 5, 4, 7, 8, 5, 4, 7, 5, 5, 6, 7};
	
	char bom[12][12] = {"bom"   , "maravilhoso", "otimo"    , "sensacional", "excelente"  , "adorei",	
                        "gostei", "amei"       , "eficiente", "boa"        , "maravilhosa", "otima"};
	int vet_bom[12]  = {3, 11, 5, 11, 9, 6, 6, 4, 9, 3, 11, 5};
		
	j = 3;
	while (a_pergunta[linha][j] != ' ' || a_pergunta[linha][j+1] != ' ')
	{
		dispositivo[j-3] = a_pergunta[linha][j];                                   //   O nome do dispositivo � guardado na string "dispositivo", e seu tamanho, na vari�vel "TAM".
		j++;
		TAM++; 
	}

	char *apenas_sentenca;                                                         //   O vetor "apenas_sentenca" guarda, incluindo ';', a senten�a,
	apenas_sentenca = (char*) malloc ((400 - (TAM+1))*sizeof(char));               // sem o nome do dispositivo, como foi guardada na fun��o "recebe_sentenca".
		
	if(a_pergunta[linha][1] == 'p')             //   Este � o caso para as inten��es positivas para as senten�as.
	{
		float dividendo=0, divisor=0;
		for(i = 0; i < n_sentencas; i++)
		{
			if(strncmp(dispositivo, a_sentenca[i], TAM) == 0)                      //   Este IF compara o nome do dispositivo e o nome presente na matriz "a_sentenca".
			{
				int valor = 0;
				divisor++;
					
				for(j = TAM+1; j < 400; j++)                                       //   Nesta parte � guardada apenas a senten�a, excluindo o nome do dispositivo. 
					apenas_sentenca[j - (TAM+1)] = a_sentenca[i][j];               
				
				char delim[] = " ";
				char *word = strtok(apenas_sentenca, delim);
					
				cont = 3, cont2 = 0;
				
				while(word != NULL)
				{
					cont2++;
					for(k = 0; k < 12; k++)                                        //   O vetor "apenas_sentenca" � "quebrado" em palavras recebidas pelo vetor "word".
						if (strncmp(word, bom[k], vet_bom[k]) == 0 )               //   Caso "word" seja igual a uma das palavras definidas no vetor "vet_bom",
							valor = 1;                                             // a vari�vel "valor" recebe 1.

					if (cont == 0)
						for (k = 0; k < 12; k++){
							if (strncmp(word, bom[k], vet_bom[k]) == 0 && cont2 <= 3)   //   Foram definidas duas vari�veis inteiras, cont e cont2.
								valor = 0;                                              //   "cont" torna-se igual a 0 quando "word" � uma das palavras que invertem 
					}                                                                   //  a polaridade da senten�a.
					if (cont == 0)
						for (k = 0; k < 12; k++){
                                                                                         //   Enquanto isso, "cont2" � em 1 cada vez que a palavra muda.
							if (strncmp(word, ruim[k], vet_ruim[k]) == 0 && cont2 <= 3)  // e a polaridade s� inverte quando "cont2" � menor ou igual a 3 e
								valor = 1;                                               // quando "word" � igual a uma palavra, da matriz "ruim" ou "bom".
						}

					for(k = 0; k < 3; k++)
						if (strncmp(word, polaridade[k], vet_pol[k]) == 0)
							cont = cont2 = 0; 

					word = strtok(NULL, delim);	
				}
				if (valor == 1)                        //   Caso valor saia do while com valor 1, o dividendo � somado em 1.
					dividendo++;
			}
		}
		free(apenas_sentenca);
		return round(100*dividendo/divisor * 10)/10;  //   Como o valor � recebido em porcentagem, e arredondado a primeira casa decimal ap�s a v�rgula,
	}	                                              // a fun��o "round()", exportada da biblioteca "math.h", arredonda o produto da divis�o por 1000.
	if(a_pergunta[linha][1] == 'n')
	{                                                    //   Dada a explica��o para o caso dos positivos, o mesmo ocorre para os negativos.
		float dividendo=0, divisor=0;
		for(i = 0; i < n_sentencas; i++)
		{
			if(strncmp(dispositivo, a_sentenca[i], TAM) == 0)
			{
				int valor = 0;
				divisor++;
					
				for(j = TAM+1; j < 400; j++)
					apenas_sentenca[j - (TAM+1)] = a_sentenca[i][j];
				
				char delim[] = " ";
				char *word = strtok(apenas_sentenca, delim);
				
				cont = 3, cont2 = 0;
				
				while(word != NULL)
				{	
					cont2++;
					for(k = 0; k < 12; k++)
						if (strncmp(word, ruim[k], vet_ruim[k]) == 0)
							valor = 1;

					if (cont == 0)
						for (k = 0; k < 12; k++){
							if (strncmp(word, ruim[k], vet_ruim[k]) == 0 && cont2 <= 3)
								valor = 0;
						}
					if (cont == 0)
						for (k = 0; k < 12; k++){

							if (strncmp(word, bom[k], vet_bom[k]) == 0 && cont2 <= 3)
								valor = 1;
					}

					for(k = 0; k < 3; k++)
						if (strncmp(word, polaridade[k], vet_pol[k]) == 0)
							cont = cont2 = 0; 


					word = strtok(NULL, delim);	
				}
				if (valor == 1)
					dividendo++;
			}
		}
		free(apenas_sentenca);
		return round(100*dividendo/divisor * 10)/10;
	}
	return 0;
}
int main(void)
{
	int i;
	int n_sentencas, n_perguntas;
	char **sentenca, **pergunta;

	scanf("%d %d", &n_sentencas, &n_perguntas); // Entradas iniciais, na primeira linha, que definem o n�mero de senten�as e perguntas.
	
	sentenca = recebe_sentenca(n_sentencas);
	pergunta = recebe_pergunta(n_perguntas);
	
	for(i = 0; i < n_perguntas; i++)          // O FOR funciona at� que todas as perguntas sejam percorridas.
	{
		if (pergunta[i][0] == '1')
		{
			printf("%d\n", out(sentenca, i, n_sentencas, pergunta));       //  Output da pergunta 1.
		}
		if (pergunta[i][0] == '2')
		{
			printf("%.1f%%\n", out2(sentenca, i, n_sentencas, pergunta) ); //  Output da pergunta 2.
		}
	}
	return 0;
}
