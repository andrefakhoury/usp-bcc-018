#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//struct para bag of words
//sendo que o campo palavra tem 30 posicoes para seguranca
//o campo frequencia diz quantas vezes a palavra apareceu
//o campo linha eh um vetor de posicao, em que a linha que a palavra aparece, tem o indice do vetor setado como 1, caso contrario nada eh setado
typedef struct bow{
	char palavra[30];
	int frequencia;
	int *linha;
}bow;

//struct para armazenar dados do produto, sendo que tambem ha espaco alocado a mais por medida de seguranca
//nome eh o campo que o nome do produto eh armazenado
//positivo e negativo sao as frases positivas e negativas de determinado produto
//cada produto possui o seu proprio bag of words
typedef struct produto{
	char nome[50];
	float positivo;
	float negativo;
	bow bag[200];
}produto;


//declaracao da funcao "lerSentenca" para armazenamento dos comentarios
void lerSentenca(char **comentario,produto *prod, int indice, int qtdSentenca);
//declaracao da funcao "lerPergunta" para processar pergunta, e posteriormente realizar as funcoes para retorno da resposta
void lerPergunta(char **comentario,produto *prod, int qtdSentenca);
//funcao para alocar dinamicamente a primeira dimensao das matrizes de char do programa
//sendo o ponteiro de char passado como parametro, qtd1 como a primeira dimensao da matriz, e qtd2 como a segunda dimensao da matriz
void alocaChar1(char ***ponteiro,int qtd1, int qtd2);
//funcao para alocar dinamicamente a segunda dimensao das matrizes de char do programa, sendo qtd2 o tamanho da segunda dimensao da matriz
void alocaChar2(char **ponteiro, int qtd2);
//funcao para alocar struct produto
void alocaProduto(produto **prod, int qtd);
//funcao para alocar as linhas que a palavra de um bag of words pode aparecer
void alocaLinha(int **linha, int qtdLinha);
//funcao para escrever no vetor de struct bow de um determinado produto
void escreveBow(produto *prod,char *ptr,int boolean,int *cont,int indice, int qtdSentenca);
//funcao para calcular qual foi a frequencia de determinada palavra em relacao ao produto
int quantidadePalavra(produto *prod,char *aux);
//funcao para calcular a porcentagem de comentario positivos ou negativos de cada produto
float porcentagemAvaliacao(produto *prod, char *aux, int qtdSentenca);
//funcao para alocar e determinar todas as possiveis palavras positivas de um produto
void declaraVetorPositivos(char **vetorPositivos);
//funcao para alocar e determinar todas as possiveis palavras negativas de um produto
void declaraVetorNegativos(char **vetorNegativos);


int main(void){
	//variaveis para armazenar a quantidade de sentencas,e quantidade de perguntas respectivamente
	int qtdSentenca=0, qtdPergunta=0;
	//contador para o laco for
	int i=0;
	//declaracao do ponteiro para variavel auxiliar armazenar o comentario
	char **comentario;
	//declaracao do ponteiro para struct produto
	produto *prod;
	//alocando as 2 dimensoes de comentario, sendo 20 o numero maximo de palavras por frase, e 20 o tamanho de cada palavra
	alocaChar1(&comentario,1,380);
	//alocando struct na heap
	alocaProduto(&prod,10);
	//lendo quantas sentencas serao lidas e quantas perguntas
	scanf("%d %d", &qtdSentenca, &qtdPergunta);
	//ponteiro para auxiliar leitura de comentario, ela pode receber o nome de algum produto, mostrando que ele eh repetido e nao deve ser armazenado de novo
	//porem, caso a variavel retorne "NULL" em todos os casos, quer dizer que o produto ainda nao foi armazenado
	char *aux=NULL;
	alocaChar2(&aux,50);
	//variavel para outro laco for
	int j=0;
	//a variavel igual eh para determinar, se o nome do produto inserido, eh igual a de um produto existente
	//sendo o valor 0 indicativo de que nao ha produto igual, e 1 indicativo que o produto ja esta armazenado
	int igual=0;

	for(i=0;i<qtdSentenca;i++){
		j=0;
		igual=0;
		
		scanf(" %[^\n]s",comentario[0]);
		for(j=0;j<i;j++){
			aux=strstr(comentario[0],prod[j].nome);
			if(aux!=NULL){
				igual=1;
				break;
			}
		}
		//caso o produto ja esteja armazenado, a funcao para armazenar armazenar as palavras da sentenca no bag of words sera chamada com o indice do produto ja armazenado
		if(igual==1){
			lerSentenca(comentario,&prod[j],i,qtdSentenca);
		}
		//caso contrario, a mesma funcao eh chamada com um indice que ainda nao foi alocado
		else{
			lerSentenca(comentario,&prod[i],i,qtdSentenca);
		}
	}

	//laco for para ler as perguntas, e posteriormente fazer as devidas consultas e operacoes
	for(i=0;i<qtdPergunta;i++){
		scanf(" %[^\r\n]s",comentario[0]);
		lerPergunta(comentario,prod, qtdSentenca);
	}

	//liberando os ponteros alocados dinamicamente
	free(comentario[0]);
	free(comentario);
	free(prod);
	//erro desconhecido ao tentar liberar ponteiro aux, por isso comentado
	//free(aux);

	return 0;
}

