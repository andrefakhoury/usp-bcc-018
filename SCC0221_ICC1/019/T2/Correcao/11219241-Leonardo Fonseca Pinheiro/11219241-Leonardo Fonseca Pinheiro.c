#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Função para leitura da string. Lê até o "enter" e retorna o endereço da string
char* lercoment(void){
    char* nome = malloc(800*sizeof(char));
    scanf(" %[^\n\r]", nome);
    return nome;
}
/*Função que acha o nome do produto digitado pelo usuário.
 * Recebe como parâmetro a string com o comentario inteiro
 * e retorna uma string com o nome do produto*/
char* nomeprod(char* com){
    char* prod = malloc(50 * sizeof(char));
    int aux = 1;
    /*While que procura o ";" na string, pois ele indica o fim do nome do 
produto e o começo do comentario*/
    while(1){  
        if(com[aux] == ';'){
            break;
        }
        else{
            aux++;
        }
    }
    strncat(prod, com, aux);
    return prod;
}
/*Função que acha o comentario feito pelo usuário.
 * Recebe como parâmetro a string digitada pelo usuário e o seu tamanho, assim 
como o tamanho do nome do produto.*/
void comentario(char* coment, int tamanho1, int tamanho2){
    int tamanho = tamanho2 - tamanho1;//para calcular o tamanho do comentario
    //faz com que a string recebida tenha apenas o comentario
    for(int i = 0; i<tamanho; i++){
        coment[i] = coment[i+tamanho1+2];
    }
    //O espaço é adicionado no final para função de separação de palavras
    coment[tamanho] = ' ';
    coment[tamanho+1] = '\0';
}
/*Função para separar cada palavra do comentario.
 * Recebe como parametros a string do comentario e um inteiro,
 * que indica qual palavra do comentario a função deve retornar.
 * Retorna uma string de uma palavra*/
char* seppalavra(char* coment, int aux){
    char* palavra = malloc(19 * sizeof(char));
    int x = 1;
    x -= aux;
    int a = 0;
    int b = 0;
    while(x<=0){
    //pula as palavras indesejadas
        if(x<0){
                while(coment[a] != ' '){
                    a++;
                }
                a++;
                x++;
        }
        //cria a string com a palavra desejada
        else{
            while(coment[a] != ' '){
            palavra[b] = coment[a];
            a++;
            b++;
            }
            x++;
        }
    }
    return palavra;
}
    
/*Função que acha o tamanho da string.
Recebe a string e retorna o seu tamanho*/
int tamanho(char* string){
    return strlen(string);
}
/*Função que conta quantas palavras o comentario possui.
 * Recebe a string e seu tamanho.
 * Retorna quantas palavras ele possui.*/
