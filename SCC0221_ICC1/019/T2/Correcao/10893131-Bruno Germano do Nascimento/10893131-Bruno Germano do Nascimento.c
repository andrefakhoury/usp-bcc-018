#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 28

int lerPalavra(char* vetor)
{
	// Le uma palavra, armazena em vetor e retorna 0 se é o indicador de parada
	scanf("%s", vetor);

	if(strcmp(vetor, "Ø") == 0)
	{
		return 0;
	}
	return 1;
}

int procurarPalavra(char* procurado, char** vetor, int tamanho, int inicio)
{
	// Procura uma palavra num vetor de strings e retorna a posição dela, ou o tamanho, caso não exista
	if(inicio < tamanho)
	{
		for(int i = inicio; i < tamanho; i++)
		{
			// Checa se já existe a palavra procurada no vetor
			if(strcmp(procurado, vetor[i]) == 0)
			{
				
				return i;
			}
		}
	}
	// Não encontrada a palavra, retorna tamanho
	return tamanho;
}

void zerarString(char* array, int size)
{
	// Setta um array de tamanho size com espaços em todas as posições
	for(int i = 0; i < size; i++)
	{
		array[i] = ' ';
	}
}

void copiarSemEspaco(char* vetor, char* copiado)
{
	// Função para copiar copiado em vetor, mas sem o último caractere
	for(int i = 0; i < strlen(copiado) - 1; i++)
	{
		vetor[i] = copiado[i];
	}
}

int lerPergunta(char* procurado, char* produto)
{
	// Lê a pergunta, retorna 1 para "palavra", 2 para "quantos"
	// Retorna a palavra a ser procurada em procurado e o produto para procurar em produto
	
	char buffer[20];
	int valor;
	
	lerPalavra(buffer);
	if(strcmp(buffer, "quantos"))
 	{
 		
 		// Para uma pergunta de 'palavra', setta valor como 1
 		valor = 1;
 	}else 
 	{
 		
 		// Para uma pergunta de 'quantos', setta valor como 2
 		valor = 2;
 	}
 	zerarString(buffer, 20);

	// Lê a palavra procurada, guarda em procurado e zera o buffer	
	lerPalavra(buffer);
	strcpy(procurado, buffer);
	zerarString(buffer, 20);
	
	// Ignora "em"
	lerPalavra(buffer);
	zerarString(buffer, 20);

	// Lê o produto procurado
	lerPalavra(produto);

	// Lê a marca procurada
	lerPalavra(buffer);

	// Concatena produto e marcaProcurada
	strcat(produto, " ");
	strcat(produto, buffer);

	return valor;
}

void settarConstanteEmMatriz(int constante, int linhas, int colunas, int matriz[linhas][colunas])
{
	// Setta matriz com o valor de constante
	for(int i = 0; i < linhas; i++)
	{
		for(int j = 0; j < colunas; j++)
		{
			matriz[i][j] = constante;
		}
	}
}