//a seguir a definicao das funcoes
//para percorrer tanto as perguntas, quanto os comentarios, eh usada a funcao strtok_r, que separa a frase de acordo com um delimitador especifico
//foi usada a funcao strtok_r ao inves da strtok pois esta acaba causando muitos bugs se usada mais de uma vez

//a funcao ler pergunta, serve para identificar se esta sendo perguntado a frequencia de determinada palavra
//ou entao a porcentagem de comentarios positivos ou negativos em relacao a determinado produto
void lerPergunta(char **comentario,produto *prod, int qtdSentenca){
	char *aux;
	alocaChar2(&aux,380);
	aux=strstr(comentario[0],"palavra");
	if(aux!=NULL){
		printf("%d\n",quantidadePalavra(prod,aux));
	}
	else{
		aux=strstr(comentario[0],"quantos");
		printf("%.01f%%\n",porcentagemAvaliacao(prod,aux,qtdSentenca));
	}

}

//a funcao quantidade palavra, serve para contar a frequencia de determinada palavra sobre um produto
//ela basicamente consulta o bag of words daquele produto, e checa a sequencia
//a funcao quantidade palavra funciona normalmente
int quantidadePalavra(produto *prod,char *aux){
	int achou=0;
	int cont=0;
	int indiceProduto=0;
	int indicePalavra=0;
	char *palavraProcura;
	alocaChar2(&palavraProcura,38);
	char *nomeProduto;
	alocaChar2(&nomeProduto,64);
	char *saveptr;
	char *ptr=strtok_r(aux, " ",&saveptr);
	cont=0;
	while(ptr!=NULL){
		//a segunda posicao da pergunta, sempre eh a palavra que deve ser buscada
		if(cont==1){
			strcpy(palavraProcura,ptr);
		}
		//a quarta posicao da pergunta, sempre eh o produto que se refere a pergunta
		if(cont==3){
			strcpy(nomeProduto, ptr);
			strcat(nomeProduto," ");
		}
		//o produto nao necessariamente, tem mais de uma palavra, por isso eh checado se o vetor eh nulo
		if(cont>=4 && ptr!=NULL){
			strcat(nomeProduto,ptr);
			strcat(nomeProduto," ");
		}
		//a funcao strtok_r eh usada para percorrer toda a pergunta
		ptr=strtok_r(NULL, " ",&saveptr);
		cont++;
	}
	//nessa parte, eh procurado o produto referente a palavra digitada pelo usuario
	cont=0;
	while(strlen(prod[cont].nome)>0){
		if(strcmp(prod[cont].nome,nomeProduto)==0){
			indiceProduto=cont;
			break;
		}
		cont++;
	}
	cont=0;
	//a variavel achou eh para indicar se a palavra procurada existe ou nao
	//caso exista, seu valor eh mudado para 1
	achou=0;
	//apos achar qual o produto referente, eh procurada a palavra na struct bag of words do produt
	while(strlen(prod[indiceProduto].bag[cont].palavra)>0 && achou==0){
		if(strcmp(prod[indiceProduto].bag[cont].palavra,palavraProcura)==0){
			indicePalavra=cont;
			achou=1;
		}
		cont++;
	}
	//caso a palavra nao seja encontrada, 
	if(achou==0){
		return 0;
	}else{
		//e no final ja eh retornado diretamente a frequencia dessa palavra
		return prod[indiceProduto].bag[indicePalavra].frequencia;
	}
}

