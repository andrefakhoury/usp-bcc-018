#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int verifica_positivo(char *numero_verificado)
{   char *positivos[12]={"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	int count = 0;
	for (count=0;count < 12;count++)//compara a palavra de entrada com cada uma das palavras positivas
	{
		if (strcmp(numero_verificado,positivos[count]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int verifica_negativo(char *numero_verificado)
{   char  *negativo[12]={"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	int count = 0;
	for (count=0;count < 12;count++)// idem ao verifica_positivo
	{
		if (strcmp(numero_verificado,negativo[count])==0)
		{
			return 1;
		}
	}
	return 0;
}

int polaridade(char* entrada, int polar_atual){
	char *polaroide[3] = {"nao","nunca","jamais"};
	for(int count = 0;count<3; count++){
		if(strcmp(entrada,polaroide[count]) == 0){
			return 4;//palavra atual + 3 palavras
		}
	}
	if(polar_atual >= 0)
		return polar_atual;
	else
		return 0;
}

int main(void) {
	int numero_de_sentencas, numero_de_perguntas;
	char *textos[200];
	char *o_que_pergunta;
	char *marcas[100];
	char *marcas_das_perguntas;
	char *tipo_de_pergunta;
	char *em;
	char palavras_do_texto[200];
	int i,j,k,quantidade=0,tamanho, posicao=0,perguntas_da_marca=0,aux,achou = 0,polar;
	float resultado;
	scanf ("%d %d", &numero_de_sentencas, &numero_de_perguntas);
	for (i=0;i<numero_de_sentencas;i++)
	{
		scanf(" %m[^;];", &marcas[i]); // [^<algo>]le a string ate achar <algo>
		tamanho = strlen(marcas[i]);
		marcas[i][tamanho-1] = '\0';
		scanf(" %m[^Ø]Ø", &textos[i]);
	}
	for (i = 0; i < numero_de_perguntas; i++) // procura o tipo de pergunta de acordo com o numero_de_perguntas da entrada
	{
		scanf(" %ms ", &tipo_de_pergunta);
		scanf(" %ms ", &o_que_pergunta);
		scanf(" %ms ", &em);
		scanf(" %m[^\r\n]", &marcas_das_perguntas);
		quantidade = 0;
		polar = 0;
		if (strcmp(tipo_de_pergunta, "quantos") == 0)
		{
			for (j=0; j < numero_de_sentencas; j++) // procura as sentencas cuja marca eh pedida na pergunta
			{
				tamanho=strlen(marcas[j]);
				//marcas[j][tamanho-1]='\0';
				if (strcmp(marcas[j], marcas_das_perguntas) == 0)
				{        
					perguntas_da_marca++;
					int contador_local=0;
					achou = 0;
					polar = 0;
					for (k=0; k <  strlen(textos[j]) && achou==0;k++)// fragmenta os textos em palavras
					{
						if (textos[j][k] != ' ')
						{
							palavras_do_texto[contador_local++] = textos[j][k];
						}
						else
						{
							palavras_do_texto[contador_local] = '\0';
							contador_local = 0;
							polar --;
							polar = polaridade(palavras_do_texto,polar);

							//checa se a marca eh positivas ou negativas e se for, chama a funcao. Senao, verifica se a palavra é a palavra perguntada
							if (strcmp(o_que_pergunta,"positivos") == 0)
							{
								aux = quantidade;
								if (!polar && verifica_positivo(palavras_do_texto) == 1)
								{
									quantidade = quantidade +1;
									achou++;
								}else if(polar && verifica_negativo(palavras_do_texto)){
									quantidade = quantidade + 1;
									achou++;
								}
								if (achou>1)
								{
									quantidade = aux;
								}
							}
							else if (strcmp(o_que_pergunta,"negativos") == 0)
							{
								aux = quantidade;
								if (!polar && (verifica_negativo(palavras_do_texto) == 1))
								{
									quantidade = quantidade + 1;
									achou++;
								}else if (polar && verifica_positivo(palavras_do_texto)){
									quantidade = quantidade + 1;
									achou++;
								}
								if (achou>1)// verifica se nao foram encontradas duas palavras dentro de um mesmo texto
								{
									quantidade = aux;
								}
							}
							else if (strcmp(palavras_do_texto,o_que_pergunta) == 0)
							{
								quantidade ++;
							}
						}
					}
				}
			}
			if (perguntas_da_marca == 0)
			{
				perguntas_da_marca=1;
			}
			resultado = (100.0*quantidade)/(perguntas_da_marca);
			printf ("%.1f%%\n", resultado);
			perguntas_da_marca=0;
		}
		else if (strcmp(tipo_de_pergunta, "palavra") == 0)
		{
			for (j=0; j < numero_de_sentencas; j++)
			{
				tamanho=strlen(marcas_das_perguntas);
				//marcas[j][tamanho]='\0';
				if (strcmp(marcas[j], marcas_das_perguntas) == 0)
				{
					for (k=0; k <  strlen(textos[j]);k++)
					{
						if (textos[j][k] != ' ')
						{
							palavras_do_texto[posicao] = textos[j][k];
							posicao++;
						}
						else
						{
							palavras_do_texto[posicao] = '\0';
							posicao=0;
							if (strcmp(palavras_do_texto,o_que_pergunta) == 0)
							{
								quantidade ++;
							}
						}
					}
				}
			}
			printf ("%d\n",quantidade);
		}
		free(tipo_de_pergunta);
		free(o_que_pergunta);
		free(em);
		free(marcas_das_perguntas);
	}
	for (i=0;i<numero_de_sentencas;i++)
	{
		free (marcas[i]);
		free(textos[i]);
	}
	return 0;
}
