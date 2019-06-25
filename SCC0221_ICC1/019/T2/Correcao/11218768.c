#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Define a struct produto, para guardas as informacoes,
 * os comentarios e a bag of words de cada produto.
**/
typedef struct{
    char* nome;

    int bag[200];

    int num_comentarios;
    int* tam_comentario;
    char*** comentario;

    int negativos;
    int positivos;

}produto;

/**
 * Retorna uma variavel do tipo produto inicializada.
**/
produto novoProduto(char* nome, int num_words){
    produto p;

    p.nome = malloc((strlen(nome)+1)*sizeof(char));
    strcpy(p.nome, nome);

    memset(p.bag, 0, sizeof(p.bag));

    p.num_comentarios =  0;
    p.comentario = NULL;
    p.tam_comentario = NULL;

    p.negativos = 0;
    p.positivos = 0;

    return p;
}

/**
 * Retorna o ID do produto com nome "nome"
 * na lista de produtos, caso nao esteja 
 * presente na lista retorna -1.
**/
int getProdID(char* nome, int num_produtos, produto lista[num_produtos]){
    for(int i=0; i<num_produtos; i++){
        if(strcmp(nome, lista[i].nome) == 0){
            return i;
        }
    }

    return -1;
}

/**
 * Retorna o ID da palavra "word"
 * na lista de palavras, caso nao esteja 
 * presente na lista retorna -1.
**/
int getWordID(char* word, int num_words, char* lista[num_words]){
    for(int i=0; i<num_words; i++){
        if(strcmp(word, lista[i]) == 0){
            return i;
        }
    }

    return -1;
}

/**
 * Adiciona a palavra "word" ao comentario.
**/
void addWordToComment(char* word, int tam_comentario, char*** comentario){  
    (*comentario)[tam_comentario-1] = malloc((strlen(word) + 1)*sizeof(char));
    strcpy((*comentario)[tam_comentario-1], word);
}

/**
 * Retorna 1 se a palavra "word" pertencer a lista
 * fornecida e 0 caso contrário.
**/
int isInList(int tam, char lista[tam][20], char* word){
    for(int i=0; i<tam; i++){
        if(strcmp(lista[i], word) == 0) return 1;
    }

    return 0;
}


