/****************************	
* Nome: Larissa F. Medina	
* NUSP: 9770570					
****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXBOW 200

/*	struct bow: estrutura para guardar uma bag of words
		char produto = nome do produto
		char indice[200] = palavras do indice da BoW
		int bagofwords[MAXBOW] = a bag of words em si
		char comentarios[30] = todos os comentarios de um produto
*/
struct bow{
	char produto[50];
	char indice[MAXBOW][20];
	int bagofwords[MAXBOW];
	char comentarios[30][200];
};

/*	int posicaoproduto: função que retorna a posição de um determinado produto em um vetor de produtos
		struct bow prod[] = vetor de produtos
		char* pr = nome do produto
	Retorna a posição do produto ou -1 se o produto não foi achado
*/
int posicaoproduto(struct bow prod[], char* pr){
	for(int i = 0; i < 10; i++){
		if(strcmp(pr,prod[i].produto) == 0){
			return i;
		}
	}
	return -1;
}

/*	int posicaopalavra: função que retorna a posição de uma determinada palavra em um vetor indice
		char indice[] = vetor de palavras que compoem o indice da BoW
		char* word = palavra a ser pesquisada
	Retorna a posição da palavra no indice ou -1 se a palavra não foi achada
*/
int posicaopalavra(char indice[][20], char* word){
	for(int i = 0; i < 200; i++){
		if(strcmp(word,indice[i]) == 0){
			return i;
		}
	}
	return -1;
}

/*	int qtdcomentarios: função que retorna a quantidade de comentários de um determinado produto
		struct bow prod[] = vetor de produtos
		int k = posição do produto que queremos saber a quantidade de comentários sobre
	Retorna a quantidade de comentários (1 a ...) ou -1 se não tiver comentários
*/
int qtdcomentarios(struct bow prod[], int k){
	for(int i = 0; i < 30; i++){
		if(prod[k].comentarios[i][0] == '\0'){
			return i;
		}
	}
	return -1;
}

/*	int qtdpalavrasindice: função que retorna a quantidade de palavras distintas de um determinado indice da BoW
		char indice[] = indice a ser lido
	Retorna a quantidade de palavras que o indice possui (1 a ...) ou -1 se não tiver comentários
*/
int qtdpalavrasindice(char indice[][20]){
	for(int i = 0; i < 200; i++){
		if(strcmp(indice[i],"") == 0){
			return i;
		}
	}
	return -1;
}

/*	void gerarbagofwords: função que gera o indice e o bag of words a partir dos comentários de um produto
		struct bow prod[] = vetor de produtos
		int n = número de produtos 
	O indice e a bag of words são guardadas na struct prod[]
*/
void gerarbagofwords(struct bow prod[], int n){
	for(int i = 0; i < n; i++){
		int posind = 0;		//acumulador que guarda a posição do indice
		//passa por todos os comentários
		for(int j = 0; j < qtdcomentarios(prod,i); j++){	
			char entrada[200];			//buffer para guardar o comentário
			memset(entrada,'\0',200);	//limpa o buffer
			strcpy(entrada,prod[i].comentarios[j]);	//copia o comentário para o buffer
			//separa o buffer em várias palavras
			char *token = strtok(entrada," ");		
			for(int k = 0; k < 21; k++){
				//se tiver alguma palavra
				if(token){
					//verifica se a palavra já está no indice. Se não tiver,
					if(posicaopalavra(prod[i].indice,token) == -1){
						strcpy(prod[i].indice[posind],token);		//copia a palavra para o indice
						prod[i].bagofwords[posind]++;				//incrementa sua contagem na bagofwords
						posind++;									//incrementa o acumulador da posição do indice
					}
					//Se já tiver no indice,
					else{
						//incrementa sua contagem na bagofwords
						prod[i].bagofwords[posicaopalavra(prod[i].indice,token)]++;
					}
				}
				token = strtok(NULL," ");	
			}
		}
	}
}

