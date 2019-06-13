#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Olavo Morais 11297792
//Evitei acentuacao para nao ter problemas com a tabela ascii
//Tive uma dificuldade com a formatacao no run codes,o meu programa 'espera' um enter para mostrar o ulimo resultado
//A ideia e simples:criar um vetor para armazenar o produtos avaliados e um outro vetor para armazenar as palavras lidas
//Cada palavra possui um 'codigo',que seria seu indice no vetor bolsaDePalavras
//Tambem existe um vetor de vetor de inteiros(dados),onde cada vetor armazena informacoes sobre um produto(caso existam n produtos diferentes,entao existem n vetores dentro do vetor de vetor
//cada vetor de um produto possui pelo menos 3 inteiros:o numero de criticas positivas,o numero de criticas negativas e o numero de palavras associadas com esse produto
//Ex.:
//dados[0]={2,3,2,3,4}
//dados[1]={3,0,4,2,4,2,1}
//Entao o produto zero tem 2 criticas positivas,3 negativas e 2 palavras associadas com ele:as palavras 3 e 4(basta olhar no vetor de palavras quais sao as palavras nas posicoes 3 e 4
//Entao o produto um tem 3 criticas positivas,0 negativas e 4 palavras associadas com ele:as palavras 2,4,2 e 1(basta olhar no vetor de palavras quais sao as palavras nas posicoes 2,4,2 e 1

float Porcentagem(int fatia,int total);//retorno o quanto % fatia é do total

int IndiceFinal(char * comentario);//retorna o indice final de um comentario

int Verifica(char * str,char ** vetor,int tamanho);//funcao que verifica se uma string faz parte de um array de strings e retorna o seu indice.Retorna -1 caso nao pertenca

void Leitora(char * frase,char * palavra,int indiceInicial,int nEspaco,int charFinal);//recebe uma sentenca e armezena caractere por caracter ate encontrar o char final

int PontoVirgula(char * frase);//retorna o indice do ponto e virgula de uma expressao

void Produto(char * comentario,char * produto,char ** listaDeProdutos,int * nProdutos,int nComnt,int **dados);//recebe uma sentenca e armazena qual o produto mencionado no comentario

void BolsaDePalavras(char * comentario,char * palavra,char **bolsaDePalavras,int **dados,int * nPalavras,int nComnt,char *produto,char ** palavrasBoas,char **palavrasRuins,char ** listaDeProdutos);//recebe um setenca e armazena as palavras na bolsa de palavras e atribui pontos ao produto

void Respostas(int ** dados,char **bolsaDePalavras,int nComnt,char ** listaDeProdutos,int nPerg);//Recebe as perguntas e mostra os dados para o usuario

void LiberaRecursos(char **bolsaDePalavras,char **listaDeProdutos,int **dados,int nComnt,int nPalavras);//libera memoria

float Porcentagem(int fatia,int total){
	if(total!=0){
		return (100* ((float)fatia)/total);

	}
	return 0.0;
}

int IndiceFinal(char *comentario){
	int indicefinal=0;
	for(int k=0;comentario[k]>=0 && comentario[k]<=127;k++){//utilizado para descobrir qual a posicao do ultimo caracter. Ø nao esta representado na ascii comum,
		//entao nao se encaixa no intervalo [0,127]
		indicefinal++;
	}
	return indicefinal;
}

int Verifica(char * str,char ** vetor,int tamanho){//variavel da string,variavel do vetor de string,tamanho do vetor de strings
	int i=0;
	while(i<tamanho && vetor[i]!=NULL){
		if(strcmp(str,vetor[i])==0){
			return i;
		}
		i++;  
	}
	return -1;
}

void Leitora(char * frase,char * palavra,int indiceInicial,int nEspaco,int charFinal){//frase que sera lida,variavel que a(s) palavra(s) sera armazenada,
	//indice em que a frase comecara a ser lida,numero de espaços(ou outro caracter que sera usado como fim) que deverao ser lidos,caracter que sera usado como final
	int j=0;
	for(int i=0;i<nEspaco;i++){
		while(frase[j+indiceInicial]!=charFinal){
			palavra[j]=frase[j+indiceInicial];
			j++;
		}
	}
	palavra[j]=0;//adiciona um \0 na ultima posicao para evitar problemas ao reutilizar variaveis
}