int contpalavras(char* string, int tamanho){
    int aux = 1;
    for(int i = 0; i<tamanho; i++){
        if(string[i] == ' '){
            aux++;
        }
    }
    return aux;
}
/*Função que analisa se a pergunta quer saber quantas palavras "x" tem em
 * algum produto ou se quer saber quantos comentarios positivos ou negativos 
algum produto tem.
Recebe a pergunta.
Retorna um inteiro que varia de acordo com o que a pergunta significa.*/
int analisaperg(char* perg){
    //retorna um se quer saber quantos positivos ou negativos
    if(perg[0] == 'q'){
        return 1;
    }
    //retorna 0 se quer saber quantas palavras
    if(perg[0] == 'p'){
    return 0;
    }
    return -2;
}
/* Função que pega apenas o produto e a palavra na pergunta de quantas palavras 
tem em algum produto.
Recebe a pergunta.
Retorna uma string com o nome do produto e a palavra.*/
char* perg1(char* perg){
    char* prodpalavra = malloc(100 * sizeof(char));
    int aux = 8;//para pular o "palavra "
    int pos = 0;
//While que pega toda a palavra, lendo a pergunta ate o "em"
    while(perg[aux] != 'e' || perg[aux+1] != 'm'){
        prodpalavra[pos] = perg[aux];
        aux++;
        pos++;
    }
    prodpalavra[pos-1] = ';';//coloca o ";" para reutilizar a funcao nomeprod
    aux+= 3;//pula o "em "
    //Le o nome do produto
    while(perg[aux] != '\0'){
        prodpalavra[pos] = perg[aux];
        aux++;
        pos++;
    }
    return prodpalavra;
}
/*Função que, no caso da pergunta ser quantos positivos ou negativos tem sobre 
algum produto, diferencia o caso positivo e o negativo
Recebe a pergunta.
Retorna um inteiro em cada caso*/
int positivonegativo(char* perg){
    //Posicao 8 para pular o "Quantos "
    if(perg[8] == 'p'){
        return 0;
    }
    if(perg[8] =='n'){
        return 1;
    }
    return -2;
}
/*Função usada quando deseja-se saber quantas opiniões positivas ou negativas 
tem sobre algum produto.
Recebe como parâmetro a pergunta inteira.
Retorna uma string com o nome do produto em questão */
char* perg2(char* perg){
    char* produto = malloc(100* sizeof(char));
    int aux = 21;//Posição 21 para pegar o começo do nome do produto
    int a = 0;
    while(perg[aux] != '\0'){
        produto[a] = perg[aux];
        aux++;
        a++;
    }
    produto[a] = ' ';
    return produto;
}
/*Função para verificar se o comentario tem sentido positivo ou negativo.
Recebe o comentario e quantas palavras têm nele.
Retorna 1 se a palavra tiver sentido positivo, -1 se tiver sentido negativo e 
0 se tiver sentido neutro.*/
int pn(char* comentario, int palavras){
    char** palavra = malloc(20* sizeof(char*));
    int d = 1;
    char* string1 = malloc(4 * sizeof(char));
    string1 = "bom";
    char* string2 = malloc(12 * sizeof(char));
    string2 = "maravilhoso";
    char* string3 = malloc(6 * sizeof(char));
    string3 = "otimo";
    char* string4 = malloc(12 * sizeof(char));
    string4 = "sensacional";
    char* string5 = malloc(10 * sizeof(char));
    string5 = "excelente";
    char* string6 = malloc(7 * sizeof(char));
    string6 = "adorei";
    char* string7 = malloc(7 * sizeof(char));
    string7 = "gostei";
    char* string8 = malloc(5 * sizeof(char));
    string8 = "amei";
    char* string9 = malloc(10 * sizeof(char));
    string9 = "eficiente";
    char* string10 = malloc(4 * sizeof(char));
    string10 = "boa";
    char* string11 = malloc(12 * sizeof(char));
    string11 = "maravilhosa";
    char* string12 = malloc(6 * sizeof(char));
    string12 = "otima";
     char* string13 = malloc(5 * sizeof(char));
    string13 = "ruim";
    char* string14 = malloc(9 * sizeof(char));
    string14 = "detestei";
    char* string15 = malloc(6 * sizeof(char));
    string15 = "odiei";
    char* string16 = malloc(8 * sizeof(char));
    string16 = "pessimo";
    char* string17 = malloc(9 * sizeof(char));
    string17 = "terrivel";
    char* string18 = malloc(6 * sizeof(char));
    string18 = "raiva";
    char* string19 = malloc(6 * sizeof(char));
    string19 = "lento";
    char* string20 = malloc(5 * sizeof(char));
    string20 = "odio";
    char* string21 = malloc(7 * sizeof(char));
    string21 = "fragil";
    char* string22 = malloc(6 * sizeof(char));
    string22 = "lenta";
    char* string23 = malloc(8 * sizeof(char));
    string23 = "desisti";
     char* string24 = malloc(8 * sizeof(char));
    string24 = "pessima";
    char* string25 = malloc(4*sizeof(char));
    string25 = "nao";
    char* string26 = malloc(7*sizeof(char)); 
    string26 = "jamais";
    char* string27 = malloc(6*sizeof(char));
    string27 = "nunca";
    //cria um vetor com as palavras do comentario
    for(int i = 0; i<palavras; i++){
            palavra[i] = seppalavra(comentario, d);
            d++;
    }
    for(int i = 0; i<palavras;i++){
    if(strcmp(palavra[i], string1) == 0 || strcmp(palavra[i], string2) == 0 || 
    strcmp(palavra[i], string3) == 0 || strcmp(palavra[i], string4) == 0 || 
    strcmp(palavra[i], string5) == 0 || strcmp(palavra[i], string6) == 0 || 
    strcmp(palavra[i], string7) == 0 || strcmp(palavra[i], string8) == 0 || 
    strcmp(palavra[i], string9) == 0 || strcmp(palavra[i], string10) == 0 || 
    strcmp(palavra[i], string11) == 0 || strcmp(palavra[i], string12) == 0){
        //verifica se tem alguma palavra de negação em relacao à palavra
       for(int j = i-3; j<i;j++){
           if(j>=0){
                if(strcmp(palavra[j], string25) == 0 || 
                strcmp(palavra[j],string26) == 0 || strcmp(palavra[j], 
                string27) == 0){
                    return -1;
                }
           }
       }
                    return 1;
       }
    }
    for(int i = 0; i<palavras; i++){
    if(strcmp(palavra[i], string13) == 0 || strcmp(palavra[i], string14) == 0 
    || strcmp(palavra[i], string15) == 0 || strcmp(palavra[i], string16) == 0 
    || strcmp(palavra[i], string17) == 0 || strcmp(palavra[i], string18) == 0 
    || strcmp(palavra[i], string19) == 0 || strcmp(palavra[i], string20) == 0 
    || strcmp(palavra[i], string21) == 0 || strcmp(palavra[i], string22) == 0 
    || strcmp(palavra[i], string23) == 0 || strcmp(palavra[i], string24) == 0){
        for(int j = i-3; j<i;j++){
           if(j>=0){
                if(strcmp(palavra[j], string25) == 0 || 
                strcmp(palavra[j],string26) == 0 || strcmp(palavra[j], 
                string27) == 0){
                    return 1;
                }
           }
        }
                    return -1;
       }
    }
        return 0;
}
/*Função que descobre o nome do produto em questão.
 * Recebe palavra ; produto.
 * Retorna Produto .*/
