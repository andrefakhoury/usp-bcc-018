#include <stdio.h>
#include <string.h>
//Tamanho máximo de diferentes palavras
#define MAX1 220
//Tamanho máximo de palavras
#define MAX2 30
//Define a palavra chave para as perguntas
#define QUEST1 "palavra"
#define QUEST2 "quantos"
#define QUEST2_POS "positivos"
#define QUEST2_NEG "negativos"
#define SIZE_POS 12
#define SIZE_NEG 12
#define SIZE_ADV 3

//Define as palavras especiais positivas,negativas e adverbiais. OBS.: Definição Global, porém constante logo não pode ser alterada
const char pos_words[][MAX2] = {"bom","maravilhoso","otimo","sensacional","excelente","adorei","gostei","amei","eficiente","boa","maravilhosa","otima"};
const char neg_words[][MAX2] = {"detestei","odiei","ruim","pessimo","terrivel","raiva","odio","pessima","lento","lenta","fragil","desisti"};
const char adv_words[][MAX2] = {"nao","jamais","nunca"};

/*Estrutura de um PAIR que contém:
	*char word[MAX]: Uma palavra
	*int qtd: a quantidade que aquela string se repete
*/
typedef struct{
	char word[MAX2];
	int qtd;
}Pair;
/*Estrutura de um PRODUCT que contém:
	*int size_name: Tamanho do nome do Product
	*int size_bag: Quantidade de palavras diferentes referidas ao produto
	*double pos_sent: Total de sentenças positivas
	*double neg_sent: Total de sentenças negativas
	*double pos_words: Total de palavras positivas
	*double neg_words: Total de palavras negativas
	*char name[MAX]: Nome do product
	*Pair bag[MAX]: Bag-of-words do produto que contém um pair com a palavra referida ao produto e a quantidade
*/
typedef struct{
	int size_name;
	int size_bag;
	double pos_sent;
	double neg_sent;
	double pos_words;
	double neg_words;
	char name[MAX2];
	Pair bag[MAX1];
}Product;
//Função que recebe a sentença e separa em palavras, atribuindo as palavras em words e retorna a quantidade de palavras extraídas
int split_string(char words[MAX1][MAX2],char line[MAX1],int size){
	int cont1 = 0,cont2 = 0,cont3 =0;
	if(line[0]==' ')
		cont1++;
	for(;cont1 < size;cont1++){
		if(line[cont1] != ' '){
			words[cont2][cont3]=line[cont1];
			cont3++;	
		}else{
			if(cont3 != 0){
				words[cont2][cont3]='\0';
				cont3 = 0;
				cont2++;
			}
		}
	}
	return cont2;	
}
//Função que recebe o nome de um produto e verifica se ele já foi lido anteriormente, retorna -1 caso não exista ou a posição do produto no vetor Products
int exist_product(char name[MAX2],Product products[MAX1],int size){
	int cont = 0;
	for(cont = 0;cont < size;cont++){
		if(strcmp(products[cont].name , name) == 0){
			return cont;
		}
	}
	return -1;
}
//Função que recebe uma palavra e verifica se ela já existe no Bag-of-Words passado, retorna -1 caso não exista ou a posição da palavra no vetor bag
int exist_word(char words[MAX2],Pair bag[MAX1],int size){
	int cont = 0;
	
	for(cont = 0;cont < size;cont++){
		if(strcmp(words, bag[cont].word) == 0){
			return cont;
		}
	}
	return -1;
}
//Função que verifica se uma palavra é um advérbio
int is_adverb(char word[MAX2]){
	int cont;
	for(cont = 0;cont < SIZE_ADV;cont++){
		if( strcmp(word,adv_words[cont]) == 0 )
			return 1;
	}
	return 0;
}
//Função que verifica se a palavra é positiva e se ela tem negação de adverbio
int is_positive(char word[MAX1][MAX2],int pos){
	int cont,is = 0;
	for(cont = 0;cont < SIZE_POS;cont++){
		if(strcmp(word[pos],pos_words[cont]) == 0 ){
			is = 1;
			break;
		}
	}
	if(is){
		for(cont = 1;(cont <= 3)&&((pos-cont)>=0);cont++){
			if( is_adverb(word[(pos-cont)]) ){
				return -1;
			}
		}
	}
	return is;
}
//Função que verifica se a palavra é negativa e se ela tem negação de adverbio
int is_negative(char word[MAX1][MAX2],int pos){
	int cont,is = 0;
	for(cont = 0;cont < SIZE_NEG;cont++){
		if( strcmp(word[pos],neg_words[cont]) == 0 ){
			is = 1;
			break;
		}
	}
	if(is){
		for(cont = 1;(cont <= 3)&&((pos-cont)>=0);cont++){
			if( is_adverb(word[(pos-cont)]) ){
				return -1;
			}
		}
	}
	return is;
}

