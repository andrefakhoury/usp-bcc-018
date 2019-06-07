

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 
char *name (char *comment){
    char *product;
    int num = 40; //tamanho máximo de caracteres de um produto
    product = (char *)calloc(num, sizeof(char));
    int a = 0;
    while(comment[a] != ';'){
        product[a] = comment[a];
        a++;
    }
    return product;
}
 
 
char *aval(char *comment, char *product){
    int num = strlen(product);
    char *evaluation = (char *)calloc(381, sizeof(char));
    int a = 0;
    num += 2;
    while(comment[num] != '\0'){
        evaluation[a] = comment[num];
        num++;
        a = a +1;
    }
    return evaluation;
}
 
 
float qualidade(char *pergunta, char **p, int n_comments, char **c){
    char **perg, *prod, *aux1, *aux4, *aux3, *compquali, *palavra;  
    int i, j = 0, k, l, count = 0, compara, compara2, n_palavras = 0;
   
    //alocando memória
    perg = (char**)calloc(6, sizeof(char*));
    for(i = 0; i < 6; i++){
        perg[i] = (char *)calloc(20, sizeof(char));
    }
    prod = (char *)calloc(41, sizeof(char));
    aux1 = (char *)calloc(20, sizeof(char));
    aux3 = (char *)calloc(20, sizeof(char));
    aux4 = (char *)calloc(20, sizeof(char));
    compquali = (char *)calloc(41, sizeof(char));
    palavra = (char *)calloc(20, sizeof(char));
   
    //separando as palavras da pergunta
    for(i = 0; i < 5; i++){
        if(i == 0){
            j = 0;
        }
        k = 0;
        while(pergunta[j] != ' '){
            perg[i][k] = pergunta[j];
            j++;
            k++;
        }
        j++;
    }
   
    //para determinar se o que se pede são os comentários positivos ou os negativos
    for(i = 0; i < strlen(perg[1]); i++){
        aux1[i] = perg[1][i];
    }
    //para descobrir o produto relativo a pergunta
    for(i = 0; i < strlen(perg[3]); i++){
        aux3[i] = perg[3][i];
    }
    for(i = 0; i < strlen(perg[4]); i++){
        aux4[i] = perg[4][i];
    }
    strcat(aux3, " ");
    strcat(aux3, aux4);
    strcat(aux3, " ");
    prod = aux3;
   
    for(i = 0; i < n_comments; i++){
        for(j = 0; j < 41; j++){
            *(compquali+j) = p[i][j];
        }
        j = 0;
        compara = strcmp(compquali, prod); //compara o produto pedido com o do comentário
        if(compara == 0){
            for(l = 0; l < strlen(c[i]); l++){ //conta o número de palavras do comentário
                if(c[i][l] == ' '){
                    n_palavras++;
                }
            }
            for(l = 0; l < n_palavras + 1; l++){
                k = 0;
                while(c[i][j] != ' '){
                    palavra[k] = c[i][j];   //varedura das palavras na posicao do produto
                    j++;
                    k++;
                }
                j++;
                k = 0;
                compara2 = strcmp(palavra, aux1);
                if(compara2 == 0){
                    count++;  //caso identificada a palavra pedida, há a contagem
                }
                memset(palavra,' ', strlen(palavra));
                memset(palavra,'\0', strlen(palavra));
            }
            n_palavras = 0;
        }
    }
 
    //libera memória
    free(perg);
    free(compquali);
    
    return count;
}
 
 
float quantos(char *pergunta, char **p, int n_comments, char **c){
    char **perg, *prod, *aux1, *aux3, *aux4, *palavra, *comando, *compprod;
    char *palavras_boas[12] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
    char *palavras_ruins[13] = {"detestei", "odiei", "nojo", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
    int i, j, k, l, x, compara, comppos, compneg, posouneg, n_palavras = 0;
    float resp, positivo = 0, negativo = 0;
   
    //alocação de memória
    perg = (char **)calloc(6, sizeof(char*));
    for(i = 0; i < 6; i++){  
        perg[i] = (char *)calloc(20, sizeof(char));
    }
    comando = (char *)calloc(10, sizeof(char));
    prod = (char *)calloc(41, sizeof(char));
    aux1 = (char *)calloc(20, sizeof(char));
    aux3 = (char *)calloc(20, sizeof(char));
    aux4 = (char *)calloc(20, sizeof(char));
    compprod = (char *)calloc(41, sizeof(char));
    palavra = (char *)calloc(20, sizeof(char));
   
   
    //separando as palavras da pergunta
    for(i = 0; i < 5; i++){
        if(i == 0){
            j = 0;
        }
        k = 0;
        while(pergunta[j] != ' '){
            perg[i][k] = pergunta[j];
            j++;
            k++;
        }
        j++;
    }
    //para determinar se o que se pede são os comentários positivos ou os negativos
    for(i = 0; i < strlen(perg[1]); i++){
        aux1[i] = perg[1][i];
    }
    //para descobrir o produto relativo a pergunta
    for(i = 0; i < strlen(perg[3]); i++){
        aux3[i] = perg[3][i];
    }
    for(i = 0; i < strlen(perg[4]); i++){
        aux4[i] = perg[4][i];
    }
   
    //ver qual é o produto
    aux3 = perg[3];
    aux4 = perg[4];
    strcat(aux3, " ");
    strcat(aux3, aux4);
    prod = strcat(aux3, " ");
   
    for(i = 0; i < n_comments; i++){
        for(j = 0; j < 41; j++){
            *(compprod+j) = p[i][j];
        }
       
        j = 0;
        compara = strcmp(compprod, prod);  //compara o produto dos comentários com o produto pedido
        memset(palavra,' ', strlen(compprod));
        memset(palavra,'\0', strlen(compprod));
        memset(palavra,' ', strlen(prod));
        memset(palavra,'\0', strlen(prod));
       
        if(compara == 0){
            for(l = 0; l < strlen(c[i]); l++){ //conta o número de palavras do comentário
                if(c[i][l] == ' '){
                    n_palavras++;
                }
            }
            for(l = 0; l < n_palavras+1; l++){  
                k = 0;
                while(c[i][j] != ' '){
                    palavra[k] = c[i][j];   //varedura das palavras na posicao do produto
                    j++;
                    k++;
                }
                j++;
                k = 0;
                for(x = 0; x < 12; x++){
                    comppos = strcmp(palavra, palavras_boas[x]); //caso veja uma palavra positiva
                    if(comppos == 0){
                        break;
                    }    
                }
                for(x = 0; x < 13; x++){
                    compneg = strcmp(palavra, palavras_ruins[x]);  //caso veja uma palavra negativa
                    if(compneg == 0){
                        break;
                    }    
                }
                memset(palavra,' ', strlen(palavra));
                memset(palavra,'\0', strlen(palavra));
                if(comppos == 0){
                    positivo++;
                    break;
                }
                if(compneg == 0){
                    negativo++;
                    break;
                }
            }
            n_palavras = 0;
        }
    }
 
    //verificando se pede as avaliações positivas ou negativas
    comando = perg[1];
    posouneg = strcmp(comando, "negativos");
    if(posouneg == 0){
        resp =(100 * negativo)/(negativo+positivo);
    }
    else if(posouneg != 0){
        resp = (100 * positivo)/(negativo+positivo);
    }
 
    //desalocando memória
    free(perg);
    free(comando);
    free(compprod);
    free(palavra);
 
    return resp;
}
 
int main (void){
    int n_comments, n_questions, i, j, t_produto = 40, t_comentario = 380, t_perg = 101, t_max = 400, comp;
    char *comment, *question, *product, *evaluation, **p, **c, **q,  *enunciados;
    float resposta;
 
    scanf("%d %d", &n_comments, &n_questions);
 
    //alocação de memória
    comment = (char *)calloc(t_max + 1, sizeof(char));
    product = (char *)calloc(t_produto, sizeof(char));
    p = (char **)calloc(n_comments, sizeof(char*));
    for(i = 0; i < n_comments; i++){
        p[i] = (char *)calloc(t_produto + 1, sizeof(char));
    }
    c = (char **)calloc(n_comments, sizeof(char*));
    for(i = 0; i < n_comments; i++){
        c[i] = (char *)calloc(t_comentario + 1, sizeof(char));
    }
    evaluation = (char *)calloc(t_comentario, sizeof(char));
    question = (char *)calloc(t_max, sizeof(char));
    q = (char **)calloc(n_questions, sizeof(char*));
    for(i = 0; i < n_questions; i++){
        q[i] = (char *)calloc(t_perg, sizeof(char));
    }
    enunciados = (char *)calloc(20, sizeof(char));
   
    //leitura dos comentarios
    for(i = 0; i < n_comments; i++){
        scanf(" %[^\n]", comment);
        product = name(comment); //separa o nome do produto
        for(j = 0; j < strlen(product); j++){
            p[i][j] = *(product+j); //produto vai para a vetor p
        }
        evaluation = aval(comment, product); //separa o comentario sobre o produto
        for(j = 0; j < strlen(evaluation); j++){
            c[i][j] = *(evaluation+j); //comentario vai para a vetor c  
        }
    }
 
    //leitura das perguntas
    for(i = 0; i < n_questions; i++){
        scanf(" %[^\n]", question);
        for(j = 0; j < strlen(question); j++){
            q[i][j] = *(question+j);
        }
        memset(question,' ', strlen(question));
        memset(question,'\0', strlen(question));
    }
 
    //gerar resposta
    for(i = 0; i < n_questions; i++){
        j = 0;
        while(q[i][j] != ' '){
            enunciados[j] = q[i][j];
            j++;
        }   //separar palavras da pergunta : reconhecer qual é a pergunta e qual é o produto
        comp = strcmp(enunciados, "palavra");
        if(comp == 0){
            resposta = qualidade(q[i], p, n_comments, c); //função para quando a pergunta é relacionada a uma determinada palavra
            printf("%.f\n", resposta);
        }
        else{
            resposta = quantos(q[i], p, n_comments, c);  //função para quando a pergunta é relacionada às avaliações do produto
            printf("%.1f%%\n", resposta);
        }
    }
 
    //liberando memória
    // free(comment);
    // free(product);
    // free(*p);
    // free(*c);
    // free(evaluation);
    // free(question);
    // free(*q);
    // free(enunciados);
   
    return 0;
}

//o programa está rodando perfeitamente no meu compilador no caso 1 e no caso 2. Já no 4, 5, 6 e 7, elee daria a resposta certa mas está dando um erro (corrupted size vs. prev_size ; Aborted (core dumped)) a partir de determinado momento. Nos casos 4 e 5 ele roda até a 3ª pergunts corretamanete. No caso 6 e no 7 ele roda a primeira pergunta perfeitamente e depois para.