char* palaperg(char* perg){
    char* palavra = malloc(100*sizeof(char));
    int aux = 0;
    int a = 0;
    //Avança até o ;
    while(perg[aux] != ';'){
    aux++;
    }
    aux++;//Pula o ;
    while(perg[aux] != '\0'){
        palavra[a] = perg[aux];
        aux++;
        a++;
    }
    //Coloca um espaço porque os produtos no BOW têm um espaço depois do nome,
    //então o espaço é necessário para comparação.
    palavra[a] = ' ';
    return palavra;
}
int main(void){
    int a, b;//Número de comentarios e de perguntas, respectivamente
    scanf("%d %d", &a, &b);
    char* bow[400];//Vetor que armazena cada palavra dos comentários
    char* produtos[30];//Vetor que armazena o nome dos produtos
    //Matriz que guarda quantas vezes a palavra foi usada em um produto:
    int contagem[30][400];//A linha é referente ao produto e a coluna à palavra
    char* coment = malloc(400 * sizeof(char));//String que recebe o comentario
    int tamanhos[30][2];//Guarda os tamanhos dos produtos e dos comentários
    int palavras = 0;//Conta o número de palavras diferentes encontradas
    int c = 1;//Quantidade atual de palavras no BOW +1
    int d = 1;//Em qual palavra do comentário a busca se encontra
    int e = 0;//Utilizado na comparação entre a provisória e as palavras do BOW
    char* pergunta = malloc(100 * sizeof(char));//String que recebe a pergunta
    //Guarda uma palavra para compará-la às outras ja armazenadas no BOW
    char* provisoria = malloc(19 * sizeof(char));
    int tipo;//Referente ao tipo de pergunta
    char* palavraperg;//Palavra buscada pela pergunta
    float qtd = 0;//Quantas vezes o evento desejado pela pergunta ocorre
    float total = 0;//Vezes que o produto desejado pela pergunta é citado
    float res;//Resposta para pergunta do positivo/negativo.
    int poun[30]; //Vetor que fala se o comentario é positivo ou negativo
    int p;//Variável para passar o numero de palavras de um comentario à função
    for(int i = 0; i<=400; i++){
        bow[i] = calloc(1,  sizeof(char*));
    }
    for(int i = 0; i<=30; i++){
        produtos[i] = calloc(1,  sizeof(char*));
    }
    for(int i = 0; i<a; i++){
        coment = lercoment();
        //Armazena o tamanho do comentário inteiro
        //como seu uso é temporário, usa-se a posição 0,0 várias vezes
        tamanhos[0][0] = tamanho(coment);
        produtos[i+1] = nomeprod(coment);
        tamanhos[i+1][0] = tamanho(produtos[i+1]);
        comentario(coment, tamanhos[i+1][0], tamanhos[0][0]);
        tamanhos[i+1][1] = tamanho(coment) - 1;
        p = -palavras;
        palavras += contpalavras(coment, tamanhos[i+1][1]);
        p += palavras;//Número de palavras naquele comentario
        poun[i+1] = pn(coment, p);
        for(int j = c; j<palavras; j++){
                provisoria = seppalavra(coment, d);
                while(e<c){//Compara com todas as palavras ja armazenadas
                    if(strcmp(bow[e], provisoria)==0){
                        contagem[i+1][e] = contagem[i+1][e] + 1;
                        palavras--;
                        e = 0;
                        d++;
                        j--;
                        break;
                    }
                    else{
                        e++;
                    }
                }
                if(e == c){
                    strcat(bow[j],provisoria);
                    contagem[i+1][j] = 1;
                    e = 0;
                    d++;
                    c++;
                }
        }
        d = 1;
    }
    for(int i = 0; i<b; i++){
        pergunta = lercoment();
        tipo = analisaperg(pergunta);
        if(tipo == 0){
            pergunta = perg1(pergunta);
            palavraperg = nomeprod(pergunta);
            pergunta = palaperg(pergunta);
            for(int j = 0; j<=a; j++){
                //Acha a linha equivalente ao produto
                if(strcmp(produtos[j], pergunta)==0){
                    for(int k = 0; k<=palavras;k++){
                        //Acha a coluna equivalente à palavra
                        if(strcmp(bow[k], palavraperg) == 0){
                            qtd += contagem[j][k];
                        }
                    }
                }
            }
            printf("%.0f\n", qtd);
            qtd = 0;
        }
        else{
            tipo = positivonegativo(pergunta);
            pergunta = perg2(pergunta);
            for(int j = 1; j<=a; j++){
                //Acha a linha do produto
                if(strcmp(produtos[j], pergunta) == 0){
                    total++;
                    if(tipo == 0){
                        if(poun[j] == 1){
                            qtd++;
                        }
                    }
                    if(tipo == 1){
                        if(poun[j] == -1){
                            qtd++;
                        }
                    }
                }
            }
            if(total == 0){
                printf("0\n");
            }
            else{
                res = (qtd * 100)/total;
                printf("%.1f%%\n", res);
            }
        }
        qtd = 0;
        total = 0;
    }
    free(coment);
    free(pergunta);
    free(provisoria);
    for(int i = 0; i<=400; i++){
        free(bow[i]);
    }
    for(int i = 0; i<30; i++){
        free(produtos[i]);
    }
    return 0;
    }