int PontoVirgula(char * frase){//frase que sera analisada
	int pontoVirgula=0;
	while(frase[pontoVirgula]!=';'){
		pontoVirgula++;
	}
	return pontoVirgula;
}

void Produto(char * comentario,char * produto,char ** listaDeProdutos,int * nProdutos,int nComnt,int **dados){//comentario,variavel que armazena o produto,variavel que armazena todos 
	//os produtos,numero de produtos no vetor listaDeprodutos,numero de comentarios(tamanho total do vetor listaDeProdutos),array com dados sobre os produtos

	Leitora(comentario,produto,0,1,59);
	produto[PontoVirgula(comentario)-1]=0;//retira o espaco antes da ultima posicao do produto

	char *auxiliar=(char *)malloc(21*sizeof(char));//uma auxiliar é usada para armazenar a palavra pois armazenar uma variavel reutilizada nao é interessante visto que,embora 
	//seu conteudo mude,ela sempre aponta para o mesmo lugar
	for(int i=0;i<21;i++){
		auxiliar[i]=produto[i];
	}
	if(Verifica(produto,listaDeProdutos,nComnt)==-1){
		listaDeProdutos[*nProdutos]=auxiliar;
		dados[*nProdutos]=(int *)calloc(3,sizeof(int));
		*(nProdutos)+=1;
	}
}


void BolsaDePalavras(char * comentario,char * palavra,char **bolsaDePalavras,int **dados,int * nPalavras,int nComnt,char *produto,char ** palavrasBoas,char **palavrasRuins,char ** listaDeProdutos){//comentario é a sentenca completa,palavra é o ponteiro que armazena a palavra lida,bolsaDePalavras é o array de palavras,dados é o array com as informacoes sobre os produtos,
	//nPalavras é o numero de palavras no array bolsaDePalavras,nComnt é o numero de comentarios,produto é o nome do atual produto,palavrasBoas é o array de palavras positivas,
	////palavrasRuins é o vetor de palavras negativas,listaDeProdutos é o array de produtos
	int posicao=0,jaAvaliado=0;//posicao e usada para guiar a variavel "palavra" enquanto "jaAvaliado" serve para registrar se um produto ja foi avaliado
	for(int k=0;PontoVirgula(comentario)+k+2<IndiceFinal(comentario);k++){//Dessa forma o computador apenas le os caracteres importantes(apos o ponto e virgula)
		if(comentario[PontoVirgula(comentario)+k+2]!=' '){
			palavra[posicao]=comentario[PontoVirgula(comentario)+k+2];
			posicao++;
		}else{
			palavra[posicao]=0;//essa linha evita problemas com a reutilizecao da variavel palavra
			if(strcmp(palavra," ")!=0){//garante que nao estamos lendo uma palavra nula
				char * auxiliar=(char *)malloc(20*sizeof(char));//a auxiliar é salva para nao dar problema com a reutilizacao da variavel palavra
				for(int l=0;l<20;l++){
					auxiliar[l]=palavra[l];
				}
				if(Verifica(auxiliar,bolsaDePalavras,200)==-1){
					bolsaDePalavras[*nPalavras]=auxiliar;
					*nPalavras+=1;
				}
				//Verifica(produto,listaDeProdutos,nComnt) é o indice de produto no vetor produtos
				//realoca o vetor desse produto visto que ele tem uma palavra nova
				//atualiza o indicador de palavras no vetor desse produto
				//adiciona o 'código/id'da palavra no fim do vetor do produto
				dados[Verifica(produto,listaDeProdutos,nComnt)]=realloc(dados[Verifica(produto,listaDeProdutos,nComnt)],
						sizeof(int)*(4+*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+2)));
				*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+2)+=1;
				*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+2+*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+2))=Verifica(palavra,bolsaDePalavras,200);

				if(Verifica(palavra,palavrasBoas,12)!=-1){//avalia o produto
					if(jaAvaliado==0){
						**(dados+Verifica(produto,listaDeProdutos,nComnt))+=1;
						jaAvaliado=1;
					}
				}else if(Verifica(palavra,palavrasRuins,12)!=-1){
					if(jaAvaliado==0){
						*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+1)+=1;
						jaAvaliado=1;
					}
				}
				posicao=0;//retorna a posicao para reescrever a variavel 'palavra'
			}
		}
	}
}