/*	int procuranabow: procura a quantidade de vezes que a palavra_alvo foi encontrada nos comentários do produto_alvo
		struct bow prod[] = vetor de produtos
		char* produto_alvo = nome do produto a ser pesquisado
		char* palavra_alvo = nome da palavra a ser pesquisada
	Retorna a quantidade de vezes que a palavra foi encontrada nos comentários de certo produto
*/
int procuranabow(struct bow prod[], char* produto_alvo, char* palavra_alvo){
	int qtd = 0;		//inteiro que guarda a quantidade de vezes que a palavra foi encontrada
	//passa pelos 10 possíveis produtos
	for(int i = 0; i < 10; i++){
		//se encontrar o produto
		if(strcmp(produto_alvo,prod[i].produto) == 0){
			//passa pelo indice do produto
			for(int j = 0; j < 200; j++){
				//se encontrar a palavra no indice,
				if(strcmp(palavra_alvo,prod[i].indice[j]) == 0){
					qtd = prod[i].bagofwords[j];	//retorna a quantidade de vezes que a palavra foi encontrada nos comentários (via bagofwords)
					return qtd;
				}
			}
		}
	}
	return qtd;
}

/*	float reviewbow: procura a porcentagem de vezes que o produto foi classificado como negativo ou positivo
		struct bow prod[] = vetor de produtos
		char* produto_alvo = nome do produto a ser pesquisado
		char* review_alvo = pode ser "negativos" ou "positivos"
	Retorna a porcentagem de vezes que o produto foi classificado como negativo ou positivo
*/
float reviewbow(struct bow prod[], char* produto_alvo, char* review_alvo){
	//a lista das palavras negativas
	char listanegativa[12][10] = {"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
	//a lista das palavras positivas
	char listapositiva[12][12] = {"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};	
	float porcentagem = 0.0;		//numero de ponto flutuante que guarda a porcentagem de vezes
	int achoupalavra = 0;			//inteiro que guarda a quantidade de vezes que as palavras de alguma lista foram achadas nos comentários
	//passa pelos 10 possíveis produtos
	for(int i = 0; i < 10; i++){
		//se encontrar o produto
		if(strcmp(produto_alvo,prod[i].produto) == 0){
			//se quiser saber dos reviews negativos
			if(strcmp(review_alvo,"negativos") == 0){
				//passa por todos os comentários
				for(int j = 0; j < qtdcomentarios(prod,i); j++){		
					char comentario[200];						//buffer que guarda o comentário
					memset(comentario,'\0',200);				//limpa o buffer
					strcpy(comentario,prod[i].comentarios[j]);	//copia o comentário para o buffer
					//separa o buffer em várias palavras
					char *token = strtok(comentario," ");
					for(int k = 0; k < 20; k++){
						//se existe alguma palavra
						if(token){
							//passa pela lista negativa
							for(int l = 0; l < 12; l++){
								//se achou a palavra na lista negativa,
								if(strcmp(listanegativa[l],token) == 0){
									achoupalavra++;		//incrementa a quantidade de vezes que as palavras da lista negativa foram achadas
									k = 20;				//para passar pro próximo comentário
									break;				//para parar de comparar com a lista
								}
							}
						}
					token = strtok(NULL," ");	
					}
				}
			}
			//se quiser saber dos reviews positivos
			else if(strcmp(review_alvo,"positivos") == 0){
				//passa por todos os comentários
				for(int j = 0; j < qtdcomentarios(prod,i); j++){		
					char comentario[200];						//buffer que guarda o comentário
					memset(comentario,'\0',200);				//limpa o buffer
					strcpy(comentario,prod[i].comentarios[j]);	//copia o comentário para o buffer
					//separa o buffer em várias palavras
					char *token = strtok(comentario," ");	
					for(int k = 0; k < 20; k++){
						//se existe alguma palavra
						if(token){
							//passa pela lista positiva
							for(int l = 0; l < 12; l++){
								//se achou a palavra na lista positiva,
								if(strcmp(listapositiva[l],token) == 0){
									achoupalavra++;		//incrementa a quantidade de vezes que as palavras da lista negativa foram achadas
									k = 20;				//para passar pro próximo comentário
									break;				//para parar de comparar com a lista
								}
							}
						}
					token = strtok(NULL," ");	
					}
				}
			}
			//se achou alguma palavra em alguma lista, 
			if(achoupalavra != 0){
				//calcula a porcentagem
				porcentagem = (float)achoupalavra / (float)qtdcomentarios(prod,i);
			}
			return porcentagem;
		}
	}
	return porcentagem;
}

int main(){
	/****************************	
	* DECLARAÇÃO DE VARIÁVEIS
	* i, j, k = para loops for
	* nsentencas = numero de sentencas
	* nperguntas = numero de perguntas
	* passou = bool se passou do produto para o comentário
	* nprodutos = numero de produtos
	* retorno1 = inteiro para a resposta para a pergunta 1
	* retorno2 = numero de ponto flutuante para a resposta para a pergunta 2
	* entrada = string para receber as linhas de entrada
	* produto = string para receber o nome do produto
	* comentario = string para receber o comentário
	* produto_alvo = string para receber o produto alvo
	* review_alvo = string para receber as palavras "negativos" ou "positivos"
	* palavra_alvo = string para receber a palavra alvo 
	****************************/
	int i, j, k, nsentencas = 0, nperguntas = 0, passou = 0, nprodutos = 0, retorno1 = 0;
	float retorno2 = 0.0;
	char entrada[200], produto[50], comentario[200], produto_alvo[50], review_alvo[20], palavra_alvo[20];

	//limpa a string da entrada
	memset(entrada,'\0',200);

	//le a primeira linha da entrada
	fgets(entrada,200,stdin);

	//funcao para ler os numeros de sentenças e de perguntas
	char *token = strtok(entrada, " ");
	for(i = 0; i < 2; i++){
		if(i == 0 && token){
			nsentencas = strtol(token,NULL,10);
		}
		if(i == 1 && token){
			nperguntas = strtol(token,NULL,10);
		}
		token = strtok(NULL," ");	
	}

	//cria a struct com o vetor de produtos
	struct bow prod[10];

	//loop para limpar e zerar a struct acima
	for(i = 0; i < 10; i++){
		//limpa o produto
		memset(prod[i].produto,'\0',50);
		//limpa os indices
		for(j = 0; j < 200; j++){
			memset(prod[i].indice[j],'\0',20);
		}
		//limpa os comentarios
		for(j = 0; j < 30; j++){
			memset(prod[i].comentarios[j],'\0',200);
		}
		//zera os contadores da bag
		for(j = 0; j < MAXBOW; j++){
			prod[i].bagofwords[j] = 0;
		}
	}

	//le as sentencas de entrada
	for(i = 0; i < nsentencas; i++){
		//limpa as strings da entrada, dos produtos e dos comentarios
		memset(entrada,'\0',200);
		memset(produto,'\0',50);
		memset(comentario,'\0',200);
		
		//le a primeira linha da entrada
		scanf("%[^Ø]Ø\n",entrada);

		//Volta pro nome do produto
		passou = 0;
		
		//loop para ler todas as palavras de uma sentença
		token = strtok(entrada," ");
		for(j = 0; j < 25; j++){
			//verifica se o comentário acabou
			if(!token){
				break;
			}
			//para verificar se tá lendo produto ou comentário
			if(strcmp(token,";") == 0){
				passou = 1;
				token = strtok(NULL," ");	
				continue;
			}
			//vai concatenando as palavras que foram lidas no nome do produto
			if(!passou && token){
				strcat(produto,token);
				strcat(produto," ");
			}
			//vai concatenando as palavras que foram lidas no comentário
			else if(passou && token){
				strcat(comentario,token);
				strcat(comentario," ");
			}
			token = strtok(NULL," ");		
		}

		//para tirar o espaço do final dos produtos
		if(produto[strlen(produto)-1] == ' '){
			produto[strlen(produto)-1] = '\0';
		}
		//para tirar o espaço do final dos comentarios
		if(comentario[strlen(comentario)-1] == ' '){
			comentario[strlen(comentario)-1] = '\0';
		}

		//se esse produto não apareceu ainda
		if(posicaoproduto(prod,produto) == -1){
			strcpy(prod[nprodutos].produto,produto);			//coloca o nome do produto no vetor de produtos
			strcpy(prod[nprodutos].comentarios[0],comentario);	//coloca o comentário nos comentários do vetor de produtos
			nprodutos++;										//incrementa a quantidade de produtos distintos
		}
		//se esse produto já apareceu
		else{
			//coloca o comentário no final dos comentários do vetor de produtos
			strcpy(prod[posicaoproduto(prod,produto)].comentarios[qtdcomentarios(prod,posicaoproduto(prod,produto))],comentario);
		}	
		
	}

	//gera o indice e a bag-of-words a partir dos comentarios, para cada produto
	gerarbagofwords(prod, nprodutos);
	
	//vetor de palavras em cada pergunta
	char palavras[nperguntas][10][25];

	//le as perguntas de entrada
	for(i = 0; i < nperguntas; i++){
		//limpa as palavras da pergunta
		for(j = 0; j < 10; j++){
			memset(palavras[i][j],'\0',25);
		}

		//limpa as strings da entrada, dos produtos e dos comentarios
		memset(entrada,'\0',200);

		//le a primeira linha da entrada
		fgets(entrada,200,stdin);
		
		//loop para ler todas as palavras da pergunta
		token = strtok(entrada," ");
		for(j = 0; j < 10; j++){
			//verifica se a pergunta acabou
			if(!token){
				break;
			}
			//se nao acabou ainda, adiciona a palavra
			else{
				strcpy(palavras[i][j],token);
			}

			token = strtok(NULL," ");		
		}
	}

	//para tirar os \n ou \r das palavras
	for(i = 0; i < nperguntas; i++){
		for(j = 0; j < 10; j++){
			for(k = 0; k < 25; k++){
				//se o char for '\n' ou '\r', trocar por '\0'
				if(palavras[i][j][k] == '\n' || palavras[i][j][k] == '\r'){
					palavras[i][j][k] = '\0';
					break;
				}
			}
		}
	}


	//interpreta a pergunta
	for(i = 0; i < nperguntas; i++){
		//limpa as strings
		memset(produto_alvo,'\0',50);
		memset(review_alvo,'\0',20);
		memset(palavra_alvo,'\0',20);	
		
		//caso a pergunta for relacionada a alguma palavra específica
		if(strcmp(palavras[i][0],"palavra") == 0){
			//le a palavra alvo (segunda palavra da pergunta)
			strcpy(palavra_alvo,palavras[i][1]);
			//passa lendo o produto_alvo
			for(j = 0; j < 5; j++){
				//ve se existe uma palavra. Se existir,
				if(strcmp(palavras[i][j+3],"") != 0){
					strcat(produto_alvo,palavras[i][j+3]);	//concatena ela no nome do produto
					strcat(produto_alvo," ");				//concatena um espaço no nome do produto
				}
				//se nao existir, sai do for
				else{
					break;
				}
			}
			//verifica se tem um espaço no final da string produto_alvo
			if(produto_alvo[strlen(produto_alvo)-1] == ' '){
				produto_alvo[strlen(produto_alvo)-1] = '\0';
			}

			//procura quantas vezes a palavra alvo foi encontrada nos comentários do produto alvo
			retorno1 = procuranabow(prod,produto_alvo,palavra_alvo);
				
			//printa esse resultado
			printf("%d\n",retorno1);
		
		}
		//caso a pergunta for relacionada a quantas pessoas estão falando bem ou mal
		else if(strcmp(palavras[i][0],"quantos") == 0){
			//le o review alvo (se é negativos ou positivos)
			strcpy(review_alvo,palavras[i][1]);
			//passa lendo o produto_alvo
			for(j = 0; j < 5; j++){
				//ve se existe uma palavra. Se existir,
				if(strcmp(palavras[i][j+3],"") != 0){
					strcat(produto_alvo,palavras[i][j+3]);	//concatena ela no nome do produto
					strcat(produto_alvo," ");				//concatena um espaço no nome do produto
				}
				//se nao existir, sai do for
				else{
					break;
				}
			}
			//verifica se tem um espaço no final da string produto_alvo
			if(produto_alvo[strlen(produto_alvo)-1] == ' '){
				produto_alvo[strlen(produto_alvo)-1] = '\0';
			}

			//calcula a porcentagem de vezes que o produto alvo recebeu um review negativo ou positivo
			retorno2 = reviewbow(prod,produto_alvo,review_alvo);

			//printa esse resultado
			printf("%.1f%%\n",retorno2*100);
		}
		//caso nao foi possível identificar a pergunta
		else{
			fprintf(stderr,"\nNao foi possivel identificar a pergunta %d.\n",i);
		}
	}

	return 0;
}
