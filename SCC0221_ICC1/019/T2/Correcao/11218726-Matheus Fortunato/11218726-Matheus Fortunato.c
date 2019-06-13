#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int numeroSentecas=0,numeroPerguntas=0;
    scanf("%d %d",&numeroSentecas,&numeroPerguntas);

    char dicionario[2][12][12]; 
    /* 
        a ideia é um array para as palavras que indicam positividade e negatividade. 
        dicionario[2 siginificados (0-positivo,1-negativo)][12 palavras][12 caracteres (a maior palavra é maravilhoso)] 
    */
    // atribuições positivas
    strcpy (dicionario[0][0],"bom");
    strcpy (dicionario[0][1],"maravilhoso");
    strcpy (dicionario[0][2],"otimo");
    strcpy (dicionario[0][3],"sensacional");
    strcpy (dicionario[0][4],"excelente");
    strcpy (dicionario[0][5],"adorei");
    strcpy (dicionario[0][6],"gostei");
    strcpy (dicionario[0][7],"amei");
    strcpy (dicionario[0][8],"eficiente");
    strcpy (dicionario[0][9],"boa");
    strcpy (dicionario[0][10],"maravilhosa");
    strcpy (dicionario[0][11],"otima");

    // atribuições negativas
    strcpy (dicionario[1][0],"detestei");
    strcpy (dicionario[1][1],"odiei");
    strcpy (dicionario[1][2],"ruim");
    strcpy (dicionario[1][3],"pessimo");
    strcpy (dicionario[1][4],"terrivel");
    strcpy (dicionario[1][5],"raiva");
    strcpy (dicionario[1][6],"odio");
    strcpy (dicionario[1][7],"pessima");
    strcpy (dicionario[1][8],"lento");
    strcpy (dicionario[1][9],"lenta");
    strcpy (dicionario[1][10],"fragil");
    strcpy (dicionario[1][11],"desisti");

    /*  
        como tenho certeza do maximo de caracteres e do maximo de palavras, só não sei a quantodade de sentenças ate a execução
        tenho que ter um array arr[x sentenças][22 palavras][20 caracteres] (aqui se pontua 22 ao inves de 20, pois escolhi guardar
        o produto e a marca nos dois primeiros espaços), sendo x dinamico, baseado em numeroSetencas
    */
    char*** comentarios = NULL;

    comentarios = malloc(sizeof(char**)*numeroSentecas);

    char*** pergunta = NULL;

    pergunta = malloc(sizeof(char**)*numeroPerguntas);

    for (int i = 0; i < numeroSentecas; i++) //input sentenças
    {
        comentarios[i] = malloc(sizeof(char*)*22);
        for (int j = 0; j < 22; j++) //for para alocar memoria para todos as celulas
        {
            comentarios[i][j] = malloc(sizeof(char)*20);
        }

        //pega a marca e o produto, isso não pode  ficar junto no laço a seguir por causa do ; no meio da frase
        
        scanf("%s",comentarios[i][0]);    
        scanf("%s",comentarios[i][1]); 
        scanf("%s",comentarios[i][2]); // simplismente para receber o ; de alguma maneira, será sobrescrito depois 

        int j=1;
        do //laço para input
        {
            j++; //igualei o j a 1 pois o primeiro registro vai no comentarios[i][2]
            scanf("%s",comentarios[i][j]); //o scanf("%s") considera o espaço fim da palavra, por isso isso funciona
        } while (strcmp(comentarios[i][j], "Ø")); 
    }
    
   
 
    int auxiliarContaPalavras=0;
    float auxiliarTotalSentecasProdutos=0;
    float auxiliarOpiniaoSentenca=0;
    //float auxiliarPorcentagemOpiniao=0;
    int analisado=0;
	int valido;
    for (int i = 0; i < numeroPerguntas; i++) // input perguntas
    {
        auxiliarContaPalavras=0;
        auxiliarTotalSentecasProdutos=0;
        auxiliarOpiniaoSentenca=0;
         /* 
            tem basicamente dois tipos de perguntas:
                palavra [palavra] em [produto] [marca] 
                quantos [positivos/negativo] em [produto] [marca] 
            ou seja, cada perguntas é um array perguntas[5], sendo que perguntas[0] é o que define o tipo da pergunta,
            perguntas[1] é "o que buscar" e perguntas[3] e [4] são "onde buscar"
        */
        
        pergunta[i] = malloc(sizeof(char*)*5);
        for (int j = 0; j < 5; j++) //for para alocar memoria para todos as celulas
        {
            pergunta[i][j] = malloc(sizeof(char)*20);
        }

        for (int j = 0; j < 5; j++) //for para alocar memoria para todos as celulas
        {
            scanf("%s",pergunta[i][j]);
        }
        
        if (!strcmp(pergunta[i][0], "palavra")) //caso seja o primeiro tipo de pergunta
        {
           
           for (int x= 0; x < numeroSentecas; x++)
           {
               
               if (!strcmp(pergunta[i][3],comentarios[x][0]) && !strcmp(pergunta[i][4],comentarios[x][1]))
               {
                    for (int y = 2; y < 22; y++)
                    {
                        if (!strcmp(pergunta[i][1],comentarios[x][y]))
                        {
                            auxiliarContaPalavras++;
                        }   

                    }
               }
           }
           printf("%d\n",auxiliarContaPalavras);
        }
        else if (!strcmp(pergunta[i][0], "quantos")) //caso seja o segundo tipo de pergunta
        {

            for (int x= 0; x < numeroSentecas; x++)
            {
                if (!strcmp(pergunta[i][3],comentarios[x][0]) && !strcmp(pergunta[i][4],comentarios[x][1]))
                {
                    auxiliarTotalSentecasProdutos++; //pega o numero total de sentenças sobre o produto
                }
            }
            
            if (!strcmp(pergunta[i][1], "negativos")) //caso a pergunta seja sobre sentencas negativas
            {
                
                for (int x= 0; x < numeroSentecas; x++) //conta o total de sentenças negativas puras
                {
					valido=1;
                    if (!strcmp(pergunta[i][3],comentarios[x][0]) && !strcmp(pergunta[i][4],comentarios[x][1]))
                    {
                        
                        for (int y = 2; y < 22; y++)
                        {
                            
                            for (int z = 0; z < 12; z++)
                            {
                                //printf("%s %s\n",dicionario[1][z],comentarios[x][y]);
                                if (!strcmp(dicionario[1][z],comentarios[x][y]))
                                {
									
                                    for (int w = 1; w <= 3; w++) //checa se não há uma  inversao
									{
										if (!(y==2 && w==3))
										{
											if (!strcmp("jamais",comentarios[x][y-w]) || !strcmp("nunca",comentarios[x][y-w]) || !strcmp("nao",comentarios[x][y-w]))
											{
												valido=0;
											}
										}	
									}
									if (valido)
									{
										auxiliarOpiniaoSentenca++;
									}
                                    analisado=1;
                                }
                                
                            }
                            
                            if (analisado)
                            {
                                analisado=0;
                                break;
                            }
                            
                        }
                    }
                }
				for (int x= 0; x < numeroSentecas; x++) //conta o total de sentenças negativas invertidas de uma positiva
                {
					valido=0;
                    if (!strcmp(pergunta[i][3],comentarios[x][0]) && !strcmp(pergunta[i][4],comentarios[x][1]))
                    {
                        for (int y = 2; y < 22; y++)
                        {
                            for (int z = 0; z < 12; z++)
                            {
                                if (!strcmp(dicionario[0][z],comentarios[x][y]))
                                {
									for (int w = 1; w <= 3; w++) //checa se não há uma  inversao
									{
										if (!(y==2 && w==3))
										{
											if (!strcmp("jamais",comentarios[x][y-w]) || !strcmp("nunca",comentarios[x][y-w]) || !strcmp("nao",comentarios[x][y-w]))
											{
												
												valido=1;
											}
										}
										
									}
									if (valido)
									{
										auxiliarOpiniaoSentenca++;
									}
									
                                    
                                    analisado=1;
                                }
                                
                            }
                            
                            if (analisado)
                            {
                                analisado=0;
                                break;
                            }
                            
                        }
                    }
                }

            }
            else if (!strcmp(pergunta[i][1], "positivos")) //caso a pergunta seja sobre sentencas positivas
            {
                for (int x= 0; x < numeroSentecas; x++) //conta o total de sentenças positivas puras
                {
					valido=1;
                    if (!strcmp(pergunta[i][3],comentarios[x][0]) && !strcmp(pergunta[i][4],comentarios[x][1]))
                    {
                        for (int y = 2; y < 22; y++)
                        {
                            for (int z = 0; z < 12; z++)
                            {
                                if (!strcmp(dicionario[0][z],comentarios[x][y]))
                                {
									for (int w = 1; w <= 3; w++) //checa se não há uma  inversao
									{
										if (!(y==2 && w==3))
										{
											if (!strcmp("jamais",comentarios[x][y-w]) || !strcmp("nunca",comentarios[x][y-w]) || !strcmp("nao",comentarios[x][y-w]))
											{
												valido=0;
											}
										}
										
									}
									if (valido)
									{
										auxiliarOpiniaoSentenca++;
									}
									
                                    
                                    analisado=1;
                                }
                                
                            }
                            
                            if (analisado)
                            {
                                analisado=0;
                                break;
                            }
                            
                        }
                    }
                }
				for (int x= 0; x < numeroSentecas; x++) //conta o total de sentenças positivas invertidas de uma negativa
                {
					valido=0;
                    if (!strcmp(pergunta[i][3],comentarios[x][0]) && !strcmp(pergunta[i][4],comentarios[x][1]))
                    {
                        for (int y = 2; y < 22; y++)
                        {
                            for (int z = 0; z < 12; z++)
                            {
                                if (!strcmp(dicionario[1][z],comentarios[x][y]))
                                {
									
									for (int w = 0; w < 3; w++) //checa se não há uma  inversao
									{
										if (!(y==2 && w==3))
										{
											if (!strcmp("jamais",comentarios[x][y-w]) || !strcmp("nunca",comentarios[x][y-w]) || !strcmp("nao",comentarios[x][y-w]))
											{
												valido=1;
											}
										}
										
									}
									if (valido)
									{
										auxiliarOpiniaoSentenca++;
									}
									
                                    
                                    analisado=1;
                                }
                                
                            }
                            
                            if (analisado)
                            {
                                analisado=0;
                                break;
                            }
                            
                        }
                    }
                }

            }


            //printf("%d %d",auxiliarOpiniaoSentenca,auxiliarTotalSentecasProdutos);
            printf("%.1f%%\n",((auxiliarOpiniaoSentenca/auxiliarTotalSentecasProdutos)*100));

        }       
    } 
    

    /*for (int i = 0; i < numeroSentecas; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            printf("%s ",comentarios[i][j]);
        }
        printf("\n");
    }*/
    
    /*for (int i = 0; i < numeroPerguntas; i++)
    {
        printf("%s",pergunta[i][0]);
        
        for (int j = 0; j < 5; j++)
        {
            printf("%s ",pergunta[i][j]);
        }
        printf("\n");
    }*/

  

    return 0;
}