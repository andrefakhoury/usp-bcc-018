/*
Trabalho 2 de ICC (03/06/19)
Aluno: Benrardo Silva de Andrade
NºUSP: 11218789
Professor: Rudinei Goularte
*/


/*
COMENTARIO SOBRE O TRABALHO:
Encontrei muitas dificuldades para a realizacao do trabalho, tive que pedir ajud a veteranos e amigos.
No fim, acredito que tenha respeitado a realizaçao dos objetivos, considerando a estruturaçao do codigo e a existencia de todas as funcoes necessarias
Nao consegui resolver todos os casos teste, nao consegui resolver o caso bonus.
Entretanto, nos casos 1, 2 e 3 meu codigo deu certo, porem nao apareceu no run.codes como correto.
Comparei as saidas com, pelo menos, 4 amigos e nenhum de nos entendemos onde nem porque pode estar dando como incorreto
Nao sei se foi o \n , se precisava ser outra coisa, mas acredito que, ao meu ver, tenha rodado corretamente
Enfim, peço compaixao na correcao <3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 //aqui fica a minha bag of words: ela armazena uam sentenca, uma palavra da sentenca e quantas vezes ela aparece
typedef struct Bag_of_Words{
	char* palavra;
	int count;
}BAG;

//aqui fica os dados do produto: seu nome, o tamanho de sua bag of words, o vec_count, que aponta para sua Bag of Words, grava tb a propria sentenca e n de frases
typedef struct Produto{ 
	char* tipo_marca;
	int tam_bag;
	BAG* vec_count;
	char** sentenca;
	int qtdfrases;
}PRODUTO;

//optei por declarar esses globalmente pois se fizesse dentro das funcoes, pois ele teria que ficar realocando n vezes memoria para eles 
char positivos[12][20] = {"bom\0", "maravilhoso\0", "otimo\0", "sensacional\0", "excelente\0", "adorei\0", "gostei\0", "amei\0", "eficiente\0", "boa\0", "maravilhosa\0", "otima\0"};
char negativos[12][20] = {"detestei\0", "odiei\0", "ruim\0", "pessimo\0", "terrivel\0", "raiva\0", "odio\0", "pessima\0", "lento\0", "lenta\0", "fragil\0", "desisti\0"};

// essa funcao checa se existe produto, retornando -1 para criar um novo ou, caso ja exista, sua posicao na lista de produtos
int existe_produto(PRODUTO* lista_produtos, int num_produtos, char* nome_produto){ 
	int i=0;
	for(i = 0; i < num_produtos; i++){
		if(strcmp(lista_produtos[i].tipo_marca, nome_produto) == 0){
			return i;
		}
	}
	return -1;
}
// essa funcao serve para checar se a palavra ja existe na Bag of Words do produto: se nao, retorna -1 para adiciona-la. se sim, retorna sua posicao na Bag do produto
int existe_palavra(BAG* bag, int tam_bag, char* palavra){
	int i=0;
	for(i = 0; i < tam_bag; i++){
        //printf("%s:%d\n", bag[i].palavra, bag[i].count);
		if(strcmp(bag[i].palavra, palavra) == 0){
			return i;
		}
	}
	return -1;
}

float Porcentagem(char polar, char *nome_produto, PRODUTO *product){ // funcao que responde a porcentagem de positivos / negativos

	int i = 0, j = 0;
    char *ptr = NULL, buffer[1000];
	int acmposi = 0, acmneg = 0;// acumulada positivos, acumulada negativos
	char jarotulei = 0; // ve se ja achei positivo ou negativo na frase, se sim, ele passa p proxima
	
	for(i=0; i < product->qtdfrases; i++){ //compara palavra a palavra pra encontrar posi ou neg nas frases
	    strcpy(buffer, product->sentenca[i]);
	    jarotulei = 0;
    	for(ptr = strtok(buffer, " "); ptr != NULL; ptr = strtok(NULL, " ")){
	    	for(j=0; j< 12; j++){
	    		if(strcmp(ptr, positivos[j]) == 0){// percorrendo o vetor das positivas e acumulando as vezes q ela aparece
	    			acmposi++;
	    			jarotulei = 1;
	    			break;
	    		}
			    if(strcmp(ptr, negativos[j]) == 0){// percorrendo o vetor das negativas e acumulando as vezes q ela aparece
			    	acmneg++;
	    			jarotulei = 1;
	    			break;
			    }
	    	}
	    	if(jarotulei == 1) break;
	    }
	}
		
	if(polar == 'p'){ // se ele pedir positivas (p), a porcentagem contara postivas/total
		return (((float)acmposi/(acmneg+acmposi))*100);
	}
	else if(polar == 'n'){ // se ele pedir negativas (n), a porcentagem contara negativas/total
		return (((float)acmneg/(acmposi+acmneg))*100);
	}
	return 0;
}
	
		
	
int Quantas_vezes(char *palavra_desejada, PRODUTO *produto){ // funcao que responde quantas vezes uma palavra aparece
	int i=0;
	for(i=0; i< produto->tam_bag; i++){
		if(strcmp(palavra_desejada, produto->vec_count[i].palavra) == 0){
			return ((int)produto->vec_count[i].count);
		}
	}
	return 0;
	
}


int main(void){
	int num_com=0;
	int num_perg=0;
	int num_produtos = 0;
	int pos_prod=0;
	int pos_palavra = 0;
	int i=0, j=0;
	PRODUTO *lista_produtos = NULL;
	char *nome_produto, *sentenca; 
	
	scanf("%d %d\n", &num_com, &num_perg); //pego o numero de comentarios e numero de perguntas
	
	PRODUTO *produto = NULL;
	lista_produtos = (PRODUTO*)calloc(num_com, sizeof(PRODUTO)); // armazena espaço para a lista de produtos: no max, teremos n de produtos == ao num de comentarios
	for(i = 0; i < num_com; i++){ 
		scanf("%m[^;]; %m[^\n]\n", &nome_produto, &sentenca); // lendo os comentarios e separando entre nome do produto e sentenca
	
		pos_prod = existe_produto(lista_produtos, num_produtos, nome_produto); // a posicao do produto depende se ele ja existe ou nao 
		if(pos_prod == -1){//se ainda nao exite esse produto
			produto = &lista_produtos[num_produtos];
			produto->tipo_marca = nome_produto;
			produto->vec_count = (BAG *)calloc(200, sizeof(BAG));//defino maxi 200 palavras
			num_produtos++;
			produto->sentenca = (char **)calloc(num_com, sizeof(char *));
			produto->sentenca[produto->qtdfrases++] = sentenca;
		}
		else{// se ja existe esse produto
			produto = &lista_produtos[pos_prod];
			produto->sentenca[produto->qtdfrases++] = sentenca;
		}
	    char buffer2[1000];
	    strcpy(buffer2, sentenca);
    	char *ptr = strtok(buffer2, " ");
    	for(j=0; j<20 && ptr != NULL; j++, ptr = strtok(NULL, " ")){ // esse for serve para separarmos a sentenca em palavras
        	pos_palavra = existe_palavra(produto->vec_count, produto->tam_bag, ptr);
        	if(pos_palavra != -1){ // se palavra ja existe, adicionamos somente ao seu contador
        		produto->vec_count[pos_palavra].count++;
        	}
            else{ // se nao existe, adicionamos a palavra na bag, aumentamos o tamanho da bag e adicionamos ao seu contador
	    	   	produto->vec_count[produto->tam_bag].palavra = ptr;
	    	   	produto->vec_count[produto->tam_bag++].count++;
	        }
    	}
	}

	char primeiraletra = 0;
	char *posi_neg=0;
	char *palavraquevoubuscar = 0;
	for(i = 0; i < num_perg; i++){ //respondendo as perguntas
		scanf("%c", &primeiraletra); //pegaremos a primeira letra de cada pergunta
		if(primeiraletra == 'q'){ // se for Q, teremos que responder a porcentagem de positivos e negativos
			scanf("uantos %m[^ ] em %m[^\n]\n", &posi_neg, &nome_produto);
			printf("%.1f%%\n", Porcentagem(posi_neg[0], nome_produto, produto)); //funcao que responde a pergunta
		}
		else if(primeiraletra == 'p'){ // se for P, teremos que responder a quantidade de vezes que tal palavra aparece para o produto
			scanf("alavra %m[^ ] em %m[^\n]\n", &palavraquevoubuscar, &nome_produto);
			printf("%d\n", Quantas_vezes(palavraquevoubuscar, produto)); // funcao que responde a pergunta
		}
	}
	// aqui desaloco oq usei de heap :)
	for(i = 0; i < num_produtos; i++){
	    for(j = 0; j < lista_produtos[i].qtdfrases; j++){
	        free(lista_produtos[i].sentenca[j]);
	    }
	    free(lista_produtos[i].sentenca);
	    
	    for(j = 0; j < lista_produtos[i].tam_bag; j++){
	        free(lista_produtos[i].vec_count[j].palavra);
	    }
	    
	    free(lista_produtos[i].vec_count);
	    
	    free(lista_produtos[i].tipo_marca);
	}
	free(lista_produtos);
	
	return 0;
}

