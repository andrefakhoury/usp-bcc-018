#include <stdio.h>
#include <stdlib.h>
#include <string.h>   

int main(){
	
	//contador_positivo e contador_negativo se referem as palavras boas e ruins de cada descricao
	//contador_positivo2 e contador_negativo2 se referem as proprias descricoes
	//contador_total se refere ao total de palavras em cada descricao
	int numero_coment, numero_perg,contador_palavras=0,contador_positivo2=0, contador_negativo2=0;
	float porcentagem=0.0;
	int *contador_total=NULL, *contador_positivo=NULL, *contador_negativo=NULL;
	char** lista_de_produtos = NULL;
	char*** lista_de_descricoes = NULL;
	char*** lista_de_perguntas = NULL;

	//aloca os contadores de palavras totais, positivas e negativas e define todos como 0
	contador_total = calloc(50, sizeof(int));
	contador_negativo = calloc(50, sizeof(int));
	contador_positivo = calloc(50, sizeof(int));

	//le a quantidade de comentarios
	scanf("%d %d", &numero_coment, &numero_perg);

	//aloca a lista de produtos e descricoes
	lista_de_descricoes = realloc(lista_de_descricoes, numero_coment*sizeof(char**));
	lista_de_produtos = realloc(lista_de_produtos, numero_coment*sizeof(char*));

	//para cada comentario, aloca um array de char para os produtos e uma lista de array de char para ler 
	//as palavras da descricao separadamente
	for (int i = 0; i < numero_coment; i++)
	{
		lista_de_produtos[i] = realloc(lista_de_produtos[i], 40*sizeof(char));
		scanf(" %[^;];", lista_de_produtos[i]);
		lista_de_descricoes[i] = realloc(lista_de_descricoes[i], 40*sizeof(char*));

		//aloca e le um array de char para cada palavra do comentario depois do ';'e antes do 'Ø'
		for (int j = 0; j < 20; j++)
		{
			lista_de_descricoes[i][j] = realloc(lista_de_descricoes[i][j], 20*sizeof(char));
			scanf(" %s", lista_de_descricoes[i][j]);
			//interrompe quando ler o caractere especial
			if (strcmp(lista_de_descricoes[i][j], "Ø") == 0)
			{
				break;
			}
			//alocando array de polaridade
			char *positivas[12], *negativas[12];
			//array de palavras positivas
			positivas[0] = "bom";
			positivas[1] = "maravilhoso";
			positivas[2] = "otimo";
			positivas[3] = "sensacional";
			positivas[4] = "excelente";
			positivas[5] = "adorei";
			positivas[6] = "gostei";
			positivas[7] = "amei";
			positivas[8] = "eficiente";
			positivas[9] = "boa";
			positivas[10] = "maravilhosa";
			positivas[11] = "otima";
			//array de palavras negativas
			negativas[0] = "detestei";
			negativas[1] = "odiei";
			negativas[2] = "ruim";
			negativas[3] = "pessimo";
			negativas[4] = "terrivel";
			negativas[5] = "raiva";
			negativas[6] = "odio";
			negativas[7] = "pessima";
			negativas[8] = "lento";
			negativas[9] = "lenta";
			negativas[10] = "fragil";
			negativas[11] = "desisti";
			//conta as palavras positivas em um comentario considerando os inversores de opiniao
			//considera caso o inversor esteja 1, 2 ou 3 palavras atras
			for (int k = 0; k < 12; k++)
			{
				if (strcmp(lista_de_descricoes[i][j], positivas[k]) == 0)
				{
					_Bool flag=1;
					if (j==0)
					{
						contador_positivo[i]++;
						flag = 0;		
					}
					else if(j==1)
					{
						if(strcmp(lista_de_descricoes[i][j-1], "nao")==0 || strcmp(lista_de_descricoes[i][j-1], "nunca")==0 || strcmp(lista_de_descricoes[i][j-1], "jamais")==0)
						{	
							contador_negativo[i]++;
							flag = 0;
						}
						else
						{
							contador_positivo[i]++;
							flag = 0;
						}
					}
					else if(j==2)
					{
						if(strcmp(lista_de_descricoes[i][j-2], "nao")==0 || strcmp(lista_de_descricoes[i][j-2], "nunca")==0 || strcmp(lista_de_descricoes[i][j-2], "jamais")==0)								
						{
							contador_negativo[i]++;
							flag = 0;
						}
						else if (strcmp(lista_de_descricoes[i][j-1], "nao")==0 || strcmp(lista_de_descricoes[i][j-1], "nunca")==0 || strcmp(lista_de_descricoes[i][j-1], "jamais")==0)
						{
							contador_negativo[i]++;
							flag = 0;
						}
						else
						{
							contador_positivo[i]++;
							flag = 0;
						}
					}
					else
					{
						if (strcmp(lista_de_descricoes[i][j-3], "nao")==0 || strcmp(lista_de_descricoes[i][j-3], "nunca")==0 || strcmp(lista_de_descricoes[i][j-3], "jamais")==0)
						{
							contador_negativo[i]++;
							flag = 0;
						}
						else if(strcmp(lista_de_descricoes[i][j-2], "nao")==0 || strcmp(lista_de_descricoes[i][j-2], "nunca")==0 || strcmp(lista_de_descricoes[i][j-2], "jamais")==0)								
						{
							contador_negativo[i]++;
							flag = 0;
						}
						else if (strcmp(lista_de_descricoes[i][j-1], "nao")==0 || strcmp(lista_de_descricoes[i][j-1], "nunca")==0 || strcmp(lista_de_descricoes[i][j-1], "jamais")==0)
						{
							contador_negativo[i]++;
							flag = 0;
						}
						else
						{
							contador_positivo[i]++;
							flag = 0;
						}
					}
					if (flag)
					{
						contador_positivo++;
					}
				}
			}
			//conta as palavras negativas em um comentario considerando os inversores de opiniao
			//da mesma maneira que o caso acima
			for (int k = 0; k < 12; k++)
			{
				if (strcmp(lista_de_descricoes[i][j], negativas[k]) == 0)
				{
					_Bool flag=1;
					if (j==0)
					{
						contador_negativo[i]++;
						flag = 0;		
					}
					else if(j==1)
					{
						if(strcmp(lista_de_descricoes[i][j-1], "nao")==0 || strcmp(lista_de_descricoes[i][j-1], "nunca")==0 || strcmp(lista_de_descricoes[i][j-1], "jamais")==0)
						{	
							contador_positivo[i]++;
							flag = 0;
						}
						else
						{
							contador_negativo[i]++;
							flag = 0;
						}
					}
					else if(j==2)
					{
						if(strcmp(lista_de_descricoes[i][j-2], "nao")==0 || strcmp(lista_de_descricoes[i][j-2], "nunca")==0 || strcmp(lista_de_descricoes[i][j-2], "jamais")==0)								
						{
							contador_positivo[i]++;
							flag = 0;
						}
						else if (strcmp(lista_de_descricoes[i][j-1], "nao")==0 || strcmp(lista_de_descricoes[i][j-1], "nunca")==0 || strcmp(lista_de_descricoes[i][j-1], "jamais")==0)
						{
							contador_positivo[i]++;
							flag = 0;
						}
						else
						{
							contador_negativo[i]++;
							flag = 0;
						}
					}
					else
					{
						if (strcmp(lista_de_descricoes[i][j-3], "nao")==0 || strcmp(lista_de_descricoes[i][j-3], "nunca")==0 || strcmp(lista_de_descricoes[i][j-3], "jamais")==0)
						{
							contador_positivo[i]++;
							flag = 0;
						}
						else if(strcmp(lista_de_descricoes[i][j-2], "nao")==0 || strcmp(lista_de_descricoes[i][j-2], "nunca")==0 || strcmp(lista_de_descricoes[i][j-2], "jamais")==0)								
						{
							contador_positivo[i]++;
							flag = 0;
						}
						else if (strcmp(lista_de_descricoes[i][j-1], "nao")==0 || strcmp(lista_de_descricoes[i][j-1], "nunca")==0 || strcmp(lista_de_descricoes[i][j-1], "jamais")==0)
						{
							contador_positivo[i]++;
							flag = 0;
						}
						else
						{
							contador_negativo[i]++;
							flag = 0;
						}
					}
					if (flag)
					{
						contador_negativo++;
					}
				}	
			}
			//conta o total de palavras
			contador_total[i]++;
		}
	}

	//aloca a lista de perguntas
	lista_de_perguntas = realloc(lista_de_perguntas, numero_perg*sizeof(char**));
	//aloca e le as palavras das perguntas
	for (int i = 0; i < numero_perg; ++i)
	{
		lista_de_perguntas[i] = realloc(lista_de_perguntas[i], 20*sizeof(char*));
		//aloca 20 sizeofchar para as 3 primeiras palavras e 40 para os produtos, 
		//pois possuem 2 palavras
		for (int j = 0; j < 3; j++)
		{
			lista_de_perguntas[i][j] = realloc(lista_de_perguntas[i][j], 20*sizeof(char));
		}
		lista_de_perguntas[i][3] = realloc(lista_de_perguntas[i][3], 40*sizeof(char));
		char aux[20];
		scanf(" %s", lista_de_perguntas[i][0]);
		//PERGUNTA TIPO 1
		if (strcmp(lista_de_perguntas[i][0],"palavra")==0)
		{
			//le o restante da pergunta	
			scanf(" %s", lista_de_perguntas[i][1]);
			scanf(" %s", lista_de_perguntas[i][2]);
			//caso especifi coque concatena as duas strings lidas com um espaco entre elas
			scanf(" %s %s", lista_de_perguntas[i][3],aux);
			strcat(lista_de_perguntas[i][3]," ");
			strcat(lista_de_perguntas[i][3],aux);
			strcat(lista_de_perguntas[i][3]," ");

			for (int j = 0; j < numero_coment; j++)
			{
				//compara o final da pergunta com a lista de produtos
				if (strcmp(lista_de_perguntas[i][3], lista_de_produtos[j])==0)
				{
					for (int k = 0; k < contador_total[j]; k++)
					{
						if (strcmp(lista_de_perguntas[i][1], lista_de_descricoes[j][k])==0)
						{
							contador_palavras++;
						}
					}
				}
			}
			printf("%d\n", contador_palavras);
			contador_palavras=0;
		}
		//PERGUNTA TIPO 2
		if (strcmp(lista_de_perguntas[i][0], "quantos")==0)
		{
			//le o restante da pergunta	
			scanf(" %s", lista_de_perguntas[i][1]);
			scanf(" %s", lista_de_perguntas[i][2]);
			//caso especifico que concatena as duas strings lidas com um espaco entre elas
			scanf(" %s %s", lista_de_perguntas[i][3],aux);
			strcat(lista_de_perguntas[i][3]," ");
			strcat(lista_de_perguntas[i][3],aux);
			strcat(lista_de_perguntas[i][3]," ");

			for (int j = 0; j < numero_coment; j++)
			{
				//compara o final da pergunta com a lista de produtos
				if (strcmp(lista_de_perguntas[i][3], lista_de_produtos[j])==0)
				{
					if (contador_positivo[j]>contador_negativo[j])
					{
						contador_positivo2++;
					}
					if (contador_negativo[j]>contador_positivo[j])
					{
						contador_negativo2++;
					}					
				}
			}
			//define a porcentagem de positivos
			if(strcmp(lista_de_perguntas[i][1], "positivos")==0)
			{
				porcentagem = (float)contador_positivo2 /(float)(contador_negativo2+contador_positivo2);
			}
			//define a porcentagem de negativos
			if(strcmp(lista_de_perguntas[i][1], "negativos")==0)
			{
				porcentagem = (float)contador_negativo2 /(float)(contador_negativo2+contador_positivo2);
			}
			printf("%.1f%%\n", porcentagem*100);
			//limpa os contadores e a porcentagem
			porcentagem=0;
			contador_negativo2=0;
			contador_positivo2=0;
		}
	}

	//FREE
	//reallocando para 0 bytes

	contador_total = realloc(contador_total, 0*sizeof(int));
	contador_negativo = realloc(contador_negativo, 0*sizeof(int));
	contador_positivo = realloc(contador_positivo, 0*sizeof(int));

	for (int i = 0; i < numero_coment; i++)
	{
		for (int j = 0; j < 20; ++j)
		{
			lista_de_descricoes[i][j] = realloc(lista_de_descricoes[i][j], 0*sizeof(char));
		}

		lista_de_produtos[i] = realloc(lista_de_produtos[i], 0*sizeof(char));
		lista_de_descricoes[i] = realloc(lista_de_descricoes[i], 0*sizeof(char*));
	}

	lista_de_descricoes = realloc(lista_de_descricoes, 0*sizeof(char**));
	lista_de_produtos = realloc(lista_de_produtos, 0*sizeof(char*));


	for (int i = 0; i < numero_perg; ++i)
	{
			lista_de_perguntas[i][0] = realloc(lista_de_perguntas[i][0], 0*sizeof(char));
		lista_de_perguntas[i][1] = realloc(lista_de_perguntas[i][1], 0*sizeof(char));
		lista_de_perguntas[i][2] = realloc(lista_de_perguntas[i][2], 0*sizeof(char));
		lista_de_perguntas[i][3] = realloc(lista_de_perguntas[i][3], 0*sizeof(char));

		lista_de_perguntas[i] = realloc(lista_de_perguntas[i], 0*sizeof(char*));
	}

	lista_de_perguntas = realloc(lista_de_perguntas, 0*sizeof(char**));

	return 0;
}