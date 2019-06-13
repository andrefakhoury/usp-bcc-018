#include <string.h>                                            //   Observações / Mea culpa: Todos os casos teste propostos pelo run.codes (inclusive o bônus) funcionam normalmente nos compiladores
#include <stdio.h>                                             // que utilizo. Fiquei dezenas de horas depurando o programa, mas não encontrei o porquê de não funcionar no run.codes.
#include <stdlib.h>                                            //   Algumas alterações no código original foram realizadas por conta de o run.codes simplesmente não compilar,
#include <math.h>                                              // ou por conta do ERRO "Falha de segmentação". Espero que não sejam discontados tantos pontos, mas o que vale é o aprendizado.
                                                               //   Gostaria de solicitar, caso o senhor saiba o problema de meu programa, uma explicação detalhada, não quero 
                                                               // que esse problema se repita futuramente.
                                                               //   Como professor, caso o senhor tenha acesso a documentos que expliquem o funcionamento do compilador do run.codes,
                                                               // gostaria de solicitá-los, caso não seja inconveniente. 
                                                               
//protótipo de funções:
void adiciona_nada (char ** matrix, int linhas, int colunas);  // Essa função recebe uma matrix char e preenche-a pelo caractere ' ' .
char ** recebe_sentenca (int n_sentencas);                     // ''  ''  ''  as sentenças digitadas e guarda-a em uma matrix char.
char ** recebe_pergunta(int n_perguntas);					   // ''  ''  ''  as perguntas e retorna uma matrix char contendo informações . 				
int out(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta ); // '' '' trabalha com os dados recebidos para a pergunta "1" .
float out2(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta ); // '' '' trabalha com os dados recebidos para a pergunta "2" .

