/*Fernando Cincinato Alves de Oliveira
Nº USP:11275213
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*** aloca_e_le_comentarios(unsigned int num_coment, char *** coment);
char*** aloca_e_le_perguntas(unsigned int num_perg, char *** perg);
void processamento_da_pergunta(char*** coment,char*** perg,unsigned int num_perg,unsigned int num_coment);
void Bow(char*** perg, char*** coment, short int i, short int num_coment);
void liberar_matriz(char***coment, char*** perg, unsigned int num_coment, unsigned int num_perg);


char*** aloca_e_le_comentarios(unsigned int num_coment, char *** coment){
	/*coment->matriz de 3 dimensoes;
	 * 1ª dimensao: faz a passagem entre os comentarios;
	 * 2ª dimensao: faz a passagem entre as palavras do comentario;
	 * 3ª dimensao: armazena cada letra das palavras;
	 */
	coment=(char***)malloc(num_coment*sizeof(char**));
	for(int i=0;i!=num_coment;i++){
		coment[i]=(char**)malloc(23*sizeof(char*));       //coment[i] guarda 23 strings: 2 para o produto e marca, 1 para o ';' e 20 para as strings do comentario
		for(int j=0;j<23;j++){
			coment[i][j]=(char*)malloc(20*sizeof(char));  //a string coment[i][j] tem espaço para os 19 caracteres + o caracter de fim de comentario 'Ø'; 
			scanf("%s", coment[i][j]);
			if(strcmp(coment[i][j], "Ø")==0){
				break;
			}
		}
	}
	return (coment);
}


char*** aloca_e_le_perguntas(unsigned int num_perg, char *** perg){
	/*coment->matriz de 3 dimensoes;
	 * 1ª dimensao: faz a passagem entre as perguntas;
	 * 2ª dimensao: faz a passagem entre as palavras da pergunta;
	 * 3ª dimensao: armazena cada letra das palavras;
	 */
	perg=(char***)malloc(num_perg*sizeof(char**));
	
	for(int i=0;i!=num_perg;i++){
		perg[i]=(char**)malloc(5*sizeof(char*));    //cada pergunta só tem 5 palavras, por isso o perg[i] é definido 
		for(int j=0;j<5;j++){
			perg[i][j]=(char*)malloc(20*sizeof(char));
			scanf("%s", perg[i][j]);
		}
	}
	return (perg);
}


void Bow(char*** perg, char*** coment, short int i, short int num_coment){
	float cont_de_setencas_aceitas=0., res=0., qtd=0.; //variaveis que recebem valores para calcular a qtd de positivos ou negativos
	
	short int k, y, j;      //contadores utilizados
	short int flag=0; //variavel que recebe um determinado valor para interromper um for. Funciona como um segundo break;
	
	char positivos[]={"positivos"};
	
	//vetores de strings que armazenam as palavras positivas ou negativas:
	char positivo[12][12] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char negativo[12][10] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	
	if(strcmp(perg[i][1],positivos)==0){
		for(k=0;k!=num_coment;k++){
		    flag=0;
			if(strcmp(coment[k][0],perg[i][3])==0 && strcmp(coment[k][1],perg[i][4])==0){ //o if busca o produto da marca selecionado pela pergunta
				cont_de_setencas_aceitas+=1.;
				for(j=3;j<22;j++){
					for(y=0;y<12;y++){
					    if(strcmp(coment[k][j], "Ø")==0){
					        flag=1;
							break;
						}
						else if(strcmp(coment[k][j], positivo[y])==0){
							    qtd+=1.0;
							    flag=1;
							    break;
						        }
					}
				if(flag==1)
				    break;
				}
			}
		}
	if(cont_de_setencas_aceitas==0){ //previne que nao ocorra uma divisao por zero
		printf("0\n");
	}
	
	else{
		res=(qtd*100/cont_de_setencas_aceitas);
		printf("%.1f%%\n", res);
	}
	}
	else{ //analogo ao que foi feito no if
		for(k=0;k!=num_coment;k++){
		    flag=0;
			if(strcmp(coment[k][0],perg[i][3])==0 && strcmp(coment[k][1],perg[i][4])==0){
			    cont_de_setencas_aceitas+=1.;
				for(j=3;j<22;j++){
					for(y=0;y<12;y++){
						if(strcmp(coment[k][j], "Ø")==0){
						    flag=1;
							break;
						}
						else if(strcmp(coment[k][j], negativo[y])==0){
						    	qtd+=1.;
							    flag=1;
							    break;
						    }
					}
				if(flag==1)
				    break;
				}		
			}
		}
	if(cont_de_setencas_aceitas==0){
		printf("0\n");
	}
	else{
		res=(qtd*100/cont_de_setencas_aceitas);
		printf("%.1f%%\n", res);
	}
	}
}


void processamento_da_pergunta(char*** coment,char*** perg,unsigned int num_perg,unsigned int num_coment){
	short int cont_de_palavra_buscada=0;
	short int j, k;
	for(short int i=0;i!=num_perg;i++){
		/*a primeira palavra da pergunta começa sempre com 'palavra' ou com 'quantos'*/
		if(strcmp(perg[i][0],"palavra")==0){
			cont_de_palavra_buscada=0;
			for(k=0;k!=num_coment;k++){
				if(strcmp(coment[k][0],perg[i][3])==0 && strcmp(coment[k][1],perg[i][4])==0){
					for(j=3;j<22;j++){ //analise comeca na quarta palavra, por isso o j começa em 3, considerando que o vetor inicia em zero
						if(strcmp(coment[k][j],perg[i][1])==0)
							cont_de_palavra_buscada++;
						else if(strcmp(coment[k][j],"Ø")==0)
								break;
					}
				}
			}
			printf("%hd\n", cont_de_palavra_buscada);
		}
		else{
			Bow(perg,coment,i, num_coment);
		}
	}
}


void liberar_matriz(char***coment, char*** perg, unsigned int num_coment, unsigned int num_perg){
	short int i, j;
	for(i=num_coment-1;i>=0;i--){
		for(j=21;j>=0;j--){
			free(coment[i][j]);
		}
		free(coment[i]);
	}
	for(i=num_perg-1;i>=0;i--){
		for(j=4;j<=0;j--){
			free(perg[i][j]);
		}
		free(perg[i]);
	}
	free(coment);
	free(perg);
}


int main(void){
	unsigned int num_coment, num_perg;
	char ***coment=NULL, ***perg=NULL;

	scanf("%u %u", &num_coment, &num_perg);
	
	coment=aloca_e_le_comentarios(num_coment,coment);            // lendo e alocando os comentarios na heap
	perg=aloca_e_le_perguntas(num_perg,perg);                    // lendo e alocando as perguntas na heap
	processamento_da_pergunta(coment,perg,num_perg,num_coment);  //processando as perguntas
	liberar_matriz(coment,perg, num_coment, num_perg);           //liberando o espaço alocado
	return 0;
}