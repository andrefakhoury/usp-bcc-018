#include <stdio.h>
#include <string.h>

int word_in_bow(char word[20], char word_header[200][20]){
	for(int i = 0; i < 200; i++){
		if(strcmp(word,word_header[i]) == 0){
			return i;
		}
	}
	return -1;
}

int product_in_bow(char product[50], char prod_header[10][50]){
	for(int i = 0; i < 10; i++){
		if(strcmp(product, prod_header[i]) == 0){
			return i;
		}
	}
	return -1;
}

// polaridade simples
int get_polarity(char sentence[20][20]){
	char termos_positivos[12][20] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char termos_negativos[12][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    char negacoes[3][20] = {"nao", "nunca", "jamais"};

    int flag_negacao = -1;

    for(int i = 0; i < 20; i++){

    	for(int j=0; j < 12; j++){
	    	if(strcmp(sentence[i],termos_positivos[j]) == 0){
	    		if(i <= flag_negacao){
	    			return -1;
	    		}else{
		    		return 1;
		    	}
	    	}
	    	if(strcmp(sentence[i],termos_negativos[j]) == 0){
	    		if(i <= flag_negacao){
	    			return 1;
	    		}else{
		    		return -1;
		    	}
	    	}
    	}

    	for(int k=0; k < 3; k++){
	    	if(strcmp(sentence[i],negacoes[k]) == 0){
	    		flag_negacao = i+3;
	    	}
    	}
    }
    return 0;
}


void imprime_bow(char prod_header[10][50], char word_header[200][20]){
	printf("\nImprimindo ---------------------\n");
	printf("Prod:\n");
	for(int i = 0; i < 10; i++){
		if(strcmp("Ø", prod_header[i]) != 0){
			printf("%d %s\n",i, prod_header[i]);
		}
	}
	printf("Palavras:\n");
	for(int i = 0; i < 200; i++){
		if(strcmp("Ø", word_header[i]) != 0){
			printf("%d %s\n",i, word_header[i]);
		}
	}
}

void imprime_pol(char prod_header[10][50], int pos[10], int neg[10]){
	printf("\nImprimindo ---------------------\n");
	for(int i = 0; i < 10; i++){
		if(strcmp("Ø", prod_header[i]) != 0){
			printf("%d %s %d %d\n",i, prod_header[i], pos[i], neg[i]);
		}
	}
}

void imprime_full_bow(char prod_header[10][50], char word_header[200][20], int bow[10][200]){
	int max_word = 0;
	for(int i =0; i < 200; i++){
		if(strcmp(word_header[i],"Ø")==0){
			max_word = i;
			break;
		}
	}

	for(int i=-1;i<10;i++){
		if(i == -1){
			printf("\t");
		}else{
			if(strcmp(prod_header[i],"Ø")==0){
				break;
			}else{
				printf("%s\t",prod_header[i]);
			}
		}
		for(int j=0;j<max_word;j++){
			if(i == -1){
				printf("%s\t",word_header[j]);
			}else{
				printf("%d\t",bow[i][j]);
			}
		}
		printf("\n");
	}
}

int main(){
	// Numero de sentenças
	int n_sent, n_questions;
	scanf("%d %d", &n_sent, &n_questions);

	// Bag of words
	int bow[10][200];
	char product_header[10][50];
	char word_header[200][20];
	int positive_pol[10];
	int negative_pol[10];

	int pos_prod, pos_word;
	printf("Step one");
	// Clean structures
	for(int i = 0; i < 200; i++){
		if(i < 10){
			strcpy(product_header[i],"Ø");
			positive_pol[i] = 0;
			negative_pol[i] = 0;
		}
		strcpy(word_header[i],"Ø");
		for(int j = 0; j < 10; j ++){
			bow[j][i] = 0;
		}
	}
	printf('Its okay');
	// Read lines and fill bow
	for(int i=0; i<n_sent; i++){
		// read product
		char produto[20] = "";
		char marca[20] = "";
		scanf("%s %s ; ", produto, marca);
		
		char prod_name[50] = "";
		
		strcat(prod_name,produto);
		strcat(prod_name," ");
		strcat(prod_name,marca);

		// Check if product in bow
		pos_prod = product_in_bow(prod_name,product_header);
		// If it is not - add new product to the bow
		if(pos_prod == -1){
			for(int j=0; j < 10; j++){
				if(strcmp(product_header[j],"Ø") == 0){
					pos_prod = j;
					strcpy(product_header[j],prod_name);
					break;
				}
			}
		}

		// read sentence and fill bow
		char sentence[20][20];
		for(int j = 0; j < 20; j++){
			scanf("%s",sentence[j]);
			// if it is the end of sentence
			if(strcmp(sentence[j],"Ø")==0){
				break;
			}else{
				// check if word in bow
				pos_word = word_in_bow(sentence[j],word_header);

				// if it is not, then add it to bow
				if(pos_word == -1){
					for(int k=0; k < 200; k++){
						if(strcmp(word_header[k],"Ø") == 0){
							pos_word = k;
							strcpy(word_header[k],sentence[j]);
							break;
						}
					}
				}
			}

			// increase counting in bow
			bow[pos_prod][pos_word]++;
		}
		if( get_polarity(sentence) > 0){
			positive_pol[pos_prod]++;
		}else{
			negative_pol[pos_prod]++;
		}

	}
	//imprime_pol(product_header, positive_pol, negative_pol);
	//imprime_bow(product_header,word_header);
	//imprime_full_bow(product_header,word_header,bow);
	
	// reading questions
	for(int i=0; i < n_questions;i++){
		char question[5][20];
		for(int j = 0; j < 5; j++){
			scanf("%s",question[j]);
		}
		int index_word, index_prod;
		char prod_query[50] = "";
			
		strcat(prod_query,question[3]);
		strcat(prod_query," ");
		strcat(prod_query,question[4]);
		
		index_prod = product_in_bow(prod_query,product_header);

		// question - how many times a word appears?
		if(strcmp(question[0],"palavra") == 0){
			index_word = word_in_bow(question[1],word_header);
			printf("%d\n", bow[index_prod][index_word]);
		// question - how many people are speaking nice/bad stuff about a brand? 
		}else{
			float total = positive_pol[index_prod]+negative_pol[index_prod];
			
			if(strcmp(question[1],"positivos")==0){
				float pos_percent = 100*positive_pol[index_prod]/total;
				printf("%.1f%%\n",pos_percent);
			}else{
				float neg_percent = 100*negative_pol[index_prod]/total;
				printf("%.1f%%\n",neg_percent);
			}
		}
	}

	return 0;
}