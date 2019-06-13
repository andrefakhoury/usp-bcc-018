//Trabalho ICC - Contando Palavras
//USP - São Carlos
//Autor: Mateus Penteado
//Data: 27/05/2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tipo de estrutura de dados que armazena todas informações necessarias de cada frase
typedef struct FRASES{
	int n_palavras;
	char id[100];
	char oracao[400];
	char **palavras;	
	char **bag_of_words;
	int *bag_of_words_id;
	int different_words;
	
}frase;

//Tipo de estrutura de dados que armazena todas as informações necessarias de cada pergunta
typedef struct perg{
	int n_palavras_perg;
	char perg[400];
	char **palavras_perg;
	char produto[40];
	char indicativo[21];
}pergunta;

//Essa função pega a frase e identifica a que produto ela está se referindo
void identificador (char* frase,char* produto)
{
    int i=0;
    
    while(1)
    {
        if(frase[i]==';')
        {
            produto[i-1]='\0';
            break;
        }
        else
        {
            produto[i]=frase[i];
            i++;
        }
    }
    return;
}

//Essa função serve para retirar o identificador do produto da frase e deixar apenas o comentário do cliente
void tratar_oracao(char *frase)
{
    int i=0,j,k,l;
    
    while(1)
    {
        if(frase[i]==';')
        {
            for(l=i,j=2,k=0;l<strlen(frase);l++,j++,k++)
            {
                frase[k]=frase[i+j];
            }
            break;
        }
        else
        {
            i++;
        }
    }
    return;
}

//Essa função recebe uma frase e retorna o número de palavras da frase
int num_palavras (char *frase)
{
    int n_de_palavras=1,i;
    
    for(i=0;i<strlen(frase);i++)
    {
        if(frase[i]==' ')
        {
            n_de_palavras++;
        }
    }
    return n_de_palavras;
}

//Essa função aloca dinamicamente uma matriz de tamanho n x m
char** aloca(char** matriz,int n,int m)
{
	int i;
	
	if((matriz = (char **) malloc(sizeof(char*)*n))==NULL)
	{
	    printf("Erro ao alocar na heap\n");
	    exit(1);
	}
	
	for(i=0;i<n;i++)
	{
	    if((matriz[i]= (char *) malloc(sizeof(char)*m))==NULL)
	    {
	        printf("Erro ao alocar na heap\n");
	        exit(1);
	    }
	}
	
	return matriz;
}

//Essa função pega uma frase e separa palavra por palavra armazenando cada palavra em um matriz de char
//Ela também recebe um int n que é o número de palavras
void separa_palavras(char** palavras,char* frase,int n)
{
	int i,j,k;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<20;j++)
		{
			palavras[i][j]=0;
		}
	}
	
	for(k=0,i=0,j=0;k<strlen(frase);k++)
	{
		if(frase[k]==' ')
		{
			i++;
			j=0;
		}
		else
		{
			palavras[i][j]=frase[k];
			j++;
		}
	}
	
	return;
}

//Essa função recebe 2 matrizes de char onde uma contém todas palavras de uma frase e a outra armazenará as palavras sem repetir palavras iguais assim criando a bag of words
//e retorna o número de palavras diferentes
//Ela também recebe um int n que é o número de palavras
int compara_palavras(char **palavras,char **bag,int n)
{
	int i,j,jatem=0,ultimapos=0;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<20;j++)
		{
			bag[i][j]=0;
		}
	}
	
	
	for(i=0;i<n;i++)
	{
		jatem=0;
		for(j=0;j<n;j++)
		{
			if(strcmp(palavras[i],bag[j])==0)
			{
				jatem=1;
			}
		}
		if(jatem==0)
		{
			bag[ultimapos]=palavras[i];
			ultimapos++;
		}
	}
	
	return ultimapos;
}

//Essa função recebe a bag of words e associa cada palavra a um id numérico em uma array e recebe a matriz com todas palavras e guarda quantas vezes a
//palavra de determinado id foi utilizada
//Ela também recebe um int n e paraid que é,respectivamente,o número de palavras e o número de palavras diferentes
void repeticao_palavras(char **bag,int *ids,char **palavras,int n,int paraid)
{
	int i,j,id=0;
	
	for(i=0;i<paraid;i++)
	{
		ids[i]=0;
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(strcmp(palavras[i],bag[j])==0)
			{
				id = j;
				break;
			}
		}
		ids[id]++;
	}
	return;
}

//Essa função identifica a que produto a pergunta está se referindo
void identificar_produto(char **palavras,char *produto)
{
	int aux;
	
	strcpy(produto,palavras[3]);
	aux = strlen(produto);
	produto[aux]=' ';
	produto[aux+1]='\0';
	strcat(produto,palavras[4]);
}

