/*Created by Henrique Hiram Libutti Núñez ©2019 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Defining constants for analysis*/

#define POSITIVE 1
#define NEGATIVE -1

char *GOOD_WORDS[] = {
	"bom", 
	"maravilhoso", 
	"otimo", 
	"sensacional", 
	"excelente", 
	"adorei", 
	"gostei", 
	"amei", 
	"eficiente", 
	"boa", 
	"maravilhosa", 
	"otima",
    "STOP"
    };

char *BAD_WORDS[] = {
	"detestei", 
	"odiei", 
	"ruim", 
	"pessimo", 
	"terrivel", 
	"raiva", 
	"odio", 
	"pessima", 
	"lento", 
	"lenta", 
	"fragil", 
	"desisti",
    "STOP"
    };
        
char *INV_WORDS[] = {
    "nao",
    "jamais",
    "nunca",
    "STOP"
    };

/*Struct for storing the product information and its related bag of words*/    

typedef struct _products{
	char* name;
    char** bag_of_words;
    int* n_bag_of_words;
    int bag_size;
    int meaning;
    } products;

int check_in_bag(char* test_word , char** this_bag , int bag_size);
int check_type(char* test_word , char** type);
products read_entry();
void store_in_bag(char *review , products* prod);
float review_type(char* prod , products* entries , int type , int num_entries);
void free_entries(products* entries , int num_entries);
void query(char* input , products* entries , int num_entries , int query_num);
void count_words(char* prod , products* entries , char* search_word , int num_entries);
void strip(char *s);
char *choppy( char *s );

int main(){
	int nreviews;
	int nquestions;
	int index;
    
    char out_buff[1024];
    setvbuf(stdout, out_buff, _IOFBF, 1024); //output buffer
	
    unsigned long int t = 0; //variables for query acquisition
    char* input = NULL;
    
    scanf(" %d %d " , &nreviews , &nquestions);
	
    products* entry = (products*) malloc(nreviews * sizeof(products));
	
	for (index = 0 ; index < nreviews ; index++){
        entry[index] = read_entry();
        /*entry = (products*) realloc (entry , (index+1) * sizeof(products));*/
	}
    
    //printf("delbem\n");
    
    for (index = nquestions-1 ; index >= 0; index--){
        /*review_type("Impressora Epson " , entry , POSITIVE , nreviews);*/
        getline(&input , &t , stdin);
        query(input , entry , nreviews , index);
    }
    
    fflush(stdout);
    free_entries(entry , nreviews);
    free(entry);
    return 0;
    }

products read_entry(){
    
    products this_product;
    char* input = NULL;
    unsigned long int t = 0;
    char* prod;
    char* _review;
    this_product.name = NULL;
    
    getline(&input , &t , stdin);
    prod = strtok(input , ";");
    //prod = (char*) realloc (prod , strlen(prod)+2);
    _review = strtok(NULL , "Ø");
    sscanf(prod , "%s[^;];" , this_product.name);
    this_product.name = prod; 
    
    
    store_in_bag(_review , &this_product);

    return this_product;
    }

void store_in_bag(char *review ,  products* prod){ 
    prod->meaning = 0;
    int bag_size = 1;
    int aux_meaning;
    int iteration = 0; /*iteration upon the received string*/
    int inv_aux = -4; /*initialize, otherwise the meaning will be changed unproperly, aka "INVERTENDO OPINIOES"*/
    int check_return;
    char* word;
    
    char** words_in_review = (char**) calloc (200 , 200 * sizeof(char*));
    int* n_words_in_review = (int*) calloc (200 , 200 * sizeof(int));
    
    word = strtok ( review ," ");
    while (word != NULL){
        
        iteration++;
        if (check_type(word , INV_WORDS)){ /*checks if the analysis needs to be inverted*/
           
            inv_aux = iteration + 3; /*Stores the iteration(position in review) for inversion */
            } 
            else {
                if(iteration <= inv_aux){
                    aux_meaning = prod->meaning;
                    prod->meaning += (check_type(word , GOOD_WORDS) - check_type(word , BAD_WORDS))*(-1);
                    
                    if(aux_meaning != prod->meaning) inv_aux = -1;
                } 
                else {
                    prod->meaning += (check_type(word , GOOD_WORDS) - check_type(word , BAD_WORDS));
                }
            }
        
        
        check_return = check_in_bag(word , words_in_review , bag_size - 1); /*checks wether the word was already entered or not*/
        
        if (check_return == -1){ /*creates new bag entry, if the word was not found*/
            
            words_in_review[bag_size-1] = (char*) malloc (20*sizeof(char));
            strcpy(words_in_review[bag_size-1] , word);
            
            n_words_in_review[bag_size-1] = 1;
            bag_size++;
                        
            } else {
                n_words_in_review[check_return]++;
                
                }
        word = strtok(NULL, " ");
    }
    
    
    prod->bag_size = --bag_size;
    
    prod->n_bag_of_words = n_words_in_review;
    prod->bag_of_words = words_in_review;
    
    }
    
