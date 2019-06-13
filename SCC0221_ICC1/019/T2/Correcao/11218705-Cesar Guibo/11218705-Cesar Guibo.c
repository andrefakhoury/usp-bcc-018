#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ElementoDaBagOfWords{
	struct ElementoDaBagOfWords *proximo;
	char *palavra;
	int numAparicoes;
}ElementoBoW;

typedef struct InformacoesDoProduto{
	struct InformacoesDoProduto *proximo;
	ElementoBoW *headerBoW;
	char *aparelho;
	char *marca;
	int numComentarios;
	int numComentariosPos;
	int numComentariosNeg;
}InfoProduto;

typedef struct Sentenca_{
	char aparelho[20];
	char marca[20];
	char comentario[20][20];
	int numPalavras;
}Sentenca;

typedef struct Pergunta_{
	char tipo[8];
	char dadoRequisitado[20];
	char aparelho[20];
	char marca[20];
}Pergunta;

InfoProduto *alocaInformacoesDoProduto(int strlenAparelho, int strlenMarca, int strlenPalavraBoW);
ElementoBoW *alocaElementoDaBoW(int strlenPalavra);
void preencheListaDeInformacoesDosProdutos(InfoProduto *headerInfoProdutos, Sentenca sent);
void preencheBagOfWords(ElementoBoW *headerBoW, char *palavra);
int descobrePolaridadeDoComentario(char comentario[20][20], int numPalavras);
int comparaPalavraComPalavrasPolarizadoras(char *palavra);
int verificaMudancaPolaridade(char *palavra);
int leSentenca(Sentenca *sent);//Retorna o numero de palavras que estao presentes no comentario
int lePergunta(Pergunta *perg);//Retorna 1 se o programa deve procurar uma palavra ou 2 se ele deve procurar polaridade
InfoProduto *procuraProduto(InfoProduto *headerInfoProdutos, char *aparelho, char *marca);
float calculaPorcentagemDeComentariosPosOuNeg(InfoProduto *produto, char *polaridade);
int procuraNumAparicoesDaPalavraNaBoW(ElementoBoW *headerBoW, char *palavra);
void liberaListaDeInformacoesDosProdutos(InfoProduto *headerInfoProduto);
void liberaBagOfWords(ElementoBoW *headerBoW);

InfoProduto *alocaInformacoesDoProduto(int strlenAparelho, int strlenMarca, int strlenPalavraBoW){
	InfoProduto *produto;

	if((produto = (InfoProduto *)malloc(sizeof(InfoProduto))) == NULL)
		exit(1);
	if((produto->aparelho = (char *)malloc((strlenAparelho+1)*sizeof(char))) == NULL)
		exit(1);
	if((produto->marca = (char *)malloc((strlenMarca+1)*sizeof(char))) == NULL)
		exit(1);
	produto->headerBoW = alocaElementoDaBoW(strlenPalavraBoW);
	produto->numComentarios = 0;
	produto->numComentariosPos = 0;
	produto->numComentariosNeg = 0;
	produto->proximo = NULL;

	return produto;
}

ElementoBoW *alocaElementoDaBoW(int strlenPalavra){
	ElementoBoW *elemBoW;

	if((elemBoW = (ElementoBoW *)malloc(sizeof(ElementoBoW))) == NULL)
		exit(1);
	if((elemBoW->palavra = (char *)malloc((strlenPalavra+1)*sizeof(char))) == NULL)
		exit(1);
	elemBoW->proximo = NULL;

	return elemBoW;
}

void preencheListaDeInformacoesDosProdutos(InfoProduto *headerInfoProdutos, Sentenca sent){
	int polaridade;
	int i;

	while(1){
		if(strcmp(headerInfoProdutos->aparelho, sent.aparelho) == 0 && strcmp(headerInfoProdutos->marca, sent.marca) == 0){
			for(i = 0; i < sent.numPalavras; i++)
				preencheBagOfWords(headerInfoProdutos->headerBoW, sent.comentario[i]);
			headerInfoProdutos->numComentarios++;

			polaridade = descobrePolaridadeDoComentario(sent.comentario, sent.numPalavras);
			if(polaridade == 1)
				headerInfoProdutos->numComentariosPos++;
			else if(polaridade == -1)
				headerInfoProdutos->numComentariosNeg++;

			return;
		}
		else if(headerInfoProdutos->proximo == NULL){
			headerInfoProdutos->proximo = alocaInformacoesDoProduto(strlen(sent.aparelho), strlen(sent.marca), strlen(sent.comentario[0]));

			strcpy(headerInfoProdutos->proximo->aparelho, sent.aparelho);
			strcpy(headerInfoProdutos->proximo->marca, sent.marca);
			strcpy(headerInfoProdutos->proximo->headerBoW->palavra, sent.comentario[0]);
			headerInfoProdutos->proximo->numComentarios++;

			for(i = 0; i < sent.numPalavras; i++)
				preencheBagOfWords(headerInfoProdutos->proximo->headerBoW, sent.comentario[i]);

			polaridade = descobrePolaridadeDoComentario(sent.comentario, sent.numPalavras);
			if(polaridade == 1)
				headerInfoProdutos->proximo->numComentariosPos++;
			else if(polaridade == -1)
				headerInfoProdutos->proximo->numComentariosNeg++;	
			
			return;
		}
		else
			headerInfoProdutos = headerInfoProdutos->proximo;
	}
}