int main(int argc, char const *argv[])
{
	// Declaração de variaveis
		int  sentencas, perguntas;
		// Quantidade de palavras encontradas ate então
		int qtdPalavras = 0;
		// BoW, linhas - sentencas, colunas - palavras
		int  bagOfWords[MAX_SIZE][200] = {};
		// Vetor buffer de cada palavra
		char bufferPalavra[20];
		// Vetor buffer de produto, para armazenar produto e marca
		char bufferProduto[41];
		// Variavel de retorno pro programa
		int  palavrasEncontradas;
		// Variavel para posição dos vetores a serem procurados
		int  posProcurada;
		// vetor com a marca a ser procurada pelas perguntas
		char marcaProcurada[20];
		// Vetor com as indices das palavras dos comentarios
		int comentarios[MAX_SIZE][20] = {};
		// Contador para as palavras inversoras
		int contadorInversor;
		// Variavel para controle de quantidade de leituras das sentencas
		int parada;
		// Variavel para controle de palavras validas na pergunta de "quantos"
		int palavraValida;
		// Variaveis para armazenar as quantidades de sentencas validas e totais para as perguntas
		float qtdValidas, qtdTotal;
		// Variaveis auxiliares
		int i, n, x;

		// Vetores de palavras nao definidas (const char*)
			// Vetor ordenado com as palavras encontradas
			char* palavras[200];
			// Vetor com o produto de cada comentario
			char* produto[MAX_SIZE];

		// Vetores com as palavras pre-definidas (const char* = {...})
			// Vetor de strings de comentarios positivo
			char* positivo[12];
				  positivo[0]  = "bom";
				  positivo[1]  = "maravilhoso";
				  positivo[2]  = "otimo";
				  positivo[3]  = "sensacional";
				  positivo[4]  = "excelente";
				  positivo[5]  = "adorei";
				  positivo[6]  = "gostei";
				  positivo[7]  = "amei";
				  positivo[8]  = "eficiente";
				  positivo[9]  = "boa";
				  positivo[10] = "maravilhosa";
				  positivo[11] = "otima";

			// Vetor de strings de comentarios negativo
			char* negativo[12];
				  negativo[0]  =  "detestei";
				  negativo[1]  =  "odiei";
				  negativo[2]  =  "ruim";
				  negativo[3]  =  "pessimo";
				  negativo[4]  =  "terrivel";
				  negativo[5]  =  "raiva";
				  negativo[6]  =  "odio";
				  negativo[7]  =  "pessima";
				  negativo[8]  =  "lento";
				  negativo[9]  =  "lenta";
				  negativo[10] =  "fragil";
				  negativo[11] =  "desisti";

			// Vetor de strings de inversores
			char* inversores[3];
				  inversores[0] = "nao";
				  inversores[1] = "jamais";
				  inversores[2] = "nunca";
			
	// Programa começa de fato aqui

	scanf("%d %d", &sentencas, &perguntas);

	zerarString(bufferPalavra, 20);

	// Setta a matriz de comentarios com todas as posicoes '-1'
	settarConstanteEmMatriz(-1, sentencas, 20, comentarios);

	for(i = 0; i < sentencas; i++)
	{
		/* 
			Laco para ler as sentencas e guardar as informacoes importantes, como:
				- Produto referente a cada sentença
				- Ordem e quantidade das palavras para cada comentario
		*/ 
		
		// N sera usado como o numero da palavra que estamos na frase
		n = 0;
		
		// Ler produto
		scanf(" %[^;]", bufferProduto);

		// Aloca dinamicamente o vetor produto[i] para receber o nome do produto lido
		produto[i] = realloc(produto[i], (strlen(bufferProduto) * sizeof(char)) - 1);
		copiarSemEspaco(produto[i], bufferProduto);
		
		// Pula o ';'
		scanf("%s", bufferPalavra);

		// Ler a primeira palavra, guardar no vetor de palavras
		// Settar parada como o retorno da leitura, para comparacao com 'Ø'
		parada = lerPalavra(bufferPalavra);
			
		// Procura uma posicao para colocar a primeira palavra
		posProcurada = procurarPalavra(bufferPalavra, palavras, qtdPalavras, 0);
		
		// Coloca a primeira posição na matriz de comentários
		comentarios[i][0] = posProcurada;
		n++;

		if(posProcurada != qtdPalavras)
		{
			// Palavra antiga, aumenta o bag of words e zera buffer
			bagOfWords[i][posProcurada]++;
			zerarString(bufferPalavra, 20);
		}else
		{
			// Nova palavra, realoca o vetor de palavras para armazenar essa palavra
			palavras[qtdPalavras] = realloc(palavras[qtdPalavras], strlen(bufferPalavra) * sizeof(char));
			strcpy(palavras[qtdPalavras], bufferPalavra);
			zerarString(bufferPalavra, 20);
			// Aumenta o bag of words e aumenta quantidade de palavras totais
			bagOfWords[i][qtdPalavras]++;
			qtdPalavras++;
		}

		
		while(parada) 
		{
			// Laco para ler palavras até encontrar o simbolo de parada

			parada = lerPalavra(bufferPalavra);
			
			
			if(parada != 0)
			{
				// Setta posicao de procura das palavras nas ja existentes e atualiza a ordem das palavras na matriz comentarios

				posProcurada = procurarPalavra(bufferPalavra, palavras, qtdPalavras, 0);
				
				comentarios[i][n] = posProcurada;
				n++;
				if(posProcurada != qtdPalavras)
				{
					// Palavra antiga, aumenta bag of words e zera string
					bagOfWords[i][posProcurada]++;
					zerarString(bufferPalavra, 20);
				}else
				{
					// Palavra nova, realoca memoria, coloca palavra no vetor de palavras 
					palavras[posProcurada] = realloc(palavras[posProcurada], strlen(bufferPalavra) * sizeof(char));
					strcpy(palavras[posProcurada], bufferPalavra);
					zerarString(bufferPalavra, 20);
					// Aumenta o bag of words e a quantidade total de palavras
					bagOfWords[i][qtdPalavras]++;
					qtdPalavras++;
				}
			}
		}
	}
	
	for(i = 0; i < perguntas; i++)
	{
		// Laco para leitura e execucao das perguntas
		
		qtdValidas = 0;
		palavraValida = 0;
		qtdTotal = 0;

		// Lê "palavra" ou "quantos", o tipo da pergunta, com o valor, entra no case adequado

	 	switch(lerPergunta(bufferPalavra, bufferProduto))
	 	{
	 		case 1: 
	 			// Procurar palavra indicada no produto pedido

	 			palavrasEncontradas = 0;
	 			
	 			// Setta n como o indice da sentenca referente ao primeiro produto procurado
				n = procurarPalavra(bufferProduto, produto, sentencas, 0);
				// Setta posProcurada como a primeira ocorrencia da palavra procurada no vetor palavras
				posProcurada = procurarPalavra(bufferPalavra, palavras, qtdPalavras, 0);
				

				if((n < sentencas) && (posProcurada < qtdPalavras))
				{
					// Se encontrados produto e palavra, aumenta Encontradas com o valor no bag of words
					palavrasEncontradas += bagOfWords[n][posProcurada];
				}

				while((n < sentencas) && (posProcurada < qtdPalavras))
				{
					// Setta n como o proximo indice referente ao produto procurado
					n = procurarPalavra(bufferProduto, produto, sentencas, n + 1);
					if(n != sentencas)
					{
				 		palavrasEncontradas += bagOfWords[n][posProcurada];						
					}					
				}
				// Print da informação pedida, zeradas as strings usadas para próximo uso
				printf("%d\n", palavrasEncontradas);
				zerarString(marcaProcurada, 20);
				zerarString(bufferProduto, 41);
	 		break;

	 		case 2:
	 			// Classificar frases como negativas ou positivas, e mostrar o resultado

	 			// Setta n como o index do produto procurado
				n = procurarPalavra(bufferProduto, produto, sentencas, 0);

	 			if(strcmp(bufferPalavra, "negativos") == 0)
	 			{
	 				// Laco para classificar sentencas como negativas
					while(n < sentencas)
					{
						palavraValida = 0;
						// Settado como 5 para passar automaticamente pelo laco verificador
						contadorInversor = 5;
						for(int k = 0; k < 20; k++)
						{
							// x é a posicao da palavra procurada no vetor de palavras
							x = comentarios[n][k];
							if(x != -1)
							{
								if(contadorInversor >= 4)
								{
									// Se o contador ultrapassar a terceira posição, loop normal de verificacao de palavras
									if(procurarPalavra(palavras[x], inversores, 3, 0) != 3)
									{
										// Se a palavra encontrada e um inversor, o contador zera
										contadorInversor = 0;
									}else if(procurarPalavra(palavras[x], negativo, 12, 0) != 12)
									{
										// Se a palavra for negativa, setta palavra valida para passar no loop
										palavraValida = 1;
									}
								}else if(procurarPalavra(palavras[comentarios[n][k]], positivo, 12, 0) != 12)
								{
									// Se a palavra for positiva depois de um inversor, setta palavra valida
									palavraValida = 1;
								}
							}
							// Acrescenta contador para o inversor
							contadorInversor++;
						}
						if(palavraValida == 1)
						{
							// Caso a sentenca seja valida, aumenta quantidade de validas
							qtdValidas++;
						}
						// Aumenta quantidade total de sentencas vistas e prepara para a proxima
						qtdTotal++;
						n = procurarPalavra(bufferProduto, produto, sentencas, n + 1);
						
					}

	 			}else
	 			{
	 				// Laco para classificar positivas
	 				while(n < sentencas)
					{
						// Laco igual ao anterior, porem espelhado com positivos e negativos
						palavraValida = 0;
						contadorInversor = 5;
						for(int k = 0; k < 20; k++)
						{
							x = comentarios[n][k];
							if(x != -1)
							{
								if(contadorInversor >= 4)
								{
									if(procurarPalavra(palavras[x], inversores, 3, 0) != 3)
									{
										contadorInversor = 0;
									}else if(procurarPalavra(palavras[comentarios[n][k]], positivo, 12, 0) != 12)
									{
										palavraValida = 1;
									}
								}else if(procurarPalavra(palavras[x], negativo, 12, 0) != 12)
								{
									palavraValida = 1;
								}
							}
							contadorInversor++;
						}
						if(palavraValida == 1)
						{
							qtdValidas++;
						}
						qtdTotal++;
						n = procurarPalavra(bufferProduto, produto, sentencas, n + 1);
					}
	 			}
				// Printa a porcentagem de validas/total
	 			printf("%.1f%%\n", qtdValidas/qtdTotal*100);
	 		break;
	 	}
	}
	// Liberação de memória alocada
		for(int i = 0; i < MAX_SIZE; i++)
		{
			free(produto[i]);
		}
		for(int i = 0; i < 200; i++)
		{
			free(palavras[i]);
		}
	return 0;
}