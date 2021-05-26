#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Prot�tipos de Fun��o
void livra_matriz(int **l, int i);
int **abre_arquivo(char c[10], int NxM[2]);
int **leitura_arquivo(char c[10],int NxM[2]);
int **avalia_pixels(int *tamanhoNxM, int **l, int **m, int **n, int K);
void imprime_pixels (int **n, int *NxM);

void livra_matriz(int **l, int i){
	int k;                              //   Esta fun��o livra da mem�ria heap a matriz "l",
	                                    // com "i" linhas. 
	for (k = 0; k < i; k++)
		free(l[k]);
	
	free(l);
	
	return;
}

int **leitura_arquivo(char c[10],int NxM[2]){
	FILE *fp;
	int **matriz_arquivo;
	char letra;
	int i=0, j=0, k, numero;
	
	if (c[6] == '.'){
		if (c[5] == '1')
			if((fp = fopen("teste1.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");				//    Recebidos o nome do arquivo e o ponteiro "NxM", se seleciona o arquivo a ser aberto,
		if (c[5] == '2')											//  atrav�s da posi��o de cada caractere digitado.
			if((fp = fopen("teste2.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");				//   Quando se confirma o nome do arquivo, ocorre a abertura do mesmo no ponteiro "fp".
		if (c[5] == '3')
			if((fp = fopen("teste3.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
		if (c[5] == '4')
			if((fp = fopen("teste4.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
		if (c[5] == '5')
			if((fp = fopen("teste5.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
		if (c[5] == '6')
			if((fp = fopen("teste6.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
		if (c[5] == '7')
			if((fp = fopen("teste7.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
		if (c[5] == '8')
			if((fp = fopen("teste8.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
		if (c[5] == '9')
			if((fp = fopen("teste9.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
	}
	else{
		if (c[6] == '0')
			if((fp = fopen("teste10.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
		if (c[6] == '1')
			if((fp = fopen("teste11.pgm", "r")) == NULL)
				printf("Erro ao abrir o arquivo\n");
	}

	fscanf(fp, "%c%d", &letra, &numero);									//   Ignora-se a primeira linha .
	fscanf(fp, "%d %d", &NxM[0], &NxM[1]);									//   Na segunda linha, se obt�m o n�mero de linhas e colunas da matriz que representa a imagem. Os valores s�o guardados no vetor "NxM[2]".
	fscanf(fp, "%d", &numero);												//	 Ignora-se a terceira linha.

	if ((matriz_arquivo = (int**)malloc(NxM[1] * sizeof(int*))) == NULL)    //   Dadas as dimens�es da matriz da imagem, alocada-se dinamicamente uma matriz
		exit(1);														    // de mesmo n�mero de linhas e colunas.
	
	for (k = 0; k < NxM[1]; k++)
		if ((matriz_arquivo[k] = (int*)malloc(NxM[0] * sizeof(int))) == NULL)
			exit(1);

	while ((fscanf(fp, "%d", &numero)) != EOF){

		matriz_arquivo[i][j] = numero;										//   Havendo ainda valores a se ler, os valores do arquivo s�o guardados, na matriz alocada anteriormente.
																			
		j++;																
		if (j == NxM[0]){
			i++;
			j=0;
		}
		if (i == NxM[1])
			break;

	}

	fclose(fp); 															//    Havendo guardadas as informa��es �teis do arquivo, n�o havendo mais necessidade de utilizar o arquivo,
																			//  o mesmo se encerra nesse trecho.
	return matriz_arquivo;													//    A matriz "matriz_arquivo" � retornada na matriz "l" da main.		
}

int **avalia_pixels(int *tamanhoNxM, int **l, int **m, int **n, int K){
	int i, j, k, a;
	int soma;
	float count = 1;
	int **direcao;
	
	if ((direcao = (int**)malloc(tamanhoNxM[1] * sizeof(int*))) == NULL)		//   A matriz "direcao", com mesmas dimens�es de "l", possui papel fundamental no programa.
		exit(1);
	
	for (k = 0; k < tamanhoNxM[1]; k++)
		if ((direcao[k] = (int*)malloc(tamanhoNxM[0] * sizeof(int))) == NULL)
			exit(1);			
	
	for (i = 0; i < tamanhoNxM[1]; i++)											//   Seu conte�do foi preenchido pelo n�mero inteiro '8', apenas por conveni�ncia.
		for (j = 0; j < tamanhoNxM[0]; j++)
			direcao[i][j] = 8;
	
	for (a = 0; a < K; a++ ){
		int sinal;
		sinal = 0;																//	"i" e "j" assumem a posi��o tocada pelo usu�rio.
		
		i = m[a][0];	
		j = m[a][1];
		if (n[i][j] != 0)														//   Caso n[i][j], antes preenchida por '0', n�o contenha '0' na posi��o de toque,
			continue;															//  descarta-se a senten�a atual e se avan�a para a pr�xima.
		
		n[i][j] = a + 1;														//   Caso seja '0', a posi��o n[i][j] recebe o n�mero "a + 1".

		soma = l[i][j];															//   "soma" se inicia com o valor do pixel inicial, e count com o float '1'.

		count = 1;
																						//	Para o entendimento desse trecho, precisa-se entender o papel da matriz "direcao".
																						//  A matriz "direcao", que possui as mesmas dimens�es da matriz "l", aponta para a posi��o onde
		while (sinal != 2){																// o pixel passou no "teste da m�dia". Caso o pixel que passou no teste se encontra acima do pixel sendo avaliado,
																						// na posi��o "i" "j" do pixel avaliado, a matriz "direcao" recebe valor '0'. O mesmo ocorre se o pixel que passou no teste se encontrar na direita '1',
			int up, left, down, right;													// baixo '2', e esquerda '3'. Desta forma, se obt�m o sentido por onde se percorreu a matriz "n".
			up = left = down = right = 0;												//	Os valores tamb�m indicam os sentidos que ainda n�o foram avaliados, como '0', que faltam os sentidos '1', '2' e '3'.
																		//				    2                           0
			if (direcao[i][j] == 4){									//			1 --->	X  <--- 3             3 <--------> 1
				sinal = 0;												//				    0	                        2
				if (j != 0 && direcao[i][j-1] == 1){									//  Dado o valor '4', "i" e "j" retrocedem para o pixel que o avaliou. As vari�veis "up", "left", "down" e "right" impedem
					up = left = 1;														// que sejam avaliados novamente o "teste da m�dia" para quando se j� avaliou. Como para '2', que j� foram avaliados os sentidos
					j--;																// '0', '1' e '2'.
					sinal = 1;
				}
				if (sinal == 0 && i != tamanhoNxM[1] - 1 && direcao[i+1][j] == 0){
					up = 1;
					i++;
					sinal = 1;
				}	
				if (sinal == 0 && j != tamanhoNxM[0] - 1 && direcao[i][j+1] == 3){
					up = left = down = right = 1;
					j++;
					sinal = 1;
				}
				if (sinal == 0 && i != 0 && direcao[i-1][j] == 2){
					up = left = down = 1;
					i--;
					sinal = 1;
				}
				sinal = 1;
			}
			
			
			if (i != 0 && n[i-1][j] == 0 && up == 0){
				if (sqrt(pow(l[i-1][j] - soma/count, 2)) <= m[a][2] && direcao[i-1][j] == 8){		//	Exclui-se o "teste da m�dia" para certos valores, como os indicativos (up, left, right, down, quando s�o igual a 1)
					soma += l[i-1][j];																// e para as linhas e colunas nas extremidades da matriz.
					count++;
					direcao[i][j] = 0;																//  Realiza-se o teste, caso positivo, "direcao" recebe o valor do sentido
					n[i-1][j] = a + 1;																// para onde o pixel se encontra, "n" recebe o valor inteiro "a + 1", e a posi��o "i" e "j" se locomovem para o pixel.
					i--;
					continue;
				}
			}
			if (j != tamanhoNxM[0] - 1 && n[i][j+1] == 0 && left == 0){
				if (sqrt(pow(l[i][j+1] - soma/count, 2)) <= m[a][2] && direcao[i][j+1] == 8){
					soma += l[i][j+1];
					count++;
					direcao[i][j] = 1;
					n[i][j+1] = a + 1;
					j++;
					continue;
				}	
			}
			if (i != tamanhoNxM[1] - 1 && n[i+1][j] == 0 && down == 0){
				if (sqrt(pow(l[i+1][j] - soma/count, 2)) <= m[a][2] && direcao[i+1][j] == 8){
					soma += l[i+1][j];
					count++;
					direcao[i][j] = 2;
					n[i+1][j] = a + 1;
					i++;
					continue;
				}	
			}
			if (j != 0 && n[i][j-1] == 0 && right == 0){
				if (sqrt(pow(l[i][j-1] - soma/count, 2)) <= m[a][2] && direcao[i][j-1] == 8){
					soma += l[i][j-1];
					count++;
					direcao[i][j] = 3;
					n[i][j-1] = a + 1;
					j--;
					continue;
				}
			}
			direcao[i][j] = 4;																		//   Caso nenhuma dire��o passe no teste, em "direcao[i][j]" se deposita o valor '4'.
				
			if (direcao[i][j] == 4 && sinal == 1 && i == m[a][0] && j == m[a][1] )					//   Retornando para a posi��o de origem, e tendo como valor de "direcao[i][j]" igual a '4', 
				sinal = 2;																			//  o "while" rompe, para a avalia��o da pr�xima senten�a.
		}

		
	}
	livra_matriz(direcao, tamanhoNxM[1]);							//   Se livra a mem�ria da heap ocupada pela matriz "direcao", ap�s seu uso intensivo.
	
	return n;														//   A matriz "n" retorna contendo o valor de diferentes segmentos depositados.
}

void imprime_pixels (int **n, int *NxM){
	int i, j;
	
	for (i = 0; i < NxM[1]; i++){
		for(j = 0; j < NxM[0]; j++){
			if (n[i][j] != 0){
				if (i != 0 && n[i-1][j] != n[i][j]){
					printf("(%d, %d)\n", i, j);								//	A fun��o "imprime_pixels" percorre a matriz "n" procurando "bordas" 
					continue;												// de n�meros diferentes ao pixel atual. 
				}
				if (j != NxM[0] - 1 && n[i][j + 1] != n[i][j]){				//  Imprime-se a posi��o "i" "j" dos valores onde "n[i][j]" � a "borda".
					printf("(%d, %d)\n", i, j);
					continue;
				}
				if (i != NxM[1] - 1 && n[i+1][j] != n[i][j]){
					printf("(%d, %d)\n", i, j);
					continue;
				}
				if (j != 0 && n[i][j-1] != n[i][j]){
					printf("(%d, %d)\n", i, j);
					continue;
				}
			}
			if (n[i][j] == 0){

				if (i != 0 && n[i-1][j] != 0){								//  Caso "n[i][j]" seja '0', se avalia caso haja algum n�mero diferente de '0' nas proximidades do pixel.
					printf("(%d, %d)\n", i, j);								//	Sendo afirmativo, imprime-se a posi��o "i" "j" desse pixel.
					continue;
				}

				if (j != NxM[0] - 1 && n[i][j + 1] != 0){
					printf("(%d, %d)\n", i, j);
					continue;
				}
				if (i != NxM[1] - 1 && n[i+1][j] != 0){
					printf("(%d, %d)\n", i, j);
					continue;
				}
				if (j != 0 && n[i][j-1] != 0){
					printf("(%d, %d)\n", i, j);
					continue;
				}
			}
		}
		
	}
	return;
}

int main(void){
	char nome_arquivo[10];
	int K;
	int i, j, k;
	int tamanhoNxM[2];
	int **l, **m, **n;           
	
	scanf("%s", nome_arquivo);                                            //   O nome do arquivo, digitado pelo usu�rio, � guardado em uma
	scanf("%d", &K);                                                      // string de tamanho 10.

	if ((m = (int**)malloc(K * sizeof(int*))) == NULL)                    //   Dado o valor de "K" pelo usu�rio, � alocado dinamicamente
		exit(1);                                                          //  a matriz "m", que guarda as "K" linhas de entradas do
	                                                                      //  usu�rio, que representam a posi��o do toque e a intensidade 
	for (k = 0; k < K; k++)                                               //  do pixel a avaliar.
		if ((m[k] = (int*)malloc(3 * sizeof(int))) == NULL)
			exit(1);

	for(i = 0; i < K; i++)                                                //   O usu�rio digita as entradas, e o valor � guardado
		scanf("%d %d %d", &m[i][0], &m[i][1], &m[i][2]);                  // na matriz "m".
	
	l = leitura_arquivo(nome_arquivo, tamanhoNxM);                        //   As entradas de nome de arquivo e o ponteiro
																		  // "tamanhoNxM" entram como argumento da fun��o indicada.
	if ((n = (int**)malloc(tamanhoNxM[1] * sizeof(int*))) == NULL)
		exit(1);
	
	for (k = 0; k < tamanhoNxM[1]; k++)									  //   Foi alocado dinamicamente a matriz "n", que possui a mesma dimens�o
		if ((n[k] = (int*)malloc(tamanhoNxM[0] * sizeof(int))) == NULL)	  // de l. 
			exit(1);
	
	for (i = 0; i < tamanhoNxM[1]; i++)									  //   Seu conte�do � preenchido pelo n�mero inteiro '0'.
		for (j = 0; j < tamanhoNxM[0]; j++)
			n[i][j] = 0;
	

	
	n = avalia_pixels(tamanhoNxM, l, m, n, K);							  //   "n" recebe uma matriz trabalhada pela fun��o "avalia_pixels".

	imprime_pixels(n, tamanhoNxM);
	
	livra_matriz(l, tamanhoNxM[1]);										  //   Livra-se a mem�ria heap ocupada pelas matrizes "n", "l" e "m".
	livra_matriz(n, tamanhoNxM[1]);
	livra_matriz(m, K);
	
	return 0;
}