int main(){
	
	//Variáveis auxiliáveis do programa
	int exist_p,exist_w,cont3,cont2,cont=0,size_sent,size_quest,size_products=0,size_bag = 0;
	char crc='.';
	//Vetores de leitra do nome do produto e da sentença
	char sent[MAX1],product_name[MAX2],quest[MAX1];	
	//Instancia do vetor de produtos lidos
	Product products[MAX1],product;
	//Instancia de um Bag-of-words
	Pair pair;
	//Leitura da quantidade de sentenças e perguntas
	scanf("%d %d", &size_sent,&size_quest);
	//Limpa buffer do teclado pegando o caractere de nova linha
	getchar();
	getchar();
	//Loop de leitura das Sentenças
	for(cont2 = 0;cont2 < size_sent;cont2++){
		//Inicialização de variáveis auxiliares
		cont =0;
		crc='.';
		size_bag = 0;
		//Leitura do nome do produto até o caractere ';'
		scanf("%[^;]",product_name);
		//Verifica se existe o produto lido nos products
		exist_p = exist_product(product_name,products,size_products);
		//Limpa buffer do teclado pegando o caractere de nova linha
		getchar();
		
		//Caracteres a ignorar: (int)-99 e Ø e \n e null(\0)
		//Leitura da sentença até o fim da linha
		while(crc != '\0' && crc != 'Ø' && crc != '\n' && crc != -99){
			scanf("%c",&crc);
			if(crc != '\0' && crc != 'Ø' && crc != '\n' && crc != -99){
				sent[cont]=crc;
				cont++;
			}else{
				sent[cont]='\0';
			}
		}
		char words[MAX1][MAX2];
		int is_pos = 0,is_neg = 0;
		double total_positives = 0,total_negatives=0;
		//Separa a sentença em palavras
		int tam = split_string(words,sent,strlen(sent));
		//Se o produto não existe Adicione nos products, se existe apenas altere seu bag-of-words
		if(exist_p == -1){
			//Verifica todas palavras da sentença
			for(cont3=0;cont3<tam;cont3++){
				//Verifica se a palavra é positiva ou negativa
				is_pos = is_positive(words,cont3);
				is_neg = is_negative(words,cont3);
				if(is_pos == 1)
					total_positives++;
				if(is_pos == -1)
					total_negatives++;
				if(is_neg == 1)
					total_negatives++;
				if(is_neg == -1)
					total_positives++;
				
				//Verifica se a palavra já existe no bag-of-words
				exist_w = exist_word(words[cont3],product.bag,size_bag);
				//Se não existe adicione no bag-of-words com tamanho 1, se existe apenas aumente seu tamanho
				if(exist_w == -1){
					strcpy(pair.word,words[cont3]);
					pair.qtd = 1;
					product.bag[size_bag] = pair;
					size_bag++;
				}else{
					product.bag[exist_w].qtd++;
				}
			}
			//Adiciona o produto nos vetores dos produtos
			product.size_name = strlen(product_name);
			product.size_bag = size_bag;
			strcpy(product.name,product_name);
			product.pos_words = total_positives;
			product.neg_words = total_negatives;
			product.pos_sent = 0;
			product.neg_sent = 0;
			if(total_positives > 0){
				product.pos_sent++;
			}else if(total_negatives > 0){
				product.neg_sent++;
			}
			products[size_products] = product;
			size_products++;
		}else{
			//Verifica todas palavras da sentença
			for(cont3=0;cont3<tam;cont3++){
				//Verifica se a palavra é positiva ou negativa
				is_pos = is_positive(words,cont3);
				is_neg = is_negative(words,cont3);
				if(is_pos == 1)
					total_positives++;
				if(is_pos == -1)
					total_negatives++;
				if(is_neg == 1)
					total_negatives++;
				if(is_neg == -1)
					total_positives++;
					
				//Verifica se a palavra já existe no bag-of-words do produto já existente
				exist_w = exist_word(words[cont3],products[exist_p].bag,products[exist_p].size_bag);
				//Se não existe adicione no bag-of-words do produto com tamanho 1, se existe apenas aumente seu tamanho
				if(exist_w == -1){
					strcpy(pair.word,words[cont3]);
					pair.qtd = 1;
					products[exist_p].bag[products[exist_p].size_bag] = pair;
					products[exist_p].size_bag++;
				}else{
					products[exist_p].bag[exist_w].qtd++;
				}
			}
			if(total_positives > 0){
				products[exist_p].pos_sent++;
			}else if(total_negatives > 0){
				products[exist_p].neg_sent++;
			}
			products[exist_p].pos_words += total_positives;
			products[exist_p].neg_words += total_negatives;
		}
	}
	

	//Loop de leitura das perguntas
	for(cont2 = 0;cont2 < size_quest;cont2++){
		//Leitura da pergunta
		scanf("%[^\n]",quest);
		//Limpa buffer do teclado
		getchar();
		//Cria variáveis auxiliares
		int size_name=0,total_space = 0,comp;
		char words[MAX1][MAX2];
		char product_name_quest[MAX2];
		//Separa a pergunta em palavras
		split_string(words,quest,strlen(quest));
		comp = strlen(quest);
		if(size_quest > 1 && cont2+1!=size_quest)
			comp--;
		//Extrai o produto alvo da pergunta 
		for(cont = 0;cont < comp;cont++){
			if(total_space ==3){
				product_name_quest[size_name] = quest[cont];
				size_name++;
			}else if(quest[cont] == ' '){
				total_space++;
			}
			if(cont+1 == comp){
				product_name_quest[size_name] = ' ';
				size_name++;
				product_name_quest[size_name] = '\0';
			}
		}	
		//Verifica se o produto da pergunta já teve alguma leitura
		exist_p = exist_product(product_name_quest,products,size_products);
		//Se existe Verifica a pergunta
		if(exist_p != -1){
			//Verifica se a pergunta é do primeiro tipo ou do segundo
			if(strcmp(QUEST1,words[0]) == 0){
				//Verifica se a palavra alvo da pergunta existe relacionado ao produto
				exist_w = exist_word(words[1],products[exist_p].bag,products[exist_p].size_bag);
				//Se não existe então digite 0, se existe digite a quantidade de vezes que ela foi usada relacionado ao produto
				if(exist_w == -1){
					printf("0\n");
				}else{
					printf("%d\n",products[exist_p].bag[exist_w].qtd);
				}
			}else if(strcmp(QUEST2,words[0]) == 0){
				double prcent;
				//Verifica se quer comentários positivos ou negativos
				if(strcmp(QUEST2_POS,words[1]) == 0){
					//printf("%lf %lf\n",products[exist_p].pos_words,products[exist_p].neg_words);
					//Calcula a porcentagem de comentarios positivos
					if((products[exist_p].pos_sent+products[exist_p].neg_sent) != 0)
						prcent = 100*products[exist_p].pos_sent / (products[exist_p].pos_sent+products[exist_p].neg_sent);
					else
						prcent = 0;
						
					printf("%.1lf%%\n",prcent);
				}else if(strcmp(QUEST2_NEG,words[1]) == 0){
					//Calcula a porcentagem de comentarios negativos
					if((products[exist_p].pos_sent+products[exist_p].neg_sent) != 0)
						prcent = 100*products[exist_p].neg_sent / (products[exist_p].pos_sent+products[exist_p].neg_sent);
					else
						prcent = 0;
						
					printf("%.1lf%%\n",prcent);
				}
			}
		}
	}

	return 0;
}