int main(){
    char positivas[12][20] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char negativas[12][20] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    char adverbios[3][20] = {"nao", "jamais", "nunca"};

    int num_setencas, num_perguntas;
    
    produto prodList[10];
    int num_produtos = 0;
    int prodID = 0;

    char* wordList[200];
    memset(wordList, 0, sizeof(wordList));
    int num_words = 0;
    int wordID = 0;

    scanf("%d %d", &num_setencas, &num_perguntas);


    for(int i=0; i<num_setencas; i++){
        char str[45];
        
        /**
         * Le o nome do produto, caso o mesmo nao esteja
         * na lista o inclui e inicializa.
        **/
        scanf("\n%[^;]s", str);

        str[strlen(str)-1] = '\0'; // remover o espaco no final do nome.

        prodID = getProdID(str, num_produtos, prodList);
        if(prodID == -1){
            num_produtos++;

            prodID = num_produtos - 1;

            prodList[prodID] = novoProduto(str, 0);
        }

    
        /**
         * Realoca memoria para incluir um novo comentario.
        **/
        prodList[prodID].num_comentarios++;  

        int commentID = prodList[prodID].num_comentarios - 1;

        prodList[prodID].comentario = realloc(prodList[prodID].comentario, prodList[prodID].num_comentarios*sizeof(char**));
        prodList[prodID].comentario[commentID] = malloc(20*sizeof(char*));
        prodList[prodID].tam_comentario = realloc(prodList[prodID].tam_comentario, prodList[prodID].num_comentarios*sizeof(int));
        prodList[prodID].tam_comentario[commentID] = 0;
        
        
        /**
         * Processa o comentario colocando uma palavra de cada vez
         * em str e atualizando a bag do produto da vez.
         * Caso a palavra ainda nao esteja na wordList, a adiciona.
        **/
        while(1){
            getchar();
            scanf("%s", str);

            if(strcmp(str, "Ø") == 0){
                break;
            }

            wordID = getWordID(str, num_words, wordList);
            
            if(wordID == -1){
                wordID = num_words;
                num_words++;
                
                wordList[num_words-1] = malloc((strlen(str)+1)*sizeof(char));
                strcpy(wordList[num_words-1], str);
            }

            prodList[prodID].bag[wordID]++;
        
            prodList[prodID].tam_comentario[commentID]++;
            addWordToComment(str, prodList[prodID].tam_comentario[commentID], &prodList[prodID].comentario[commentID]);
        }
        

        /**
         * Olha se o comentario e' negativo ou positivo.
         * (Considerei a soma da quantidade de adverbios
         * nas 3 palavras anteriores para o caso de outro 
         * adverbio poder inverter uma palavra que ja foi invertida)
        **/
        for(int j=0; j<prodList[prodID].tam_comentario[commentID]; j++){
            int inverte = 0;

            if(j>=1){
                if(isInList(3, adverbios, prodList[prodID].comentario[commentID][j-1])) inverte++;
            }
            if(j>=2){
                if(isInList(3, adverbios, prodList[prodID].comentario[commentID][j-2])) inverte++;
            }
            if(j>=3){
                if(isInList(3, adverbios, prodList[prodID].comentario[commentID][j-3])) inverte++;
            }

            inverte = inverte%2;

            if(isInList(12, negativas, prodList[prodID].comentario[commentID][j])){

                if(inverte == 1){
                    prodList[prodID].positivos++;
                }else{
                    prodList[prodID].negativos++;
                }

                break;

            }else if(isInList(12, positivas, prodList[prodID].comentario[commentID][j])){

                if(inverte == 1){
                    prodList[prodID].negativos++;
                }else{
                    prodList[prodID].positivos++;
                }

                break;
            }
        }
    }


    for(int i=0; i<num_perguntas; i++){
        /**
         * Separa a pergunta em palavras.
        **/
        char pergunta[5][20];
        for(int i=0; i<5; i++){
            scanf("%s", pergunta[i]);
        }

        /**
         * Define sobre qual produto e' a pergunta.
        **/
        char nome[45];
        memset(nome, 0, sizeof(nome));
        strcpy(nome, pergunta[3]);
        nome[strlen(pergunta[3])] = ' '; // substituindo '\0' por ' '.
        strcat(nome, pergunta[4]);

        prodID = getProdID(nome, num_produtos, prodList);

        /**
         * Olha qual tipo de pergunta foi feita e
         * responde com as informacoes salvas.
        **/
        if(strcmp(pergunta[0], "palavra") == 0){

            wordID = getWordID(pergunta[1], num_words, wordList);

            if(wordID == -1){
                printf("0\n");
            }else{
                printf("%d\n", prodList[prodID].bag[wordID]);
            }

        }else if(strcmp(pergunta[0], "quantos") == 0){

            float resp = 0.0;

            if(strcmp(pergunta[1], "negativos") == 0){
                resp = 100.0 * ((float)prodList[prodID].negativos/(float)prodList[prodID].num_comentarios);
            }else if(strcmp(pergunta[1], "positivos") == 0){
                resp = 100.0 * ((float)prodList[prodID].positivos/(float)prodList[prodID].num_comentarios);
            }

            printf("%.1f%%\n", resp);

        }

    }
    

    /**
     * Libera toda a memoria que foi locada dinamicamente.
    **/
    for(int i=0; i<num_words; i++){
        free(wordList[i]);
    }
    for(int i=0; i<num_produtos; i++){
       for(int j=0; j<prodList[i].num_comentarios; j++){
            for(int k=0; k<prodList[i].tam_comentario[j]; k++){
                free(prodList[i].comentario[j][k]);
            }
            free(prodList[i].comentario[j]);
        }
       free(prodList[i].comentario);
       free(prodList[i].nome);
       free(prodList[i].tam_comentario);
    }

    return 0;
}