#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{ /*definimos uma struct que possui um identificador do produto, as criticas atribuidas a ele
 e a quantidade de comentarios positivos e negativos*/
    char nome[17];
    char criticas[200][17];
    int positivos, negativos;
    
}produtos;

produtos* alok (int a); //aloca dinamicamente o maximo possivel de produtos a serem comentados
produtos* alok (int a){
    produtos *b = (produtos*) calloc (a, sizeof (produtos));
    return (b);
}

void liberar (produtos *b); //sempre que um vetor e alocado, deve ser liberado
void liberar (produtos *b){
    free (b);
}

int main (void){
    
    int frases, perguntas, verif = 0, retorno = -1, a =0, resultado = 0;
    float pos = 0.0, neg = 0.0;
    char prod_aux[15];
    char marca_aux[15];
    char critica_aux[15];
    char tipo_perg[10];

    char pol[3][15] = {{"nao\0"}, {"jamais\0"}, {"nunca\0"}};
    //inversores

    char positivos[12][16] = {{"bom\0"}, {"maravilhoso\0"}, {"otimo\0"}, {"sensacional\0"}, {"excelente\0"}, {"adorei\0"}, {"gostei\0"}, {"amei\0"}, {"eficiente\0"}, {"boa\0"}, {"maravilhosa\0"}, {"otima\0"}};
    //possibilidades de comentarios positivos

    char negativos[12][16] = {{"detestei\0"}, {"odiei\0"}, {"ruim\0"}, {"pessimo\0"}, {"terrivel\0"}, {"raiva\0"}, {"odio\0"}, {"pessima\0"}, {"lento\0"}, {"lenta\0"}, {"fragil\0"}, {"desisti\0"}};
    //possivilidade de negativos
    
    scanf ("%d %d", &frases, &perguntas);
    
    produtos *matriz = alok (frases);
    
   

    for (int j = 0; j < frases; j++){ //guarda os produtos e as palavras importantes que existem no comentario a ele atribuido em cada cama da matriz
        scanf ("%s", prod_aux);
        scanf (" %s", marca_aux);
        strcat (prod_aux, marca_aux);

        retorno = -1;

        for (int i = 0; i < frases; i++){ 
                if (strcmp(matriz[i].nome, prod_aux) == 0){ //caso o produto ja tenha sido comentado, evita que seja criada mais uma camada, atribui apos o ultimo comentario do mesmo
                  retorno = i;
                }
            
        }

        if (retorno == -1){ //caso o produto ainda nao verificado
            retorno = verif;
            verif++;
        }

        strcpy (matriz[retorno].nome, prod_aux); //guarda todas as palavras atribuidas ao produto
        scanf ("%s", critica_aux);
        
        if (strcmp (critica_aux, ";") == 0 ){ //evita que seja considerado ";" na critica
            int w=0;

            while (strcmp (matriz[retorno].criticas[a], "\0") !=0 ){ //verifica a quantidade de palavras atruibuidas ao produto
                a++;
            }

            while  (strcmp(critica_aux, "Ø\0") != 0 && strcmp(critica_aux, "\n\0") != 0){
                scanf ("%s", critica_aux);
                strcpy(matriz[retorno].criticas[w+a], critica_aux);
                w++;
                
                for (int z=0; z<12; z++){ //do incio do programa, temos um padrao de palavras positivas, estas, caso ocorram, incrementam um contador aos positivos
                	if (strcmp (positivos[z], critica_aux) == 0){
                    	matriz[retorno].positivos++;
                    
          				}
        		}
                
                for (int z=0; z<12; z++){ //semelhante ao anterior, porem para comentarios negativos
                	if (strcmp (negativos[z], critica_aux) == 0){
                    	matriz[retorno].negativos++;
                    
                  	}
                }
                
                for (int k=0; k<3; k++){ //caso o comentario seja um inversor, sera verificado se as palavras que o acompanham e positiva ou negativa
                	if (strcmp(critica_aux, pol[k]) == 0){
                    	for (int l = 0; l<3; l++){
                      	scanf("%s", critica_aux);
                      	strcpy(matriz[retorno].criticas[w+a], critica_aux);
                      	w++;
        
                        for (int z=0; z<12; z++){ 
                          if (strcmp (positivos[z], critica_aux) == 0){ //em caso positivo, inverte e atribui aos negativos
                            matriz[retorno].negativos++;
                            
                          }
                        }
                          
                      for (int z=0; z<12; z++){ 
                        if (strcmp (negativos[z], critica_aux) == 0){ //em caso negativos, inverte e atribui aos positivos
                          matriz[retorno].positivos++; 
                        }
                      }
                    }
                      
                  }
                  
                }
          }
          retorno = -1;
          a=0;
        }
    }

  for (int i = 0; i< perguntas; i++){
    scanf ("%s", tipo_perg);
    
        
	  if (strcmp(tipo_perg, "quantos") == 0 || strcmp(tipo_perg, "palavra") == 0){
	    if (strcmp(tipo_perg, "palavra") == 0){ //verifica se o tipo e 1 ou 2
	      scanf ("%s", critica_aux);           
	      scanf (" %s", prod_aux);
        
	
	      if (strcmp(prod_aux, "em") == 0){ //evita que em seja considerado na definicao da pergunta
	        scanf ("%s", prod_aux);
	        scanf ("%s", marca_aux);
	        strcat (prod_aux, marca_aux);
      
		    for (int n=0; n<frases; n++){
		        if  (strcmp (prod_aux, matriz[n].nome) == 0){ //verifica qual o produto esta sendo referido
		        	retorno = n;
		        }
		      }
		      
        	int j = 0;

		    while (strcmp(matriz[retorno].criticas[j], "\0") != 0){
		        if (strcmp(critica_aux, matriz[retorno].criticas[j]) == 0){ //contabiliza as ocorrencias da palavra nos comentarios do produto
		            resultado++;
	              
		        }
              	j++;
		    }
            printf("%d\n", resultado);
            resultado = 0;
	        }
	    }

	    else if (strcmp(tipo_perg, "quantos") == 0){
	      scanf ("%s", critica_aux); //semelhante ao anterior       
	      scanf ("%s", prod_aux);
	
		    if (strcmp(prod_aux, "em") == 0){
		        scanf ("%s", prod_aux);
		        scanf (" %s", marca_aux);
		        strcat (prod_aux, marca_aux);       
		                
		        for (int n=0; n<frases; n++){
		            if  (strcmp(prod_aux, matriz[n].nome) == 0){
		            	retorno = n;
		            }
		        }
		
		          
		
		        pos = matriz[retorno].positivos; //verifica o contador de positivos e negativos
		        neg = matriz[retorno].negativos;
		
		        if (strcmp(critica_aux, "positivos") == 0){ //reotorna a porcentagem entre positivos e negativos
		            printf("%.1f%%\n", ((pos / (pos+neg)*100)));
		        }
		        else if (strcmp(critica_aux, "negativos") == 0){
		            printf ("%.1f%%\n", ((neg / (pos+neg)*100)));
		        }
		
		        pos = 0; 
		        neg = 0;
		    }
	    }
    }
  }

liberar(matriz);

return 0;
} 
        
    
