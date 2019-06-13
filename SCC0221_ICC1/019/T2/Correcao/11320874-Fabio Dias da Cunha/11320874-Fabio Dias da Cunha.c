/*
    Autor : Fabio Dias da Cunha
    Número USP: 11320874
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Protótipo das funções 
int source(char frase[], char palavra[]);
int contador(char frase[], char frase2[]);
int contador2(char frase[], char frase2[]);

int main() 
{
    //Variáveis usadas no programa 
    int i, j, k, x, y, z, numseq, numperg, ver1=0, ver2=0, cont=0, total=0, subt=0,subt1=0,subt2=0,numfrases=0,pos=0,neg=0,pos1,pos2, pos3, r;
    char produto[30][100], fabricante[30][100], comentario[30][400], pergunta1[30][100],pergunta2[30][100],pergunta3[30][100],var[100],var1[100], var2[100], var3[100], g[100];
    char fraseP[13][13] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char fraseN[13][13] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    char fraseA[4][8] = {"nao", "jamais", "nunca"};
    char var4[100], var5[100];
    double result=0;
    
    scanf("%d %d", &numseq, &numperg);//Leitura dos dados
    
    for(i=0;i<numseq;i++)
    {
        scanf("%s", produto[i]);
        getchar();
        scanf("%s", fabricante[i]);
        getchar();
        getchar();
        getchar();
        scanf("%[^Ø]s", comentario[i]);
        scanf("%[Ø]s", var);
    }
    
    for(j=0;j<numperg;j++)
    {
        getchar();
        scanf("%s", pergunta1[j]);
        scanf("%s", pergunta2[j]);
        scanf("%s", g);
        getchar();
        scanf("%[^\n]s", pergunta3[j]);
    }
    
    for(k=0;k<numperg;k++)//Estrutura para percorrer as perguntas
    {
        ver1 = 0;
        ver2 = 0;
        cont = 0;
        total = 0;
        numfrases=0;
        pos=0;
        pos2=0;
        neg=0;
        subt1 = 0;
        subt2 = 0;
        
        while(cont<numseq)//Estrutura para percorrer os produtos e comentários
        {   
            subt = 0;
            strcpy(var1, pergunta3[k]);
            ver1 = source(var1, produto[cont]);
            ver2 = source(var1, fabricante[cont]);
            
            if(ver1==2 && ver2==2)//Verifica se o comentário está relacionado com o produto
            {
                numfrases += 1;   
                
                if(strcmp(pergunta2[k],"positivos")!=0 && strcmp(pergunta2[k],"negativos")!=0)//Verifica qual será o retorno para a pergunta
                {
                    strcpy(var2, comentario[cont]);
                    subt = contador(var2, pergunta2[k]);
                    total += subt;
                }
                else if(strcmp(pergunta2[k],"positivos")==0)
                {
                    for(x=0;x<12;x++)//Verifica se contém alguma palavra positiva
                    {
                        strcpy(var2, comentario[cont]);
                        strcpy(var3, fraseP[x]);
                        subt1 = contador2(var2, var3);
                        
                        if(subt1>0)
                        {
                            strcpy(var2, comentario[cont]);
                            strcpy(var3, fraseP[x]);
                            pos1 = contador2(var2, var3);
                            break;
                        }
                    }
                    if(subt1==0)
                    {
                        pos1 = 0;     
                    }
                    for(y=0;y<3;y++)//Verifica se contém algum advérbio
                    {
                        strcpy(var4, comentario[cont]);
                        strcpy(var5, fraseA[y]);
                        subt2 = contador2(var4, var5);
                        
                        if(subt2>0)
                        {
                            strcpy(var4, comentario[cont]);
                            strcpy(var5, fraseA[y]);
                            pos2 = contador2(var4, var5);
                        }
                        
                    }
                     
                    pos3 = pos1-pos2;
                    //Classificação da frase
                    if(pos3>3 && pos1>0 && pos2>0)
                    {
                        pos++;
                    }
                    else if(pos1>0 && pos2==0)
                    {
                        pos++;
                    }
                    else if(pos1==0)
                    {
                        for(z=0;z<12;z++)//Verifica se contém alguma palavra negativa
                        {
                            strcpy(var2, comentario[cont]);
                            strcpy(var3, fraseN[z]);
                    
                            subt1 = contador2(var2, var3);
                        
                    
                            if(subt1>0)
                            {
                                strcpy(var2, comentario[cont]);
                                strcpy(var3, fraseN[z]);
                                pos1 = contador2(var2, var3);
                                break;
                            }
                        }
                        if(subt1==0)
                        {
                            pos1 = 0;
                         
                        }
                        for(y=0;y<3;y++)//Verifica se contém algum advérbio
                        {
                            strcpy(var4, comentario[cont]);
                            strcpy(var5, fraseA[y]);
                            subt2 = contador2(var4, var5);
                        
                            if(subt2>0)
                            {
                                strcpy(var4, comentario[cont]);
                                strcpy(var5, fraseA[y]);
                                pos2 = contador2(var4, var5);
                            }
                        
                        }
                     
                        pos3 = pos1-pos2;
                        //Classificação da frase
                        if(pos3>3 && pos1>0 && pos2>0)
                        {
                            neg++;
                        }
                        else if(pos1>0 && pos2==0)
                        {
                            neg++;
                        }
                        else
                        {
                            pos++;
                        } 

                    }
                      
                }
                
                else if(strcmp(pergunta2[k],"negativos")==0)
                {
                    for(z=0;z<12;z++)//Verifica se contém alguma palavra negativa
                    {
                        strcpy(var2, comentario[cont]);
                        strcpy(var3, fraseN[z]);
                        subt1 = contador2(var2, var3);
                        
                        if(subt1>0)
                        {
                            strcpy(var2, comentario[cont]);
                            strcpy(var3, fraseN[z]);
                            pos1 = contador2(var2, var3);
                            break;
                        }
                    }
                    if(subt1==0)
                    {
                        pos1 = 0;
                    }
                    pos2=0;
                    for(y=0;y<3;y++)//Verifica se contém algum advérbio
                    {
                        strcpy(var4, comentario[cont]);
                        strcpy(var5, fraseA[y]);
                        subt2 = contador2(var4, var5);
                        
                        if(subt2>0)
                        {
                            strcpy(var4, comentario[cont]);
                            strcpy(var5, fraseA[y]);
                            r = contador2(var4, var5);
                            
                            if(r>pos2)
                            {
                                pos2 = r;
                            }
                            
                        }
                        
                    }
                     
                    pos3 = pos1-pos2;
                    //Classificação da frase
                    if(pos3>3 && pos1>0 && pos2>0)
                    {
                        neg++;
                    }
                    else if(pos1>0 && pos2==0)
                    {
                        neg++;
                    }
                    else if(pos3>3 && pos1>0 && pos2==0)
                    {
                        pos++;
                    }
                    else if(pos3<0 && pos1>0 && pos2>0)
                    {
                        neg++;
                    }
                    else if(pos1==0)
                    {
                        for(x=0;x<12;x++)//Verifica se contém alguma palavra positiva
                        {
                            strcpy(var2, comentario[cont]);
                            strcpy(var3, fraseP[x]);
                            subt1 = contador2(var2, var3);
                        
                            if(subt1>0)
                            {
                                strcpy(var2, comentario[cont]);
                                strcpy(var3, fraseP[x]);
                                pos1 = contador2(var2, var3);
                                break;
                            }
                        }
                        if(subt1==0)
                        {
                            pos1 = 0; 
                        }
                        pos2=0;
                        for(y=0;y<3;y++)//Verifica se contém algum advérbio
                        {
                            strcpy(var4, comentario[cont]);
                            strcpy(var5, fraseA[y]);
                            subt2 = contador2(var4, var5);
                        
                            if(subt2>0)
                            {
                                strcpy(var4, comentario[cont]);
                                strcpy(var5, fraseA[y]);
                                pos2 = contador2(var4, var5);
                            
                                if(r>pos2)
                                {
                                    pos2 = r;
                                }
                            }
                        
                        }
                     
                        pos3 = pos1-pos2;
                        //Classificação da frase
                        if(pos3>3 || (pos1==0 && pos2>0))
                        {
                            pos++;
                        }
                        else if(pos3<0)
                        {
                            pos++;
                        }
                       else
                        {
                            neg++;
                        }
                    }
                    
                }
                
            }
            
            cont++;
        }
        
        //Cálculo do resultado de cada pergunta
        if(total>=0 && strcmp(pergunta2[k],"positivos")==0)
        {
            result = (double)pos/numfrases;
            result = result*100;
            printf("%.1lf%%\n", result);
            total = 0;
            result=0;
        }
        else if(total>=0 && strcmp(pergunta2[k],"negativos")==0)
        {
            result = (double)neg/numfrases;
            result = result*100;
            printf("%.1lf%%\n", result);
            total = 0;
            result=0;
        }
        else if(total>=0)
        {
            printf("%d\n", total);
            total = 0;
        }
        
    }
    
    return 0;
}

int source(char frase[], char palavra[])//Função usada para verificar se existe o produto e a marca no comentário
{

    char *res;
    res = strstr(frase, palavra);

    if (res != NULL) 
    {
        return 2;
    }  
    else 
    {
        return 1;
    }

}

int contador(char frase[], char frase2[])//Função usada para verificar quantas vezes uma palavra se repete no comentário
{
    char *word;
    int i=0;

    word = strtok(frase," ");
    
    while(word != NULL) 
    {
	    if(strcmp(word,frase2)==0)
	    {
	        i += 1;
	    }
	    
        word = strtok(NULL, " ");
	}
	
	return i;
}

int contador2(char frase[], char frase2[])//Função usada para determinar a posição de uma palavra
{
    char *word;
    int j=0;
    static int i=1;
    
    word = strtok(frase," ");
    
    while(word != NULL) 
    {
      
	    if(strcmp(word,frase2)==0)
	    {
	        j = i;
	        i = 1;
	        return j;
	    }
	    else
	    {  
	        i++;
	    }
    
	    word = strtok(NULL, " ");
	
	}

	return 0;
}