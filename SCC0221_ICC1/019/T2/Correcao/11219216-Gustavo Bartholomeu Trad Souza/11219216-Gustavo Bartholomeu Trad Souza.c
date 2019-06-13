#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------------------------

 //Define o número máximo de palavras em cada sentença(20 da frase + 4 dos complementos)
#define MAXPALAVRAS 24

 //Define o número máximo de letras em cada palavra
#define MAXLETRAS 19

//Define o número máximo de palavras em cada pergunta
#define MAXPERGUNTA 5

//Define o número maximo de palvras em cada item do BoW 
#define MAXBOW 200

//Define o caracter que sinaliza o final da frase 
#define END "Ø" 

//_____________________________________
typedef struct BOW{                  //|
    char marca[MAXLETRAS];           //|
    char prod[MAXLETRAS];            //|
    char palavras[MAXBOW][MAXLETRAS];//|->Struct de cada produto do BoW
    char num_palavra[MAXBOW];        //|
    int last_index;                  //|
}bow;                                //|
//_____________________________________|

//--------------------------------------------------------------------------------------------------

//Função que aloca posições na memória  
char ***aloca(int n, int pal, int let); 

 //Função que trata da entrada das sentenças
void get_sent(int nsent, char ***sent);

//Função que trata da entrada das perguntas
void get_perg(int nperg, char ***perg);

 //Função que identifica o tipo de cada pergunta e mostra os resultados
void do_perg(int nperg, char ***perg, int nsent, char ***sent);

//Função que calcula a porcentagem de comentários do tipo desejado
float porcent_coment(int nsent, char ***sent, char *prod, char *marca, char *tipo); 

//Função que identifica a inversão de polaridade da frase
int pol_invert(int i, int j, char ***sent); 

 //Função que gera o BoW
bow *do_bow(char ***sent, int nsent);

//Função que checa a palvra desejada no BoW
int check_bow(bow *BoW, int nsent, char *prod, char *marca, char *palavra);

//Função que limpa as posições alocadas pela funçao 'aloca'
void free_mat(int n, int pal, char ***mat);

//--------------------------------------------------------------------------------------------------

int main(){
    int nsent,nperg;
    scanf("%d %d", &nsent, &nperg);
    
    char ***sent, ***perg;
    sent=aloca(nsent, MAXPALAVRAS, MAXLETRAS);
    perg=aloca(nperg, MAXPERGUNTA, MAXLETRAS);

    get_sent(nsent, sent); 
    get_perg(nperg, perg); 
    
    do_perg(nperg, perg, nsent, sent); 

    free_mat(nperg, MAXPERGUNTA, perg);
    free_mat(nsent, MAXPALAVRAS, sent); 
}

//-------------------------------------------------------------------------------------------------

char ***aloca(int n, int pal, int let){
    //______________________________________
    char ***out;                          //|
    out=(char***)malloc(n*sizeof(char**));//|->Aloca a primeira dimensão que guarda as frases
    //______________________________________|
    
    for(int i=0; i<n; i++){
        out[i]=(char**)malloc(pal*sizeof(char*)); //|->Aloca a segunda dimensão que guarda as palavras de cada frase
        
        for(int j=0; j<pal; j++){
            out[i][j]=(char*)malloc(let*sizeof(char)); //|->Aloca a terceira dimensão que guarda as letras de cada palavra
        }
    }
    return out;
}

//-------------------------------------------------------------------------------------------------

void get_sent(int nsent, char ***sent){

    for(int sent_num=0; sent_num<nsent; sent_num++){ //Itera pelas matrizes das sentenças
        
        int pal_num=0; //Contador de palavras (para avançar uma posição a cada palvra inserida)

        do{
            scanf("%s", &sent[sent_num][pal_num][0]);
            pal_num++;
        
        }while(strcmp(sent[sent_num][pal_num-1],END)); //A função permanece na sentença até encontrar o caracter que indica o fim (Ø)
    }
}

//-------------------------------------------------------------------------------------------------

