#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Algumas listas de palavras importantes.
const char* positivas[] =  {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
const char* negativas[] =  {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
const char* adverbios[] = {"nao","nunca","jamais"};

/*
 * A struct bag mapeia um vetor de palavras (de ate 30 caracteres) para um vetor de enderecos da memoria heap.
 * E' necessario usar a variavel 'tamanho_tipo' para definir quantos bytes serao alocados em cada endereco.
 * Utilize com as funcoes 'valor' e 'liberar'.
 */
typedef struct {
	char** chaves;
	void** valores;
	int tamanho_tipo;
	int qntd_itens;
} bag;

//Retorna o endereco relativo a palavra 'chave' na bag 'b'. Caso a palavra nao tenha sido colocada na bag ele adiciona a palavra e zera o valor do endereco relativo. 
void* valor(bag* b, char* chave){
	for(int i = 0; i < b->qntd_itens; i++){
		if(strcmp(chave,b->chaves[i])==0){
			return b->valores[i];
		}		
	}
	b->qntd_itens++;
	b->chaves = realloc(b->chaves, b->qntd_itens*sizeof(char*));		
	b->chaves[b->qntd_itens-1]  = malloc(30*sizeof(char));
	strcpy(b->chaves[b->qntd_itens-1],chave);
	b->valores = realloc(b->valores,b->qntd_itens * sizeof(void*));
	b->valores[b->qntd_itens-1] = malloc(b->tamanho_tipo);
	memset(b->valores[b->qntd_itens-1],0,b->tamanho_tipo);
	return b->valores[b->qntd_itens-1];
}

//Libera todos as alocacoes da bag 'b'.
void liberar(bag* b){
	for(int i = 0; i < b->qntd_itens; i++){
		free(b->chaves[i]);
		free(b->valores[i]);
	}
	free(b->valores);
	free(b->chaves);
}


//Tira o ultimo caracter da palavra
void tiraEspaco(char* palavra){
	palavra[strlen(palavra)-1] = '\0';
}

//Verifica se a palavra 'palavra' esta na lista das palavras positivas.
int ehPositiva(char* palavra){	
	for(int i = 0; i < 12; i++){
		if(strcmp(palavra,positivas[i])==0){
			return 1;
		}		
	}
	return 0;
}

//Verifica se a palavra 'palavra' esta na lista das palavras negativas.
int ehNegativa(char* palavra){	
	for(int i = 0; i < 12; i++){
		if(strcmp(palavra,negativas[i])==0){
			return 1;
		}		
	}
	return 0;
}

//Verifica se a palavra 'palavra' esta na lista dos adverbios de negacao.
int ehAdverbio(char* palavra){	
	for(int i = 0; i < 3; i++){
		if(strcmp(palavra,adverbios[i])==0){
			return 1;
		}		
	}
	return 0;
}

int main() {

    //Le o numero de comentarios e 	perguntas
	int nComentarios;
	int nPerguntas;
    scanf("%d %d ", &nComentarios, &nPerguntas);

	//Cria uma bag para relacionar o nome dos aparelhos com outras bags, para utiliza-las como bag de frequancia de palavras.
	bag aparelhos;
	aparelhos.tamanho_tipo =sizeof(bag);
	aparelhos.qntd_itens = 0;
	aparelhos.chaves = NULL;
	aparelhos.valores = NULL;

    for(int i = 0;i < nComentarios; i++){
		
		//Le o nome do aparelho e atribui a variavel 'bag_aparelho' o endereco da bag de frequencias daquele aparelho.
		char* aparelho = malloc(30*sizeof(char));
		scanf("%[^;]%*c",aparelho);
		tiraEspaco(aparelho);
		bag* bag_aparelho = (bag*) valor(&aparelhos,aparelho);
		bag_aparelho->tamanho_tipo = sizeof(int);
		free(aparelho);
		
		//Le o comentario, verifica se tem palavras positivas ou negativas (considerando adverbios de negacao), e aumenta um na bag de frequencias para cada palavra.
		int nao_chegou_no_fim = 1;
		int eh_positiva = 0;
		int eh_negativa = 0;
		int negada = -1;
        while(nao_chegou_no_fim){
			char* palavra = malloc(20*sizeof(char));
			scanf("%s",palavra); 
			if(ehAdverbio(palavra)){
				negada = 3;
			}
			eh_negativa |= (ehNegativa(palavra) && negada < 0) || (ehPositiva(palavra) && negada >= 0);
			eh_positiva |= (ehPositiva(palavra) && negada < 0) || (ehNegativa(palavra) && negada >= 0);
			negada--;
			(*((int*)valor(bag_aparelho,palavra)))++;
			if(strcmp(palavra, "Ø")== 0){
				nao_chegou_no_fim = 0;
			}
			free(palavra);
		}

		//Usa as palavras "POSIVA" e "NEGATIVA" na bag do aparelho, para contar a quantidade de comentarios negativos/positivos do aparelho.
		if(eh_positiva){
			(*((int*)valor(bag_aparelho,"POSITIVA")))++;
		}
		if(eh_negativa){
			(*((int*)valor(bag_aparelho,"NEGATIVA")))++;
		}
		scanf("%*c%*c");
    }

    for(int i = 0; i < nPerguntas; i++){
		
		//Le a pergunta separando em comando(palavra/quantos), palavra e aparelho.
        char* aparelho = malloc(30 * sizeof(char*));
        char* palavra = malloc(30 * sizeof(char*));
        char* comando = malloc(30 * sizeof(char*));
        scanf("%s%s em %[^\r]",comando,palavra,aparelho );

		//Atribui a variavel 'bag_aparelho' o endereco da bag de frequencias daquele aparelho.
		bag* bag_aparelho = (bag*) valor(&aparelhos,aparelho);
		bag_aparelho->tamanho_tipo = sizeof(int);

		//Se o comando for "palavra", mostra na tela o quantas vezes a palavra apareceu nos comentarios do aparelho.
		if(strcmp(comando,"palavra")==0){
			int* val = (int*)valor(bag_aparelho,palavra);
			printf("%d\n",*val); 
        }

		//Se o comando for "quantos", mostra na tela a porcentagem de comentarios positivos/negativos.
        else{
			if(strcmp(palavra,"positivos")== 0){
				strcpy(palavra,"POSITIVA");
			}
			else{
				strcpy(palavra,"NEGATIVA");
			}
			int favoraveis = *((int*)valor(bag_aparelho,palavra));
			int espaco  = *((int*)valor(bag_aparelho,"Ø"));
			float porcentagem = 100.0*favoraveis/espaco;
			printf("%.1f%%\n", porcentagem);
		}
		free(comando);
		free(palavra);
		free(aparelho);
    }    

	//Libera todas as alocacoes usadas no programa.
	for(int i = 0; i < aparelhos.qntd_itens; i++){
		bag* b = (bag*)valor(&aparelhos,aparelhos.chaves[i]);
		liberar(b);
	}
	liberar(&aparelhos);
}