//essa funcao calcula a porcentagem de comentarios positivos ou negativos de determinado produto
float porcentagemAvaliacao(produto *prod,char *aux, int qtdSentenca){
	char** vetorPositivos=NULL;
	char** vetorNegativos=NULL;
	int total=0;
	int positivos=0;
	int indiceProduto=0;
	int cont=0;
	char *nomeProduto;
	alocaChar2(&nomeProduto,64);
	char *saveptr;
	char *ptr=strtok_r(aux, " ",&saveptr);
	cont=0;
	//nesse while a pergunta eh percorrida
	//a variavel positivos, quando igual a 1 significa que o usuario quer que seja calculada a porcentagem de frases positivas
	//caso contrario, o usuario quer a porcentagem de frases negativas
	while(ptr!=NULL){
		//a segunda posicao da pergunta, sempre indica se o usuario quer frases positivas ou negativas
		if(cont==1){
			if(strcmp(ptr,"positivos")==0){
				positivos=1;
			}
		}
		//a quarta posicao da pergunta, sempre eh o produto que se refere a pergunta
		if(cont==3){
			strcpy(nomeProduto, ptr);
			strcat(nomeProduto," ");
		}
		//o produto nao necessariamente, tem mais de uma palavra, por isso eh checado se o vetor eh nulo
		if(cont>=4 && ptr!=NULL){
			strcat(nomeProduto,ptr);
			strcat(nomeProduto," ");
		}
		//aqui indica que a string esta sendo percorrida
		ptr=strtok_r(NULL, " ",&saveptr);
		cont++;
	}
	//essa parte do codigo, eh feita a checagem do produto digitado pelo usuario
	cont=0;
	while(strlen(prod[cont].nome)>0){
		if(strcmp(prod[cont].nome,nomeProduto)==0){
			indiceProduto=cont;
			break;
		}
	cont++;
	}
	//essa parte eh feita a checagem se o bag of words do produto bate com algum elemento de palavras positivas ou negativas
	cont=0;
	//antes a alocacao dos vetores era feita dentro da funcao "declaraVetoresPositivos" e "declaraVetoresNegativos"
	//porem antes ocorria um erro em que os vetores nao eram alocados corretamente, e por isso estao sendo alocados no meio do codigo
	alocaChar1(&vetorPositivos,12,20);
	alocaChar1(&vetorNegativos,12,20);
	declaraVetorPositivos(vetorPositivos);
	declaraVetorNegativos(vetorNegativos);
	int sucesso=0;
	//aqui eh checado se a linha do comentario bate com a linha em que esta sendo analisada
	//a linha eh analisada, pois assim evita que 2 comentarios da mesma linha sejam computados
	//a variavel sucesso serve para indicar que ira ser computado um comentario positivo ou negativo de determinada frase, e assim sair do while para mudanca de linha
	for(int j=0; j<qtdSentenca; j++){
		sucesso=0;
		cont=0;
		while(strlen(prod[indiceProduto].bag[cont].palavra)>0 && sucesso==0){
			for(int i=0;i<12;i++){
				if(strcmp(prod[indiceProduto].bag[cont].palavra,vetorPositivos[i])==0){
					if(prod[indiceProduto].bag[cont].linha[j]==1){
						prod[indiceProduto].positivo++;
						sucesso=1;
						break;
					}
				}
				else if(strcmp(prod[indiceProduto].bag[cont].palavra,vetorNegativos[i])==0){
					if(prod[indiceProduto].bag[cont].linha[j]==1){
						prod[indiceProduto].negativo++;
						sucesso=1;
						break;
					}
				}
			}
			cont++;
		}
	}
	//aqui a variavel total eh usada para fazer o calculo da porcentagem
	//logo abaixo eh feita a checagem se o usuario quer a porcentagem de frases negativas ou positivas
	total=prod[indiceProduto].positivo+prod[indiceProduto].negativo;
	if(positivos==1){
		return (prod[indiceProduto].positivo/total)*100.0;
	}
	else{
		return (prod[indiceProduto].negativo/total)*100.0;
	}
}

//funcao para declarar um vetor que contenha todas as palavras positivas possiveis
void declaraVetorPositivos(char **vetorPositivos){
	strcpy(vetorPositivos[0],"bom");strcpy(vetorPositivos[1],"maravilhoso");strcpy(vetorPositivos[2],"otimo");strcpy(vetorPositivos[3],"sensacional");strcpy(vetorPositivos[4],"excelente");strcpy(vetorPositivos[5],"adorei");
	strcpy(vetorPositivos[6],"gostei");strcpy(vetorPositivos[7],"amei");strcpy(vetorPositivos[8],"eficiente");strcpy(vetorPositivos[9],"boa");strcpy(vetorPositivos[10],"maravilhosa");strcpy(vetorPositivos[11],"otima");
}
//funcao para declarar um vetor que contenha todas as palavras negativas possiveis
void declaraVetorNegativos(char **vetorNegativos){
	strcpy(vetorNegativos[0],"detestei");strcpy(vetorNegativos[1],"odiei");strcpy(vetorNegativos[2],"ruim");strcpy(vetorNegativos[3],"pessimo");strcpy(vetorNegativos[4],"terrivel");strcpy(vetorNegativos[5],"raiva");
	strcpy(vetorNegativos[6],"odio");strcpy(vetorNegativos[7],"pessima");strcpy(vetorNegativos[8],"lento");strcpy(vetorNegativos[9],"lenta");strcpy(vetorNegativos[10],"fragil");strcpy(vetorNegativos[11],"desisti");
}