void get_perg(int nperg, char ***perg){

    for(int perg_num=0; perg_num<nperg; perg_num++){ //Itera pelas matrizes das perguntas
        
        int pal_num=0; //Contador de palavras (para avançar uma posição a cada palvra inserida)
        
        while(pal_num<MAXPERGUNTA){

           scanf("%s", perg[perg_num][pal_num]); 
           pal_num++; 
        
        } 
    }
}

//-------------------------------------------------------------------------------------------------

void do_perg(int nperg, char ***perg, int nsent, char ***sent){
    //______________________________________
    bow *BoW;                             //|
    BoW=(bow*)malloc(nsent*sizeof(bow));  //|-> Inicializa o Bag of Words e o preenche
    BoW=do_bow(sent, nsent);              //|
    //______________________________________|
    //___________________________________________________________________________________
    for(int i=0; i<nperg; i++){                                                        //|
                                                                                       //|
        if(!strcmp(perg[i][0],"palavra")){                                             //|
                                                                                       //|
            int qt=check_bow(BoW, nsent, perg[i][3], perg[i][4], perg[i][1]);          //|
            printf("%d\n", qt);                                                        //|
                                                                                       //|
        }else if(!strcmp(perg[i][0],"quantos")){                                       //|->Identifica o
                                                                                       //|  tipo de pergunta
            float pct=porcent_coment(nsent, sent, perg[i][3], perg[i][4], perg[i][1]); //|  e chama a funçao 
            printf("%.1f%%\n", pct*100);                                               //|  correspondente
                                                                                       //|
        }                                                                              //|
    }                                                                                  //|
    //___________________________________________________________________________________|
    
    free(BoW); //|->Libera a memoria alocada para o BoW
}

//-------------------------------------------------------------------------------------------------