int check_in_bag(char* test_word , char** this_bag , int bag_size){
	int i;
	for (i = 0 ; i < bag_size ; i++){
        if(this_bag[i] == NULL) {
            break;
            }
		if(strcmp(test_word , this_bag[i]) == 0){
			return i;
		}
	}
    return -1;
    }    
    
int check_type(char* test_word , char** type){
    int i = 0;
    while(strcmp(type[i] , "STOP") != 0){
        /*printf("testing... %s\n" , type[i]);*/
        if (strcmp(type[i] , test_word) == 0) {
            /*printf("just found the type!!\n");*/
            return 1;
            }
        i++;
        }
    return 0;
    }

float review_type(char* prod , products* entries , int type , int num_entries){
    
    int i;
    int num_prod = 0;
    int num_of_type = 0;
    float ratio;
    
    for (i = 0 ; i < num_entries ; i++){ //counts how many reviews are of the related type
        //printf("");
        if(strcmp(entries[i].name , prod) == 0){
            num_prod++;
        
            if( (entries[i].meaning > 0 && type > 0) || (entries[i].meaning < 0 && type < 0) ) { /*checks wether meaning and type have the same sign*/
                num_of_type++;
            }
        }
    }
    
    ratio = ((float)num_of_type/(float)num_prod)*100;
    
    fprintf( stdout ,"%.1f%%\n" , ratio);
    return ratio;
    }

void count_words(char* prod , products* entries , char* search_word , int num_entries){ //counts words within the entries, by checking the matching of those
    
    int i;
    int j;
    int times_appeared = 0;
    
    for (i = 0 ; i < num_entries ; i++){
        //printf("");
        if(strcmp(entries[i].name , prod) == 0){
            for (j = 0 ; j < entries[i].bag_size ; j++){
                
                if(strcmp(entries[i].bag_of_words[j] , search_word) == 0){
                    times_appeared += entries[i].n_bag_of_words[j];
                    break;
                    } 
                }
            }
        }
    fprintf(stdout , "%d\n" , times_appeared);
    }

void query(char* input , products* entries , int num_entries , int query_num){ //parses the received query for further interpretation of the review
        char* command = NULL;
        char* buffer = NULL;
        char* prod_name = (char*) calloc (50 , 50 * sizeof(char));
        bool query_type;
               
        command = strtok(input , " ");
        
        if (strcmp(command , "palavra") == 0){
            command = strtok(NULL , " ");
            query_type = true;
        } else {
            command = strtok(NULL , " ");
            query_type = false;
        }
        
        strtok(NULL , " "); /* em */
        
        buffer = strtok(NULL , " \n");
        strcat(prod_name , buffer);
        buffer = strtok(NULL , " \n");
        
        while(buffer != NULL){
            strcat(prod_name , " ");
            strcat(prod_name , buffer);
            buffer = strtok(NULL , " \n");
        }
        
        if(query_num)
        prod_name = choppy(prod_name);
        
        strcat(prod_name , " ");
        
        if(query_type){ /*palavra X*/
            count_words(prod_name , entries , command , num_entries);
        } else { /*quantos X*/
            if (strcmp(command , "positivos") == 0){
                review_type(prod_name , entries , POSITIVE , num_entries);
            } else {
                review_type(prod_name , entries , NEGATIVE , num_entries);
            }
        }
        
    }
    
void free_entries(products* entries , int num_entries){ //frees the allocated memory
        int i , j ;
        
        for(i = 0 ; i < num_entries ; i++){
            free(entries[i].name);
            free(entries[i].n_bag_of_words);
            for(j = 0 ; j < entries[j].bag_size ; j++){
                free(entries[i].bag_of_words[j]);
            }
            free(entries[i].bag_of_words);
        }
    }

char *choppy( char *s ){ //removes the last character of a string in case it's \n
    char *n = malloc( strlen( s ? s : "\n" ) );
    if( s )
        strcpy( n, s );
    n[strlen(n)-1]='\0';
    return n;
}
    