void preencheBagOfWords(ElementoBoW *headerBoW, char *palavra){
	while(1){
		if(strcmp(headerBoW->palavra, palavra) == 0){
			headerBoW->numAparicoes++;

			return;
		}
		else if(headerBoW->proximo == NULL){
			headerBoW->proximo = alocaElementoDaBoW(strlen(palavra));

			strcpy(headerBoW->proximo->palavra, palavra);

			headerBoW->proximo->numAparicoes = 1;

			return;
		}
		else
			headerBoW = headerBoW->proximo;
	}
}

int descobrePolaridadeDoComentario(char comentario[20][20], int numPalavras){
	int polaridadeDoComentario = 0;
	int i, j;

	for(i = 0; i < numPalavras && polaridadeDoComentario == 0; i++)
		polaridadeDoComentario = comparaPalavraComPalavrasPolarizadoras(comentario[i]);

	if(polaridadeDoComentario != 0)
		for(j = i-4; j < i-1; j++)//verifica apenas as 3 palavras que antecedem a palavra polarizadora
			polaridadeDoComentario *= verificaMudancaPolaridade(comentario[j]);

	return polaridadeDoComentario;
}

int comparaPalavraComPalavrasPolarizadoras(char *palavra){
	if(strcmp(palavra, "bom") == 0)
		return 1;
	else if(strcmp(palavra, "maravilhoso") == 0)
		return 1;
	else if(strcmp(palavra, "otimo") == 0)
		return 1;
	else if(strcmp(palavra, "sensacional") == 0)
		return 1;
	else if(strcmp(palavra, "excelente") == 0)
		return 1;
	else if(strcmp(palavra, "adorei") == 0)
		return 1;
	else if(strcmp(palavra, "gostei") == 0)
		return 1;
	else if(strcmp(palavra, "amei") == 0)
		return 1;
	else if(strcmp(palavra, "eficiente") == 0)
		return 1;
	else if(strcmp(palavra, "boa") == 0)
		return 1;
	else if(strcmp(palavra, "maravilhosa") == 0)
		return 1;
	else if(strcmp(palavra, "otima") == 0)
		return 1;
	else if(strcmp(palavra, "detestei") == 0)
		return -1;
	else if(strcmp(palavra, "odiei") == 0)
		return -1;
	else if(strcmp(palavra, "ruim") == 0)
		return -1;
	else if(strcmp(palavra, "pessimo") == 0)
		return -1;
	else if(strcmp(palavra, "terrivel") == 0)
		return -1;
	else if(strcmp(palavra, "raiva") == 0)
		return -1;
	else if(strcmp(palavra, "odio") == 0)
		return -1;
	else if(strcmp(palavra, "pessima") == 0)
		return -1;
	else if(strcmp(palavra, "lento") == 0)
		return -1;
	else if(strcmp(palavra, "lenta") == 0)
		return -1;
	else if(strcmp(palavra, "fragil") == 0)
		return -1;
	else if(strcmp(palavra, "desisti") == 0)
		return -1;

	return 0;
}

int verificaMudancaPolaridade(char *palavra){
	if(strcmp(palavra, "nao") == 0){
		return -1;
	} 
	else if(strcmp(palavra, "jamais") == 0){
		return -1;
	} 
	else if(strcmp(palavra, "nunca") == 0){
		return -1;
	} 
	else
		return 1;
}

int leSentenca(Sentenca *sent){
	char lixo[2];
	int i;

	scanf("%s", sent->aparelho);
	scanf("%s", sent->marca);
	scanf("%s", lixo);
	
	scanf("%s", sent->comentario[0]);
	
	for(i = 1; strcmp(sent->comentario[i-1], "Ø") != 0; i++)
		scanf("%s", sent->comentario[i]);

	return i-1;
}