float porcent_coment(int nsent, char ***sent, char *prod, char *marca, char *tipo){

    //Arrays com as palavras que caracterizam um comentario do tipo boa ou ruim
    const char bom[12][12]={"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    const char ruim[12][9]={"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    
    float num=0, tot=0; //Numero de comentarios do tipo desejado e numero total de comentarios para um determinado produto

    for(int i=0; i<nsent; i++){ //Itera pelas sentenças

        if(!strcmp(sent[i][0], prod) && !strcmp(sent[i][1], marca)){ //Checa se a sentença se refere ao produto desejado
            tot+=1;
            int fnd=0; //Variável que indica que o tipo da sentença foi identificado

            int j=0;
            while(strcmp(sent[i][j],END)){ //Checa todas as palavras até o caracter de fim de sentença

                if(!strcmp(tipo, "positivos")){ //Identifica se o tipo dos comentarios desejados é positivo

                    for(int k=0; k<12; k++){ //Itera pelo vetor das palavras que caracterizam o tipo de comentário

                        if(!strcmp(sent[i][j], bom[k])){ //Caso uma das palavras esteja presente o tipo daquele comentario é definido
                        
	                        if(!pol_invert(i, j, sent)){ //Identifica se não é um falso positivo

	                        	num+=1;
	                        	fnd=1; //Altera a flag que indica que o tipo do comentario foi definido
	                        	break;
	                    	}
                        }else if(!strcmp(sent[i][j], ruim[k])){ //Identifica se é um falso negativo

                        	if(pol_invert(i, j, sent)){
                        		num+=1;
                        		fnd=1;
                        		break;
                        	}
						}
                    }
				}else if(!strcmp(tipo, "negativos")){ //Mesma coisa para o outro tipo de comentário

                    for(int k=0; k<12; k++){

                        if(!strcmp(sent[i][j], ruim[k])){
	                        
	                        if(!pol_invert(i, j, sent)){ 

	                        	num+=1;
	                        	fnd=1; 
	                        	break;
	                    	}
                        
                        }else if(!strcmp(sent[i][j], bom[k])){ 

                        	if(pol_invert(i, j, sent)){
                        		
                        		num+=1;
                        		fnd=1;
                        		break;
                        	}
                        }
                    }
                }

                if(fnd){  //Se ja tiver encontrado uma das palavras que definem o tipo do comentario passa para o proximo pulando as demais palavras
                    break;
                }

                j++;
            }
        }
    }
    return (num/tot); //Retorna o numero de comentarios do tipo desejado sobre o total, para o produto desejado
}

//-------------------------------------------------------------------------------------------------

void free_mat(int n, int pal, char ***mat){

    for(int i=0; i<n; i++){

        for(int j=0; j<pal; j++){

            free(mat[i][j]); //Libera as posições ocupadas pelos elementos da terceira dimensão (letras)
        }
        
        free(mat[i]); //Libera as posições ocupadas pelos elementos da seguda dimensão (palavras)
    }
    free(mat); //Libera as posições ocupadas pelos elementos da primeira dimensão (frases)
}

//-------------------------------------------------------------------------------------------------

int pol_invert(int i, int j, char ***sent){
	
	const char neg[3][7]={"nao", "nunca", "jamais"};

	for(int k=j-1; k>=j-3; k--){ //Itera pelas tres palavras antes da palavra encontrada para checar por advérbios de negação
		
		for(int m=0; m<3; m++){
			
			if(!strcmp(sent[i][k], neg[m])){

				return 1; //Caso haja um adverbio de negação retorna 1
			}
		}
	}
	return 0; //Caso nao haja retorna 0
}

//------------------------------------------------------------------------------------------------

bow *do_bow(char ***sent, int nsent){
    
    bow *BoW;
    BoW=(bow*)malloc(nsent*sizeof(bow));
    
    int last_index_bow=0;//->Ultima posição ocupada da BoW

    
    //____________________________________
    for(int i=0; i<nsent; i++){         //|
                                        //|
        for(int j=0; j<MAXBOW; j++){    //|
            BoW[i].num_palavra[j]=0;    //|
            BoW[i].palavras[j][0]='\0'; //| 
        }                               //|->Itera pelo BoW recem criado 'limpando' as variáveis
        BoW[i].last_index=0;            //|  para impedir a interferência do lixo presente na posição
        BoW[i].prod[0]='\0';            //|  de memória
        BoW[i].marca[0]='\0';           //|
    }                                   //|
    //____________________________________|

    for(int i=0; i<nsent; i++){ //Itera pelos comentarios
        int ok_bow=0; //|->Flag que indica que o produto ja tem sua BoW
        
        for(int j=0; j<nsent; j++){ //Itera pelas BoW

            if(!strcmp(sent[i][0], BoW[j].prod) && !strcmp(sent[i][1], BoW[j].marca)){ //Checa se o produto ja tem uma BoW
                ok_bow=1; 
                int k=3;
           
                while(strcmp(sent[i][k],END)){ //Itera pelas palavras de um comentario ate o caracter de fim de comentario
                    int ok=0; //|->Flag que indica que a palavra ja esta na BoW do produto

                    for(int l=0; l<MAXBOW; l++){ //Itera pelas palavras presentes na BoW de um produto
           
                        if(!strcmp(sent[i][k],BoW[j].palavras[l])){ //Checa se cada palvra ja esta na BoW
                            BoW[j].num_palavra[l]++; //Incrementa numero de vezes que aquela palavra aparece
                            ok=1;
                        }
                    }
           
                    if(!ok){ //Se a palvra não estiver na BoW ela é adicionada
                        strcpy(BoW[j].palavras[BoW[j].last_index], sent[i][k]);
                        BoW[j].num_palavra[BoW[j].last_index]++;
                        BoW[j].last_index++;
                    }
                    k++;
                }
            }
           
        }
        if(!ok_bow){ //Se o produto não tiver uma BoW ela é criada
            strcpy(BoW[last_index_bow].prod, sent[i][0]);
            strcpy(BoW[last_index_bow].marca, sent[i][1]);
            last_index_bow++;
            i--;
        }
    }

    return BoW;
}

//-----------------------------------------------------------------------------------------------

int check_bow(bow *BoW, int nsent, char *prod, char *marca, char *palavra){
    
    for(int i=0; i<nsent; i++){
        
        if(!strcmp(BoW[i].prod, prod) && !strcmp(BoW[i].marca, marca)){
            
            for(int j=0; j<MAXBOW; j++){
                
                if(!strcmp(BoW[i].palavras[j], palavra)){
                    
                    return BoW[i].num_palavra[j];
                }
            }
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------------------