//Essa função desaloca as matrizes alocadas dinamicamente
//Essa função também recebe um int n que é o número de linhas da matriz
void limpar(char **matriz,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		free(matriz[i]);
	}
	free(matriz);
	return;
}

int main()
{
    double porcentagem;
    int pos,neg,num_indicativo,acabou,fim,foi,n_perg,n_sentencas;
    int i,j,k,l,m,aux;
    frase *sentenca;
    pergunta *perguntas;
    char positivos[12][15] = {"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};
	char negativos[12][10] = {"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
	
    scanf("%d%d",&n_sentencas,&n_perg);
    
    if((sentenca = (frase *) malloc(sizeof(frase)*n_sentencas))==NULL)
    {
        printf("Erro ao alocar na heap\n");
	    exit(1);
    }
    
    if((perguntas = (pergunta *) malloc(sizeof(pergunta)*n_perg))==NULL)
    {
        printf("Erro ao alocar na heap\n");
	    exit(1);
    }
    
    for(i=0;i<n_sentencas;i++)
    {
    	//Scanf com máscara para ler até o enter
        scanf(" %[^\n\r]",sentenca[i].oracao);
        identificador(sentenca[i].oracao,sentenca[i].id);
        tratar_oracao(sentenca[i].oracao);
        sentenca[i].n_palavras = num_palavras(sentenca[i].oracao);
        sentenca[i].palavras = aloca(sentenca[i].palavras,sentenca[i].n_palavras,20);
        separa_palavras(sentenca[i].palavras,sentenca[i].oracao,sentenca[i].n_palavras);
		sentenca[i].bag_of_words = aloca(sentenca[i].bag_of_words,sentenca[i].n_palavras,20);
		sentenca[i].different_words = compara_palavras(sentenca[i].palavras,sentenca[i].bag_of_words,sentenca[i].n_palavras);
		if((sentenca[i].bag_of_words_id = (int*) malloc(sizeof(int)*sentenca[i].different_words))==NULL)
		{
		    printf("Erro ao alocar na heap\n");
	        exit(1);
		}
		repeticao_palavras(sentenca[i].bag_of_words,sentenca[i].bag_of_words_id,sentenca[i].palavras,sentenca[i].n_palavras,sentenca[i].different_words);
    }
    
    for(i=0;i<n_perg;i++)
    {
        pos=0;
        neg=0;
        num_indicativo=0;
        //Scanf com máscara para ler até o enter
        scanf(" %[^\n\r]",perguntas[i].perg);
        perguntas[i].n_palavras_perg = num_palavras(perguntas[i].perg);
        perguntas[i].palavras_perg = aloca(perguntas[i].palavras_perg,perguntas[i].n_palavras_perg,20);
        separa_palavras(perguntas[i].palavras_perg,perguntas[i].perg,perguntas[i].n_palavras_perg);
		strcpy(perguntas[i].indicativo,perguntas[i].palavras_perg[1]);
		identificar_produto(perguntas[i].palavras_perg,perguntas[i].produto);
		if(strcmp(perguntas[i].palavras_perg[0],"quantos")==0)
		{
		   for(j=0;j<n_sentencas;j++)
		   {
		       acabou =0;
		       fim =0;
		       foi=0;
		       aux=0;
	    	   if(strcmp(sentenca[j].id,perguntas[i].produto)==0)
	    	   {
	    	   		//Para analisar essa pergunta eu achei melhor não modularizar por meio de funções e sim por meio de 4 for que estão dispostos por ordem de relevancia
	    	   		//e podem ser tratados como funções que se comunicam
	    	   		//Esse for identifica se há inversão de opinião positiva para negativa
	    	       for(k=0;k<sentenca[j].n_palavras;k++)
	    	       {
	    	            if((strcmp(sentenca[j].palavras[k],"nao")==0) || (strcmp(sentenca[j].palavras[k],"jamais")==0) || (strcmp(sentenca[j].palavras[k],"nunca")==0))
	    	            {
	    	                for(l=k+1;l<=k+3;l++)
	    	                {
	    	                    if(l>=sentenca[j].n_palavras)
	    	                    {
	    	                        break;
	    	                    }
	    	                    else
	    	                    {
	    	                        for(m=0;m<12;m++)
	    	                        {
	    	                            if(strcmp(sentenca[j].palavras[l],positivos[m])==0)
	    	                            {
	    	                                neg++;
	    	                                foi=1;
	    	                                break;
	    	                            }
	    	                        }
	    	                        if(foi==1)
	    	                        {
	    	                            acabou=1;
	    	                            break;
	    	                        }
	    	                    }
	    	                }
	    	        	}
	    	       	}
	    	       	//Se não foi identificada o item do for anterior esse for identifica se há inversão de opinião negativa para positiva 
	    	        for(k=0;k<sentenca[j].n_palavras;k++)
	    	       	{
	    	            if(foi!=1)
	    	            {
	    	                if((strcmp(sentenca[j].palavras[k],"nao")==0) || (strcmp(sentenca[j].palavras[k],"jamais")==0) || (strcmp(sentenca[j].palavras[k],"nunca")==0))
	    	            	{			
								for(l=k+1;l<=k+3;l++)
	    	                	{
	    	                    	if(l>=sentenca[j].n_palavras)
	    	                    	{
	    	                       		break;
	    	                    	}
	    	                    	else
	    	                    	{
	    	                        	for(m=0;m<12;m++)
	    	                        	{
	    	                            	if(strcmp(sentenca[j].palavras[l],negativos[m])==0)
	    	                            	{
	    	                                	pos++;
	    	                                	foi=1;
	    	                                	break;
	    	                            	}
	    	                        	}
	    	                        	if(foi==1)
	    	                        	{
	    	                            	acabou=1;
	    	                            	break;
	    	                    		} 
									}
								}
							}
						}
						else
						{
							acabou=1;
							break;
						}
	    	        }
	    	        //Se não foi identificado um dos itens dos for anteriores esse for identifica se há palavras de elogio 
					for(k=0;k<sentenca[j].n_palavras;k++)
	    	       	{
	    	            if(acabou==1)
	    	            {
	    	                break;
	    	            }
	    	            else
	    	            {
	    	                for(k=0;k<sentenca[j].n_palavras;k++)
	    	                {
	    	                    for(l=0;l<12;l++)
	    	                    {
	    	                        if(aux==1)
	    	                        {
	    	                            continue;
	    	                        }
	    	                        if(strcmp(sentenca[j].palavras[k],positivos[l])==0)
	    	                        {
	    	                            pos++;
	    	                            fim=1;
	    	                            break;
	    	                        }
	    	                    }
	    	                    if(fim==1)
	    	                    {
	    	                        aux=1;
	    	                    }
	    	                }
	    	        	}
	    	    	}
	    	        if(fim!=1)
	    	        {
	    	        	//Se não foi identificado um dos itens dos for anteriores esse for identifica se há palavras de reclamação 
	    	            for(k=0;k<sentenca[j].n_palavras;k++)
	    	            {
	    	                for(l=0;l<12;l++)
	    	                {
	    	                    if(acabou==1)
	    	                    {
	    	                        continue;
	    	                    }
	    	                    if(aux==1)
	    	                    {
	    	                        continue;
	    	                    }
	    	                    if(strcmp(sentenca[j].palavras[k],negativos[l])==0)
	    	                    {
	    	                        neg++;
	    	                        fim=1;
	    	                        break;
	    	                    }
	    	                    if(fim==1)
	    	                    {
	    	                        break;
	    	                    }
	    	                }
	    	                if(fim==1)
	    	                {
	    	                    aux=1;
	    	                }
	    	            }
	    	       	} 	
	    	   }
		   }
		   //Esses if e else if identificam qual é a pergunta e calculam a porcentagem
		   if(pos+neg==0)
		   {
		       porcentagem=0;
		   }
		   else if(strcmp(perguntas[i].indicativo,"negativos")==0)
		   {
		       porcentagem=((neg*1.00)/((neg+pos)*1.00))*100;
		   }
		   else if(strcmp(perguntas[i].indicativo,"positivos")==0)
		   {
		       porcentagem=((pos*1.00)/((neg+pos)*1.00))*100;
		   }
		   //Exibe o resultado
		   printf("%.1lf%%\n",porcentagem);
		}
		else if(strcmp(perguntas[i].palavras_perg[0],"palavra")==0)
		{
		   for(j=0;j<n_sentencas;j++)
			{
				if(strcmp(sentenca[j].id,perguntas[i].produto)==0)
				{
					//Como analisar essa pergunta é fácil, preferi deixar o código inteiro na main
					//Esse for verifica se há a palavra pedida pela pergunta na frase e se houver pega o id dessa palavra e ve quantas vezes ela foi dita na frase
					for(k=0;k<sentenca[j].different_words;k++)
					{
						if(strcmp(sentenca[j].bag_of_words[k],perguntas[i].indicativo)==0)
						{
							num_indicativo+=sentenca[j].bag_of_words_id[k];
						}
					}
				}
		    }
		    //Exibe o resultado
		    printf("%d\n",num_indicativo);
		}	    
    }
    
    //Desaloca
    for(i=0;i<n_sentencas;i++)
    {
    	limpar(sentenca[i].bag_of_words,sentenca[i].n_palavras);
    	limpar(sentenca[i].palavras,sentenca[i].n_palavras);
    	free(sentenca[i].bag_of_words_id);
	}
	
	//Desaloca
	for(i=0;i<n_perg;i++)
    {
    	limpar(perguntas[i].palavras_perg,perguntas[i].n_palavras_perg);
	}
    
    //Desaloca
    free(sentenca);
    free(perguntas);
    
	return 0;
}