void Respostas(int ** dados,char ** bolsaDePalavras,int nComnt ,char ** listaDeProdutos,int nPerg){//Variavel com os dados,array de palavras,tamanho do vetor de produtos,numero de perguntas
	//numero de comentarios,array com os produtos
	char * palavra=(char *)malloc(20*sizeof(char));
	char * produto=(char *)malloc(20*sizeof(char));
	char * comentario=(char *)malloc(20*sizeof(char));
	printf("\n");
	for(int i=0;i<nPerg;i++){
		fgets(comentario,402,stdin);
		Leitora(comentario,palavra,0,1,32);
		if(strcmp(palavra,"palavra")==0){//analisa o tipo de pergunta
			//analisa a palavra e o produto que a pergunta se refere
			Leitora(comentario,palavra,8,1,32);
			Leitora(comentario,produto,12+strlen(palavra),1,10);//10 é o caractere de fim de linha na tabela ascii
			int codigoPalavra=Verifica(palavra,bolsaDePalavras,200);
			int nVezes=0;

			for(int j=0;j<*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+2);j++){//conta quantas vezes o 'codigo' da palavra aparece no vetor de dados do produto
				if(*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+3+j)==codigoPalavra){
					nVezes++;
				}
			}
			printf("%d\n",nVezes);
		}else{//pergunta do tipo 'quantos positivos/negativos'
			Leitora(comentario,palavra,8,1,32);
			Leitora(comentario,produto,12+strlen(palavra),1,10);
			int criticasPositivas=**(dados+Verifica(produto,listaDeProdutos,nComnt));
			int criticasNegativas=*(*(dados+Verifica(produto,listaDeProdutos,nComnt))+1);
			if(strcmp(palavra,"positivos")==0){
				printf("%.1f%%\n",Porcentagem(criticasPositivas,criticasPositivas+criticasNegativas));
			}else{
				printf("%.1f%%\n",Porcentagem(criticasNegativas,criticasPositivas+criticasNegativas));
			}
		}
	}
	free(palavra);
	free(produto);
	free(comentario);
}

void LiberaRecursos(char ** bolsaDePalavras,char ** listaDeProdutos,int ** dados,int nComnt,int nPalavras){//enderecos que serao liberados
	for(int i=0;i<nComnt;i++){
		free(listaDeProdutos[i]);
		free(dados[i]);
	}
	free(listaDeProdutos);
	free(dados);
	for(int i=0;i<nPalavras;i++){
		free(bolsaDePalavras[i]);
	}
	free(bolsaDePalavras);
}

int main(void){

	int nComnt,nPerg,nProdutos=0,nPalavras=0;//numero de comentarios,numero de perguntas,numero de listaDeProdutos no vetor de produtos e numero de palavras no vetor de palavras
	scanf("%d %d ",&nComnt,&nPerg);
	char ** listaDeProdutos=(char **)malloc(nComnt*sizeof(char *));//na pior das hipoteses,existem nComnt produtos  diferentes
	char * palavrasBoas[12]={"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};
	char * palavrasRuins[12]={"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
	//char * adverbios[3]={"nao","jamais","nunca"};
	char ** bolsaDePalavras=(char **)malloc(200*sizeof(char *));
	int ** dados=(int **)malloc(nComnt*sizeof(int *)); 
        char * palavra=(char *)malloc(20*sizeof(char));//cada palavra possui no maximo 19 caractares+1 caracter \0=20 caracteres	
	char * comentario=(char *)malloc(402*sizeof(char));//20*20+/0+Ø=402 caracteres
	char * produto=(char *)malloc(21*sizeof(char));

	for(int i=0;i<nComnt;i++){//cada volta representa um comentario
		fgets(comentario,402,stdin);
		Produto(comentario,produto,listaDeProdutos,&nProdutos,nComnt,dados);//armazena o produto que sera avaliado
		BolsaDePalavras(comentario,palavra,bolsaDePalavras,dados,&nPalavras,nComnt,produto,palavrasBoas,palavrasRuins,listaDeProdutos);//armazena e avalia o produto
	}

	free(comentario);
	free(produto);
	free(palavra);

	Respostas(dados,bolsaDePalavras,nComnt,listaDeProdutos,nPerg);

	LiberaRecursos(bolsaDePalavras,listaDeProdutos,dados,nComnt,nPalavras);
	return 0;
}