void adiciona_nada (char ** matrix, int linhas, int colunas)
{
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)      //  A função percorre todas as posições da matriz e preenche-a com o caracter ' '.
			matrix[i][j] = ' ';
	
	return ;
}
char ** recebe_sentenca (int n_sentencas)
{
	int i, j;
	char c, **cc;
	
	if (n_sentencas == 1)                                       //  A matriz é alocada dinamicamente, dadas as "n_sentencas", a matriz "cc" que guardará
	{                                                           //o nome dos dispositivos e as sentenças digitadas, com limite máximo de 400 caracteres.
		cc = (char**) malloc (2 * sizeof(char));                
		for(i = 0; i < 2; i++)                                  //  Após a alocação, a função "adiciona_nada" preenche a matriz pelo caractere ' ', para
			cc[i] = (char*) malloc (400*sizeof(char));          //limpá-la de lixos presentes na memória onde a matriz foi alocada.
		adiciona_nada (cc, 2, 400);                             
	}
	else
	{
		cc = (char**) malloc(n_sentencas * sizeof(char*));      //OBS: O if/else para o caso "n_sentencas == 1" foi definido por conta
		for(i = 0; i < n_sentencas; i++)                        // do run.codes alarmar o ERRO "Falha de segmentação", apesar de o programa
			cc[i] = (char*) malloc (400*sizeof(char));          // funcionar normalmente em outros compiladores.
		adiciona_nada (cc, n_sentencas, 400);                       
	}
	i = 0;
	j = 0;
	setbuf(stdin, NULL);                                        //  O setbuf nesse caso elimina o caracter anteriormente digitado "\n"          
	
	while (scanf("%c", &c)==1)                                  //  Nessa parte, o que é digitado como sentença é gravado na matriz,
	{                                                           //incluindo todos os caracteres digitados, exceto '\n'.
		if (c != '\n')                                          //  Ao reconhecer o caracter '\n', a matriz passa a gravar a sentença
			cc[i][j] = c;                                       //na próxima linha da matriz.
		j++;
		if (c == '\n')
		{
			i++;               
			j = 0;
		}
		if (i == n_sentencas)                                   //  O while se encerra no momento em que a variável 'i' é igual
			break;                                              //ao 'n_sentencas', que é o número máximo de sentenças a ser gravado.      
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
		for(i = 0; i < 2; i++)                                      // a segunda matriz (l) será detalhada a seguir.
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
			c = 'a', j = 1;                                       //   Nesta parte, há uma conversão dos dados recebidos por "pp".
			while (c != ' ')                                      //   Dadas que sempre as perguntas começam com o caractere 'p' ou 'q' 
			{                                                     // e 'p' sempre refere-se à pergunta de número 1, e 'q' sempre se refere
				l[i][j] = pp[i][j + 7];                           // à pergunta de número 2, a matriz "l" recebe essa informação e a guarda sempre
				c = pp[i][j + 8];                                 // na primeira posição de cada uma de suas linhas.
				j++;
			}
			while (pp[i][j+11] != ' ' || pp[i][j+12] != ' ')      //   Após constar '1' na primeira posição da linha, é guardada
			{                                                     // a palavra no qual se quer contar, a partir da segunda posição.
				l[i][j + 1] = pp[i][j+11];                        //   É pulada uma posição, e a em seguida é guardado o nome do dispositivo
				j++;                                              // no qual se pretende procurar a palavra.
			}
		}
		if(pp[i][0] == 'q')
		{
			l[i][0] = '2';
			c = 'a', j = 0;                                        //  Após constar '2' na primeira posição da linha, é guardada na segunda posição
	                                                               // o caractere 'n' para negativos e 'p' para positivos.
			if (pp[i][8] == 'n'){
				while (pp[i][j+20] != ' ' || pp[i][j+21] != ' ')   //  A seguir, é pulada uma posição e é guardado o nome do dispositivo digitado.
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
		for(i = 0; i < 2; i++)                //  Dada que não será mais utilizada, a matriz "pp" é liberada.
			free(pp[i]);
		free(pp);
	}
	return l;                                 //  Todas as informações úteis da pergunta digitada são armazenadas na matriz "l"
}                                             //e retornadas;
int out(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta )
{
	int i, j, cont = 0, TAM = 0, tam = 0;
	char c, dispositivo[30], palavra[21];
	
	for (i = 0; i < 21; i++)              //  São definidos dois vetores de caracteres, que servem como
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
				palavra[j-1] = a_pergunta[linha][j];      //  O vetor "palavra" recebe a palavra no qual será utilizada para comparação,
			c = a_pergunta[linha][j];                     // contida na matriz "a_pergunta", de sua segunda posição até o caractere ' '.
		}
		tam = j-1;                                        //  A variável "tam" representa o número de caracteres contidos em "palavra".
		j++;
		while (a_pergunta[linha][j] != ' ' || a_pergunta[linha][j+1] != ' ')     //   Esse while percorre todas as posições depois do caractere ' '
		{                                                                        // que separa a "palavra" e o nome do dispositivo, na matriz "a_pergunta"
			dispositivo[TAM] = a_pergunta[linha][j];                             // e para quando há dois caracteres ' ' consecutivos.
			j++;
			TAM++;                                                               //   A variável "TAM" representa o número de caracteres presentes 
		}                                                                        // no nome do dispositivo a ser avaliado.

		char *apenas_sentenca;                                                   //   O vetor "apenas_sentenca" guarda, incluindo ';', a sentença,
		apenas_sentenca = (char*) malloc ((400 - (TAM+1))*sizeof(char));	     // sem o nome do dispositivo, como foi guardado na função "recebe_sentenca".
		
		for(i = 0; i < n_sentencas; i++)
		{
			if(strncmp(dispositivo, a_sentenca[i], TAM) == 0)                    //   Caso o nome do dispositivo seja o mesmo presente no início da matriz "a_sentenca" ...
			{
				
				for(j = TAM+1; j < 400; j++)
					apenas_sentenca[j - (TAM+1)] = a_sentenca[i][j];             //   O vetor de caractere "apenas_sentenca" recebe aqui a sentença sem o nome do dispositivo.
				
				char delim[] = " ";
				
				char *word = strtok(apenas_sentenca, delim);                     //   
				
				while (word != NULL)
				{	
		
					if (strncmp(word, palavra, tam) == 0 && word[tam] == 0)      //   O vetor "apenas_sentenca" é "cortado" em strings recebidas por "word" 
						cont++;                                                  // e "palavra" é comparada com cada palavra presente no vetor "apenas_sentenca".
					word = strtok(NULL, delim);                                  //   Há uma contagem cada vez que "palavra" é igual a "word".
				}
			}
		}
		free(apenas_sentenca);          // "apenas_sentenca" foi alocada dinamicamente, portanto é liberta aqui, após não possuir mais utilidade na função.
	}
	return cont;                    //   A função retorna o número de vezes que a palavra perguntada apareceu, dado o nome do dispositivo.
}
float out2(char **a_sentenca, int linha, int n_sentencas, char **a_pergunta )
{
	int i, j, k, TAM = 0, cont=0, cont2;
	char dispositivo[30];
	
	for (i = 0; i < 21; i++)
		dispositivo[i] = ' ';
	
	char polaridade[3][7] = {"nao", "jamais", "nunca"};
	int vet_pol[3] = {3, 6, 5};
	
	char ruim[12][9] = {"detestei", "odiei"  , "ruim" , "pessimo", "terrivel", "raiva",                        //   São abaixo definidas as strings que representam "positivos" ou "negativos.
	                    "odio"    , "pessima", "lento", "lenta"  , "fragil"  , "desisti"};                     //   São também definidos os tamanhos dessas strings, e guardados em um vetor inteiro.
	int vet_ruim[12] = {8, 5, 4, 7, 8, 5, 4, 7, 5, 5, 6, 7};
	
	char bom[12][12] = {"bom"   , "maravilhoso", "otimo"    , "sensacional", "excelente"  , "adorei",	
                        "gostei", "amei"       , "eficiente", "boa"        , "maravilhosa", "otima"};
	int vet_bom[12]  = {3, 11, 5, 11, 9, 6, 6, 4, 9, 3, 11, 5};
		
	j = 3;
	while (a_pergunta[linha][j] != ' ' || a_pergunta[linha][j+1] != ' ')
	{
		dispositivo[j-3] = a_pergunta[linha][j];                                   //   O nome do dispositivo é guardado na string "dispositivo", e seu tamanho, na variável "TAM".
		j++;
		TAM++; 
	}

	char *apenas_sentenca;                                                         //   O vetor "apenas_sentenca" guarda, incluindo ';', a sentença,
	apenas_sentenca = (char*) malloc ((400 - (TAM+1))*sizeof(char));               // sem o nome do dispositivo, como foi guardada na função "recebe_sentenca".
		
	if(a_pergunta[linha][1] == 'p')             //   Este é o caso para as intenções positivas para as sentenças.
	{
		float dividendo=0, divisor=0;
		for(i = 0; i < n_sentencas; i++)
		{
			if(strncmp(dispositivo, a_sentenca[i], TAM) == 0)                      //   Este IF compara o nome do dispositivo e o nome presente na matriz "a_sentenca".
			{
				int valor = 0;
				divisor++;
					
				for(j = TAM+1; j < 400; j++)                                       //   Nesta parte é guardada apenas a sentença, excluindo o nome do dispositivo. 
					apenas_sentenca[j - (TAM+1)] = a_sentenca[i][j];               
				
				char delim[] = " ";
				char *word = strtok(apenas_sentenca, delim);
					
				cont = 3, cont2 = 0;
				
				while(word != NULL)
				{
					cont2++;
					for(k = 0; k < 12; k++)                                        //   O vetor "apenas_sentenca" é "quebrado" em palavras recebidas pelo vetor "word".
						if (strncmp(word, bom[k], vet_bom[k]) == 0 )               //   Caso "word" seja igual a uma das palavras definidas no vetor "vet_bom",
							valor = 1;                                             // a variável "valor" recebe 1.

					if (cont == 0)
						for (k = 0; k < 12; k++){
							if (strncmp(word, bom[k], vet_bom[k]) == 0 && cont2 <= 3)   //   Foram definidas duas variáveis inteiras, cont e cont2.
								valor = 0;                                              //   "cont" torna-se igual a 0 quando "word" é uma das palavras que invertem 
					}                                                                   //  a polaridade da sentença.
					if (cont == 0)
						for (k = 0; k < 12; k++){
                                                                                         //   Enquanto isso, "cont2" é em 1 cada vez que a palavra muda.
							if (strncmp(word, ruim[k], vet_ruim[k]) == 0 && cont2 <= 3)  // e a polaridade só inverte quando "cont2" é menor ou igual a 3 e
								valor = 1;                                               // quando "word" é igual a uma palavra, da matriz "ruim" ou "bom".
						}

					for(k = 0; k < 3; k++)
						if (strncmp(word, polaridade[k], vet_pol[k]) == 0)
							cont = cont2 = 0; 

					word = strtok(NULL, delim);	
				}
				if (valor == 1)                        //   Caso valor saia do while com valor 1, o dividendo é somado em 1.
					dividendo++;
			}
		}
		free(apenas_sentenca);
		return round(100*dividendo/divisor * 10)/10;  //   Como o valor é recebido em porcentagem, e arredondado a primeira casa decimal após a vírgula,
	}	                                              // a função "round()", exportada da biblioteca "math.h", arredonda o produto da divisão por 1000.
	if(a_pergunta[linha][1] == 'n')
	{                                                    //   Dada a explicação para o caso dos positivos, o mesmo ocorre para os negativos.
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

	scanf("%d %d", &n_sentencas, &n_perguntas); // Entradas iniciais, na primeira linha, que definem o número de sentenças e perguntas.
	
	sentenca = recebe_sentenca(n_sentencas);
	pergunta = recebe_pergunta(n_perguntas);
	
	for(i = 0; i < n_perguntas; i++)          // O FOR funciona até que todas as perguntas sejam percorridas.
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
