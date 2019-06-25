#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//este struct armazena os produtos(sem repetição) e suas respectivas sentenças
typedef struct
{
	char produtos[20][50]; // Produtos / Caracteres
	char sentencas[20][20][400]; // Produto Correspondente / Sentença / Caracteres
}bag;

int main()
{   
	bag bolsa;
	//armazenamento das palavras positivas e negativas
	char positivo[12][12] = {"bom","maravilhoso","otimo","sensacional", "excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};
	char negativo[12][9] = {"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};

	int n, m, k=0, flag = 1, contProdutos = 0;
	char product[50];
	char sentence[400];
	int nsent[10];
	scanf("%d %d", &n, &m);
	getchar();

	//este bloco faz o trabalho de scanear e armazenar 
	//todos os produtos e sentenças
	for(int i=0; i<n; i++)
	{
		//escaneia separadamente o nome do produto e a sentença correspondente
		scanf("%[^;] ; ", product);
		scanf("%[^Ø]Ø", sentence);
		getchar();
		product[strlen(product)-1] = '\0';
		sentence[strlen(sentence)-1] = '\0';

		//este bloco verifica se já existe aquele produto na lista de produtos
		contProdutos++;
		for(int j=0; j<contProdutos; j++)
		{
			if(strcmp(bolsa.produtos[j], product) == 0)
			{
				contProdutos--;
				k=j;
				flag = 0;
				break;
			}
		}

		//se ainda não há este produto na lista, ele é adicionado aqui
        //além disso adiciona a primeira setença relacionada a cada produto
		if(flag == 1)
		{
			strncpy(bolsa.produtos[contProdutos-1], product, strlen(product));
			strncpy(bolsa.sentencas[contProdutos-1][nsent[contProdutos-1]], sentence,strlen(sentence));
			nsent[contProdutos-1]++;
		}

		//adiciona as demais sentenças aos seus respectivos produtos
		if(flag == 0)
		{
			strncpy(bolsa.sentencas[k][nsent[k]], sentence,strlen(sentence));
			nsent[k]++;
		}
		flag=1;
	}

	int i = 0;
	while(i<m)
	{
		int l=0, p=0, r=0, cont2=0, cont=0;
        float neg=0, pos=0;
		char quests[10][200]; // num da pergunta / caractere
		char words[10][5][20]; // num da pergunta / palavra / caractere
		char palavra[1][8] = {"palavra"};
		char quantos[1][8] = {"quantos"};
        char positivos[1][10] = {"positivos"};
		
		fgets(quests[i], 200, stdin);

		//separa cada pergunta em 5 palavras
		for(int j=0; j<strlen(quests[i]); j++)
		{
			if(quests[i][j] != ' ' && quests[i][j] != '\r' && quests[i][j] != '\n')
			{
				
				words[i][l][p] = quests[i][j];
				p++;
			}
			else
			{
				l++;
				p=0;
			}
		}
		p=0;
		l=0;

        //conta quantas vezes a palavra aparece
		if(strcmp(words[i][0], palavra[0]) == 0)
		{
            for(int j=0; j<contProdutos; j++)
            {
				//verifica qual produto corresponde à pergunta em questão
                if(strstr(bolsa.produtos[j], words[i][4]) != NULL)
                {
                    for(int t=0; t<nsent[j]; t++)
                    {
						//verífica quantas vezes aquela palavra aparece na sentença
                        if(strstr(bolsa.sentencas[j][t] ,words[i][1]) != NULL)
                        {
                            char *pont = strstr(bolsa.sentencas[j][t] ,words[i][1]);
                            *pont = '1';	//transformamos o primeiro caractere da palavra em '1' para poder verificar quantas aparições
                            t--;			//a palavra tem em uma mesma sequência e retornamos o loop para verificarmos a sentença novamente
                            if(pont[strlen(words[i][1])] != 's') //ignoramos os casos em que a letra após a palavra em questão é 's', para casos de plural.
                            {
                                cont++;
                            }
                        }
                    }
                }
            }
            printf("%d\n", cont);
            cont = 0;
            ++i;
		}

        //verifica sentenças positivas e negativas
		else if(strcmp(words[i][0], quantos[0]) == 0)
		{
			if(strcmp(words[i][1], positivos[0]) == 0) //verificamos se devemos contar sentenças negativas ou positivas
            {
                for(int j=0; j<contProdutos; j++)
                {
                    if(strstr(bolsa.produtos[j] ,words[i][4]) != NULL) //verifica qual produto corresponde à pergunta em questão
                    {
						//verífica se existe alguma palavra positiva na sentença
						//calcula a porcentagem de sentenças positivas
                        while(r<=12 && cont2<nsent[j])
                        {
                            if(strstr(bolsa.sentencas[j][cont2],positivo[r]) == NULL && r!=12)
                            {
                                r++;
                            }
                            else if(strstr(bolsa.sentencas[j][cont2],positivo[r]) != NULL && r!=12)
                            {
                                pos++;
                                r=0;
                                cont2++;
                            }

                            else if(r == 12)
                            {
                                r=0;
                                cont2++;
                            }
                        }
                    }
                }
                printf("%.1f%%\n", (pos/cont2)*100.00);
                cont2=0;
                r=0;
            }
            else
            {
                for(int j=0; j<contProdutos; j++)
                {
                    if(strstr(bolsa.produtos[j] ,words[i][4]) != NULL) //verifica qual produto corresponde à pergunta em questão
                    {
						//verífica se existe alguma palavra negativa na sentença
						//calcula a porcentagem de sentenças negativas
                        while(r<=12 && cont2<nsent[j])
                        {
                            if(strstr(bolsa.sentencas[j][cont2],negativo[r]) == NULL && r!=12)
                            {
                                r++;
                            }
                            else if(strstr(bolsa.sentencas[j][cont2],negativo[r]) != NULL && r!=12)
                            {
                                neg++;
                                r=0;
                                cont2++;
                            }

                            else if(r == 12)
                            {
                                r=0;
                                cont2++;
                            }
                        }
                    }
                }
                printf("%.1f%%\n", (neg/cont2)*100.00);
                cont2=0;
                r=0;
            }
			++i;
		}
	}
	return 0;
}