//a funcao lerSentenca eh para armazenar o bag of words
void lerSentenca(char **comentario, produto *prod, int indice, int qtdSentenca){
	char *saveptr;
	int boolean=0;
	int cont=0;
	char *aux;
	alocaChar2(&aux,380);
	char *ptr;
	//esse laco serve para quando o produto ja foi armazenado, e o contador pula alguns valores, para checar propriamente o comentario
	//sem ter que passar pelo nome de novo, ja que este ja foi armazenado
	if(strlen(prod->nome)>0){
		cont=strlen(prod->nome);
		boolean=1;
		aux=strstr(comentario[0],";");
		ptr=strtok_r(aux, " ",&saveptr);
	}
	//se o nome nao foi armazenado, toda a string eh percorrida
	else{
		ptr=strtok_r(comentario[0], " ",&saveptr);
	}
	//aqui eh checado se a string ja percorreu todo o nome do produto, usando o caractere ";" como delimitador
	//isso eh feito pois o nome do produto nao deve ser contado no bag of words
	//a variavel boolean quando tem valor 0, diz que ainda o nome nao foi completamente percorrido
	//quando a variavel assume 1, quer dizer que as palavras seguintes ja farao parte do bag of words
	//nesse laco o bag of words eh propriamente escrito
	while(ptr!=NULL){
		if(strcmp(ptr,";")==0){
			boolean=1;
		}
		escreveBow(prod,ptr,boolean,&cont,indice,qtdSentenca);
		ptr=strtok_r(NULL, " ",&saveptr);
		cont++;
	}
	//erro desconhecido ao tentar liberar ponteiro aux, por isso comentado
	//free(aux);

}

//funcao onde cada struct do bag of words referente ao produto eh escrita
void escreveBow(produto *prod,char *ptr, int boolean, int *cont,int indice, int qtdSentenca){
	int i=0;
	int existe=0;
	//esses 2 caracteres, so sao delimitadores, por isso nao sao armazenados
	if(strcmp(ptr,";")==0 || strcmp(ptr,"Ø")==0){
		//essa linha faz com que nada seja armazenado, e diminuindo um indice de cont para que nao tenha vetores com valores nulos
		*(cont)-=1;
	}
	else{
	//caso o boolean seja 0, o nome ainda esta sendo percorrido, e nada deve ser armazenado
	//cont tambem eh subtraido 1 para nao haver vetores com valores nulos
	if(boolean==0){
		strcat(prod->nome,ptr);
		strcat(prod->nome," ");
		*(cont)-=1;
	}
	//nessa parte, todo o nome ja foi percorrido
	else{
		for(i=0;strlen(prod->bag[i].palavra)!=0;i++){
			//aqui eh checado se a palavra a ser armazenada ja existe ou nao
			//a variavel existe eh usada para isso, sendo 1 significando que ja existe, e 0 nao
			//a variavel linha eh setada 1, para indicar que naquela linha a palavra foi escrita
			if(strcmp(ptr,prod->bag[i].palavra)==0){
				prod->bag[i].frequencia++;
				prod->bag[i].linha[indice]=1;
				existe=1;
				break;
			}
		}
		//se a variavel existe for 0, quer dizer que a palavra eh nova, e por isso todo o vetor eh percorrido para uma posicao que ainda nao tem nada armazenado 
		if(existe==0){
			int j=0;
			if(strlen(prod->bag[j].palavra)>0){
				while(strlen(prod->bag[j].palavra)!=0){
					j++;
				}
			}
			strcpy(prod->bag[j].palavra,ptr);
			prod->bag[j].frequencia++;
			//funcao para alocar quantas linhas (comentarios) terao no programa
			alocaLinha(&(prod->bag[j].linha),qtdSentenca);
			memset(prod->bag[j].linha,0,qtdSentenca);
			prod->bag[j].linha[indice]=1;
		}
	}
}
	
}

//definicao de alocaChar1
void alocaChar1(char ***ponteiro, int qtd1, int qtd2){
	*ponteiro=(char **) malloc(sizeof(char *)*qtd1);
	int i=0;
	if(qtd2!=0){
		for(i=0;i<qtd1;i++){
			alocaChar2(&(*ponteiro)[i],qtd2);
		}
	}
}

//definicao de alocaChar2
void alocaChar2(char **ponteiro, int qtd2){
	*ponteiro=(char *) malloc(qtd2*sizeof(char));
}
//definicao de alocao da struct de produto
void alocaProduto(produto **prod,int qtd){
	*prod=(produto *) malloc(qtd*sizeof(produto));
}

void alocaLinha(int **linha, int qtdLinha){
	*linha=(int *) malloc(qtdLinha*sizeof(int));
}