int lePergunta(Pergunta *perg){
	char lixo[3];

	scanf("%s", perg->tipo);
	scanf("%s", perg->dadoRequisitado);
	scanf("%s", lixo);
	scanf("%s", perg->aparelho);
	scanf("%s", perg->marca);
	
	if(strcmp(perg->tipo, "palavra") == 0)
		return 1;
	else
		return 2;
}

InfoProduto *procuraProduto(InfoProduto *headerInfoProdutos, char *aparelho, char *marca){
	while(1){
		if(strcmp(headerInfoProdutos->aparelho, aparelho) == 0 && strcmp(headerInfoProdutos->marca, marca) == 0)
			return headerInfoProdutos;//posicao da memoria que armazena as informacoes do produto requisitado
		else if(headerInfoProdutos->proximo == NULL)
			return NULL;
		else
			headerInfoProdutos = headerInfoProdutos->proximo;
	}
}

float calculaPorcentagemDeComentariosPosOuNeg(InfoProduto *produto, char *polaridade){
	float porcentagem;
	
	if(strcmp(polaridade, "positivos") == 0)
		porcentagem = produto->numComentariosPos;
	else
		porcentagem = produto->numComentariosNeg;
	porcentagem /= (float)produto->numComentarios;
    porcentagem *= 100;

	return porcentagem;
}

int procuraNumAparicoesDaPalavraNaBoW(ElementoBoW *headerBoW, char *palavra){
	while(1){
		if(strcmp(headerBoW->palavra, palavra) == 0)
			return headerBoW->numAparicoes;
		else if(headerBoW->proximo == NULL)
			return 0;
		else 
			headerBoW = headerBoW->proximo;
	}
}


void liberaListaDeInformacoesDosProdutos(InfoProduto *headerInfoProdutos){
	InfoProduto *tmp;

	while(1){
		free(headerInfoProdutos->aparelho);
		free(headerInfoProdutos->marca);
		liberaBagOfWords(headerInfoProdutos->headerBoW);
		if(headerInfoProdutos->proximo == NULL){
			free(headerInfoProdutos);
			return;
		}
		else{
			tmp = headerInfoProdutos->proximo;
			free(headerInfoProdutos);
			headerInfoProdutos = tmp;
		}
	}
}

void liberaBagOfWords(ElementoBoW *headerBoW){
	ElementoBoW *tmp;

	while(1){
		free(headerBoW->palavra);
		if(headerBoW->proximo == NULL){
			free(headerBoW);
			return;
		}
		else{
			tmp = headerBoW->proximo;
			free(headerBoW);
			headerBoW = tmp;
		}
	}
}


int main(void){
	InfoProduto *headerInfoProdutos;//header aponta para o primeiro elemento da lista
	InfoProduto *produtoRequisitado;
	Sentenca sent;
	Pergunta perg;
	int numSentencas;
	int numPerguntas;
	int i;

	scanf("%d%d", &numSentencas, &numPerguntas);

	sent.numPalavras = leSentenca(&sent);

	headerInfoProdutos = alocaInformacoesDoProduto(strlen(sent.aparelho), strlen(sent.marca), strlen(sent.comentario[0]));

	strcpy(headerInfoProdutos->aparelho, sent.aparelho);
	strcpy(headerInfoProdutos->marca, sent.marca);
	strcpy(headerInfoProdutos->headerBoW->palavra, sent.comentario[0]);

	preencheListaDeInformacoesDosProdutos(headerInfoProdutos, sent);

	for(i = 1; i < numSentencas; i++){
		sent.numPalavras = leSentenca(&sent);
		preencheListaDeInformacoesDosProdutos(headerInfoProdutos, sent);
	}

	for(i = 0; i < numPerguntas; i++)
		if(lePergunta(&perg) == 1){
			produtoRequisitado = procuraProduto(headerInfoProdutos, perg.aparelho, perg.marca);
			printf("%d\n", procuraNumAparicoesDaPalavraNaBoW(produtoRequisitado->headerBoW, perg.dadoRequisitado));
		}
		else{
			produtoRequisitado = procuraProduto(headerInfoProdutos, perg.aparelho, perg.marca);
			printf("%.1f%%\n", calculaPorcentagemDeComentariosPosOuNeg(produtoRequisitado, perg.dadoRequisitado));
		}

	liberaListaDeInformacoesDosProdutos(headerInfoProdutos);

	return 0;
}

